#include <fstream>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <xbyak_riscv/xbyak_riscv.hpp>

class Brainfuck : public Xbyak_riscv::CodeGenerator {
public:
	int getContinuousChar(std::istream &is, char c) {
		int count = 1;
		char p;
		while (is >> p) {
			if (p != c)
				break;
			count++;
		}
		is.unget();
		return count;
	}
	Brainfuck(std::istream &is) : CodeGenerator(100000) {
		// void (*)(void* putchar, void* getchar, int *stack)
		using namespace Xbyak_riscv;
		const auto &pPutchar = s2;
		const auto &pGetchar = s3;
		const auto &stack = s4;
		const int saveSize = 16*2;
		addi(sp, sp, -saveSize);
		sd(pPutchar, sp, 8);
		sd(pGetchar, sp, 16);
		sd(stack, sp, 24);
		sd(ra, sp, 32);

		mv(pPutchar, a0);
		mv(pGetchar, a1);
		mv(stack, a2);

		std::stack<Label> labelF, labelB;
		char c;
		while (is >> c) {
			switch (c) {
			case '+':
			case '-': {
				int count = getContinuousChar(is, c);
				ld(a0, stack);
				// QQQ : not support large count
				if (c == '+') {
					addi(a0, a0, count);
				} else {
					addi(a0, a0, -count);
				}
				sd(a0, stack);
			} break;
			case '>':
			case '<': {
				int count = getContinuousChar(is, c) * 8;
				if (c == '>') {
					addi(stack, stack, count);
				} else {
					addi(stack, stack, -count);
				}
			} break;
			case '.':
				ld(a0, stack);
				jalr(pPutchar);
				break;
			case ',':
				jalr(pGetchar);
				sd(a0, stack);
				break;
			case '[': {
				Label B = L();
				labelB.push(B);
				ld(a0, stack);
				Label F;
				beq(a0, x0, F);
				labelF.push(F);
			} break;
			case ']': {
				Label B = labelB.top();
				labelB.pop();
				j_(B);
				Label F = labelF.top();
				labelF.pop();
				L(F);
			} break;
			default:
				break;
			}
		}

		ld(ra, sp, 32);
		ld(stack, sp, 24);
		ld(pGetchar, sp, 16);
		ld(pPutchar, sp, 8);
		addi(sp, sp, saveSize);
		ret();
	}
};

int main(int argc, char *argv[]) try {
	if (argc < 2) {
		fprintf(stderr, "bf filename.bf [-d]\n");
		return 1;
	}
	bool doDump = argc == 3 && strcmp(argv[2], "-d") == 0;
	std::ifstream ifs(argv[1]);
	Brainfuck bf(ifs);
	bf.ready();
	static int64_t stack[128 * 1024];
	auto f = bf.getCode<void (*)(const void *, const void *, int64_t *)>();
	if (doDump) {
		FILE *fp = fopen("bf.dump", "wb");
		fwrite((const void*)f, bf.getSize(), 1, fp);
		fclose(fp);
	}
	f((const void *)putchar, (const void *)getchar, stack);
} catch (std::exception &e) {
	printf("ERR:%s\n", e.what());
	return 1;
}
