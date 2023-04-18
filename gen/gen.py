import copyright
copyright.put()

tbl = [
 (0b0000000,0b000, 0b0110011, 'add'),
 (0b0100000,0b000, 0b0110011, 'sub'),
 (0b0000000,0b001, 0b0110011, 'sll'),
 (0b0000000,0b010, 0b0110011, 'slt'),
 (0b0000000,0b011, 0b0110011, 'sltu'),
 (0b0000000,0b100, 0b0110011, 'xor_'),
 (0b0000000,0b101, 0b0110011, 'srl'),
 (0b0100000,0b101, 0b0110011, 'sra'),
 (0b0000000,0b110, 0b0110011, 'or_'),
 (0b0000000,0b111, 0b0110011, 'and_'),

 (0b0000000,0b000, 0b0111011, 'addw'),
 (0b0100000,0b000, 0b0111011, 'subw'),
 (0b0000000,0b001, 0b0111011, 'sllw'),
 (0b0000000,0b101, 0b0111011, 'srlw'),
 (0b0100000,0b101, 0b0111011, 'sraw'),

 (0b0000001,0b000, 0b0110011, 'mul'),
 (0b0000001,0b001, 0b0110011, 'mulh'),
 (0b0000001,0b010, 0b0110011, 'mulhsu'),
 (0b0000001,0b011, 0b0110011, 'mulhu'),
 (0b0000001,0b100, 0b0110011, 'div'),
 (0b0000001,0b101, 0b0110011, 'divu'),
 (0b0000001,0b110, 0b0110011, 'rem'),
 (0b0000001,0b111, 0b0110011, 'remu'),

 (0b0000001,0b000, 0b0111011, 'mulw'),
 (0b0000001,0b100, 0b0111011, 'divw'),
 (0b0000001,0b110, 0b0111011, 'remw'),
 (0b0000001,0b111, 0b0111011, 'remuw'),
]

for (funct7, funct3, opcode, name) in tbl:
  if name in ['sub', 'xor_', 'or_', 'and_', 'subw', 'addw']:
    tbl2 = {
      'sub' : (0b100011, 0b00),
      'xor_': (0b100011, 0b01),
      'or_' : (0b100011, 0b10),
      'and_': (0b100011, 0b11),
      'subw': (0b100111, 0b00),
      'addw': (0b100111, 0b01),
    }
    (cf3, cf2) = tbl2[name]
    rvc = f'if (supportRVC_ && c_noimm(rd, rs1, rs2, {hex(cf3)}, {cf2})) return; '
  else:
    rvc = ''
  print(f'void {name}(const Reg& rd, const Reg& rs1, const Reg& rs2) {{ {rvc}Rtype({hex(opcode)}, {funct3}, {hex(funct7)}, rd, rs1, rs2); }}')

tbl = [
 (0b000, 0b0010011, 'addi'),
 (0b010, 0b0010011, 'slti'),
 (0b011, 0b0010011, 'sltiu'),
 (0b100, 0b0010011, 'xori'),
 (0b110, 0b0010011, 'ori'),
 (0b111, 0b0010011, 'andi'),
 (0b000, 0b0011011, 'addiw'),
]

for (funct3, opcode, name) in tbl:
  if name == 'addi':
    rvc = 'if (supportRVC_ && c_addi(rd, rs1, imm)) return; '
  elif name == 'addiw':
    rvc = 'if (supportRVC_ && c_addi_inner(rd, rs1, imm, 1)) return; '
  elif name == 'andi':
    rvc = 'if (supportRVC_ && c_srli(rd, rs1, imm, 2)) return; '
  else:
    rvc = ''
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm) {{ {rvc}Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

tbl = [
 (0b000, 0b1100111, 'jalr'),
 (0b000, 0b0000011, 'lb'),
 (0b001, 0b0000011, 'lh'),
 (0b010, 0b0000011, 'lw'),
 (0b100, 0b0000011, 'lbu'),
 (0b101, 0b0000011, 'lhu'),
 (0b110, 0b0000011, 'lwu'),
 (0b011, 0b0000011, 'ld'),
]

print('// load-op rd, imm(addr); rd = addr[imm];')
for (funct3, opcode, name) in tbl:
  if name == 'lw':
    rvc = 'if (supportRVC_ && (c_lwsp(rd, addr, imm, 2) || c_lsw(rd, addr, imm, 2))) return; '
  elif name == 'ld':
    rvc = 'if (supportRVC_ && c_lsd(rd, addr, imm, 3)) return; '
  else:
    rvc = ''
  print(f'void {name}(const Reg& rd, const Reg& addr, int imm = 0) {{ {rvc}Itype({hex(opcode)}, {funct3}, rd, addr, imm); }}')

tbl = [
#  (0b0110111, 'lui'),
  (0b0010111, 'auipc'),
]

for (opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, uint32_t imm) {{ Utype({hex(opcode)}, rd, imm); }}')
print(f'void lui(const Reg& rd, uint32_t imm) {{ if (supportRVC_ && c_lui(rd, imm)) return; Utype({hex(0b0110111)}, rd, imm); }}')

tbl = [
  (0b0000000, 0b001, 0b0010011, 'slli'),
  (0b0000000, 0b101, 0b0010011, 'srli'),
  (0b0100000, 0b101, 0b0010011, 'srai'),
]

for (pre, funct3, opcode, name) in tbl:
  if name == 'srli':
    rvc = f'if (supportRVC_ && c_srli(rd, rs1, shamt, 0)) return; '
  elif name == 'srai':
    rvc = f'if (supportRVC_ && c_srli(rd, rs1, shamt, 1)) return; '
  elif name == 'slli':
    rvc = f'if (supportRVC_ && rd == rs1 && shamt != 0 && c_li(rd, shamt, 0, 2)) return; '
  print(f'void {name}(const Reg& rd, const Reg& rs1, uint32_t shamt) {{ {rvc}opShift({hex(pre)}, {funct3}, {hex(opcode)}, rd, rs1, shamt); }}')

tbl = [
  (0b0000000, 0b001, 0b0011011, 'slliw'),
  (0b0000000, 0b101, 0b0011011, 'srliw'),
  (0b0100000, 0b101, 0b0011011, 'sraiw'),
]

for (pre, funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, uint32_t shamt) {{ opShift({hex(pre)}, {funct3}, {hex(opcode)}, rd, rs1, shamt, 5); }}')
tbl = [
  (0x0330000f, 'fence_rw_rw'),
  (0x8330000f, 'fence_tso'),
  (0x0310000f, 'fence_rw_w'),
  (0x0230000f, 'fence_r_rw'),
  (0x0220000f, 'fence_r_r'),
  (0x0110000f, 'fence_w_w'),
  (0x0000100f, 'fence_i'),
  (0x00000073, 'ecall'),
  (0x00100073, 'ebreak'),
]

for (code, name) in tbl:
  print(f'void {name}() {{ append4B({hex(code)}); }}')

tbl = [
 (0b000, 0b0100011, 'sb'),
 (0b001, 0b0100011, 'sh'),
 (0b010, 0b0100011, 'sw'),
 (0b011, 0b0100011, 'sd'),
]

print('// store-op rs, imm(addr) ; addr[imm] = rs;')
for (funct3, opcode, name) in tbl:
  if name == 'sw':
    rvc = 'if (supportRVC_ && c_lsw(rs, addr, imm, 6)) return; '
  elif name == 'sd':
    rvc = 'if (supportRVC_ && c_lsd(rs, addr, imm, 7)) return; '
  else:
    rvc = ''
  print(f'void {name}(const Reg& rs, const Reg& addr, int imm = 0) {{ {rvc}Stype({hex(opcode)}, {funct3}, addr, rs, imm); }}')

tbl = [
  (0b000, 0b1100011, 'beq'),
  (0b001, 0b1100011, 'bne'),
  (0b100, 0b1100011, 'blt'),
  (0b101, 0b1100011, 'bge'),
  (0b110, 0b1100011, 'bltu'),
  (0b111, 0b1100011, 'bgeu'),
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rs1, const Reg& rs2, const Label& label) {{ Jmp jmp(getCurr(), {hex(opcode)}, {funct3}, rs1, rs2); opJmp(label, jmp); }}')

tbl = [
  ('beqz', 'beq', 'rs, x0'),
  ('bnez', 'bne', 'rs, x0'),
  ('blez', 'bge', 'x0, rs'),
  ('bgez', 'bge', 'rs, x0'),
  ('bltz', 'blt', 'rs, x0'),
  ('bgtz', 'blt', 'x0, rs'),
]

for (alias, name, args) in tbl:
  print(f'void {alias}(const Reg& rs, const Label& label) {{ {name}({args}, label); }}')

tbl = [
  ('bgt', 'blt', 'rt, rs'),
  ('ble', 'bge', 'rt, rs'),
  ('bgtu', 'bltu', 'rt, rs'),
  ('bleu', 'bgeu', 'rt, rs'),
]

for (alias, name, args) in tbl:
  print(f'void {alias}(const Reg& rs, const Reg& rt, const Label& label) {{ {name}({args}, label); }}')

def opAtomic(funct7, name, suf, funct3):
  print(f'void {name}_{suf}(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) {{ opAtomic(rd, rs2, addr, {hex(funct7)}, {funct3}, flag); }}')

tbl = [
  (0b00011, 'sc'),
  (0b00001, 'amoswap'),
  (0b00000, 'amoadd'),
  (0b00100, 'amoxor'),
  (0b01100, 'amoand'),
  (0b01000, 'amoor'),
  (0b10000, 'amomin'),
  (0b10100, 'amomax'),
  (0b11000, 'amominu'),
  (0b11100, 'amomaxu'),
]
print('// amos**, rd, rs2, (addr)')
for (funct7, name) in tbl:
  opAtomic(funct7, name, 'w', 2)
  opAtomic(funct7, name, 'd', 3)

# encode Zicsr instructions
tbl = [
  (0b00000000000000000001000001110011, 'csrrw', 0),
  (0b00000000000000000010000001110011, 'csrrs', 0),
  (0b00000000000000000011000001110011, 'csrrc', 0),
  (0b00000000000000000101000001110011, 'csrrwi', 1),
  (0b00000000000000000110000001110011, 'csrrsi', 1),
  (0b00000000000000000111000001110011, 'csrrci', 1),
]
for (code, name, imm) in tbl:
  if imm == 0:
    print(f'void {name}(const Reg& rd, CSR csr, const Reg& rs1) {{ opCSR({hex(code)}, csr, rs1, rd); }}')
  else:
    print(f'void {name}(const Reg& rd, CSR csr, uint32_t imm) {{ opCSR({hex(code)}, csr, imm, rd); }}')

# encode RV32F, RV64F instructions with OP-FP opcode
tbl = [
  # RV32_F extension
  (0b00000000000000000000000001010011, 'rs2', 'rm', 'fadd_s'),
  (0b11100000000000000001000001010011, '-', '-', 'fclass_s'),
  (0b11010000000000000000000001010011, '-', 'rm', 'fcvt_s_w'),
  (0b11010000000100000000000001010011, '-', 'rm', 'fcvt_s_wu'),
  (0b11000000000000000000000001010011, '-', 'rm', 'fcvt_w_s'),
  (0b11000000000100000000000001010011, '-', 'rm', 'fcvt_wu_s'),
  (0b00011000000000000000000001010011, 'rs2', 'rm', 'fdiv_s'),
  (0b10100000000000000010000001010011, 'rs2', '-', 'feq_s'),
  (0b10100000000000000000000001010011, 'rs2', '-', 'fle_s'),
  (0b10100000000000000001000001010011, 'rs2', '-', 'flt_s'),
  (0b00101000000000000001000001010011, 'rs2', '-', 'fmax_s'),
  (0b00101000000000000000000001010011, 'rs2', '-', 'fmin_s'),
  (0b00010000000000000000000001010011, 'rs2', 'rm', 'fmul_s'),
  (0b11110000000000000000000001010011, '-', '-', 'fmv_w_x'),
  (0b11100000000000000000000001010011, '-', '-', 'fmv_x_w'),
  (0b00100000000000000000000001010011, 'rs2', '-', 'fsgnj_s'),
  (0b00100000000000000001000001010011, 'rs2', '-', 'fsgnjn_s'),
  (0b00100000000000000010000001010011, 'rs2', '-', 'fsgnjx_s'),
  (0b01011000000000000000000001010011, '-', 'rm', 'fsqrt_s'),
  (0b00001000000000000000000001010011, 'rs2', 'rm', 'fsub_s'),
  # RV64_F extension
  (0b11000000001000000000000001010011, '-', 'rm', 'fcvt_l_s'),
  (0b11000000001100000000000001010011, '-', 'rm', 'fcvt_lu_s'),
  (0b11010000001000000000000001010011, '-', 'rm', 'fcvt_s_l'),
  (0b11010000001100000000000001010011, '-', 'rm', 'fcvt_s_lu'),
  # RV32_Zfh extension
  (0b00000100000000000000000001010011, 'rs2', 'rm', 'fadd_h'),
  (0b11100100000000000001000001010011, '-', '-', 'fclass_h'),
  (0b01000100000000000000000001010011, '-', 'rm', 'fcvt_h_s'),
  (0b11010100000000000000000001010011, '-', 'rm', 'fcvt_h_w'),
  (0b11010100000100000000000001010011, '-', 'rm', 'fcvt_h_wu'),
  (0b01000000001000000000000001010011, '-', 'rm', 'fcvt_s_h'),
  (0b11000100000000000000000001010011, '-', 'rm', 'fcvt_w_h'),
  (0b11000100000100000000000001010011, '-', 'rm', 'fcvt_wu_h'),
  (0b00011100000000000000000001010011, 'rs2', 'rm', 'fdiv_h'),
  (0b10100100000000000010000001010011, 'rs2', '-', 'feq_h'),
  (0b10100100000000000000000001010011, 'rs2', '-', 'fle_h'),
  (0b10100100000000000001000001010011, 'rs2', '-', 'flt_h'),
  (0b00101100000000000001000001010011, 'rs2', '-', 'fmax_h'),
  (0b00101100000000000000000001010011, 'rs2', '-', 'fmin_h'),
  (0b00010100000000000000000001010011, 'rs2', 'rm', 'fmul_h'),
  (0b11110100000000000000000001010011, '-', '-', 'fmv_h_x'),
  (0b11100100000000000000000001010011, '-', '-', 'fmv_x_h'),
  (0b00100100000000000000000001010011, 'rs2', '-', 'fsgnj_h'),
  (0b00100100000000000001000001010011, 'rs2', '-', 'fsgnjn_h'),
  (0b00100100000000000010000001010011, 'rs2', '-', 'fsgnjx_h'),
  (0b01011100000000000000000001010011, '-', 'rm', 'fsqrt_h'),
  (0b00001100000000000000000001010011, 'rs2', 'rm', 'fsub_h'),
  # RV64_Zfh extension
  (0b11010100001000000000000001010011, '-', 'rm', 'fcvt_h_l'),
  (0b11010100001100000000000001010011, '-', 'rm', 'fcvt_h_lu'),
  (0b11000100001000000000000001010011, '-', 'rm', 'fcvt_l_h'),
  (0b11000100001100000000000001010011, '-', 'rm', 'fcvt_lu_h'),
]


def opFP(baseValue, rs2, rm, name):
  # nested helper functions
  def is_encoded(arg): return arg == '-'
  def is_not_encoded(arg): return arg != '-'

  # generate C++ signature
  rd_type, rs1_type = 'FReg', 'FReg'
  if any([name.startswith(p) for p in ['fcvt', 'fmv', 'fclass']]):
    if name not in ['fcvt_s_w', 'fcvt_s_wu', 'fcvt_s_l', 'fcvt_s_lu', 'fmv_w_x',
                    'fcvt_h_w', 'fcvt_h_wu', 'fcvt_h_l', 'fcvt_h_lu', 'fmv_h_x']:
      rd_type = 'Reg'

    if name not in ['fcvt_w_s', 'fcvt_wu_s', 'fcvt_l_s', 'fcvt_lu_s', 'fmv_x_w', 'fclass_s',
                                'fcvt_w_h', 'fcvt_wu_h', 'fcvt_l_h', 'fcvt_lu_h', 'fmv_x_h', 'fclass_h']:
      rs1_type = 'Reg'

  if any([name.startswith(p) for p in ['feq', 'flt', 'fle']]):
    rd_type = 'Reg'

  signature_args = [f'const {rd_type}& rd', f'const {rs1_type}& rs1']
  if is_not_encoded(rs2):
    signature_args.append('const FReg& rs2')
  if is_not_encoded(rm):
    signature_args.append('RM rm=RM::dyn')
  signature_args_joined = ', '.join(signature_args)
  signature = f'{name}({signature_args_joined})'
  # generate emitter call
  emitter_args = [hex(baseValue), 'rs2', 'rs1', 'rm', 'rd']
  if is_encoded(rs2):
    emitter_args = ['0' if arg == 'rs2' else arg for arg in emitter_args]
  if is_encoded(rm):
    emitter_args = ['0' if arg == 'rm' else arg for arg in emitter_args]
  emitter_args_joined = ', '.join(emitter_args)
  emitter_call = f'opFP({emitter_args_joined});'
  # generate final implementation
  print(f'void {signature} {{ {emitter_call} }}')


for (baseValue, rs2, rm, name) in tbl:
  opFP(baseValue, rs2, rm, name)


# encode F[N]MADD/F[N]MSUB instructions
print('''
void fmadd_s(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x43, rs3, rs2, rs1, rm, rd); }
void fmsub_s(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x47, rs3, rs2, rs1, rm, rd); }
void fnmsub_s(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x4b, rs3, rs2, rs1, rm, rd); }
void fnmadd_s(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x4f, rs3, rs2, rs1, rm, rd); }

void fmadd_h(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x4000043, rs3, rs2, rs1, rm, rd); }
void fmsub_h(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x4000047, rs3, rs2, rs1, rm, rd); }
void fnmsub_h(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x400004b, rs3, rs2, rs1, rm, rd); }
void fnmadd_h(const FReg& rd, const FReg& rs1, const FReg& rs2, const FReg& rs3, RM rm=RM::dyn) { opR4(0x400004f, rs3, rs2, rs1, rm, rd); }
''')

# encode LOAD-FP, STORE-FP instructions
print('''
void flw(const FReg& rd, const Reg& rs1, int32_t imm12 = 0) { opLoadFP(0x2007, imm12, rs1, rd); }
void fsw(const FReg& rs2, const Reg& rs1, int32_t imm12 = 0) { opStoreFP(0x2027, imm12, rs2, rs1); }
void flh(const FReg& rd, const Reg& rs1, int32_t imm12 = 0) { opLoadFP(0x1007, imm12, rs1, rd); }
void fsh(const FReg& rs2, const Reg& rs1, int32_t imm12 = 0) { opStoreFP(0x1027, imm12, rs2, rs1); }
''')

# misc
print('''
void nop() { if (supportRVC_) { append2B(0x0001); return;} addi(x0, x0, 0); }
void li(const Reg& rd, int imm) { addi(rd, x0, imm); }
void mv(const Reg& rd, const Reg& rs) { addi(rd, rs, 0); }
void not_(const Reg& rd, const Reg& rs) { xori(rd, rs, -1); }
void neg(const Reg& rd, const Reg& rs) { sub(rd, x0, rs); }
void negw(const Reg& rd, const Reg& rs) { subw(rd, x0, rs); }
void sext_b(const Reg& rd, const Reg& rs) { slli(rd, rs, XLEN_ - 8); srai(rd, rd, XLEN_ - 8); }
void sext_h(const Reg& rd, const Reg& rs) { slli(rd, rs, XLEN_ - 16); srai(rd, rd, XLEN_ - 16); }
void sext_w(const Reg& rd, const Reg& rs) { addiw(rd, rs, 0); }
void zext_b(const Reg& rd, const Reg& rs) { andi(rd, rs, 255); }
void zext_h(const Reg& rd, const Reg& rs) { slli(rd, rs, XLEN_ - 16); srli(rd, rd, XLEN_ - 16); }
void zext_w(const Reg& rd, const Reg& rs) { slli(rd, rs, XLEN_ - 32); srli(rd, rd, XLEN_ - 32); }
void seqz(const Reg& rd, const Reg& rs) { sltiu(rd, rs, 1); }
void snez(const Reg& rd, const Reg& rs) { sltu(rd, x0, rs); }
void sltz(const Reg& rd, const Reg& rs) { slt(rd, rs, x0); }
void sgtz(const Reg& rd, const Reg& rs) { slt(rd, x0, rs); }
void fence() { append4B(0x0ff0000f); }
void j_(const Label& label) { jal(x0, label); }
void jal(const Reg& rd, const Label& label) { Jmp jmp(getCurr(), 0x6f, rd); opJmp(label, jmp); }
void jr(const Reg& rs) { jalr(x0, rs, 0); }
void jalr(const Reg& rs) { jalr(x1, rs, 0); }
void ret() { jalr(x0, x1); }
// lr rd, (addr)
void lr_w(const Reg& rd, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, 0, addr, 2, 2, flag); }
void lr_d(const Reg& rd, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, 0, addr, 2, 3, flag); }
void csrr(const Reg& rd, CSR csr) { csrrs(rd, csr, x0); }
void csrw(CSR csr, const Reg& rs) { csrrw(x0, csr, rs); }
void csrs(CSR csr, const Reg& rs) { csrrs(x0, csr, rs); }
void csrc(CSR csr, const Reg& rs) { csrrc(x0, csr, rs); }
void csrwi(CSR csr, uint32_t imm) { csrrwi(x0, csr, imm); }
void csrsi(CSR csr, uint32_t imm) { csrrsi(x0, csr, imm); }
void csrci(CSR csr, uint32_t imm) { csrrci(x0, csr, imm); }
''')
