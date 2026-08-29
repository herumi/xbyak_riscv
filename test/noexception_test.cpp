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

// a failed allocation must not cause a null pointer write
CYBOZU_TEST_AUTO(alloc_fail)
{
	struct NullAllocator : Allocator {
		uint8_t *alloc(size_t) override { return 0; }
		void free(uint8_t *) override {}
	} a;
	CodeGenerator c(4096, 0, &a);
	CYBOZU_TEST_EQUAL(GetError(), (int)ERR_CANT_ALLOC);
	ClearError();
	c.nop();
	CYBOZU_TEST_EQUAL(GetError(), (int)ERR_CANT_ALLOC);
	ClearError();
}
