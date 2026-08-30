#include <cybozu/test.hpp>
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

CYBOZU_TEST_AUTO(align)
{
	struct Code : CodeGenerator {
		Code()
		{
			nop();
			addr1 = getCurr();
			align(16);
			addr2 = getCurr();
			nop();
			nop();
			addr3 = getCurr();
			align(16);
			addr4 = getCurr();
			for (int i = 0; i < 4; i++) nop();
			addr5 = getCurr();
			// already aligned
			align(16);
			addr6 = getCurr();

		}
		const uint8_t *addr1;
		const uint8_t *addr2;
		const uint8_t *addr3;
		const uint8_t *addr4;
		const uint8_t *addr5;
		const uint8_t *addr6;
	} c;
	c.ready();
	printf("addr1=%p\n", c.addr1);
	printf("addr2=%p\n", c.addr2);
	printf("addr3=%p\n", c.addr3);
	printf("addr4=%p\n", c.addr4);
	printf("addr5=%p\n", c.addr5);
	printf("addr6=%p\n", c.addr6);
	CYBOZU_TEST_ASSERT(size_t(c.addr1) % 16);
	CYBOZU_TEST_ASSERT((size_t(c.addr2) % 16) == 0);
	CYBOZU_TEST_ASSERT(size_t(c.addr3) % 16);
	CYBOZU_TEST_ASSERT((size_t(c.addr4) % 16) == 0);
	CYBOZU_TEST_ASSERT((size_t(c.addr5) % 16) == 0);
	CYBOZU_TEST_EQUAL(c.addr5, c.addr6);
}



// reset() must restore write access after readyRE()/setProtectModeRE()
CYBOZU_TEST_AUTO(reset_after_readyRE)
{
	{
		CodeGenerator c;
		c.nop();
		c.readyRE();
		c.reset();
		c.nop();
		CYBOZU_TEST_EQUAL(c.getSize(), 4u);
	}
	{
		CodeGenerator c(4096, DontSetProtectRWE);
		c.nop();
		c.setProtectModeRE();
		c.reset();
		c.nop();
		CYBOZU_TEST_EQUAL(c.getSize(), 4u);
	}
}

static uint32_t read4ByteLE(const uint8_t *p)
{
	return p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);
}

// li takes a 64-bit immediate (gas compatible) ; RV32 accepts a 32-bit value
CYBOZU_TEST_AUTO(li)
{
	// RV64
	{
		CodeGenerator c;
		c.li(x1, 0x80000000); // addi x1, x0, 1 ; slli x1, x1, 31
		CYBOZU_TEST_EQUAL(c.getSize(), 8u);
		CYBOZU_TEST_EQUAL(read4ByteLE(c.getCode()), 0x00100093u);
		CYBOZU_TEST_EQUAL(read4ByteLE(c.getCode() + 4), 0x01f09093u);
	}
	{
		CodeGenerator c;
		c.li(x1, 0xffffffff80000000); // lui x1, 0x80000
		CYBOZU_TEST_EQUAL(c.getSize(), 4u);
		CYBOZU_TEST_EQUAL(read4ByteLE(c.getCode()), 0x800000b7u);
	}
	// RV32 : the same as RV64 for a sign-extended 32-bit value
	{
		CodeGenerator c;
		c.setRV32();
		c.li(x1, 0x80000000); // lui x1, 0x80000
		c.li(x1, 0xffffffff80000000); // lui x1, 0x80000
		c.li(x1, 0xffffffff); // addi x1, x0, -1
		c.li(x1, -1); // addi x1, x0, -1
		c.li(x1, 0x12345678); // lui x1, 0x12345 ; addi x1, x1, 0x678
		CYBOZU_TEST_EQUAL(c.getSize(), 24u);
		const uint32_t expected[] = { 0x800000b7, 0x800000b7, 0xfff00093, 0xfff00093, 0x123450b7, 0x67808093 };
		for (size_t i = 0; i < 6; i++) {
			CYBOZU_TEST_EQUAL(read4ByteLE(c.getCode() + i * 4), expected[i]);
		}
		// not a 32-bit value
		CYBOZU_TEST_EXCEPTION(c.li(x1, 0x100000000), std::exception);
		CYBOZU_TEST_EXCEPTION(c.li(x1, 0xfffffffe80000000), std::exception);
	}
}
