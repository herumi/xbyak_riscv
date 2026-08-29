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
	std::cout << std::hex;
	const size_t codeSize = 4 /*nop*/ * 3 + sizeof(size_t)/*label*/ * 2;
	CYBOZU_TEST_EQUAL(c.getSize(), codeSize);
	uint32_t nop = 0x00000013;
	const uint8_t *p = c.getCode();
	CYBOZU_TEST_EQUAL(read4ByteLE(p), nop);
	CYBOZU_TEST_EQUAL(read4ByteLE(p + 4), nop);
	CYBOZU_TEST_EQUAL(readBytesLE(p + 8), c.Faddr);
	CYBOZU_TEST_EQUAL(read4ByteLE(p + 8 + sizeof(size_t)), nop);
	CYBOZU_TEST_EQUAL(readBytesLE(p + 8 + sizeof(size_t) + 4), c.Baddr);
	std::cout << std::dec;
}



// assignL(dst, src) where dst has not been referenced yet
CYBOZU_TEST_AUTO(assignL_unreferenced_dst)
{
	struct Code : CodeGenerator {
		Code()
		{
			Label src, dst;
			L(src);
			assignL(dst, src);
			CYBOZU_TEST_EQUAL(dst.getAddress(), src.getAddress());
			jal(x0, dst); // backward reference must be resolved
			CYBOZU_TEST_ASSERT(!hasUndefinedLabel());
			// a second assignL with another unreferenced dst must not throw ERR_LABEL_IS_REDEFINED
			Label dst2;
			assignL(dst2, src);
			CYBOZU_TEST_EQUAL(dst2.getAddress(), src.getAddress());
		}
	} c;
	c.ready();
	const uint8_t *p = c.getCode();
	CYBOZU_TEST_EQUAL(read4ByteLE(p), 0x0000006f); // jal x0, 0
}

// assignL(dst, src) after a forward reference to dst
CYBOZU_TEST_AUTO(assignL_forward_ref)
{
	struct Code : CodeGenerator {
		size_t srcAddr;
		Code()
		{
			Label src, dst;
			jal(x0, dst);      // +0
			beq(x1, x2, dst);  // +4
			putL(dst);         // +8
			L(src);            // +8+sizeof(size_t)
			srcAddr = size_t(src.getAddress());
			nop();
			nop();
			assignL(dst, src); // dst must point to src, not here
			CYBOZU_TEST_EQUAL(dst.getAddress(), src.getAddress());
		}
	} c;
	c.ready();
	const uint8_t *p = c.getCode();
	const uint32_t off = 8 + sizeof(size_t);
	// jal x0, off : imm[20|10:1|11|19:12] = (off>>1)<<21
	CYBOZU_TEST_EQUAL(read4ByteLE(p), ((off >> 1) << 21) | 0x6f);
	// beq x1, x2, off-4 : imm[4:1] at [11:8]
	const uint32_t boff = off - 4;
	CYBOZU_TEST_EQUAL(read4ByteLE(p + 4), (((boff >> 1) & 0xf) << 8) | (2 << 20) | (1 << 15) | 0x63);
	CYBOZU_TEST_EQUAL(readBytesLE(p + 8), c.srcAddr);
}
