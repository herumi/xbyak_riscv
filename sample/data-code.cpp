#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

static const size_t dataSize = 4096;
static const size_t codeSize = 4096;

/*
	+--------+
	|data(RW)| dataSize
	+--------+
	|code(RE)| codeSize
	+--------+
*/

struct Generator : public CodeGenerator {
    Generator()
		: CodeGenerator(dataSize + codeSize, DontSetProtectRWE)
	{
		// data from here
		dataTop = const_cast<uint8_t*>(getCurr());
		Label d1L, d2L;
		L(d1L);
        append4B(123000);
		L(d2L);
        append4B(456);

		// set the other data

		setSize(dataSize);

		// code from here
        codeTop = getCurr<uint32_t(*)(uint8_t *data)>();

        const Reg &dataTop = a2;
		mv(dataTop, a0);
        lw(a0, dataTop, getOffset(d1L));
		lw(a1, dataTop, getOffset(d2L));
		add(a0, a0, a1);
        ret();
    }
	uint32_t getOffset(const Label& L) const
	{
		return L.getAddress() - dataTop;
	}
	uint8_t* dataTop;
	uint32_t (*codeTop)(uint8_t *data);
};


int main()
	try
{
    Generator gen;
    gen.ready();
	CodeArray::protect((void*)gen.codeTop, codeSize, CodeArray::PROTECT_RE);
	printf("data=%p\n", gen.dataTop);
	printf("code=%p\n", gen.codeTop);
    printf("exec = %d\n", gen.codeTop(gen.dataTop));
} catch (std::exception& e) {
	printf("err %s\n", e.what());
	return 1;
}

