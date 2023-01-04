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
]

for (funct7, funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, const Reg& rs2) {{ Rtype({hex(opcode)}, {funct3}, {hex(funct7)}, rd, rs1, rs2); }}')

tbl = [
 (0b000, 0b0010011, 'addi'),
 (0b010, 0b0010011, 'slti'),
 (0b011, 0b0010011, 'sltiu'),
 (0b100, 0b0010011, 'xori'),
 (0b110, 0b0010011, 'ori'),
 (0b111, 0b0010011, 'andi')
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm) {{ Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

tbl = [
 (0b000, 0b1100111, 'jalr'),
 (0b000, 0b0000011, 'lb'),
 (0b001, 0b0000011, 'lh'),
 (0b010, 0b0000011, 'lw'),
 (0b100, 0b0000011, 'lbu'),
 (0b101, 0b0000011, 'lhu'),
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm = 0) {{ Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

tbl = [
  (0b0110111, 'lui'),
  (0b0010111, 'auipc'),
]

for (opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, uint32_t imm) {{ Utype({hex(opcode)}, rd, imm); }}')

tbl = [
  (0b0000000, 0b001, 0b0010011, 'slli'),
  (0b0000000, 0b101, 0b0010011, 'srli'),
  (0b0100000, 0b101, 0b0010011, 'srai'),
]

for (pre, funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, uint32_t shamt) {{ opShift({hex(pre)}, {funct3}, {hex(opcode)}, rd, rs1, shamt); }}')

tbl = [
  (0x0330000f, 'rw_rw'),
  (0x8330000f, 'tso'),
  (0x0310000f, 'rw_w'),
  (0x0230000f, 'r_rw'),
  (0x0220000f, 'r_r'),
  (0x0110000f, 'w_w'),
  (0x0000100f, 'i'),
]

for (code, name) in tbl:
  print(f'void fence_{name}() {{ dd({hex(code)}); }}')

tbl = [
 (0b000, 0b0100011, 'sb'),
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rs2, const Reg& rs1, int imm = 0) {{ Stype({hex(opcode)}, {funct3}, rs1, rs2, imm); }}')

# misc
print('void ret() { jalr(x0, x1); }')
