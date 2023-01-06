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
  print(f'void {name}(const Reg& rd, const Reg& rs1, const Reg& rs2) {{ Rtype({hex(opcode)}, {funct3}, {hex(funct7)}, rd, rs1, rs2); }}')

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
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm) {{ Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

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

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rs2, const Reg& rs1, int imm = 0) {{ Stype({hex(opcode)}, {funct3}, rs1, rs2, imm); }}')

tbl = [
  (0b000, 0b1100011, 'beq'),
  (0b001, 0b1100011, 'bne'),
  (0b100, 0b1100011, 'blt'),
  (0b101, 0b1100011, 'bge'),
  (0b110, 0b1100011, 'bltu'),
  (0b111, 0b1100011, 'bgeu'),
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& src1, const Reg& src2, const Label& label) {{ Jmp jmp(getSize(), {hex(opcode)}, {funct3}, src1, src2); opJmp(label, jmp); }}')

# misc
print('void ret() { jalr(x0, x1); }')
print('void jal(const Reg& rd, const Label& label) { Jmp jmp(getSize(), 0x6f, rd); opJmp(label, jmp); }')
