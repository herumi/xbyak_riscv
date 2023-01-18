#include <cybozu/test.hpp>
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

uint32_t read4ByteLE(const uint8_t *p)
{
	return p[0] | (p[1]<<8) | (p[2]<<16) | (p[3]<<24);
}

uint64_t read8ByteLE(const uint8_t *p)
{
	return read4ByteLE(p) | (uint64_t(read4ByteLE(p + 4))<<32);
}

size_t readBytesLE(const uint8_t *p)
{
	if (sizeof(size_t) == 4) return read4ByteLE(p);
	return read8ByteLE(p);
}

CYBOZU_TEST_AUTO(putL)
{
	struct Code : CodeGenerator {
		size_t Faddr;
		size_t Baddr;
		Code()
		{
			nop();
			Label F, B;
			F = L();
			Faddr = size_t(F.getAddress());
			nop();
			putL(F);
			nop();
			putL(B);
			L(B);
			Baddr = size_t(B.getAddress());
		}
	} c;
	c.ready();
	const size_t codeSize = 4 /*nop*/ * 3 + sizeof(size_t)/*label*/ * 2;
	CYBOZU_TEST_EQUAL(c.getSize(), codeSize);
	uint32_t nop = 0x00000013;
	const uint8_t *p = c.getCode();
	CYBOZU_TEST_EQUAL(read4ByteLE(p), nop);
	CYBOZU_TEST_EQUAL(read4ByteLE(p + 4), nop);
	CYBOZU_TEST_EQUAL(readBytesLE(p + 8), c.Faddr);
	CYBOZU_TEST_EQUAL(read4ByteLE(p + 8 + sizeof(size_t)), nop);
	CYBOZU_TEST_EQUAL(readBytesLE(p + 8 + sizeof(size_t) + 4), c.Baddr);
}


