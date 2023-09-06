################################################################################
# Copyright (C), 2023, KNS Group LLC (YADRO)
#
# Licensed under the 3-Clause BSD License
# You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
################################################################################

import yaml
from yaml.loader import SafeLoader
from typing import List
from collections import defaultdict
from copy import deepcopy
import re
import copyright

# LOAD-FP major opcode for Vector Load Instructions
LOAD_FP_MAJOR = '0000111'
# STORE-FP major opcode for Vector Store Instructions
STORE_FP_MAJOR = '0100111'

# OP-V major opcode for Vector Arithmetic Instructions
OPV_MAJOR = '1010111'
FUNC3_TO_OPV_MINOR = {
    # vector arithmetic instructions
    '000': 'OPIVV',
    '001': 'OPFVV',
    '010': 'OPMVV',
    '011': 'OPIVI',
    '100': 'OPIVX',
    '101': 'OPFVF',
    '110': 'OPMVX',
    # vector configuration instructions
    '111': 'OPCFC'
}


def extract_opcode(instr_encoding: str) -> str:
    '''
        Extract major opcode from encoding string,
        i.e. `0100111` from `000000101000-----000-----0100111`
    '''
    return instr_encoding[-7:]


def extract_func3(instr_encoding: str) -> str:
    '''
        Extract func3 from encoding string with OP-V major opcode,
        i.e. `110` from `110111-----------110-----1010111`
    '''
    if extract_opcode(instr_encoding) != OPV_MAJOR:
        raise ValueError(f'Trying to extract func3 but encoding is not of \
                           OP-V major opcode:\n {instr_encoding}')
    return instr_encoding[-15:-12]


def generate_instruction_signature(instr_name: str,
                                   instr_args: List[str],
                                   minor_opcode: str,
                                   major_opcode: str,
) -> str:
    '''
        Generates signature for the C++ function of the instruction
        depending on the its arguments.
    '''
    __instr_args = deepcopy(instr_args)
    # a helper dict to properly encode scalar registers for different opcodes
    opcode_to_scalar_reg_type = defaultdict(lambda: 'Reg')
    opcode_to_scalar_reg_type['OPFVV'] = 'FReg'
    opcode_to_scalar_reg_type['OPFVF'] = 'FReg'

    if minor_opcode is not None:
        minor_opcode = minor_opcode.upper()

    signature_args = []
    # add destination register, if it is in the instruction's arguments
    if 'vd' in __instr_args:
        signature_args.append('VReg vd')
    elif 'rd' in __instr_args:
        reg_type = opcode_to_scalar_reg_type[minor_opcode]
        signature_args.append(f'{reg_type} rd')
    elif 'vs3' in __instr_args:
        # vectore store instructions have a vs3 operand instead of vd/rd
        signature_args.append('VReg vs3')
        __instr_args.remove('vs3')


    # add all source registers from the instruction's arguments
    def has_reverse_operands_order(instr_name: str, major_opcode: str):
        if major_opcode == OPV_MAJOR:
            opv_instrs_with_reversed_order = [
                'vmacc', 'vnmsac', 'vmadd', 'vnmsub', 'vwmacc', 'vwmaccu',
                'vwmaccsu', 'vwmaccus', 'vfmacc', 'vfnmacc', 'vfmsac', 'vfnmsac',
                'vfmadd', 'vfnmadd', 'vfmsub', 'vfnmsub', 'vfwmacc', 'vfwnmacc',
                'vfwmsac', 'vfwnmsac'
            ]

            return any([instr_name.startswith(n) for n in opv_instrs_with_reversed_order])
        else:
            # all vectore load/store instructions have reversed source operands order
            # e.g. `vluxei8.v vd, (rs1), vs2`
            return True

    regular_order = not has_reverse_operands_order(instr_name, major_opcode)
    __instr_args.sort(key=lambda arg: re.sub('[^0-9]', '', arg), reverse=regular_order)
    def is_vector_source_register(r): return bool(re.match(r'vs[\d]', r))
    def is_scalar_source_register(r): return bool(re.match(r'rs[\d]', r))
    for p in __instr_args:
        if is_vector_source_register(p):
            signature_args.append(f'VReg {p}')
        elif is_scalar_source_register(p):
            reg_type = opcode_to_scalar_reg_type[minor_opcode]
            signature_args.append(f'{reg_type} {p}')

    # add immediate value, if it is in the instruction's arguments
    if 'simm5' in __instr_args:
        signature_args.append('int32_t simm5')

    # add vector mask, if it is in the instruction's arguments
    if 'vm' in __instr_args:
        signature_args.append('VM vm=VM::unmasked')

    signature_args_joined = ', '.join(signature_args)
    return f'{instr_name}({signature_args_joined})'


def generate_emitter_call(instr_encoding: str,
                          instr_args: List[str],
                          emitter_name: str,
                          emitter_args: List[str]
) -> str:
    '''
        Produce a call to an underlying C++ emitter from
        the `CodeGenerator` class defined in xbyak_riscv.hpp
    '''
    def is_dest_register(r): return bool(re.match('.*d.*', r))
    def has_dest_register(args): return any(is_dest_register(arg) for arg in args)

    # if an argument of a C++ emitter is missing in instr_args,
    # use the 'ENCODED' value instead of it
    __emitter_args = deepcopy(emitter_args)
    for i, arg in enumerate(__emitter_args):
        if is_dest_register(arg):
            # handle destination register separately since it is vd/rd
            # in OPFVV, OPMVV OPMVX opcodes
            if not has_dest_register(instr_args):
                # destination register is not in instruction arguments and had been encoded
                # in the `encoding` string of the instruction specification
                __emitter_args[i] = 'ENCODED'
            else:
                __emitter_args[i] = instr_args[-1]
        else:
            if '_' in arg:
                # handle argument variants like lumop/lumop, rs2, vs2 in load/store instructions
                arg_variants = arg.split(sep='_')
                # try to find any of the variants in the instruction's arguments
                index = None
                for j, a in enumerate(arg_variants):
                    if a in instr_args:
                        index = j
                if index is not None:
                    # found a variant in the instruction's arguments
                    __emitter_args[i] = arg_variants[index]
                else:
                    # the argument had been encoded in the `encoding` string of the instruction specification
                    __emitter_args[i] = 'ENCODED'
            else:
                if not arg in instr_args:
                    # the argument had been encoded in the `encoding` string of the instruction specification
                    __emitter_args[i] = 'ENCODED'

    # join arguments into a single string and return the resulting emitter call
    # replace ENCODED with 0 to avoid a macro ENCODED
    emitter_args_joined = ', '.join(__emitter_args).replace("ENCODED", "0")
    # Use hexadecimal literal instead of binary literal because it is not supported in C++11.
    baseValue = hex(int('0b' + instr_encoding.replace('-', '0'), 2))
    return f'{emitter_name}({baseValue}, {emitter_args_joined});'


def generate_OPV(instr_name: str,
                 instr_encoding: str,
                 instr_args: List[str],
                 emitter_name: str,
                 emitter_args: List[str]
) -> None:
    '''
        Generates C++ implementation of an instruction under OP-V major opcode,
        combining a C++ function signature and a call to the underlying C++ emitter.
        Used to encode all Vector Arithmetic Instructions under OPIVV, OPFVV, ..., OPMVX minor opcodes.
    '''
    major_opcode = extract_opcode(instr_encoding)
    func_signature = generate_instruction_signature(instr_name, instr_args, emitter_name, major_opcode)
    emitter_call = generate_emitter_call(instr_encoding, instr_args, emitter_name, emitter_args)
    print(f'void {func_signature} {{ {emitter_call} }}')


def generate_OPIVV(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opIVV', emitter_args=['vm', 'vs2', 'vs1', 'vd'])


def generate_OPFVV(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opFVV', emitter_args=['vm', 'vs2', 'vs1', 'd'])


def generate_OPMVV(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opMVV', emitter_args=['vm', 'vs2', 'vs1', 'd'])


def generate_OPIVI(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opIVI', emitter_args=['vm', 'vs2', 'simm5', 'vd'])


def generate_OPIVX(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opIVX', emitter_args=['vm', 'vs2', 'rs1', 'vd'])


def generate_OPFVF(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opFVF', emitter_args=['vm', 'vs2', 'rs1', 'vd'])


def generate_OPMVX(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_OPV(instr_name, instr_encoding, instr_args,
                 emitter_name='opMVX', emitter_args=['vm', 'vs2', 'rs1', 'd'])


def generate_OPCFC(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    pass  # Vector Configuration Instructions are generated separately for simplicity


def generate_segment_load_store(instr_name: str, instr_encoding: str, instr_args: List[str],
                                emitter_name: str, emitter_args: List[str]) -> None:
    # encode segment variants of the load/store instruction
    eWLEN_match = re.search(r'e[\d]+', instr_name)
    if eWLEN_match is not None:
        eWLEN_pos = eWLEN_match.start()
        # for segment load/stores, nf[2:0] field specifies the number of fields in each segment
        # and may take values from 1 to 8 inclusive
        for nf in range(1, 9):
            nf_binary = format(nf - 1, '03b')
            # format the name appropriately like vlseg<nf>e<eew>,
            # for more details see `7.8. Vector Load/Store Segment Instructions`
            # chapter of the RVV 1.0 specification
            instr_name_seg = f'{instr_name[:eWLEN_pos]}seg{nf}{instr_name[eWLEN_pos:]}'
            instr_encoding_seg = instr_encoding.replace(instr_encoding[0:3], nf_binary, 1)
            generate_OPV(instr_name_seg, instr_encoding_seg, instr_args, emitter_name, emitter_args)


def generate_vector_load_store(instr_name: str, instr_encoding: str, instr_args: List[str],
                               emitter_name: str, emitter_args: List[str]) -> None:
    if 'nf' in instr_args:
        # if nf[2:0] field is in the arguments, then the instruction has
        # segment variants that should be generated separately
        generate_segment_load_store(instr_name, instr_encoding, instr_args, emitter_name, emitter_args)
    # encode nf=0b000 for regular (non-segment) vector load/stores
    instr_encoding = instr_encoding.replace(instr_encoding[0:3], '000', 1)
    generate_OPV(instr_name, instr_encoding, instr_args, emitter_name, emitter_args)


def generate_vector_load(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_vector_load_store(instr_name, instr_encoding, instr_args,
                               emitter_name='opVectorLoad', emitter_args=['vm', 'lumop_rs2_vs2', 'rs1', 'vd'])


def generate_vector_store(instr_name: str, instr_encoding: str, instr_args: List[str]) -> None:
    generate_vector_load_store(instr_name, instr_encoding, instr_args,
                               emitter_name='opVectorStore', emitter_args=['vm', 'sumop_rs2_vs2', 'rs1', 'vs3'])


def generate_RVV():
#    print('#define ENCODED uint32_t(0b0)')

    # read RVV intructions dictionary
    with open('rvv_instr_dict.yaml') as f:
        rvv_dict = yaml.load(f, Loader=SafeLoader)
        for item in rvv_dict.items():
            # get instruction specification
            instr_name = item[0]
            instr_encoding = item[1]['encoding']
            instr_args = item[1]['variable_fields']
            opcode_major = extract_opcode(instr_encoding)
            # select the right generator depending on the opcodes
            generator = None
            if opcode_major == OPV_MAJOR:
                # find generator for the Vector Arithmetic Instruction
                func3 = extract_func3(instr_encoding)
                opcode_minor = FUNC3_TO_OPV_MINOR[func3]
                try:
                    generator_name = f'generate_{opcode_minor}'
                    generator = globals()[generator_name]
                except KeyError:
                    raise ValueError(f'No generator for {opcode_minor} opcode')
            elif opcode_major == LOAD_FP_MAJOR:
                generator = generate_vector_load
            elif opcode_major == STORE_FP_MAJOR:
                generator = generate_vector_store
            else:
                pass
            # generate appropriate C++ function for the instruction
            if generator is not None:
                generator(instr_name, instr_encoding, instr_args)

    # generate Vector Configuration Instructions
    print('''
void vsetivli(const Reg& rd, uint32_t uimm, SEW sew, LMUL lmul=LMUL::m1, VTA vta=VTA::tu, VMA vma=VMA::mu) {
    uint32_t zimm = (static_cast<uint32_t>(vma)<<7) |
                    (static_cast<uint32_t>(vta)<<6) |
                    (static_cast<uint32_t>(sew)<<3) |
                    (static_cast<uint32_t>(lmul));
    uint32_t v = (0b11<<30) | (zimm<<20) | (uimm<<15) | (0b111<<12) | (rd.getIdx()<<7) | (0b1010111);
    append4B(v);
}

void vsetvli(const Reg& rd, const Reg& rs1, SEW sew, LMUL lmul=LMUL::m1, VTA vta=VTA::tu, VMA vma=VMA::mu) {
    uint32_t zimm = (static_cast<uint32_t>(vma)<<7) |
                    (static_cast<uint32_t>(vta)<<6) |
                    (static_cast<uint32_t>(sew)<<3) |
                    (static_cast<uint32_t>(lmul));
    uint32_t v = (0b0<<31) | (zimm<<20) | (rs1.getIdx()<<15) | (0b111<<12) | (rd.getIdx()<<7) | (0b1010111);
    append4B(v);
}

void vsetvl(const Reg& rd, const Reg& rs1, const Reg& rs2) {
    uint32_t v = (0b1000000<<25) | (rs2.getIdx()<<20) | (rs1.getIdx()<<15) | (0b111<<12) | (rd.getIdx()<<7) | (0b1010111);
    append4B(v);
}
''')

    # generate vector mask pseudoinstructions
    print('''
void vmmv_m(VReg vd, VReg vs) {
    vmand_mm(vd, vs, vs); // Copy mask register
}

void vmclr_m(VReg vd) {
    vmxor_mm(vd, vd, vd); // Clear mask register
}

void vmset_m(VReg vd) {
    vmxnor_mm(vd, vd, vd); // Set mask register
}

void vmnot_m(VReg vd, VReg vs) {
    vmnand_mm(vd, vs, vs); // Invert bits
}
''')


def main():
  copyright.put()
  generate_RVV()


if __name__ == '__main__':
  main()
