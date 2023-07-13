/******************************************************************************
* Copyright (C), 2023, KNS Group LLC (YADRO)
*
* Licensed under the 3-Clause BSD License
* You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
*******************************************************************************/

#include <xbyak_riscv/xbyak_riscv.hpp>
#include <xbyak_riscv/xbyak_riscv_util.hpp>
#include <iostream>

using namespace Xbyak_riscv;

int main()
{
    CPU cpu;

    std::cout << "Number of RISC-V CPU cores: " << cpu.getNumCores() << std::endl;
    std::cout << "XLENB: " << cpu.getXlenb() << std::endl;
    std::cout << "VLENB: " << cpu.getVlenb() << std::endl;
    std::cout << "FLENB: " << cpu.getFlenb() << std::endl;
    std::cout << std::endl;

    std::cout << "Supported RISC-V extensions:" << std::endl;
    std::cout << "Has I: " <<  cpu.hasExtension(RISCVExtension::I) << std::endl;
    std::cout << "Has M: " <<  cpu.hasExtension(RISCVExtension::M) << std::endl;
    std::cout << "Has A: " <<  cpu.hasExtension(RISCVExtension::A) << std::endl;
    std::cout << "Has F: " <<  cpu.hasExtension(RISCVExtension::F) << std::endl;
    std::cout << "Has D: " <<  cpu.hasExtension(RISCVExtension::D) << std::endl;
    std::cout << "Has C: " <<  cpu.hasExtension(RISCVExtension::C) << std::endl;
    std::cout << "Has V: " <<  cpu.hasExtension(RISCVExtension::V) << std::endl;
    std::cout << std::endl;

    std::cout << "Cache info:" << std::endl;
    for (uint8_t cacheLvl = 1; cacheLvl < 5; cacheLvl+=1)
    {
        const auto cacheLvlStr = std::to_string(cacheLvl);
        std::cout << "L" << cacheLvlStr << " cache size: " << cpu.getDataCacheSize(1) << std::endl;
        std::cout << "L" << cacheLvlStr << " cache line size: " << cpu.getDataCacheSize(1) << std::endl;
    }
    return 0;
}
