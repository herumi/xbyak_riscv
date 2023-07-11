/******************************************************************************
* Copyright (C), 2023, KNS Group LLC (YADRO)
*
* Licensed under the 3-Clause BSD License
* You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
*******************************************************************************/

#include <xbyak_riscv/xbyak_riscv.hpp>
#include <xbyak_riscv/xbyak_riscv_util.hpp>
#include <cstdlib>
#include <iostream>
#include <vector>
#include <random>

using namespace Xbyak_riscv;

std::vector<float> generateRandomF32Vector(size_t size, float minValue=-1000.0, float maxValue=1000.0) {
    std::random_device random_device;
    std::mt19937 random_engine(random_device());
    std::uniform_real_distribution<float> udistr(minValue, maxValue);

    std::vector<float> result(size);
    std::generate(result.begin(), result.end(), [&]() { return udistr(random_engine); });
    return result;
}

bool areF32VectorsEqual(const std::vector<float>& lhs, const std::vector<float>& rhs) {
    if (lhs.size() != rhs.size()) {
        std::cout << "Vectors are of different sizes";
        return false;
    }

    const auto mismatchPair = std::mismatch(lhs.cbegin(), lhs.cend(), rhs.cbegin());
    if (mismatchPair.first != lhs.cend()) {
        std::cout << "Incorrect result:\n";
        std::cout << "Expected " << *mismatchPair.first << ", but got "<< *mismatchPair.second << "!\n";
        return false;
    }

    return true;
}

void vecSumReference(float* result, const float* lhs, const float* rhs, int size) {
    for (int i = 0; i < size; ++i) {
        result[i] = lhs[i] + rhs[i];
    }
}

struct vecSumJITGenerator : public CodeGenerator {
    bool useRVV = false;

    vecSumJITGenerator() {
        const auto& cpu = CPU::getInstance();
        useRVV = cpu.hasExtension(RISCVExtension::V);
        generate();
    }

    void generate() {
        // Function arguments:
        // a0 = float* result
        // a1 = const float* lhs
        // a2 = const float* rhs
        // a3 = int size

        if (useRVV) {
            // V extension is available on this RISC-V CPU -
            // generate the addition function using vector instructions
            std::cout << "Generating addition function with RVV ..." << std::endl;

            // Used temp registers:
            // t0 = cycleLength
            // t1 = Processed elements counter
            // t2 = size - cycleLength
            // t3 = cycleLength elements in bytes
            // t4 = (size - cycleLength) elements in bytes

            // Save a0, a1, a2 pointers
            add(a5, x0, a0);
            add(a6, x0, a1);
            add(a7, x0, a2);

            vsetvli(t0, a3, SEW::e32, LMUL::m8);
            sub(t2, a3, t0);  // set t2 to (size - cycleLength)
            slli(t3, t0, 2);  // set t3 to cycleLength elements in bytes

            //
            //  Main loop processing cycleLength elements per iteration
            //

            // Initialize processed elements counter
            add(t1, zero, zero);

            Label vvaddfloat32;
            L(vvaddfloat32);
            add(t1, t1, t0);
            // Load VL elements from lhs and rhs
            vle32_v(v0, a1);
            vle32_v(v8, a2);
            // Sum the elements, store result to a0 address
            vfadd_vv(v16, v0, v8);
            vse32_v(v16, a0);
            // Increase the pointers by (cycleLength * 4) bytes
            add(a0, a0, t3);
            add(a1, a1, t3);
            add(a2, a2, t3);
            // Loop back if less than (size - cycleLength) elements has been processed
            blt(t1, t2, vvaddfloat32);

            //
            //  Tile processing for the last cycleLength elements
            //

            // Restore lhs, rhs, result pointers and set
            // them to [size - cycleLength]-th element
            slli(t4, t2, 2);
            add(a0, x0, a5);
            add(a0, a0, t4);
            add(a1, x0, a6);
            add(a1, a1, t4);
            add(a2, x0, a7);
            add(a2, a2, t4);

            // Read the last cycleLength elements from lhs and rhs
            vle32_v(v0, a1);
            vle32_v(v8, a2);
            // Sum the elements, store result to a0 address
            vfadd_vv(v16, v0, v8);
            vse32_v(v16, a0);
        } else {
            // V extension is not available on the current RISC-V CPU -
            // generate the addition function using only scalar instructions
            std::cout << "Generating addition function without RVV ..." << std::endl;

            // Initialize processed elements counter
            add(t4, x0, x0);

            Label vvaddfloat32;
            L(vvaddfloat32);
            // Load values from lhs and rhs, sum and store to result
            flw(f10, a1);
            flw(f11, a2);
            fadd_s(f12, f10, f11);
            fsw(f12, a0);
            // Move pointers, increase counter
            addi(a0, a0, 4);
            addi(a1, a1, 4);
            addi(a2, a2, 4);
            addi(t4, t4, 1);
            // Check loop condition
            blt(t4, a3, vvaddfloat32);
        }

        ret();
    }
};

int main() {
	std::cout << "Comparing reference implementation with JIT code." << std::endl;

	// generate JIT code
	vecSumJITGenerator jitKernel;
	jitKernel.ready();
	const auto vecSumJIT = jitKernel.getCode<void (*)(float*, const float*, const float*, int)>();

	const int testSizes[] = {1, 4, 8, 10, 32, 67, 127, 129, 2535, 3546, 10000};
	for (auto arrSize : testSizes) {
		std::cout << "running a test for size " << arrSize << std::endl;
		// generate two random vectors
		std::vector<float> lhs = generateRandomF32Vector(arrSize);
		std::vector<float> rhs = generateRandomF32Vector(arrSize);

		// sum the vectors with the reference implementation
		std::vector<float> reference(arrSize);
		vecSumReference(reference.data(), lhs.data(), rhs.data(), arrSize);

		// sum the vectors with the generated JIT function
		std::vector<float> jitResult(arrSize);
		vecSumJIT(jitResult.data(), lhs.data(), rhs.data(), arrSize);

		// compare results
		assert(areF32VectorsEqual(reference, jitResult));
	}

	std::cout << "tests passed!" << std::endl;
}
