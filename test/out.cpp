#define XBYAK_RISCV_TEST
#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

struct Code : CodeGenerator {
	Code()
	{
#include "generated.cpp"
	}
};

int main()
{
	Code c;
}
