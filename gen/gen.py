tbl = [
 (0b0000000,0b000, 0b0110011, "add"),
 (0b0100000,0b000, 0b0110011, "sub"),
 (0b0000000,0b001, 0b0110011, "sll"),
 (0b0000000,0b010, 0b0110011, "slt"),
 (0b0000000,0b011, 0b0110011, "sltu"),
 (0b0000000,0b100, 0b0110011, "xor_"),
 (0b0000000,0b101, 0b0110011, "srl"),
 (0b0100000,0b101, 0b0110011, "sra"),
 (0b0000000,0b110, 0b0110011, "or_"),
 (0b0000000,0b111, 0b0110011, "and_"),
]

for (funct7, funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, const Reg& rs2) {{ Rtype({hex(opcode)}, {funct3}, {hex(funct7)}, rd, rs1, rs2); }}')

tbl = [
 (0b000, 0b0010011, "addi"),
 (0b010, 0b0010011, "slti"),
 (0b011, 0b0010011, "sltiu"),
 (0b100, 0b0010011, "xori"),
 (0b110, 0b0010011, "ori"),
 (0b111, 0b0010011, "andi")
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm) {{ Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

tbl = [
 (0b000, 0b1100111, "jalr"),
 (0b000, 0b0000011, "lb"),
 (0b001, 0b0000011, "lh"),
 (0b010, 0b0000011, "lw"),
 (0b100, 0b0000011, "lbu"),
 (0b101, 0b0000011, "lhu"),
]

for (funct3, opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, const Reg& rs1, int imm = 0) {{ Itype({hex(opcode)}, {funct3}, rd, rs1, imm); }}')

tbl = [
  (0b0110111, "lui"),
]

for (opcode, name) in tbl:
  print(f'void {name}(const Reg& rd, uint32_t imm) {{ Utype({hex(opcode)}, rd, imm); }}')

# misc
print('void ret() { jalr(x0, x1); }')
