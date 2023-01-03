void add(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 0, 0x0, rd, rs1, rs2); }
void sub(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 0, 0x20, rd, rs1, rs2); }
void sll(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 1, 0x0, rd, rs1, rs2); }
void slt(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 2, 0x0, rd, rs1, rs2); }
void sltu(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 3, 0x0, rd, rs1, rs2); }
void xor_(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 4, 0x0, rd, rs1, rs2); }
void srl(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 5, 0x0, rd, rs1, rs2); }
void sra(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 5, 0x20, rd, rs1, rs2); }
void or_(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 6, 0x0, rd, rs1, rs2); }
void and_(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 7, 0x0, rd, rs1, rs2); }
void addi(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 0, rd, rs1, imm); }
void slti(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 2, rd, rs1, imm); }
void sltiu(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 3, rd, rs1, imm); }
void xori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 4, rd, rs1, imm); }
void ori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 6, rd, rs1, imm); }
void andi(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 7, rd, rs1, imm); }
void jalr(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x67, 0, rd, rs1, imm); }
void lb(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x3, 0, rd, rs1, imm); }
void lh(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x3, 1, rd, rs1, imm); }
void lw(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x3, 2, rd, rs1, imm); }
void lbu(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x3, 4, rd, rs1, imm); }
void lhu(const Reg& rd, const Reg& rs1, int imm = 0) { Itype(0x3, 5, rd, rs1, imm); }
void lui(const Reg& rd, uint32_t imm) { Utype(0x37, rd, imm); }
void ret() { jalr(x0, x1); }
