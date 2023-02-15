
/******************************************************************************
* Copyright (c), 2023, MITSUNARI Shigeo
* Copyright (C), 2023, KNS Group LLC (YADRO)
*
* Licensed under the 3-Clause BSD License
* You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
*******************************************************************************/

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
void addi(const Reg& rd, const Reg& rs1, int imm) { if (supportRVC_ && c_addi(rd, rs1, imm)) return; Itype(0x13, 0, rd, rs1, imm); }
void slti(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 2, rd, rs1, imm); }
void sltiu(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 3, rd, rs1, imm); }
void xori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 4, rd, rs1, imm); }
void ori(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 6, rd, rs1, imm); }
void andi(const Reg& rd, const Reg& rs1, int imm) { Itype(0x13, 7, rd, rs1, imm); }
void addiw(const Reg& rd, const Reg& rs1, int imm) { if (supportRVC_ && c_addi_inner(rd, rs1, imm, 1)) return; Itype(0x1b, 0, rd, rs1, imm); }
// load-op rd, imm(addr); rd = addr[imm];
void jalr(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x67, 0, rd, addr, imm); }
void lb(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 0, rd, addr, imm); }
void lh(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 1, rd, addr, imm); }
void lw(const Reg& rd, const Reg& addr, int imm = 0) { if (supportRVC_ && c_lsw(rd, addr, imm, 2)) return; Itype(0x3, 2, rd, addr, imm); }
void lbu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 4, rd, addr, imm); }
void lhu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 5, rd, addr, imm); }
void lwu(const Reg& rd, const Reg& addr, int imm = 0) { Itype(0x3, 6, rd, addr, imm); }
void ld(const Reg& rd, const Reg& addr, int imm = 0) { if (supportRVC_ && c_lsd(rd, addr, imm, 3)) return; Itype(0x3, 3, rd, addr, imm); }
void auipc(const Reg& rd, uint32_t imm) { Utype(0x17, rd, imm); }
void lui(const Reg& rd, uint32_t imm) { if (supportRVC_ && c_lui(rd, imm)) return; Utype(0x37, rd, imm); }
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
// store-op rs, imm(addr) ; addr[imm] = rs;
void sb(const Reg& rs, const Reg& addr, int imm = 0) { Stype(0x23, 0, addr, rs, imm); }
void sh(const Reg& rs, const Reg& addr, int imm = 0) { Stype(0x23, 1, addr, rs, imm); }
void sw(const Reg& rs, const Reg& addr, int imm = 0) { if (supportRVC_ && c_lsw(rs, addr, imm, 6)) return; Stype(0x23, 2, addr, rs, imm); }
void sd(const Reg& rs, const Reg& addr, int imm = 0) { if (supportRVC_ && c_lsd(rs, addr, imm, 7)) return; Stype(0x23, 3, addr, rs, imm); }
void beq(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 0, rs1, rs2); opJmp(label, jmp); }
void bne(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 1, rs1, rs2); opJmp(label, jmp); }
void blt(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 4, rs1, rs2); opJmp(label, jmp); }
void bge(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 5, rs1, rs2); opJmp(label, jmp); }
void bltu(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 6, rs1, rs2); opJmp(label, jmp); }
void bgeu(const Reg& rs1, const Reg& rs2, const Label& label) { Jmp jmp(getCurr(), 0x63, 7, rs1, rs2); opJmp(label, jmp); }
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

#define ENCODED uint32_t(0b0)
void vaadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00100100000000000010000001010111, vm, vs2, vs1, vd); }
void vaadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00100100000000000110000001010111, vm, vs2, rs1, vd); }
void vaaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00100000000000000010000001010111, vm, vs2, vs1, vd); }
void vaaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00100000000000000110000001010111, vm, vs2, rs1, vd); }
void vadc_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0b01000000000000000011000001010111, ENCODED, vs2, simm5, vd); }
void vadc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01000000000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vadc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01000000000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vadd_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00000000000000000011000001010111, vm, vs2, simm5, vd); }
void vadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00000000000000000000000001010111, vm, vs2, vs1, vd); }
void vadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00000000000000000100000001010111, vm, vs2, rs1, vd); }
void vand_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00100100000000000011000001010111, vm, vs2, simm5, vd); }
void vand_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00100100000000000000000001010111, vm, vs2, vs1, vd); }
void vand_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00100100000000000100000001010111, vm, vs2, rs1, vd); }
void vasub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00101100000000000010000001010111, vm, vs2, vs1, vd); }
void vasub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00101100000000000110000001010111, vm, vs2, rs1, vd); }
void vasubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00101000000000000010000001010111, vm, vs2, vs1, vd); }
void vasubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00101000000000000110000001010111, vm, vs2, rs1, vd); }
void vcompress_vm(VReg vd, VReg vs2, VReg vs1) { opMVV(0b01011110000000000010000001010111, ENCODED, vs2, vs1, vd); }
void vcpop_m(Reg rd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01000000000010000010000001010111, vm, vs2, ENCODED, rd); }
void vdiv_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10000100000000000010000001010111, vm, vs2, vs1, vd); }
void vdiv_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10000100000000000110000001010111, vm, vs2, rs1, vd); }
void vdivu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10000000000000000010000001010111, vm, vs2, vs1, vd); }
void vdivu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10000000000000000110000001010111, vm, vs2, rs1, vd); }
void vfadd_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00000000000000000101000001010111, vm, vs2, rs1, vd); }
void vfadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00000000000000000001000001010111, vm, vs2, vs1, vd); }
void vfclass_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001100000010000001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_f_x_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000011001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_f_xu_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000010001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_rtz_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000111001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_rtz_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000110001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000001001000001010111, vm, vs2, ENCODED, vd); }
void vfcvt_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000000000001000001010111, vm, vs2, ENCODED, vd); }
void vfdiv_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b10000000000000000101000001010111, vm, vs2, rs1, vd); }
void vfdiv_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b10000000000000000001000001010111, vm, vs2, vs1, vd); }
void vfirst_m(Reg rd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01000000000010001010000001010111, vm, vs2, ENCODED, rd); }
void vfmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10110000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10110000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmadd_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10100000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10100000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmax_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00011000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmax_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00011000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmerge_vfm(VReg vd, VReg vs2, FReg rs1) { opFVF(0b01011100000000000101000001010111, ENCODED, vs2, rs1, vd); }
void vfmin_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00010000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmin_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00010000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10111000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10111000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmsub_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10101000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10101000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmul_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b10010000000000000101000001010111, vm, vs2, rs1, vd); }
void vfmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b10010000000000000001000001010111, vm, vs2, vs1, vd); }
void vfmv_f_s(FReg rd, VReg vs2) { opFVV(0b01000010000000000001000001010111, ENCODED, vs2, ENCODED, rd); }
void vfmv_s_f(VReg vd, FReg rs1) { opFVF(0b01000010000000000101000001010111, ENCODED, ENCODED, rs1, vd); }
void vfmv_v_f(VReg vd, FReg rs1) { opFVF(0b01011110000000000101000001010111, ENCODED, ENCODED, rs1, vd); }
void vfncvt_f_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010100001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_f_x_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010011001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_f_xu_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010010001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_rod_f_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010101001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_rtz_x_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010111001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_rtz_xu_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010110001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_x_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010001001000001010111, vm, vs2, ENCODED, vd); }
void vfncvt_xu_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000010000001000001010111, vm, vs2, ENCODED, vd); }
void vfnmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10110100000000000101000001010111, vm, vs2, rs1, vd); }
void vfnmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10110100000000000001000001010111, vm, vs2, vs1, vd); }
void vfnmadd_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10100100000000000101000001010111, vm, vs2, rs1, vd); }
void vfnmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10100100000000000001000001010111, vm, vs2, vs1, vd); }
void vfnmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10111100000000000101000001010111, vm, vs2, rs1, vd); }
void vfnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10111100000000000001000001010111, vm, vs2, vs1, vd); }
void vfnmsub_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b10101100000000000101000001010111, vm, vs2, rs1, vd); }
void vfnmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b10101100000000000001000001010111, vm, vs2, vs1, vd); }
void vfrdiv_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b10000100000000000101000001010111, vm, vs2, rs1, vd); }
void vfrec7_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001100000000101001000001010111, vm, vs2, ENCODED, vd); }
void vfredmax_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00011100000000000001000001010111, vm, vs2, vs1, vd); }
void vfredmin_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00010100000000000001000001010111, vm, vs2, vs1, vd); }
void vfredosum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00001100000000000001000001010111, vm, vs2, vs1, vd); }
void vfredusum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00000100000000000001000001010111, vm, vs2, vs1, vd); }
void vfrsqrt7_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001100000000100001000001010111, vm, vs2, ENCODED, vd); }
void vfrsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b10011100000000000101000001010111, vm, vs2, rs1, vd); }
void vfsgnj_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00100000000000000101000001010111, vm, vs2, rs1, vd); }
void vfsgnj_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00100000000000000001000001010111, vm, vs2, vs1, vd); }
void vfsgnjn_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00100100000000000101000001010111, vm, vs2, rs1, vd); }
void vfsgnjn_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00100100000000000001000001010111, vm, vs2, vs1, vd); }
void vfsgnjx_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00101000000000000101000001010111, vm, vs2, rs1, vd); }
void vfsgnjx_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00101000000000000001000001010111, vm, vs2, vs1, vd); }
void vfslide1down_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00111100000000000101000001010111, vm, vs2, rs1, vd); }
void vfslide1up_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00111000000000000101000001010111, vm, vs2, rs1, vd); }
void vfsqrt_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001100000000000001000001010111, vm, vs2, ENCODED, vd); }
void vfsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b00001000000000000101000001010111, vm, vs2, rs1, vd); }
void vfsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b00001000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwadd_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b11000000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11000000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwadd_wf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b11010000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwadd_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11010000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwcvt_f_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001100001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_f_x_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001011001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_f_xu_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001010001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_rtz_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001111001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_rtz_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001110001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001001001000001010111, vm, vs2, ENCODED, vd); }
void vfwcvt_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0b01001000000001000001000001010111, vm, vs2, ENCODED, vd); }
void vfwmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b11110000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b11110000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b11111000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b11111000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwmul_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b11100000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11100000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwnmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b11110100000000000101000001010111, vm, vs2, rs1, vd); }
void vfwnmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b11110100000000000001000001010111, vm, vs2, vs1, vd); }
void vfwnmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0b11111100000000000101000001010111, vm, vs2, rs1, vd); }
void vfwnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0b11111100000000000001000001010111, vm, vs2, vs1, vd); }
void vfwredosum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11001100000000000001000001010111, vm, vs2, vs1, vd); }
void vfwredusum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11000100000000000001000001010111, vm, vs2, vs1, vd); }
void vfwsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b11001000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11001000000000000001000001010111, vm, vs2, vs1, vd); }
void vfwsub_wf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b11011000000000000101000001010111, vm, vs2, rs1, vd); }
void vfwsub_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b11011000000000000001000001010111, vm, vs2, vs1, vd); }
void vid_v(VReg vd, VM vm=VM::unmasked) { opMVV(0b01010000000010001010000001010111, vm, ENCODED, ENCODED, vd); }
void viota_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01010000000010000010000001010111, vm, vs2, ENCODED, vd); }
void vl1re16_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000101000000000111, ENCODED, ENCODED, rs1, vd); }
void vl1re32_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000110000000000111, ENCODED, ENCODED, rs1, vd); }
void vl1re64_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000111000000000111, ENCODED, ENCODED, rs1, vd); }
void vl1re8_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000000000000000111, ENCODED, ENCODED, rs1, vd); }
void vl2re16_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000101000000000111, ENCODED, ENCODED, rs1, vd); }
void vl2re32_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000110000000000111, ENCODED, ENCODED, rs1, vd); }
void vl2re64_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000111000000000111, ENCODED, ENCODED, rs1, vd); }
void vl2re8_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000000000000000111, ENCODED, ENCODED, rs1, vd); }
void vl4re16_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000101000000000111, ENCODED, ENCODED, rs1, vd); }
void vl4re32_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000110000000000111, ENCODED, ENCODED, rs1, vd); }
void vl4re64_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000111000000000111, ENCODED, ENCODED, rs1, vd); }
void vl4re8_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000000000000000111, ENCODED, ENCODED, rs1, vd); }
void vl8re16_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000101000000000111, ENCODED, ENCODED, rs1, vd); }
void vl8re32_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000110000000000111, ENCODED, ENCODED, rs1, vd); }
void vl8re64_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000111000000000111, ENCODED, ENCODED, rs1, vd); }
void vl8re8_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010100000000000000000000111, ENCODED, ENCODED, rs1, vd); }
void vlseg1e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vle1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vle1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vle128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vle128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vle16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vle16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vle256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vle256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000101000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vle32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vle32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vle512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010000000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00110001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01010001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01110001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10010001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10110001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11010001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11110001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vle512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00010001000000000110000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vle64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vle64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000111000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vle8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000000000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg1e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg2e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00100001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg3e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01000001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg4e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b01100001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg5e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10000001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg6e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b10100001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg7e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11000001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlseg8e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b11100001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vle8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0b00000001000000000000000000000111, vm, ENCODED, rs1, vd); }
void vlm_v(VReg vd, Reg rs1) { opVectorLoad(0b00000010101100000000000000000111, ENCODED, ENCODED, rs1, vd); }
void vloxei1024_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00011100000000000111000000000111, vm, vs2, rs1, vd); }
void vloxei128_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00011100000000000000000000000111, vm, vs2, rs1, vd); }
void vloxei16_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00001100000000000101000000000111, vm, vs2, rs1, vd); }
void vloxei256_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00011100000000000101000000000111, vm, vs2, rs1, vd); }
void vloxei32_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00001100000000000110000000000111, vm, vs2, rs1, vd); }
void vloxei512_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00011100000000000110000000000111, vm, vs2, rs1, vd); }
void vloxei64_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00001100000000000111000000000111, vm, vs2, rs1, vd); }
void vloxei8_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00001100000000000000000000000111, vm, vs2, rs1, vd); }
void vlsseg1e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg2e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00111000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg3e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01011000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg4e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01111000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg5e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10011000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg6e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10111000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg7e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11011000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg8e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11111000000000000111000000000111, vm, rs2, rs1, vd); }
void vlse1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg1e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg2e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00111000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg3e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01011000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg4e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01111000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg5e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10011000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg6e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10111000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg7e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11011000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg8e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11111000000000000000000000000111, vm, rs2, rs1, vd); }
void vlse128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg1e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg2e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00101000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg3e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01001000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg4e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01101000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg5e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10001000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg6e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10101000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg7e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11001000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg8e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11101000000000000101000000000111, vm, rs2, rs1, vd); }
void vlse16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg1e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg2e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00111000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg3e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01011000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg4e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01111000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg5e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10011000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg6e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10111000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg7e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11011000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg8e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11111000000000000101000000000111, vm, rs2, rs1, vd); }
void vlse256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000101000000000111, vm, rs2, rs1, vd); }
void vlsseg1e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg2e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00101000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg3e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01001000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg4e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01101000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg5e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10001000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg6e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10101000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg7e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11001000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg8e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11101000000000000110000000000111, vm, rs2, rs1, vd); }
void vlse32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg1e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg2e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00111000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg3e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01011000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg4e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01111000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg5e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10011000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg6e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10111000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg7e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11011000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg8e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11111000000000000110000000000111, vm, rs2, rs1, vd); }
void vlse512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00011000000000000110000000000111, vm, rs2, rs1, vd); }
void vlsseg1e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg2e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00101000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg3e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01001000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg4e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01101000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg5e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10001000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg6e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10101000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg7e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11001000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg8e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11101000000000000111000000000111, vm, rs2, rs1, vd); }
void vlse64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000111000000000111, vm, rs2, rs1, vd); }
void vlsseg1e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg2e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00101000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg3e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01001000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg4e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b01101000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg5e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10001000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg6e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b10101000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg7e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11001000000000000000000000000111, vm, rs2, rs1, vd); }
void vlsseg8e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b11101000000000000000000000000111, vm, rs2, rs1, vd); }
void vlse8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0b00001000000000000000000000000111, vm, rs2, rs1, vd); }
void vluxei1024_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00010100000000000111000000000111, vm, vs2, rs1, vd); }
void vluxei128_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00010100000000000000000000000111, vm, vs2, rs1, vd); }
void vluxei16_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00000100000000000101000000000111, vm, vs2, rs1, vd); }
void vluxei256_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00010100000000000101000000000111, vm, vs2, rs1, vd); }
void vluxei32_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00000100000000000110000000000111, vm, vs2, rs1, vd); }
void vluxei512_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00010100000000000110000000000111, vm, vs2, rs1, vd); }
void vluxei64_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00000100000000000111000000000111, vm, vs2, rs1, vd); }
void vluxei8_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0b00000100000000000000000000000111, vm, vs2, rs1, vd); }
void vmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b10110100000000000010000001010111, vm, vs2, vs1, vd); }
void vmacc_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b10110100000000000110000001010111, vm, vs2, rs1, vd); }
void vmadc_vi(VReg vd, VReg vs2, int32_t simm5) { opIVI(0b01000110000000000011000001010111, ENCODED, vs2, simm5, vd); }
void vmadc_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0b01000100000000000011000001010111, ENCODED, vs2, simm5, vd); }
void vmadc_vv(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01000110000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vmadc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01000100000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vmadc_vx(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01000110000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vmadc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01000100000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b10100100000000000010000001010111, vm, vs2, vs1, vd); }
void vmadd_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b10100100000000000110000001010111, vm, vs2, rs1, vd); }
void vmand_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01100100000000000010000001010111, vm, vs2, vs1, vd); }
void vmandn_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01100000000000000010000001010111, vm, vs2, vs1, vd); }
void vmax_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00011100000000000000000001010111, vm, vs2, vs1, vd); }
void vmax_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00011100000000000100000001010111, vm, vs2, rs1, vd); }
void vmaxu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00011000000000000000000001010111, vm, vs2, vs1, vd); }
void vmaxu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00011000000000000100000001010111, vm, vs2, rs1, vd); }
void vmerge_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0b01011100000000000011000001010111, ENCODED, vs2, simm5, vd); }
void vmerge_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01011100000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vmerge_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01011100000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vmfeq_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01100000000000000101000001010111, vm, vs2, rs1, vd); }
void vmfeq_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b01100000000000000001000001010111, vm, vs2, vs1, vd); }
void vmfge_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01111100000000000101000001010111, vm, vs2, rs1, vd); }
void vmfgt_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01110100000000000101000001010111, vm, vs2, rs1, vd); }
void vmfle_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01100100000000000101000001010111, vm, vs2, rs1, vd); }
void vmfle_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b01100100000000000001000001010111, vm, vs2, vs1, vd); }
void vmflt_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01101100000000000101000001010111, vm, vs2, rs1, vd); }
void vmflt_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b01101100000000000001000001010111, vm, vs2, vs1, vd); }
void vmfne_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0b01110000000000000101000001010111, vm, vs2, rs1, vd); }
void vmfne_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0b01110000000000000001000001010111, vm, vs2, vs1, vd); }
void vmin_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00010100000000000000000001010111, vm, vs2, vs1, vd); }
void vmin_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00010100000000000100000001010111, vm, vs2, rs1, vd); }
void vminu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00010000000000000000000001010111, vm, vs2, vs1, vd); }
void vminu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00010000000000000100000001010111, vm, vs2, rs1, vd); }
void vmnand_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01110100000000000010000001010111, vm, vs2, vs1, vd); }
void vmnor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01111000000000000010000001010111, vm, vs2, vs1, vd); }
void vmor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01101000000000000010000001010111, vm, vs2, vs1, vd); }
void vmorn_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01110000000000000010000001010111, vm, vs2, vs1, vd); }
void vmsbc_vv(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01001110000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vmsbc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01001100000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vmsbc_vx(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01001110000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vmsbc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01001100000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vmsbf_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01010000000000001010000001010111, vm, vs2, ENCODED, vd); }
void vmseq_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01100000000000000011000001010111, vm, vs2, simm5, vd); }
void vmseq_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01100000000000000000000001010111, vm, vs2, vs1, vd); }
void vmseq_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01100000000000000100000001010111, vm, vs2, rs1, vd); }
void vmsgt_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01111100000000000011000001010111, vm, vs2, simm5, vd); }
void vmsgt_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01111100000000000100000001010111, vm, vs2, rs1, vd); }
void vmsgtu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01111000000000000011000001010111, vm, vs2, simm5, vd); }
void vmsgtu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01111000000000000100000001010111, vm, vs2, rs1, vd); }
void vmsif_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01010000000000011010000001010111, vm, vs2, ENCODED, vd); }
void vmsle_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01110100000000000011000001010111, vm, vs2, simm5, vd); }
void vmsle_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01110100000000000000000001010111, vm, vs2, vs1, vd); }
void vmsle_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01110100000000000100000001010111, vm, vs2, rs1, vd); }
void vmsleu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01110000000000000011000001010111, vm, vs2, simm5, vd); }
void vmsleu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01110000000000000000000001010111, vm, vs2, vs1, vd); }
void vmsleu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01110000000000000100000001010111, vm, vs2, rs1, vd); }
void vmslt_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01101100000000000000000001010111, vm, vs2, vs1, vd); }
void vmslt_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01101100000000000100000001010111, vm, vs2, rs1, vd); }
void vmsltu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01101000000000000000000001010111, vm, vs2, vs1, vd); }
void vmsltu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01101000000000000100000001010111, vm, vs2, rs1, vd); }
void vmsne_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b01100100000000000011000001010111, vm, vs2, simm5, vd); }
void vmsne_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b01100100000000000000000001010111, vm, vs2, vs1, vd); }
void vmsne_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b01100100000000000100000001010111, vm, vs2, rs1, vd); }
void vmsof_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01010000000000010010000001010111, vm, vs2, ENCODED, vd); }
void vmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10010100000000000010000001010111, vm, vs2, vs1, vd); }
void vmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10010100000000000110000001010111, vm, vs2, rs1, vd); }
void vmulh_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10011100000000000010000001010111, vm, vs2, vs1, vd); }
void vmulh_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10011100000000000110000001010111, vm, vs2, rs1, vd); }
void vmulhsu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10011000000000000010000001010111, vm, vs2, vs1, vd); }
void vmulhsu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10011000000000000110000001010111, vm, vs2, rs1, vd); }
void vmulhu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10010000000000000010000001010111, vm, vs2, vs1, vd); }
void vmulhu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10010000000000000110000001010111, vm, vs2, rs1, vd); }
void vmv1r_v(VReg vd, VReg vs2) { opIVI(0b10011110000000000011000001010111, ENCODED, vs2, ENCODED, vd); }
void vmv2r_v(VReg vd, VReg vs2) { opIVI(0b10011110000000001011000001010111, ENCODED, vs2, ENCODED, vd); }
void vmv4r_v(VReg vd, VReg vs2) { opIVI(0b10011110000000011011000001010111, ENCODED, vs2, ENCODED, vd); }
void vmv8r_v(VReg vd, VReg vs2) { opIVI(0b10011110000000111011000001010111, ENCODED, vs2, ENCODED, vd); }
void vmv_s_x(VReg vd, Reg rs1) { opMVX(0b01000010000000000110000001010111, ENCODED, ENCODED, rs1, vd); }
void vmv_v_i(VReg vd, int32_t simm5) { opIVI(0b01011110000000000011000001010111, ENCODED, ENCODED, simm5, vd); }
void vmv_v_v(VReg vd, VReg vs1) { opIVV(0b01011110000000000000000001010111, ENCODED, ENCODED, vs1, vd); }
void vmv_v_x(VReg vd, Reg rs1) { opIVX(0b01011110000000000100000001010111, ENCODED, ENCODED, rs1, vd); }
void vmv_x_s(Reg rd, VReg vs2) { opMVV(0b01000010000000000010000001010111, ENCODED, vs2, ENCODED, rd); }
void vmxnor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01111100000000000010000001010111, vm, vs2, vs1, vd); }
void vmxor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b01101100000000000010000001010111, vm, vs2, vs1, vd); }
void vnclip_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10111100000000000011000001010111, vm, vs2, simm5, vd); }
void vnclip_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10111100000000000000000001010111, vm, vs2, vs1, vd); }
void vnclip_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10111100000000000100000001010111, vm, vs2, rs1, vd); }
void vnclipu_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10111000000000000011000001010111, vm, vs2, simm5, vd); }
void vnclipu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10111000000000000000000001010111, vm, vs2, vs1, vd); }
void vnclipu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10111000000000000100000001010111, vm, vs2, rs1, vd); }
void vnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b10111100000000000010000001010111, vm, vs2, vs1, vd); }
void vnmsac_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b10111100000000000110000001010111, vm, vs2, rs1, vd); }
void vnmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b10101100000000000010000001010111, vm, vs2, vs1, vd); }
void vnmsub_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b10101100000000000110000001010111, vm, vs2, rs1, vd); }
void vnsra_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10110100000000000011000001010111, vm, vs2, simm5, vd); }
void vnsra_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10110100000000000000000001010111, vm, vs2, vs1, vd); }
void vnsra_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10110100000000000100000001010111, vm, vs2, rs1, vd); }
void vnsrl_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10110000000000000011000001010111, vm, vs2, simm5, vd); }
void vnsrl_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10110000000000000000000001010111, vm, vs2, vs1, vd); }
void vnsrl_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10110000000000000100000001010111, vm, vs2, rs1, vd); }
void vor_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00101000000000000011000001010111, vm, vs2, simm5, vd); }
void vor_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00101000000000000000000001010111, vm, vs2, vs1, vd); }
void vor_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00101000000000000100000001010111, vm, vs2, rs1, vd); }
void vredand_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00000100000000000010000001010111, vm, vs2, vs1, vd); }
void vredmax_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00011100000000000010000001010111, vm, vs2, vs1, vd); }
void vredmaxu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00011000000000000010000001010111, vm, vs2, vs1, vd); }
void vredmin_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00010100000000000010000001010111, vm, vs2, vs1, vd); }
void vredminu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00010000000000000010000001010111, vm, vs2, vs1, vd); }
void vredor_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00001000000000000010000001010111, vm, vs2, vs1, vd); }
void vredsum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00000000000000000010000001010111, vm, vs2, vs1, vd); }
void vredxor_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b00001100000000000010000001010111, vm, vs2, vs1, vd); }
void vrem_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10001100000000000010000001010111, vm, vs2, vs1, vd); }
void vrem_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10001100000000000110000001010111, vm, vs2, rs1, vd); }
void vremu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b10001000000000000010000001010111, vm, vs2, vs1, vd); }
void vremu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b10001000000000000110000001010111, vm, vs2, rs1, vd); }
void vrgather_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00110000000000000011000001010111, vm, vs2, simm5, vd); }
void vrgather_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00110000000000000000000001010111, vm, vs2, vs1, vd); }
void vrgather_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00110000000000000100000001010111, vm, vs2, rs1, vd); }
void vrgatherei16_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00111000000000000000000001010111, vm, vs2, vs1, vd); }
void vrsub_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00001100000000000011000001010111, vm, vs2, simm5, vd); }
void vrsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00001100000000000100000001010111, vm, vs2, rs1, vd); }
void vs1r_v(VReg vs3, Reg rs1) { opVectorStore(0b00000010100000000000000000100111, ENCODED, ENCODED, rs1, vs3); }
void vs2r_v(VReg vs3, Reg rs1) { opVectorStore(0b00000010100000000000000000100111, ENCODED, ENCODED, rs1, vs3); }
void vs4r_v(VReg vs3, Reg rs1) { opVectorStore(0b00000010100000000000000000100111, ENCODED, ENCODED, rs1, vs3); }
void vs8r_v(VReg vs3, Reg rs1) { opVectorStore(0b00000010100000000000000000100111, ENCODED, ENCODED, rs1, vs3); }
void vsadd_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10000100000000000011000001010111, vm, vs2, simm5, vd); }
void vsadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10000100000000000000000001010111, vm, vs2, vs1, vd); }
void vsadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10000100000000000100000001010111, vm, vs2, rs1, vd); }
void vsaddu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10000000000000000011000001010111, vm, vs2, simm5, vd); }
void vsaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10000000000000000000000001010111, vm, vs2, vs1, vd); }
void vsaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10000000000000000100000001010111, vm, vs2, rs1, vd); }
void vsbc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0b01001000000000000000000001010111, ENCODED, vs2, vs1, vd); }
void vsbc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0b01001000000000000100000001010111, ENCODED, vs2, rs1, vd); }
void vsseg1e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00110000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01010000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01110000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10010000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10110000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11010000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11110000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vse1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00110000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01010000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01110000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10010000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10110000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11010000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11110000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vse128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00100000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01000000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01100000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10000000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10100000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11000000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11100000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vse16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00110000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01010000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01110000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10010000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10110000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11010000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11110000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vse256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000101000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00100000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01000000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01100000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10000000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10100000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11000000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11100000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vse32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00110000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01010000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01110000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10010000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10110000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11010000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11110000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vse512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00010000000000000110000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00100000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01000000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01100000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10000000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10100000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11000000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11100000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vse64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000111000000100111, vm, ENCODED, rs1, vs3); }
void vsseg1e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg2e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00100000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg3e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01000000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg4e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b01100000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg5e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10000000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg6e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b10100000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg7e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11000000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsseg8e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b11100000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vse8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0b00000000000000000000000000100111, vm, ENCODED, rs1, vs3); }
void vsext_vf2(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000111010000001010111, vm, vs2, ENCODED, vd); }
void vsext_vf4(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000101010000001010111, vm, vs2, ENCODED, vd); }
void vsext_vf8(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000011010000001010111, vm, vs2, ENCODED, vd); }
void vslide1down_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00111100000000000110000001010111, vm, vs2, rs1, vd); }
void vslide1up_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b00111000000000000110000001010111, vm, vs2, rs1, vd); }
void vslidedown_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00111100000000000011000001010111, vm, vs2, simm5, vd); }
void vslidedown_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00111100000000000100000001010111, vm, vs2, rs1, vd); }
void vslideup_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00111000000000000011000001010111, vm, vs2, simm5, vd); }
void vslideup_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00111000000000000100000001010111, vm, vs2, rs1, vd); }
void vsll_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10010100000000000011000001010111, vm, vs2, simm5, vd); }
void vsll_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10010100000000000000000001010111, vm, vs2, vs1, vd); }
void vsll_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10010100000000000100000001010111, vm, vs2, rs1, vd); }
void vsm_v(VReg vs3, Reg rs1) { opVectorStore(0b00000010101100000000000000100111, ENCODED, ENCODED, rs1, vs3); }
void vsmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10011100000000000000000001010111, vm, vs2, vs1, vd); }
void vsmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10011100000000000100000001010111, vm, vs2, rs1, vd); }
void vsoxei1024_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00011100000000000111000000100111, vm, vs2, rs1, vs3); }
void vsoxei128_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00011100000000000000000000100111, vm, vs2, rs1, vs3); }
void vsoxei16_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00001100000000000101000000100111, vm, vs2, rs1, vs3); }
void vsoxei256_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00011100000000000101000000100111, vm, vs2, rs1, vs3); }
void vsoxei32_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00001100000000000110000000100111, vm, vs2, rs1, vs3); }
void vsoxei512_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00011100000000000110000000100111, vm, vs2, rs1, vs3); }
void vsoxei64_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00001100000000000111000000100111, vm, vs2, rs1, vs3); }
void vsoxei8_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00001100000000000000000000100111, vm, vs2, rs1, vs3); }
void vsra_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10100100000000000011000001010111, vm, vs2, simm5, vd); }
void vsra_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10100100000000000000000001010111, vm, vs2, vs1, vd); }
void vsra_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10100100000000000100000001010111, vm, vs2, rs1, vd); }
void vsrl_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10100000000000000011000001010111, vm, vs2, simm5, vd); }
void vsrl_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10100000000000000000000001010111, vm, vs2, vs1, vd); }
void vsrl_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10100000000000000100000001010111, vm, vs2, rs1, vd); }
void vssseg1e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg2e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00111000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg3e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01011000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg4e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01111000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg5e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10011000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg6e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10111000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg7e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11011000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg8e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11111000000000000111000000100111, vm, rs2, rs1, vs3); }
void vsse1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg1e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg2e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00111000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg3e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01011000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg4e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01111000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg5e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10011000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg6e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10111000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg7e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11011000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg8e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11111000000000000000000000100111, vm, rs2, rs1, vs3); }
void vsse128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg1e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg2e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00101000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg3e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01001000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg4e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01101000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg5e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10001000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg6e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10101000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg7e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11001000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg8e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11101000000000000101000000100111, vm, rs2, rs1, vs3); }
void vsse16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg1e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg2e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00111000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg3e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01011000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg4e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01111000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg5e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10011000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg6e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10111000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg7e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11011000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg8e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11111000000000000101000000100111, vm, rs2, rs1, vs3); }
void vsse256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000101000000100111, vm, rs2, rs1, vs3); }
void vssseg1e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg2e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00101000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg3e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01001000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg4e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01101000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg5e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10001000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg6e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10101000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg7e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11001000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg8e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11101000000000000110000000100111, vm, rs2, rs1, vs3); }
void vsse32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg1e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg2e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00111000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg3e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01011000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg4e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01111000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg5e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10011000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg6e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10111000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg7e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11011000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg8e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11111000000000000110000000100111, vm, rs2, rs1, vs3); }
void vsse512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00011000000000000110000000100111, vm, rs2, rs1, vs3); }
void vssseg1e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg2e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00101000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg3e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01001000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg4e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01101000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg5e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10001000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg6e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10101000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg7e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11001000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg8e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11101000000000000111000000100111, vm, rs2, rs1, vs3); }
void vsse64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000111000000100111, vm, rs2, rs1, vs3); }
void vssseg1e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg2e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00101000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg3e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01001000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg4e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b01101000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg5e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10001000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg6e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b10101000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg7e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11001000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssseg8e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b11101000000000000000000000100111, vm, rs2, rs1, vs3); }
void vsse8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0b00001000000000000000000000100111, vm, rs2, rs1, vs3); }
void vssra_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10101100000000000011000001010111, vm, vs2, simm5, vd); }
void vssra_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10101100000000000000000001010111, vm, vs2, vs1, vd); }
void vssra_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10101100000000000100000001010111, vm, vs2, rs1, vd); }
void vssrl_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b10101000000000000011000001010111, vm, vs2, simm5, vd); }
void vssrl_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10101000000000000000000001010111, vm, vs2, vs1, vd); }
void vssrl_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10101000000000000100000001010111, vm, vs2, rs1, vd); }
void vssub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10001100000000000000000001010111, vm, vs2, vs1, vd); }
void vssub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10001100000000000100000001010111, vm, vs2, rs1, vd); }
void vssubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b10001000000000000000000001010111, vm, vs2, vs1, vd); }
void vssubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b10001000000000000100000001010111, vm, vs2, rs1, vd); }
void vsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00001000000000000000000001010111, vm, vs2, vs1, vd); }
void vsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00001000000000000100000001010111, vm, vs2, rs1, vd); }
void vsuxei1024_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00010100000000000111000000100111, vm, vs2, rs1, vs3); }
void vsuxei128_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00010100000000000000000000100111, vm, vs2, rs1, vs3); }
void vsuxei16_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00000100000000000101000000100111, vm, vs2, rs1, vs3); }
void vsuxei256_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00010100000000000101000000100111, vm, vs2, rs1, vs3); }
void vsuxei32_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00000100000000000110000000100111, vm, vs2, rs1, vs3); }
void vsuxei512_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00010100000000000110000000100111, vm, vs2, rs1, vs3); }
void vsuxei64_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00000100000000000111000000100111, vm, vs2, rs1, vs3); }
void vsuxei8_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0b00000100000000000000000000100111, vm, vs2, rs1, vs3); }
void vwadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11000100000000000010000001010111, vm, vs2, vs1, vd); }
void vwadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11000100000000000110000001010111, vm, vs2, rs1, vd); }
void vwadd_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11010100000000000010000001010111, vm, vs2, vs1, vd); }
void vwadd_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11010100000000000110000001010111, vm, vs2, rs1, vd); }
void vwaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11000000000000000010000001010111, vm, vs2, vs1, vd); }
void vwaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11000000000000000110000001010111, vm, vs2, rs1, vd); }
void vwaddu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11010000000000000010000001010111, vm, vs2, vs1, vd); }
void vwaddu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11010000000000000110000001010111, vm, vs2, rs1, vd); }
void vwmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b11110100000000000010000001010111, vm, vs2, vs1, vd); }
void vwmacc_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b11110100000000000110000001010111, vm, vs2, rs1, vd); }
void vwmaccsu_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b11111100000000000010000001010111, vm, vs2, vs1, vd); }
void vwmaccsu_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b11111100000000000110000001010111, vm, vs2, rs1, vd); }
void vwmaccu_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0b11110000000000000010000001010111, vm, vs2, vs1, vd); }
void vwmaccu_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b11110000000000000110000001010111, vm, vs2, rs1, vd); }
void vwmaccus_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0b11111000000000000110000001010111, vm, vs2, rs1, vd); }
void vwmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11101100000000000010000001010111, vm, vs2, vs1, vd); }
void vwmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11101100000000000110000001010111, vm, vs2, rs1, vd); }
void vwmulsu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11101000000000000010000001010111, vm, vs2, vs1, vd); }
void vwmulsu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11101000000000000110000001010111, vm, vs2, rs1, vd); }
void vwmulu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11100000000000000010000001010111, vm, vs2, vs1, vd); }
void vwmulu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11100000000000000110000001010111, vm, vs2, rs1, vd); }
void vwredsum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b11000100000000000000000001010111, vm, vs2, vs1, vd); }
void vwredsumu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b11000000000000000000000001010111, vm, vs2, vs1, vd); }
void vwsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11001100000000000010000001010111, vm, vs2, vs1, vd); }
void vwsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11001100000000000110000001010111, vm, vs2, rs1, vd); }
void vwsub_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11011100000000000010000001010111, vm, vs2, vs1, vd); }
void vwsub_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11011100000000000110000001010111, vm, vs2, rs1, vd); }
void vwsubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11001000000000000010000001010111, vm, vs2, vs1, vd); }
void vwsubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11001000000000000110000001010111, vm, vs2, rs1, vd); }
void vwsubu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0b11011000000000000010000001010111, vm, vs2, vs1, vd); }
void vwsubu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0b11011000000000000110000001010111, vm, vs2, rs1, vd); }
void vxor_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0b00101100000000000011000001010111, vm, vs2, simm5, vd); }
void vxor_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0b00101100000000000000000001010111, vm, vs2, vs1, vd); }
void vxor_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0b00101100000000000100000001010111, vm, vs2, rs1, vd); }
void vzext_vf2(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000110010000001010111, vm, vs2, ENCODED, vd); }
void vzext_vf4(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000100010000001010111, vm, vs2, ENCODED, vd); }
void vzext_vf8(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0b01001000000000010010000001010111, vm, vs2, ENCODED, vd); }

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


void csrrw(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0b00000000000000000001000001110011, csr, rs1, rd); }
void csrrs(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0b00000000000000000010000001110011, csr, rs1, rd); }
void csrrc(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0b00000000000000000011000001110011, csr, rs1, rd); }
void csrrwi(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0b00000000000000000101000001110011, csr, imm, rd); }
void csrrsi(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0b00000000000000000110000001110011, csr, imm, rd); }
void csrrci(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0b00000000000000000111000001110011, csr, imm, rd); }

