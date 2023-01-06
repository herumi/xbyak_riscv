#include <xbyak_riscv/xbyak_riscv.hpp>

using namespace Xbyak_riscv;

struct Code : CodeGenerator {
	Code(int v)
	{
		add(a0, a0, a1);
		addi(a0, a0, v);
		ret();
	}
};

int main()
{
	const int v1 = 5;
	const int v2 = 7;
	const int v3 = 9;
	Code c(v1);
	c.ready();
	auto f = c.getCode<int (*)(int, int)>();
	int v = f(v2, v3);
	printf("%d+%d+%d=%d(%s)\n", v1, v2, v3, v, v == v1 + v2 + v3 ? "ok" : "ng");
}

