#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

struct Code : CodeGenerator {
	Code()
	{
#include "generated.cpp"
		dump(true);
	}
};

int main()
{
	Code c;
}
