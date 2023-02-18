
/*
	Copyright (C), 2023, MITSUNARI Shigeo
	Copyright (C), 2023, KNS Group LLC (YADRO)
	Licensed under the 3-Clause BSD License
	You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
*/

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

void vaadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x24002057, vm, vs2, vs1, vd); }
void vaadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x24006057, vm, vs2, rs1, vd); }
void vaaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x20002057, vm, vs2, vs1, vd); }
void vaaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x20006057, vm, vs2, rs1, vd); }
void vadc_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0x40003057, 0, vs2, simm5, vd); }
void vadc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0x40000057, 0, vs2, vs1, vd); }
void vadc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0x40004057, 0, vs2, rs1, vd); }
void vadd_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x3057, vm, vs2, simm5, vd); }
void vadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x57, vm, vs2, vs1, vd); }
void vadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x4057, vm, vs2, rs1, vd); }
void vand_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x24003057, vm, vs2, simm5, vd); }
void vand_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x24000057, vm, vs2, vs1, vd); }
void vand_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x24004057, vm, vs2, rs1, vd); }
void vasub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x2c002057, vm, vs2, vs1, vd); }
void vasub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x2c006057, vm, vs2, rs1, vd); }
void vasubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x28002057, vm, vs2, vs1, vd); }
void vasubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x28006057, vm, vs2, rs1, vd); }
void vcompress_vm(VReg vd, VReg vs2, VReg vs1) { opMVV(0x5e002057, 0, vs2, vs1, vd); }
void vcpop_m(Reg rd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x40082057, vm, vs2, 0, rd); }
void vdiv_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x84002057, vm, vs2, vs1, vd); }
void vdiv_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x84006057, vm, vs2, rs1, vd); }
void vdivu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x80002057, vm, vs2, vs1, vd); }
void vdivu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x80006057, vm, vs2, rs1, vd); }
void vfadd_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x5057, vm, vs2, rs1, vd); }
void vfadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x1057, vm, vs2, vs1, vd); }
void vfclass_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x4c081057, vm, vs2, 0, vd); }
void vfcvt_f_x_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48019057, vm, vs2, 0, vd); }
void vfcvt_f_xu_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48011057, vm, vs2, 0, vd); }
void vfcvt_rtz_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48039057, vm, vs2, 0, vd); }
void vfcvt_rtz_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48031057, vm, vs2, 0, vd); }
void vfcvt_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48009057, vm, vs2, 0, vd); }
void vfcvt_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48001057, vm, vs2, 0, vd); }
void vfdiv_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x80005057, vm, vs2, rs1, vd); }
void vfdiv_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x80001057, vm, vs2, vs1, vd); }
void vfirst_m(Reg rd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x4008a057, vm, vs2, 0, rd); }
void vfmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xb0005057, vm, vs2, rs1, vd); }
void vfmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xb0001057, vm, vs2, vs1, vd); }
void vfmadd_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xa0005057, vm, vs2, rs1, vd); }
void vfmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xa0001057, vm, vs2, vs1, vd); }
void vfmax_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x18005057, vm, vs2, rs1, vd); }
void vfmax_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x18001057, vm, vs2, vs1, vd); }
void vfmerge_vfm(VReg vd, VReg vs2, FReg rs1) { opFVF(0x5c005057, 0, vs2, rs1, vd); }
void vfmin_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x10005057, vm, vs2, rs1, vd); }
void vfmin_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x10001057, vm, vs2, vs1, vd); }
void vfmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xb8005057, vm, vs2, rs1, vd); }
void vfmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xb8001057, vm, vs2, vs1, vd); }
void vfmsub_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xa8005057, vm, vs2, rs1, vd); }
void vfmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xa8001057, vm, vs2, vs1, vd); }
void vfmul_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x90005057, vm, vs2, rs1, vd); }
void vfmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x90001057, vm, vs2, vs1, vd); }
void vfmv_f_s(FReg rd, VReg vs2) { opFVV(0x42001057, 0, vs2, 0, rd); }
void vfmv_s_f(VReg vd, FReg rs1) { opFVF(0x42005057, 0, 0, rs1, vd); }
void vfmv_v_f(VReg vd, FReg rs1) { opFVF(0x5e005057, 0, 0, rs1, vd); }
void vfncvt_f_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x480a1057, vm, vs2, 0, vd); }
void vfncvt_f_x_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48099057, vm, vs2, 0, vd); }
void vfncvt_f_xu_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48091057, vm, vs2, 0, vd); }
void vfncvt_rod_f_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x480a9057, vm, vs2, 0, vd); }
void vfncvt_rtz_x_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x480b9057, vm, vs2, 0, vd); }
void vfncvt_rtz_xu_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x480b1057, vm, vs2, 0, vd); }
void vfncvt_x_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48089057, vm, vs2, 0, vd); }
void vfncvt_xu_f_w(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48081057, vm, vs2, 0, vd); }
void vfnmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xb4005057, vm, vs2, rs1, vd); }
void vfnmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xb4001057, vm, vs2, vs1, vd); }
void vfnmadd_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xa4005057, vm, vs2, rs1, vd); }
void vfnmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xa4001057, vm, vs2, vs1, vd); }
void vfnmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xbc005057, vm, vs2, rs1, vd); }
void vfnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xbc001057, vm, vs2, vs1, vd); }
void vfnmsub_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xac005057, vm, vs2, rs1, vd); }
void vfnmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xac001057, vm, vs2, vs1, vd); }
void vfrdiv_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x84005057, vm, vs2, rs1, vd); }
void vfrec7_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x4c029057, vm, vs2, 0, vd); }
void vfredmax_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x1c001057, vm, vs2, vs1, vd); }
void vfredmin_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x14001057, vm, vs2, vs1, vd); }
void vfredosum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xc001057, vm, vs2, vs1, vd); }
void vfredusum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x4001057, vm, vs2, vs1, vd); }
void vfrsqrt7_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x4c021057, vm, vs2, 0, vd); }
void vfrsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x9c005057, vm, vs2, rs1, vd); }
void vfsgnj_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x20005057, vm, vs2, rs1, vd); }
void vfsgnj_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x20001057, vm, vs2, vs1, vd); }
void vfsgnjn_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x24005057, vm, vs2, rs1, vd); }
void vfsgnjn_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x24001057, vm, vs2, vs1, vd); }
void vfsgnjx_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x28005057, vm, vs2, rs1, vd); }
void vfsgnjx_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x28001057, vm, vs2, vs1, vd); }
void vfslide1down_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x3c005057, vm, vs2, rs1, vd); }
void vfslide1up_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x38005057, vm, vs2, rs1, vd); }
void vfsqrt_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x4c001057, vm, vs2, 0, vd); }
void vfsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x8005057, vm, vs2, rs1, vd); }
void vfsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x8001057, vm, vs2, vs1, vd); }
void vfwadd_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0xc0005057, vm, vs2, rs1, vd); }
void vfwadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xc0001057, vm, vs2, vs1, vd); }
void vfwadd_wf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0xd0005057, vm, vs2, rs1, vd); }
void vfwadd_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xd0001057, vm, vs2, vs1, vd); }
void vfwcvt_f_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48061057, vm, vs2, 0, vd); }
void vfwcvt_f_x_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48059057, vm, vs2, 0, vd); }
void vfwcvt_f_xu_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48051057, vm, vs2, 0, vd); }
void vfwcvt_rtz_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48079057, vm, vs2, 0, vd); }
void vfwcvt_rtz_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48071057, vm, vs2, 0, vd); }
void vfwcvt_x_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48049057, vm, vs2, 0, vd); }
void vfwcvt_xu_f_v(VReg vd, VReg vs2, VM vm=VM::unmasked) { opFVV(0x48041057, vm, vs2, 0, vd); }
void vfwmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xf0005057, vm, vs2, rs1, vd); }
void vfwmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xf0001057, vm, vs2, vs1, vd); }
void vfwmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xf8005057, vm, vs2, rs1, vd); }
void vfwmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xf8001057, vm, vs2, vs1, vd); }
void vfwmul_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0xe0005057, vm, vs2, rs1, vd); }
void vfwmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xe0001057, vm, vs2, vs1, vd); }
void vfwnmacc_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xf4005057, vm, vs2, rs1, vd); }
void vfwnmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xf4001057, vm, vs2, vs1, vd); }
void vfwnmsac_vf(VReg vd, FReg rs1, VReg vs2, VM vm=VM::unmasked) { opFVF(0xfc005057, vm, vs2, rs1, vd); }
void vfwnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opFVV(0xfc001057, vm, vs2, vs1, vd); }
void vfwredosum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xcc001057, vm, vs2, vs1, vd); }
void vfwredusum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xc4001057, vm, vs2, vs1, vd); }
void vfwsub_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0xc8005057, vm, vs2, rs1, vd); }
void vfwsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xc8001057, vm, vs2, vs1, vd); }
void vfwsub_wf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0xd8005057, vm, vs2, rs1, vd); }
void vfwsub_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0xd8001057, vm, vs2, vs1, vd); }
void vid_v(VReg vd, VM vm=VM::unmasked) { opMVV(0x5008a057, vm, 0, 0, vd); }
void viota_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x50082057, vm, vs2, 0, vd); }
void vl1re16_v(VReg vd, Reg rs1) { opVectorLoad(0x2805007, 0, 0, rs1, vd); }
void vl1re32_v(VReg vd, Reg rs1) { opVectorLoad(0x2806007, 0, 0, rs1, vd); }
void vl1re64_v(VReg vd, Reg rs1) { opVectorLoad(0x2807007, 0, 0, rs1, vd); }
void vl1re8_v(VReg vd, Reg rs1) { opVectorLoad(0x2800007, 0, 0, rs1, vd); }
void vl2re16_v(VReg vd, Reg rs1) { opVectorLoad(0x2805007, 0, 0, rs1, vd); }
void vl2re32_v(VReg vd, Reg rs1) { opVectorLoad(0x2806007, 0, 0, rs1, vd); }
void vl2re64_v(VReg vd, Reg rs1) { opVectorLoad(0x2807007, 0, 0, rs1, vd); }
void vl2re8_v(VReg vd, Reg rs1) { opVectorLoad(0x2800007, 0, 0, rs1, vd); }
void vl4re16_v(VReg vd, Reg rs1) { opVectorLoad(0x2805007, 0, 0, rs1, vd); }
void vl4re32_v(VReg vd, Reg rs1) { opVectorLoad(0x2806007, 0, 0, rs1, vd); }
void vl4re64_v(VReg vd, Reg rs1) { opVectorLoad(0x2807007, 0, 0, rs1, vd); }
void vl4re8_v(VReg vd, Reg rs1) { opVectorLoad(0x2800007, 0, 0, rs1, vd); }
void vl8re16_v(VReg vd, Reg rs1) { opVectorLoad(0x2805007, 0, 0, rs1, vd); }
void vl8re32_v(VReg vd, Reg rs1) { opVectorLoad(0x2806007, 0, 0, rs1, vd); }
void vl8re64_v(VReg vd, Reg rs1) { opVectorLoad(0x2807007, 0, 0, rs1, vd); }
void vl8re8_v(VReg vd, Reg rs1) { opVectorLoad(0x2800007, 0, 0, rs1, vd); }
void vlseg1e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10007007, vm, 0, rs1, vd); }
void vlseg2e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x30007007, vm, 0, rs1, vd); }
void vlseg3e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x50007007, vm, 0, rs1, vd); }
void vlseg4e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x70007007, vm, 0, rs1, vd); }
void vlseg5e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x90007007, vm, 0, rs1, vd); }
void vlseg6e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb0007007, vm, 0, rs1, vd); }
void vlseg7e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd0007007, vm, 0, rs1, vd); }
void vlseg8e1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf0007007, vm, 0, rs1, vd); }
void vle1024_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10007007, vm, 0, rs1, vd); }
void vlseg1e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11007007, vm, 0, rs1, vd); }
void vlseg2e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x31007007, vm, 0, rs1, vd); }
void vlseg3e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x51007007, vm, 0, rs1, vd); }
void vlseg4e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x71007007, vm, 0, rs1, vd); }
void vlseg5e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x91007007, vm, 0, rs1, vd); }
void vlseg6e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb1007007, vm, 0, rs1, vd); }
void vlseg7e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd1007007, vm, 0, rs1, vd); }
void vlseg8e1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf1007007, vm, 0, rs1, vd); }
void vle1024ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11007007, vm, 0, rs1, vd); }
void vlseg1e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10000007, vm, 0, rs1, vd); }
void vlseg2e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x30000007, vm, 0, rs1, vd); }
void vlseg3e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x50000007, vm, 0, rs1, vd); }
void vlseg4e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x70000007, vm, 0, rs1, vd); }
void vlseg5e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x90000007, vm, 0, rs1, vd); }
void vlseg6e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb0000007, vm, 0, rs1, vd); }
void vlseg7e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd0000007, vm, 0, rs1, vd); }
void vlseg8e128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf0000007, vm, 0, rs1, vd); }
void vle128_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10000007, vm, 0, rs1, vd); }
void vlseg1e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11000007, vm, 0, rs1, vd); }
void vlseg2e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x31000007, vm, 0, rs1, vd); }
void vlseg3e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x51000007, vm, 0, rs1, vd); }
void vlseg4e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x71000007, vm, 0, rs1, vd); }
void vlseg5e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x91000007, vm, 0, rs1, vd); }
void vlseg6e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb1000007, vm, 0, rs1, vd); }
void vlseg7e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd1000007, vm, 0, rs1, vd); }
void vlseg8e128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf1000007, vm, 0, rs1, vd); }
void vle128ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11000007, vm, 0, rs1, vd); }
void vlseg1e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x5007, vm, 0, rs1, vd); }
void vlseg2e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x20005007, vm, 0, rs1, vd); }
void vlseg3e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x40005007, vm, 0, rs1, vd); }
void vlseg4e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x60005007, vm, 0, rs1, vd); }
void vlseg5e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x80005007, vm, 0, rs1, vd); }
void vlseg6e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa0005007, vm, 0, rs1, vd); }
void vlseg7e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc0005007, vm, 0, rs1, vd); }
void vlseg8e16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe0005007, vm, 0, rs1, vd); }
void vle16_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x5007, vm, 0, rs1, vd); }
void vlseg1e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1005007, vm, 0, rs1, vd); }
void vlseg2e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x21005007, vm, 0, rs1, vd); }
void vlseg3e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x41005007, vm, 0, rs1, vd); }
void vlseg4e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x61005007, vm, 0, rs1, vd); }
void vlseg5e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x81005007, vm, 0, rs1, vd); }
void vlseg6e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa1005007, vm, 0, rs1, vd); }
void vlseg7e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc1005007, vm, 0, rs1, vd); }
void vlseg8e16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe1005007, vm, 0, rs1, vd); }
void vle16ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1005007, vm, 0, rs1, vd); }
void vlseg1e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10005007, vm, 0, rs1, vd); }
void vlseg2e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x30005007, vm, 0, rs1, vd); }
void vlseg3e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x50005007, vm, 0, rs1, vd); }
void vlseg4e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x70005007, vm, 0, rs1, vd); }
void vlseg5e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x90005007, vm, 0, rs1, vd); }
void vlseg6e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb0005007, vm, 0, rs1, vd); }
void vlseg7e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd0005007, vm, 0, rs1, vd); }
void vlseg8e256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf0005007, vm, 0, rs1, vd); }
void vle256_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10005007, vm, 0, rs1, vd); }
void vlseg1e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11005007, vm, 0, rs1, vd); }
void vlseg2e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x31005007, vm, 0, rs1, vd); }
void vlseg3e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x51005007, vm, 0, rs1, vd); }
void vlseg4e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x71005007, vm, 0, rs1, vd); }
void vlseg5e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x91005007, vm, 0, rs1, vd); }
void vlseg6e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb1005007, vm, 0, rs1, vd); }
void vlseg7e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd1005007, vm, 0, rs1, vd); }
void vlseg8e256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf1005007, vm, 0, rs1, vd); }
void vle256ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11005007, vm, 0, rs1, vd); }
void vlseg1e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x6007, vm, 0, rs1, vd); }
void vlseg2e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x20006007, vm, 0, rs1, vd); }
void vlseg3e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x40006007, vm, 0, rs1, vd); }
void vlseg4e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x60006007, vm, 0, rs1, vd); }
void vlseg5e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x80006007, vm, 0, rs1, vd); }
void vlseg6e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa0006007, vm, 0, rs1, vd); }
void vlseg7e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc0006007, vm, 0, rs1, vd); }
void vlseg8e32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe0006007, vm, 0, rs1, vd); }
void vle32_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x6007, vm, 0, rs1, vd); }
void vlseg1e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1006007, vm, 0, rs1, vd); }
void vlseg2e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x21006007, vm, 0, rs1, vd); }
void vlseg3e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x41006007, vm, 0, rs1, vd); }
void vlseg4e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x61006007, vm, 0, rs1, vd); }
void vlseg5e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x81006007, vm, 0, rs1, vd); }
void vlseg6e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa1006007, vm, 0, rs1, vd); }
void vlseg7e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc1006007, vm, 0, rs1, vd); }
void vlseg8e32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe1006007, vm, 0, rs1, vd); }
void vle32ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1006007, vm, 0, rs1, vd); }
void vlseg1e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10006007, vm, 0, rs1, vd); }
void vlseg2e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x30006007, vm, 0, rs1, vd); }
void vlseg3e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x50006007, vm, 0, rs1, vd); }
void vlseg4e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x70006007, vm, 0, rs1, vd); }
void vlseg5e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x90006007, vm, 0, rs1, vd); }
void vlseg6e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb0006007, vm, 0, rs1, vd); }
void vlseg7e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd0006007, vm, 0, rs1, vd); }
void vlseg8e512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf0006007, vm, 0, rs1, vd); }
void vle512_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x10006007, vm, 0, rs1, vd); }
void vlseg1e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11006007, vm, 0, rs1, vd); }
void vlseg2e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x31006007, vm, 0, rs1, vd); }
void vlseg3e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x51006007, vm, 0, rs1, vd); }
void vlseg4e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x71006007, vm, 0, rs1, vd); }
void vlseg5e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x91006007, vm, 0, rs1, vd); }
void vlseg6e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xb1006007, vm, 0, rs1, vd); }
void vlseg7e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xd1006007, vm, 0, rs1, vd); }
void vlseg8e512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xf1006007, vm, 0, rs1, vd); }
void vle512ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x11006007, vm, 0, rs1, vd); }
void vlseg1e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x7007, vm, 0, rs1, vd); }
void vlseg2e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x20007007, vm, 0, rs1, vd); }
void vlseg3e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x40007007, vm, 0, rs1, vd); }
void vlseg4e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x60007007, vm, 0, rs1, vd); }
void vlseg5e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x80007007, vm, 0, rs1, vd); }
void vlseg6e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa0007007, vm, 0, rs1, vd); }
void vlseg7e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc0007007, vm, 0, rs1, vd); }
void vlseg8e64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe0007007, vm, 0, rs1, vd); }
void vle64_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x7007, vm, 0, rs1, vd); }
void vlseg1e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1007007, vm, 0, rs1, vd); }
void vlseg2e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x21007007, vm, 0, rs1, vd); }
void vlseg3e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x41007007, vm, 0, rs1, vd); }
void vlseg4e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x61007007, vm, 0, rs1, vd); }
void vlseg5e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x81007007, vm, 0, rs1, vd); }
void vlseg6e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa1007007, vm, 0, rs1, vd); }
void vlseg7e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc1007007, vm, 0, rs1, vd); }
void vlseg8e64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe1007007, vm, 0, rs1, vd); }
void vle64ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1007007, vm, 0, rs1, vd); }
void vlseg1e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x7, vm, 0, rs1, vd); }
void vlseg2e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x20000007, vm, 0, rs1, vd); }
void vlseg3e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x40000007, vm, 0, rs1, vd); }
void vlseg4e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x60000007, vm, 0, rs1, vd); }
void vlseg5e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x80000007, vm, 0, rs1, vd); }
void vlseg6e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa0000007, vm, 0, rs1, vd); }
void vlseg7e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc0000007, vm, 0, rs1, vd); }
void vlseg8e8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe0000007, vm, 0, rs1, vd); }
void vle8_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x7, vm, 0, rs1, vd); }
void vlseg1e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1000007, vm, 0, rs1, vd); }
void vlseg2e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x21000007, vm, 0, rs1, vd); }
void vlseg3e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x41000007, vm, 0, rs1, vd); }
void vlseg4e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x61000007, vm, 0, rs1, vd); }
void vlseg5e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x81000007, vm, 0, rs1, vd); }
void vlseg6e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xa1000007, vm, 0, rs1, vd); }
void vlseg7e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xc1000007, vm, 0, rs1, vd); }
void vlseg8e8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0xe1000007, vm, 0, rs1, vd); }
void vle8ff_v(VReg vd, Reg rs1, VM vm=VM::unmasked) { opVectorLoad(0x1000007, vm, 0, rs1, vd); }
void vlm_v(VReg vd, Reg rs1) { opVectorLoad(0x2b00007, 0, 0, rs1, vd); }
void vloxei1024_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x1c007007, vm, vs2, rs1, vd); }
void vloxei128_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x1c000007, vm, vs2, rs1, vd); }
void vloxei16_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0xc005007, vm, vs2, rs1, vd); }
void vloxei256_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x1c005007, vm, vs2, rs1, vd); }
void vloxei32_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0xc006007, vm, vs2, rs1, vd); }
void vloxei512_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x1c006007, vm, vs2, rs1, vd); }
void vloxei64_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0xc007007, vm, vs2, rs1, vd); }
void vloxei8_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0xc000007, vm, vs2, rs1, vd); }
void vlsseg1e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18007007, vm, rs2, rs1, vd); }
void vlsseg2e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x38007007, vm, rs2, rs1, vd); }
void vlsseg3e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x58007007, vm, rs2, rs1, vd); }
void vlsseg4e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x78007007, vm, rs2, rs1, vd); }
void vlsseg5e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x98007007, vm, rs2, rs1, vd); }
void vlsseg6e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xb8007007, vm, rs2, rs1, vd); }
void vlsseg7e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xd8007007, vm, rs2, rs1, vd); }
void vlsseg8e1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xf8007007, vm, rs2, rs1, vd); }
void vlse1024_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18007007, vm, rs2, rs1, vd); }
void vlsseg1e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18000007, vm, rs2, rs1, vd); }
void vlsseg2e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x38000007, vm, rs2, rs1, vd); }
void vlsseg3e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x58000007, vm, rs2, rs1, vd); }
void vlsseg4e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x78000007, vm, rs2, rs1, vd); }
void vlsseg5e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x98000007, vm, rs2, rs1, vd); }
void vlsseg6e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xb8000007, vm, rs2, rs1, vd); }
void vlsseg7e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xd8000007, vm, rs2, rs1, vd); }
void vlsseg8e128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xf8000007, vm, rs2, rs1, vd); }
void vlse128_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18000007, vm, rs2, rs1, vd); }
void vlsseg1e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8005007, vm, rs2, rs1, vd); }
void vlsseg2e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x28005007, vm, rs2, rs1, vd); }
void vlsseg3e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x48005007, vm, rs2, rs1, vd); }
void vlsseg4e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x68005007, vm, rs2, rs1, vd); }
void vlsseg5e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x88005007, vm, rs2, rs1, vd); }
void vlsseg6e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xa8005007, vm, rs2, rs1, vd); }
void vlsseg7e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xc8005007, vm, rs2, rs1, vd); }
void vlsseg8e16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xe8005007, vm, rs2, rs1, vd); }
void vlse16_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8005007, vm, rs2, rs1, vd); }
void vlsseg1e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18005007, vm, rs2, rs1, vd); }
void vlsseg2e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x38005007, vm, rs2, rs1, vd); }
void vlsseg3e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x58005007, vm, rs2, rs1, vd); }
void vlsseg4e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x78005007, vm, rs2, rs1, vd); }
void vlsseg5e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x98005007, vm, rs2, rs1, vd); }
void vlsseg6e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xb8005007, vm, rs2, rs1, vd); }
void vlsseg7e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xd8005007, vm, rs2, rs1, vd); }
void vlsseg8e256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xf8005007, vm, rs2, rs1, vd); }
void vlse256_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18005007, vm, rs2, rs1, vd); }
void vlsseg1e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8006007, vm, rs2, rs1, vd); }
void vlsseg2e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x28006007, vm, rs2, rs1, vd); }
void vlsseg3e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x48006007, vm, rs2, rs1, vd); }
void vlsseg4e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x68006007, vm, rs2, rs1, vd); }
void vlsseg5e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x88006007, vm, rs2, rs1, vd); }
void vlsseg6e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xa8006007, vm, rs2, rs1, vd); }
void vlsseg7e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xc8006007, vm, rs2, rs1, vd); }
void vlsseg8e32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xe8006007, vm, rs2, rs1, vd); }
void vlse32_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8006007, vm, rs2, rs1, vd); }
void vlsseg1e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18006007, vm, rs2, rs1, vd); }
void vlsseg2e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x38006007, vm, rs2, rs1, vd); }
void vlsseg3e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x58006007, vm, rs2, rs1, vd); }
void vlsseg4e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x78006007, vm, rs2, rs1, vd); }
void vlsseg5e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x98006007, vm, rs2, rs1, vd); }
void vlsseg6e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xb8006007, vm, rs2, rs1, vd); }
void vlsseg7e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xd8006007, vm, rs2, rs1, vd); }
void vlsseg8e512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xf8006007, vm, rs2, rs1, vd); }
void vlse512_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x18006007, vm, rs2, rs1, vd); }
void vlsseg1e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8007007, vm, rs2, rs1, vd); }
void vlsseg2e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x28007007, vm, rs2, rs1, vd); }
void vlsseg3e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x48007007, vm, rs2, rs1, vd); }
void vlsseg4e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x68007007, vm, rs2, rs1, vd); }
void vlsseg5e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x88007007, vm, rs2, rs1, vd); }
void vlsseg6e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xa8007007, vm, rs2, rs1, vd); }
void vlsseg7e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xc8007007, vm, rs2, rs1, vd); }
void vlsseg8e64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xe8007007, vm, rs2, rs1, vd); }
void vlse64_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8007007, vm, rs2, rs1, vd); }
void vlsseg1e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8000007, vm, rs2, rs1, vd); }
void vlsseg2e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x28000007, vm, rs2, rs1, vd); }
void vlsseg3e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x48000007, vm, rs2, rs1, vd); }
void vlsseg4e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x68000007, vm, rs2, rs1, vd); }
void vlsseg5e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x88000007, vm, rs2, rs1, vd); }
void vlsseg6e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xa8000007, vm, rs2, rs1, vd); }
void vlsseg7e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xc8000007, vm, rs2, rs1, vd); }
void vlsseg8e8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0xe8000007, vm, rs2, rs1, vd); }
void vlse8_v(VReg vd, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorLoad(0x8000007, vm, rs2, rs1, vd); }
void vluxei1024_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x14007007, vm, vs2, rs1, vd); }
void vluxei128_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x14000007, vm, vs2, rs1, vd); }
void vluxei16_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x4005007, vm, vs2, rs1, vd); }
void vluxei256_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x14005007, vm, vs2, rs1, vd); }
void vluxei32_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x4006007, vm, vs2, rs1, vd); }
void vluxei512_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x14006007, vm, vs2, rs1, vd); }
void vluxei64_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x4007007, vm, vs2, rs1, vd); }
void vluxei8_v(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorLoad(0x4000007, vm, vs2, rs1, vd); }
void vmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xb4002057, vm, vs2, vs1, vd); }
void vmacc_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xb4006057, vm, vs2, rs1, vd); }
void vmadc_vi(VReg vd, VReg vs2, int32_t simm5) { opIVI(0x46003057, 0, vs2, simm5, vd); }
void vmadc_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0x44003057, 0, vs2, simm5, vd); }
void vmadc_vv(VReg vd, VReg vs2, VReg vs1) { opIVV(0x46000057, 0, vs2, vs1, vd); }
void vmadc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0x44000057, 0, vs2, vs1, vd); }
void vmadc_vx(VReg vd, VReg vs2, Reg rs1) { opIVX(0x46004057, 0, vs2, rs1, vd); }
void vmadc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0x44004057, 0, vs2, rs1, vd); }
void vmadd_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xa4002057, vm, vs2, vs1, vd); }
void vmadd_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xa4006057, vm, vs2, rs1, vd); }
void vmand_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x64002057, vm, vs2, vs1, vd); }
void vmandn_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x60002057, vm, vs2, vs1, vd); }
void vmax_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x1c000057, vm, vs2, vs1, vd); }
void vmax_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x1c004057, vm, vs2, rs1, vd); }
void vmaxu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x18000057, vm, vs2, vs1, vd); }
void vmaxu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x18004057, vm, vs2, rs1, vd); }
void vmerge_vim(VReg vd, VReg vs2, int32_t simm5) { opIVI(0x5c003057, 0, vs2, simm5, vd); }
void vmerge_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0x5c000057, 0, vs2, vs1, vd); }
void vmerge_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0x5c004057, 0, vs2, rs1, vd); }
void vmfeq_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x60005057, vm, vs2, rs1, vd); }
void vmfeq_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x60001057, vm, vs2, vs1, vd); }
void vmfge_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x7c005057, vm, vs2, rs1, vd); }
void vmfgt_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x74005057, vm, vs2, rs1, vd); }
void vmfle_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x64005057, vm, vs2, rs1, vd); }
void vmfle_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x64001057, vm, vs2, vs1, vd); }
void vmflt_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x6c005057, vm, vs2, rs1, vd); }
void vmflt_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x6c001057, vm, vs2, vs1, vd); }
void vmfne_vf(VReg vd, VReg vs2, FReg rs1, VM vm=VM::unmasked) { opFVF(0x70005057, vm, vs2, rs1, vd); }
void vmfne_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opFVV(0x70001057, vm, vs2, vs1, vd); }
void vmin_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x14000057, vm, vs2, vs1, vd); }
void vmin_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x14004057, vm, vs2, rs1, vd); }
void vminu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x10000057, vm, vs2, vs1, vd); }
void vminu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x10004057, vm, vs2, rs1, vd); }
void vmnand_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x74002057, vm, vs2, vs1, vd); }
void vmnor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x78002057, vm, vs2, vs1, vd); }
void vmor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x68002057, vm, vs2, vs1, vd); }
void vmorn_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x70002057, vm, vs2, vs1, vd); }
void vmsbc_vv(VReg vd, VReg vs2, VReg vs1) { opIVV(0x4e000057, 0, vs2, vs1, vd); }
void vmsbc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0x4c000057, 0, vs2, vs1, vd); }
void vmsbc_vx(VReg vd, VReg vs2, Reg rs1) { opIVX(0x4e004057, 0, vs2, rs1, vd); }
void vmsbc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0x4c004057, 0, vs2, rs1, vd); }
void vmsbf_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x5000a057, vm, vs2, 0, vd); }
void vmseq_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x60003057, vm, vs2, simm5, vd); }
void vmseq_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x60000057, vm, vs2, vs1, vd); }
void vmseq_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x60004057, vm, vs2, rs1, vd); }
void vmsgt_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x7c003057, vm, vs2, simm5, vd); }
void vmsgt_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x7c004057, vm, vs2, rs1, vd); }
void vmsgtu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x78003057, vm, vs2, simm5, vd); }
void vmsgtu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x78004057, vm, vs2, rs1, vd); }
void vmsif_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x5001a057, vm, vs2, 0, vd); }
void vmsle_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x74003057, vm, vs2, simm5, vd); }
void vmsle_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x74000057, vm, vs2, vs1, vd); }
void vmsle_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x74004057, vm, vs2, rs1, vd); }
void vmsleu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x70003057, vm, vs2, simm5, vd); }
void vmsleu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x70000057, vm, vs2, vs1, vd); }
void vmsleu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x70004057, vm, vs2, rs1, vd); }
void vmslt_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x6c000057, vm, vs2, vs1, vd); }
void vmslt_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x6c004057, vm, vs2, rs1, vd); }
void vmsltu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x68000057, vm, vs2, vs1, vd); }
void vmsltu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x68004057, vm, vs2, rs1, vd); }
void vmsne_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x64003057, vm, vs2, simm5, vd); }
void vmsne_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x64000057, vm, vs2, vs1, vd); }
void vmsne_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x64004057, vm, vs2, rs1, vd); }
void vmsof_m(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x50012057, vm, vs2, 0, vd); }
void vmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x94002057, vm, vs2, vs1, vd); }
void vmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x94006057, vm, vs2, rs1, vd); }
void vmulh_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x9c002057, vm, vs2, vs1, vd); }
void vmulh_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x9c006057, vm, vs2, rs1, vd); }
void vmulhsu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x98002057, vm, vs2, vs1, vd); }
void vmulhsu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x98006057, vm, vs2, rs1, vd); }
void vmulhu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x90002057, vm, vs2, vs1, vd); }
void vmulhu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x90006057, vm, vs2, rs1, vd); }
void vmv1r_v(VReg vd, VReg vs2) { opIVI(0x9e003057, 0, vs2, 0, vd); }
void vmv2r_v(VReg vd, VReg vs2) { opIVI(0x9e00b057, 0, vs2, 0, vd); }
void vmv4r_v(VReg vd, VReg vs2) { opIVI(0x9e01b057, 0, vs2, 0, vd); }
void vmv8r_v(VReg vd, VReg vs2) { opIVI(0x9e03b057, 0, vs2, 0, vd); }
void vmv_s_x(VReg vd, Reg rs1) { opMVX(0x42006057, 0, 0, rs1, vd); }
void vmv_v_i(VReg vd, int32_t simm5) { opIVI(0x5e003057, 0, 0, simm5, vd); }
void vmv_v_v(VReg vd, VReg vs1) { opIVV(0x5e000057, 0, 0, vs1, vd); }
void vmv_v_x(VReg vd, Reg rs1) { opIVX(0x5e004057, 0, 0, rs1, vd); }
void vmv_x_s(Reg rd, VReg vs2) { opMVV(0x42002057, 0, vs2, 0, rd); }
void vmxnor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x7c002057, vm, vs2, vs1, vd); }
void vmxor_mm(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x6c002057, vm, vs2, vs1, vd); }
void vnclip_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xbc003057, vm, vs2, simm5, vd); }
void vnclip_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xbc000057, vm, vs2, vs1, vd); }
void vnclip_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xbc004057, vm, vs2, rs1, vd); }
void vnclipu_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xb8003057, vm, vs2, simm5, vd); }
void vnclipu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xb8000057, vm, vs2, vs1, vd); }
void vnclipu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xb8004057, vm, vs2, rs1, vd); }
void vnmsac_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xbc002057, vm, vs2, vs1, vd); }
void vnmsac_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xbc006057, vm, vs2, rs1, vd); }
void vnmsub_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xac002057, vm, vs2, vs1, vd); }
void vnmsub_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xac006057, vm, vs2, rs1, vd); }
void vnsra_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xb4003057, vm, vs2, simm5, vd); }
void vnsra_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xb4000057, vm, vs2, vs1, vd); }
void vnsra_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xb4004057, vm, vs2, rs1, vd); }
void vnsrl_wi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xb0003057, vm, vs2, simm5, vd); }
void vnsrl_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xb0000057, vm, vs2, vs1, vd); }
void vnsrl_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xb0004057, vm, vs2, rs1, vd); }
void vor_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x28003057, vm, vs2, simm5, vd); }
void vor_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x28000057, vm, vs2, vs1, vd); }
void vor_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x28004057, vm, vs2, rs1, vd); }
void vredand_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x4002057, vm, vs2, vs1, vd); }
void vredmax_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x1c002057, vm, vs2, vs1, vd); }
void vredmaxu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x18002057, vm, vs2, vs1, vd); }
void vredmin_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x14002057, vm, vs2, vs1, vd); }
void vredminu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x10002057, vm, vs2, vs1, vd); }
void vredor_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x8002057, vm, vs2, vs1, vd); }
void vredsum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x2057, vm, vs2, vs1, vd); }
void vredxor_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xc002057, vm, vs2, vs1, vd); }
void vrem_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x8c002057, vm, vs2, vs1, vd); }
void vrem_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x8c006057, vm, vs2, rs1, vd); }
void vremu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0x88002057, vm, vs2, vs1, vd); }
void vremu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x88006057, vm, vs2, rs1, vd); }
void vrgather_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x30003057, vm, vs2, simm5, vd); }
void vrgather_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x30000057, vm, vs2, vs1, vd); }
void vrgather_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x30004057, vm, vs2, rs1, vd); }
void vrgatherei16_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x38000057, vm, vs2, vs1, vd); }
void vrsub_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xc003057, vm, vs2, simm5, vd); }
void vrsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xc004057, vm, vs2, rs1, vd); }
void vs1r_v(VReg vs3, Reg rs1) { opVectorStore(0x2800027, 0, 0, rs1, vs3); }
void vs2r_v(VReg vs3, Reg rs1) { opVectorStore(0x2800027, 0, 0, rs1, vs3); }
void vs4r_v(VReg vs3, Reg rs1) { opVectorStore(0x2800027, 0, 0, rs1, vs3); }
void vs8r_v(VReg vs3, Reg rs1) { opVectorStore(0x2800027, 0, 0, rs1, vs3); }
void vsadd_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x84003057, vm, vs2, simm5, vd); }
void vsadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x84000057, vm, vs2, vs1, vd); }
void vsadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x84004057, vm, vs2, rs1, vd); }
void vsaddu_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x80003057, vm, vs2, simm5, vd); }
void vsaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x80000057, vm, vs2, vs1, vd); }
void vsaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x80004057, vm, vs2, rs1, vd); }
void vsbc_vvm(VReg vd, VReg vs2, VReg vs1) { opIVV(0x48000057, 0, vs2, vs1, vd); }
void vsbc_vxm(VReg vd, VReg vs2, Reg rs1) { opIVX(0x48004057, 0, vs2, rs1, vd); }
void vsseg1e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10007027, vm, 0, rs1, vs3); }
void vsseg2e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x30007027, vm, 0, rs1, vs3); }
void vsseg3e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x50007027, vm, 0, rs1, vs3); }
void vsseg4e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x70007027, vm, 0, rs1, vs3); }
void vsseg5e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x90007027, vm, 0, rs1, vs3); }
void vsseg6e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xb0007027, vm, 0, rs1, vs3); }
void vsseg7e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xd0007027, vm, 0, rs1, vs3); }
void vsseg8e1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xf0007027, vm, 0, rs1, vs3); }
void vse1024_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10007027, vm, 0, rs1, vs3); }
void vsseg1e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10000027, vm, 0, rs1, vs3); }
void vsseg2e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x30000027, vm, 0, rs1, vs3); }
void vsseg3e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x50000027, vm, 0, rs1, vs3); }
void vsseg4e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x70000027, vm, 0, rs1, vs3); }
void vsseg5e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x90000027, vm, 0, rs1, vs3); }
void vsseg6e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xb0000027, vm, 0, rs1, vs3); }
void vsseg7e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xd0000027, vm, 0, rs1, vs3); }
void vsseg8e128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xf0000027, vm, 0, rs1, vs3); }
void vse128_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10000027, vm, 0, rs1, vs3); }
void vsseg1e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x5027, vm, 0, rs1, vs3); }
void vsseg2e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x20005027, vm, 0, rs1, vs3); }
void vsseg3e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x40005027, vm, 0, rs1, vs3); }
void vsseg4e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x60005027, vm, 0, rs1, vs3); }
void vsseg5e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x80005027, vm, 0, rs1, vs3); }
void vsseg6e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xa0005027, vm, 0, rs1, vs3); }
void vsseg7e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xc0005027, vm, 0, rs1, vs3); }
void vsseg8e16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xe0005027, vm, 0, rs1, vs3); }
void vse16_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x5027, vm, 0, rs1, vs3); }
void vsseg1e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10005027, vm, 0, rs1, vs3); }
void vsseg2e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x30005027, vm, 0, rs1, vs3); }
void vsseg3e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x50005027, vm, 0, rs1, vs3); }
void vsseg4e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x70005027, vm, 0, rs1, vs3); }
void vsseg5e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x90005027, vm, 0, rs1, vs3); }
void vsseg6e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xb0005027, vm, 0, rs1, vs3); }
void vsseg7e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xd0005027, vm, 0, rs1, vs3); }
void vsseg8e256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xf0005027, vm, 0, rs1, vs3); }
void vse256_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10005027, vm, 0, rs1, vs3); }
void vsseg1e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x6027, vm, 0, rs1, vs3); }
void vsseg2e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x20006027, vm, 0, rs1, vs3); }
void vsseg3e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x40006027, vm, 0, rs1, vs3); }
void vsseg4e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x60006027, vm, 0, rs1, vs3); }
void vsseg5e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x80006027, vm, 0, rs1, vs3); }
void vsseg6e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xa0006027, vm, 0, rs1, vs3); }
void vsseg7e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xc0006027, vm, 0, rs1, vs3); }
void vsseg8e32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xe0006027, vm, 0, rs1, vs3); }
void vse32_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x6027, vm, 0, rs1, vs3); }
void vsseg1e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10006027, vm, 0, rs1, vs3); }
void vsseg2e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x30006027, vm, 0, rs1, vs3); }
void vsseg3e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x50006027, vm, 0, rs1, vs3); }
void vsseg4e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x70006027, vm, 0, rs1, vs3); }
void vsseg5e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x90006027, vm, 0, rs1, vs3); }
void vsseg6e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xb0006027, vm, 0, rs1, vs3); }
void vsseg7e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xd0006027, vm, 0, rs1, vs3); }
void vsseg8e512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xf0006027, vm, 0, rs1, vs3); }
void vse512_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x10006027, vm, 0, rs1, vs3); }
void vsseg1e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x7027, vm, 0, rs1, vs3); }
void vsseg2e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x20007027, vm, 0, rs1, vs3); }
void vsseg3e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x40007027, vm, 0, rs1, vs3); }
void vsseg4e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x60007027, vm, 0, rs1, vs3); }
void vsseg5e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x80007027, vm, 0, rs1, vs3); }
void vsseg6e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xa0007027, vm, 0, rs1, vs3); }
void vsseg7e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xc0007027, vm, 0, rs1, vs3); }
void vsseg8e64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xe0007027, vm, 0, rs1, vs3); }
void vse64_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x7027, vm, 0, rs1, vs3); }
void vsseg1e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x27, vm, 0, rs1, vs3); }
void vsseg2e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x20000027, vm, 0, rs1, vs3); }
void vsseg3e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x40000027, vm, 0, rs1, vs3); }
void vsseg4e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x60000027, vm, 0, rs1, vs3); }
void vsseg5e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x80000027, vm, 0, rs1, vs3); }
void vsseg6e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xa0000027, vm, 0, rs1, vs3); }
void vsseg7e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xc0000027, vm, 0, rs1, vs3); }
void vsseg8e8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0xe0000027, vm, 0, rs1, vs3); }
void vse8_v(VReg vs3, Reg rs1, VM vm=VM::unmasked) { opVectorStore(0x27, vm, 0, rs1, vs3); }
void vsext_vf2(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x4803a057, vm, vs2, 0, vd); }
void vsext_vf4(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x4802a057, vm, vs2, 0, vd); }
void vsext_vf8(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x4801a057, vm, vs2, 0, vd); }
void vslide1down_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x3c006057, vm, vs2, rs1, vd); }
void vslide1up_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0x38006057, vm, vs2, rs1, vd); }
void vslidedown_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x3c003057, vm, vs2, simm5, vd); }
void vslidedown_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x3c004057, vm, vs2, rs1, vd); }
void vslideup_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x38003057, vm, vs2, simm5, vd); }
void vslideup_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x38004057, vm, vs2, rs1, vd); }
void vsll_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x94003057, vm, vs2, simm5, vd); }
void vsll_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x94000057, vm, vs2, vs1, vd); }
void vsll_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x94004057, vm, vs2, rs1, vd); }
void vsm_v(VReg vs3, Reg rs1) { opVectorStore(0x2b00027, 0, 0, rs1, vs3); }
void vsmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x9c000057, vm, vs2, vs1, vd); }
void vsmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x9c004057, vm, vs2, rs1, vd); }
void vsoxei1024_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x1c007027, vm, vs2, rs1, vs3); }
void vsoxei128_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x1c000027, vm, vs2, rs1, vs3); }
void vsoxei16_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0xc005027, vm, vs2, rs1, vs3); }
void vsoxei256_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x1c005027, vm, vs2, rs1, vs3); }
void vsoxei32_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0xc006027, vm, vs2, rs1, vs3); }
void vsoxei512_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x1c006027, vm, vs2, rs1, vs3); }
void vsoxei64_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0xc007027, vm, vs2, rs1, vs3); }
void vsoxei8_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0xc000027, vm, vs2, rs1, vs3); }
void vsra_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xa4003057, vm, vs2, simm5, vd); }
void vsra_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xa4000057, vm, vs2, vs1, vd); }
void vsra_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xa4004057, vm, vs2, rs1, vd); }
void vsrl_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xa0003057, vm, vs2, simm5, vd); }
void vsrl_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xa0000057, vm, vs2, vs1, vd); }
void vsrl_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xa0004057, vm, vs2, rs1, vd); }
void vssseg1e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18007027, vm, rs2, rs1, vs3); }
void vssseg2e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x38007027, vm, rs2, rs1, vs3); }
void vssseg3e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x58007027, vm, rs2, rs1, vs3); }
void vssseg4e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x78007027, vm, rs2, rs1, vs3); }
void vssseg5e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x98007027, vm, rs2, rs1, vs3); }
void vssseg6e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xb8007027, vm, rs2, rs1, vs3); }
void vssseg7e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xd8007027, vm, rs2, rs1, vs3); }
void vssseg8e1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xf8007027, vm, rs2, rs1, vs3); }
void vsse1024_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18007027, vm, rs2, rs1, vs3); }
void vssseg1e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18000027, vm, rs2, rs1, vs3); }
void vssseg2e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x38000027, vm, rs2, rs1, vs3); }
void vssseg3e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x58000027, vm, rs2, rs1, vs3); }
void vssseg4e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x78000027, vm, rs2, rs1, vs3); }
void vssseg5e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x98000027, vm, rs2, rs1, vs3); }
void vssseg6e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xb8000027, vm, rs2, rs1, vs3); }
void vssseg7e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xd8000027, vm, rs2, rs1, vs3); }
void vssseg8e128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xf8000027, vm, rs2, rs1, vs3); }
void vsse128_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18000027, vm, rs2, rs1, vs3); }
void vssseg1e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8005027, vm, rs2, rs1, vs3); }
void vssseg2e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x28005027, vm, rs2, rs1, vs3); }
void vssseg3e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x48005027, vm, rs2, rs1, vs3); }
void vssseg4e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x68005027, vm, rs2, rs1, vs3); }
void vssseg5e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x88005027, vm, rs2, rs1, vs3); }
void vssseg6e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xa8005027, vm, rs2, rs1, vs3); }
void vssseg7e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xc8005027, vm, rs2, rs1, vs3); }
void vssseg8e16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xe8005027, vm, rs2, rs1, vs3); }
void vsse16_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8005027, vm, rs2, rs1, vs3); }
void vssseg1e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18005027, vm, rs2, rs1, vs3); }
void vssseg2e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x38005027, vm, rs2, rs1, vs3); }
void vssseg3e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x58005027, vm, rs2, rs1, vs3); }
void vssseg4e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x78005027, vm, rs2, rs1, vs3); }
void vssseg5e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x98005027, vm, rs2, rs1, vs3); }
void vssseg6e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xb8005027, vm, rs2, rs1, vs3); }
void vssseg7e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xd8005027, vm, rs2, rs1, vs3); }
void vssseg8e256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xf8005027, vm, rs2, rs1, vs3); }
void vsse256_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18005027, vm, rs2, rs1, vs3); }
void vssseg1e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8006027, vm, rs2, rs1, vs3); }
void vssseg2e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x28006027, vm, rs2, rs1, vs3); }
void vssseg3e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x48006027, vm, rs2, rs1, vs3); }
void vssseg4e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x68006027, vm, rs2, rs1, vs3); }
void vssseg5e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x88006027, vm, rs2, rs1, vs3); }
void vssseg6e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xa8006027, vm, rs2, rs1, vs3); }
void vssseg7e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xc8006027, vm, rs2, rs1, vs3); }
void vssseg8e32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xe8006027, vm, rs2, rs1, vs3); }
void vsse32_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8006027, vm, rs2, rs1, vs3); }
void vssseg1e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18006027, vm, rs2, rs1, vs3); }
void vssseg2e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x38006027, vm, rs2, rs1, vs3); }
void vssseg3e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x58006027, vm, rs2, rs1, vs3); }
void vssseg4e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x78006027, vm, rs2, rs1, vs3); }
void vssseg5e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x98006027, vm, rs2, rs1, vs3); }
void vssseg6e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xb8006027, vm, rs2, rs1, vs3); }
void vssseg7e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xd8006027, vm, rs2, rs1, vs3); }
void vssseg8e512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xf8006027, vm, rs2, rs1, vs3); }
void vsse512_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x18006027, vm, rs2, rs1, vs3); }
void vssseg1e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8007027, vm, rs2, rs1, vs3); }
void vssseg2e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x28007027, vm, rs2, rs1, vs3); }
void vssseg3e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x48007027, vm, rs2, rs1, vs3); }
void vssseg4e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x68007027, vm, rs2, rs1, vs3); }
void vssseg5e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x88007027, vm, rs2, rs1, vs3); }
void vssseg6e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xa8007027, vm, rs2, rs1, vs3); }
void vssseg7e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xc8007027, vm, rs2, rs1, vs3); }
void vssseg8e64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xe8007027, vm, rs2, rs1, vs3); }
void vsse64_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8007027, vm, rs2, rs1, vs3); }
void vssseg1e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8000027, vm, rs2, rs1, vs3); }
void vssseg2e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x28000027, vm, rs2, rs1, vs3); }
void vssseg3e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x48000027, vm, rs2, rs1, vs3); }
void vssseg4e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x68000027, vm, rs2, rs1, vs3); }
void vssseg5e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x88000027, vm, rs2, rs1, vs3); }
void vssseg6e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xa8000027, vm, rs2, rs1, vs3); }
void vssseg7e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xc8000027, vm, rs2, rs1, vs3); }
void vssseg8e8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0xe8000027, vm, rs2, rs1, vs3); }
void vsse8_v(VReg vs3, Reg rs1, Reg rs2, VM vm=VM::unmasked) { opVectorStore(0x8000027, vm, rs2, rs1, vs3); }
void vssra_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xac003057, vm, vs2, simm5, vd); }
void vssra_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xac000057, vm, vs2, vs1, vd); }
void vssra_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xac004057, vm, vs2, rs1, vd); }
void vssrl_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0xa8003057, vm, vs2, simm5, vd); }
void vssrl_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xa8000057, vm, vs2, vs1, vd); }
void vssrl_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0xa8004057, vm, vs2, rs1, vd); }
void vssub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x8c000057, vm, vs2, vs1, vd); }
void vssub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x8c004057, vm, vs2, rs1, vd); }
void vssubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x88000057, vm, vs2, vs1, vd); }
void vssubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x88004057, vm, vs2, rs1, vd); }
void vsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x8000057, vm, vs2, vs1, vd); }
void vsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x8004057, vm, vs2, rs1, vd); }
void vsuxei1024_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x14007027, vm, vs2, rs1, vs3); }
void vsuxei128_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x14000027, vm, vs2, rs1, vs3); }
void vsuxei16_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x4005027, vm, vs2, rs1, vs3); }
void vsuxei256_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x14005027, vm, vs2, rs1, vs3); }
void vsuxei32_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x4006027, vm, vs2, rs1, vs3); }
void vsuxei512_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x14006027, vm, vs2, rs1, vs3); }
void vsuxei64_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x4007027, vm, vs2, rs1, vs3); }
void vsuxei8_v(VReg vs3, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opVectorStore(0x4000027, vm, vs2, rs1, vs3); }
void vwadd_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xc4002057, vm, vs2, vs1, vd); }
void vwadd_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xc4006057, vm, vs2, rs1, vd); }
void vwadd_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xd4002057, vm, vs2, vs1, vd); }
void vwadd_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xd4006057, vm, vs2, rs1, vd); }
void vwaddu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xc0002057, vm, vs2, vs1, vd); }
void vwaddu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xc0006057, vm, vs2, rs1, vd); }
void vwaddu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xd0002057, vm, vs2, vs1, vd); }
void vwaddu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xd0006057, vm, vs2, rs1, vd); }
void vwmacc_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xf4002057, vm, vs2, vs1, vd); }
void vwmacc_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xf4006057, vm, vs2, rs1, vd); }
void vwmaccsu_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xfc002057, vm, vs2, vs1, vd); }
void vwmaccsu_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xfc006057, vm, vs2, rs1, vd); }
void vwmaccu_vv(VReg vd, VReg vs1, VReg vs2, VM vm=VM::unmasked) { opMVV(0xf0002057, vm, vs2, vs1, vd); }
void vwmaccu_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xf0006057, vm, vs2, rs1, vd); }
void vwmaccus_vx(VReg vd, Reg rs1, VReg vs2, VM vm=VM::unmasked) { opMVX(0xf8006057, vm, vs2, rs1, vd); }
void vwmul_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xec002057, vm, vs2, vs1, vd); }
void vwmul_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xec006057, vm, vs2, rs1, vd); }
void vwmulsu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xe8002057, vm, vs2, vs1, vd); }
void vwmulsu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xe8006057, vm, vs2, rs1, vd); }
void vwmulu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xe0002057, vm, vs2, vs1, vd); }
void vwmulu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xe0006057, vm, vs2, rs1, vd); }
void vwredsum_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xc4000057, vm, vs2, vs1, vd); }
void vwredsumu_vs(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0xc0000057, vm, vs2, vs1, vd); }
void vwsub_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xcc002057, vm, vs2, vs1, vd); }
void vwsub_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xcc006057, vm, vs2, rs1, vd); }
void vwsub_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xdc002057, vm, vs2, vs1, vd); }
void vwsub_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xdc006057, vm, vs2, rs1, vd); }
void vwsubu_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xc8002057, vm, vs2, vs1, vd); }
void vwsubu_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xc8006057, vm, vs2, rs1, vd); }
void vwsubu_wv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opMVV(0xd8002057, vm, vs2, vs1, vd); }
void vwsubu_wx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opMVX(0xd8006057, vm, vs2, rs1, vd); }
void vxor_vi(VReg vd, VReg vs2, int32_t simm5, VM vm=VM::unmasked) { opIVI(0x2c003057, vm, vs2, simm5, vd); }
void vxor_vv(VReg vd, VReg vs2, VReg vs1, VM vm=VM::unmasked) { opIVV(0x2c000057, vm, vs2, vs1, vd); }
void vxor_vx(VReg vd, VReg vs2, Reg rs1, VM vm=VM::unmasked) { opIVX(0x2c004057, vm, vs2, rs1, vd); }
void vzext_vf2(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x48032057, vm, vs2, 0, vd); }
void vzext_vf4(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x48022057, vm, vs2, 0, vd); }
void vzext_vf8(VReg vd, VReg vs2, VM vm=VM::unmasked) { opMVV(0x48012057, vm, vs2, 0, vd); }

void vsetivli(const Reg& rd, uint32_t uimm, SEW sew, LMUL lmul=LMUL::m1, VTA vta=VTA::tu, VMA vma=VMA::mu) {
    uint32_t zimm = (static_cast<uint32_t>(vma)<<7) |
                    (static_cast<uint32_t>(vta)<<6) |
                    (static_cast<uint32_t>(sew)<<3) |
                    (static_cast<uint32_t>(lmul));
    uint32_t v = (0x3<<30) | (zimm<<20) | (uimm<<15) | (0x7<<12) | (rd.getIdx()<<7) | (0x57);
    append4B(v);
}

void vsetvli(const Reg& rd, const Reg& rs1, SEW sew, LMUL lmul=LMUL::m1, VTA vta=VTA::tu, VMA vma=VMA::mu) {
    uint32_t zimm = (static_cast<uint32_t>(vma)<<7) |
                    (static_cast<uint32_t>(vta)<<6) |
                    (static_cast<uint32_t>(sew)<<3) |
                    (static_cast<uint32_t>(lmul));
    uint32_t v = (0x0<<31) | (zimm<<20) | (rs1.getIdx()<<15) | (0x7<<12) | (rd.getIdx()<<7) | (0x57);
    append4B(v);
}

void vsetvl(const Reg& rd, const Reg& rs1, const Reg& rs2) {
    uint32_t v = (0x40<<25) | (rs2.getIdx()<<20) | (rs1.getIdx()<<15) | (0x7<<12) | (rd.getIdx()<<7) | (0x57);
    append4B(v);
}


void csrrw(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0x1073, csr, rs1, rd); }
void csrrs(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0x2073, csr, rs1, rd); }
void csrrc(const Reg& rd, CSR csr, const Reg& rs1) { opCSR(0x3073, csr, rs1, rd); }
void csrrwi(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0x5073, csr, imm, rd); }
void csrrsi(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0x6073, csr, imm, rd); }
void csrrci(const Reg& rd, CSR csr, uint32_t imm) { opCSR(0x7073, csr, imm, rd); }

