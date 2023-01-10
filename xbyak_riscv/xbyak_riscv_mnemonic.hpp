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
void addw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 0, 0x0, rd, rs1, rs2); }
void subw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 0, 0x20, rd, rs1, rs2); }
void sllw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 1, 0x0, rd, rs1, rs2); }
void srlw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 5, 0x0, rd, rs1, rs2); }
void sraw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 5, 0x20, rd, rs1, rs2); }
void mul(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 0, 0x1, rd, rs1, rs2); }
void mulh(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 1, 0x1, rd, rs1, rs2); }
void mulhsu(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 2, 0x1, rd, rs1, rs2); }
void mulhu(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 3, 0x1, rd, rs1, rs2); }
void div(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 4, 0x1, rd, rs1, rs2); }
void divu(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 5, 0x1, rd, rs1, rs2); }
void rem(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 6, 0x1, rd, rs1, rs2); }
void remu(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x33, 7, 0x1, rd, rs1, rs2); }
void mulw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 0, 0x1, rd, rs1, rs2); }
void divw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 4, 0x1, rd, rs1, rs2); }
void remw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 6, 0x1, rd, rs1, rs2); }
void remuw(const Reg& rd, const Reg& rs1, const Reg& rs2) { Rtype(0x3b, 7, 0x1, rd, rs1, rs2); }
void addi(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 0, rd, rs1, imm); }
void slti(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 2, rd, rs1, imm); }
void sltiu(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 3, rd, rs1, imm); }
void xori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 4, rd, rs1, imm); }
void ori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 6, rd, rs1, imm); }
void andi(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 7, rd, rs1, imm); }
void addiw(const Reg& rd, const Reg& rs1, int imm) { Itype(0x1b, 0, rd, rs1, imm); }
// load-op rd, imm(addr); rd = addr[imm];
void jalr(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x67, 0, rd, addr, imm); }
void lb(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 0, rd, addr, imm); }
void lh(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 1, rd, addr, imm); }
void lw(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 2, rd, addr, imm); }
void lbu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 4, rd, addr, imm); }
void lhu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 5, rd, addr, imm); }
void lwu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 6, rd, addr, imm); }
void ld(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 3, rd, addr, imm); }
void lui(const Reg& rd, uint32_t imm) { Utype(0x37, rd, imm); }
void auipc(const Reg& rd, uint32_t imm) { Utype(0x17, rd, imm); }
void slli(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 1, 0x13, rd, rs1, shamt); }
void srli(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 5, 0x13, rd, rs1, shamt); }
void srai(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x20, 5, 0x13, rd, rs1, shamt); }
void slliw(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 1, 0x1b, rd, rs1, shamt, 5); }
void srliw(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x0, 5, 0x1b, rd, rs1, shamt, 5); }
void sraiw(const Reg& rd, const Reg& rs1, uint32_t shamt) { opShift(0x20, 5, 0x1b, rd, rs1, shamt, 5); }
void fence_rw_rw() { append4B(0x330000f); }
void fence_tso() { append4B(0x8330000f); }
void fence_rw_w() { append4B(0x310000f); }
void fence_r_rw() { append4B(0x230000f); }
void fence_r_r() { append4B(0x220000f); }
void fence_w_w() { append4B(0x110000f); }
void fence_i() { append4B(0x100f); }
void ecall() { append4B(0x73); }
void ebreak() { append4B(0x100073); }
// store-op rs2, imm(addr) ; addr[imm] = rs2;
void sb(const Reg& rs2, const Reg& addr, int imm = 0) { Stype(0x23, 0, addr, rs2, imm); }
void sh(const Reg& rs2, const Reg& addr, int imm = 0) { Stype(0x23, 1, addr, rs2, imm); }
void sw(const Reg& rs2, const Reg& addr, int imm = 0) { Stype(0x23, 2, addr, rs2, imm); }
void sd(const Reg& rs2, const Reg& addr, int imm = 0) { Stype(0x23, 3, addr, rs2, imm); }
void beq(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 0, rs1, rs2); opJmp(label, jmp); }
void bne(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 1, rs1, rs2); opJmp(label, jmp); }
void blt(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 4, rs1, rs2); opJmp(label, jmp); }
void bge(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 5, rs1, rs2); opJmp(label, jmp); }
void bltu(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 6, rs1, rs2); opJmp(label, jmp); }
void bgeu(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getSize(), 0x63, 7, rs1, rs2); opJmp(label, jmp); }
void beqz(const Reg& rs, const Label& label) { beq(rs, x0, label); }
void bnez(const Reg& rs, const Label& label) { bne(rs, x0, label); }
void blez(const Reg& rs, const Label& label) { bge(x0, rs, label); }
void bgez(const Reg& rs, const Label& label) { bge(rs, x0, label); }
void bltz(const Reg& rs, const Label& label) { blt(rs, x0, label); }
void bgtz(const Reg& rs, const Label& label) { blt(x0, rs, label); }
void bgt(const Reg& rs, const Reg& rt, const Label& label) { blt(rt, rs, label); }
void ble(const Reg& rs, const Reg& rt, const Label& label) { bge(rt, rs, label); }
void bgtu(const Reg& rs, const Reg& rt, const Label& label) { bltu(rt, rs, label); }
void bleu(const Reg& rs, const Reg& rt, const Label& label) { bgeu(rt, rs, label); }
// amos**, rd, rs2, (addr)
void sc_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x3, 2, flag); }
void sc_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x3, 3, flag); }
void amoswap_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x1, 2, flag); }
void amoswap_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x1, 3, flag); }
void amoadd_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x0, 2, flag); }
void amoadd_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x0, 3, flag); }
void amoxor_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x4, 2, flag); }
void amoxor_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x4, 3, flag); }
void amoand_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0xc, 2, flag); }
void amoand_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0xc, 3, flag); }
void amoor_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x8, 2, flag); }
void amoor_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x8, 3, flag); }
void amomin_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x10, 2, flag); }
void amomin_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x10, 3, flag); }
void amomax_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x14, 2, flag); }
void amomax_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x14, 3, flag); }
void amominu_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x18, 2, flag); }
void amominu_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x18, 3, flag); }
void amomaxu_w(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x1c, 2, flag); }
void amomaxu_d(const Reg& rd, const Reg& rs2, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, rs2, addr, 0x1c, 3, flag); }

void nop() { addi(x0, x0, 0); }
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
void jal(const Reg& rd, const Label& label) { Jmp jmp(getSize(), 0x6f, rd); opJmp(label, jmp); }
void jr(const Reg& rs) { jalr(x0, rs, 0); }
void jalr(const Reg& rs) { jalr(x1, rs, 0); }
void ret() { jalr(x0, x1); }
// lr rd, (addr)
void lr_w(const Reg& rd, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, 0, addr, 2, 2, flag); }
void lr_d(const Reg& rd, const Reg& addr, uint32_t flag = 0) { opAtomic(rd, 0, addr, 2, 3, flag); }

