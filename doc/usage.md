# Usage

Inherit `Xbyak_riscv::CodeGenerator` class and make the class method.

```cpp
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
```

The constructor of `Code` class generates a function that takes two integers, x and y, and returns x + y + v.
Calling `ready()` completes the code generation process.
`c.getCode<int (*)(int,int)>()` returns the function pointer and you can use it.

# Registers

Register|ABI Name
-|-
x0|zero
x1|ra
x2|sp
x3|gp
x4|tp
x5|t0
x6-7|t1-2
x8|s0/fp
x9|s1
x10-11|a0-1
x12-17|a2-7
x18-27|s2-11
x28-31|t3-6

These names are defined in the `Xbyak_riscv` namespace.
