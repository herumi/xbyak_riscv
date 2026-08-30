#define XBYAK_RISCV_LI_OLD
#include <cybozu/test.hpp>
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

static uint32_t read4ByteLE(const uint8_t *p)
{
	return p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);
}

// XBYAK_RISCV_LI_OLD : li takes a 32-bit immediate and it is sign-extended on RV64
CYBOZU_TEST_AUTO(li_old)
{
	CodeGenerator c;
	c.li(x1, 0x80000000); // lui x1, 0x80000
	c.li(x1, 0xffffffff); // addi x1, x0, -1
	c.li(x1, 0x12345678); // lui x1, 0x12345 ; addiw x1, x1, 0x678
	CYBOZU_TEST_EQUAL(c.getSize(), 16u);
	const uint32_t expected[] = { 0x800000b7, 0xfff00093, 0x123450b7, 0x6780809b };
	for (size_t i = 0; i < 4; i++) {
		CYBOZU_TEST_EQUAL(read4ByteLE(c.getCode() + i * 4), expected[i]);
	}
}
