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


def main():
    setModeFromArgv()
    vec()
    vset()


if __name__ == '__main__':
    main()
