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
void auipc(const Reg& rd, uint32_t imm) { Utype(0x17, rd, imm); }
void slli(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 1, 0x13, rd, rs1, shamt); }
void srli(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 5, 0x13, rd, rs1, shamt); }
void srai(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x20, 5, 0x13, rd, rs1, shamt); }
void fence_rw_rw() { write4byte(0x330000f); }
void fence_tso() { write4byte(0x8330000f); }
void fence_rw_w() { write4byte(0x310000f); }
void fence_r_rw() { write4byte(0x230000f); }
void fence_r_r() { write4byte(0x220000f); }
void fence_w_w() { write4byte(0x110000f); }
void fence_i() { write4byte(0x100f); }
void ecall() { write4byte(0x73); }
void ebreak() { write4byte(0x100073); }
void sb(const Reg& rs2, const Reg& rs1, int imm = 0) { Stype(0x23, 0, rs1, rs2, imm); }
void sh(const Reg& rs2, const Reg& rs1, int imm = 0) { Stype(0x23, 1, rs1, rs2, imm); }
void sw(const Reg& rs2, const Reg& rs1, int imm = 0) { Stype(0x23, 2, rs1, rs2, imm); }
void ret() { jalr(x0, x1); }
