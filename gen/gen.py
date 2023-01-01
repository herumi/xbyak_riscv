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
