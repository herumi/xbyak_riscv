#define XBYAK_RISCV_VSETV_DEFAULT_OLD 0
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

struct Code : CodeGenerator {
	Code()
		: CodeGenerator(8192)
	{
#include "generated.cpp"
		dump(true);
	}
};

int main()
{
	Code c;
}
