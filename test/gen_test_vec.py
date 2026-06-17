import os
import sys
import re
import yaml
from yaml.loader import SafeLoader
from gen_test import *

# reuse the OP-V opcode/operand logic of the header generator instead of
# duplicating it, so this test follows gen_v.py automatically.
sys.path.insert(0, os.path.join(os.path.dirname(os.path.abspath(__file__)), '..', 'gen'))
import gen_v

# Generate tests for OP-V (vector arithmetic) instructions directly from
# gen/rvv_instr_dict.yaml so that newly added instructions (e.g. vfwmaccbf16)
# are covered automatically.

YAML_PATH = '../gen/rvv_instr_dict.yaml'

# scalar register operands are FReg for floating point minor opcodes (gen_v.py:67-69)
FREG_MINORS = ('OPFVV', 'OPFVF')

# sample register/immediate tokens (identical strings are valid for both xbyak and gas)
VREG = {'vs1': 'v2', 'vs2': 'v3', 'vs3': 'v4'}

# Mandatory-mask instructions (vadc/vsbc/vmerge/vfmerge and the carry/borrow
# producing forms). They always operate on the v0 mask: the xbyak signature has
# no VM parameter (vm bit is hard-coded to 0) while the gas mnemonic requires an
# explicit trailing `v0` operand. Detected by these name suffixes.
MASK0_SUFFIX = ('_vvm', '_vxm', '_vim', '_vfm')

# Instructions that still cannot be generated in this simple form and are
# skipped. Finalized by running the generated gas output through the assembler.
SKIP = set()


def scalar_token(minor, name):
    return 'f2' if minor in FREG_MINORS else 'x5'


def build_args(name, fields, minor):
    args = list(fields)
    out = []

    # destination register
    if 'vd' in args:
        out.append('v1')
    elif 'rd' in args:
        out.append(scalar_token(minor, name))
    elif 'vs3' in args:
        out.append(VREG['vs3'])
        args.remove('vs3')

    # source registers, ordered the same way gen_v.py orders the C++ signature
    args = gen_v.sort_operands_for_signature(name, args, gen_v.OPV_MAJOR)
    for p in args:
        if re.match(r'vs[\d]', p):
            out.append(VREG[p])
        elif re.match(r'rs[\d]', p):
            out.append(scalar_token(minor, name))

    # immediate
    if 'simm5' in args:
        out.append('5')

    # vm omitted -> unmasked (default)
    return ', '.join(out)


def vec():
    with open(YAML_PATH) as f:
        rvv = yaml.load(f, Loader=SafeLoader)
    for name, spec in rvv.items():
        if name in SKIP:
            continue
        encoding = spec['encoding']
        if gen_v.extract_opcode(encoding) != gen_v.OPV_MAJOR:
            continue  # only vector arithmetic (OP-V) instructions
        minor = gen_v.FUNC3_TO_OPV_MINOR[gen_v.extract_func3(encoding)]
        if minor == 'OPCFC':
            continue  # vector configuration instructions
        args = build_args(name, spec['variable_fields'], minor)
        if name.endswith(MASK0_SUFFIX):
            # gas requires the implicit v0 mask as an explicit operand
            asm = name.strip('_').replace('_', '.')
            putEach(f'{name}({args})', f'{asm} {args}, v0')
        else:
            put(name, args)


# Vector Configuration Instructions (OPCFC) are emitted by hand in gen/gen_v.py
# instead of from the YAML table, so the vec() loop above skips them. Generate
# their tests explicitly here.
SEW_TBL = ['e8', 'e16', 'e32', 'e64']
LMUL_TBL = ['mf8', 'mf4', 'mf2', 'm1', 'm2', 'm4', 'm8']
VTA_TBL = ['tu', 'ta']
VMA_TBL = ['mu', 'ma']


def vtype(sew, lmul, vta, vma):
    if getXbyak():
        return f'SEW::{sew}, LMUL::{lmul}, VTA::{vta}, VMA::{vma}'
    return f'{sew}, {lmul}, {vta}, {vma}'


def vset():
    for sew in SEW_TBL:
        for lmul in LMUL_TBL:
            for vta in VTA_TBL:
                for vma in VMA_TBL:
                    vt = vtype(sew, lmul, vta, vma)
                    gas = f'{sew}, {lmul}, {vta}, {vma}'
                    putEach(f'vsetvli(x5, x6, {vt})', f'vsetvli x5, x6, {gas}')
                    putEach(f'vsetivli(x5, 4, {vt})', f'vsetivli x5, 4, {gas}')
    putEach('vsetvl(x5, x6, x7)', 'vsetvl x5, x6, x7')


# Vector load/store instructions (LOAD-FP/STORE-FP major opcode) are skipped by
# the vec() loop above, so generate their tests here. The gas operand order is
# the same as the C++ signature; the only difference is that the base address
# register rs1 is written `(x5)` in gas. One test per instruction (unmasked).
HEADER_PATH = os.path.join(os.path.dirname(os.path.abspath(__file__)),
                           '..', 'xbyak_riscv', 'xbyak_riscv_v.hpp')
SIG_RE = re.compile(r'^void ([a-z][a-z0-9_]*)\(([^)]*)\)')

_sigs = None


def header_sigs():
    '''Parse `void NAME(PARAMS) {` lines into {name: [param_var, ...]}.'''
    global _sigs
    if _sigs is None:
        _sigs = {}
        with open(HEADER_PATH) as f:
            for line in f:
                m = SIG_RE.match(line)
                if not m:
                    continue
                name, params = m.group(1), m.group(2)
                variables = []
                for p in params.split(','):
                    p = p.strip()
                    if p:
                        # the variable name is the last token, sans '&'/default
                        variables.append(p.split('=')[0].split()[-1].lstrip('&'))
                _sigs[name] = variables
    return _sigs


def header_names(pattern):
    rx = re.compile(pattern)
    return sorted(n for n in header_sigs() if rx.fullmatch(n))


def ldst_operand(var):
    # returns (xbyak_token, gas_token), or None to drop the operand (vm)
    if var in ('vd', 'vs3'):
        return ('v1', 'v1')
    if var == 'rs1':
        return ('x5', '(x5)')  # base address: parenthesized in gas
    if var == 'rs2':
        return ('x6', 'x6')    # stride
    if var == 'vs2':
        return ('v3', 'v3')    # index vector
    return None  # vm -> omit (unmasked default)


def ldst(names):
    sigs = header_sigs()
    for name in names:
        xs, gs = [], []
        for var in sigs[name]:
            t = ldst_operand(var)
            if t is not None:
                xs.append(t[0])
                gs.append(t[1])
        asm = name.strip('_').replace('_', '.')
        putEach(f'{name}({", ".join(xs)})', f'{asm} {", ".join(gs)}')


# Only EEW 8/16/32/64 are testable: the header also defines eew 128..1024 forms
# but those are outside the ratified V spec and the GNU assembler rejects them,
# so there is no reference encoding to diff against.
EEW = r'(8|16|32|64)'


def ldst_unit():
    # unit-stride load/store (+fault-only-first) and mask load/store
    ldst(header_names(r'v(le%s(ff)?|se%s|lm|sm)_v' % (EEW, EEW)))


def ldst_strided():
    # strided load/store: vd/vs3, (rs1), rs2
    ldst(header_names(r'v(lse%s|sse%s)_v' % (EEW, EEW)))


def ldst_indexed():
    # indexed (ordered/unordered) load/store: vd/vs3, (rs1), vs2
    ldst(header_names(r'v(lox|lux|sox|sux)ei%s_v' % EEW))


def ldst_whole():
    # whole-register load/store (no mask): vl<nf>re<eew>.v / vs<nf>r.v vd/vs3, (rs1)
    ldst(header_names(r'(vl(1|2|4|8)re%s_v|vs(1|2|4|8)r_v)' % EEW))


# Segment instructions: nf=1 is the same encoding as the non-segment form
# (vlseg1e8 == vle8) and the GNU assembler has no nf=1 mnemonic, so test nf=2..8.
SEG_NF = r'[2-8]'


def ldst_seg_unit():
    # segment unit-stride load/store (+fault-only-first): vd/vs3, (rs1)
    ldst(header_names(r'v(lseg|sseg)%se%s(ff)?_v' % (SEG_NF, EEW)))


def main():
    setModeFromArgv()
    vec()
    vset()
    ldst_unit()
    ldst_strided()
    ldst_indexed()
    ldst_whole()
    ldst_seg_unit()


if __name__ == '__main__':
    main()
