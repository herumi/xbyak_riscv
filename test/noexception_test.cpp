#define XBYAK_RISCV_NO_EXCEPTION
#include <cybozu/test.hpp>
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

CYBOZU_TEST_AUTO(imm_too_big)
{
	CodeGenerator c;
	c.addi(x1, x2, 2048);
	CYBOZU_TEST_EQUAL(GetError(), (int)ERR_IMM_IS_TOO_BIG);
	ClearError();
	CYBOZU_TEST_EQUAL(GetError(), 0);
}
