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


