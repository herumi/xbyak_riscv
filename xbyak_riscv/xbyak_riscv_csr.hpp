/******************************************************************************
* Copyright (C), 2023, KNS Group LLC (YADRO)
*
* Licensed under the 3-Clause BSD License
* You may obtain a copy of the License at https://opensource.org/license/bsd-3-clause/
*******************************************************************************/

#pragma once
namespace Xbyak_riscv {

// Control and Status Register
enum class CSR : uint32_t {
    // vector CSRs
    vstart = 0x008, // Vector start position
    vxsat  = 0x009, // Fixed-Point Saturate Flag
    vxrm   = 0x00A, // Fixed-Point Rounding Mode
    vcsr   = 0x00F, // Vector control and status register
    vl     = 0xC20, // Vector length
    vtype  = 0xC21, // Vector data type register
    vlenb  = 0xC22, // VLEN/8 (vector register length in bytes)
};

// Selected Element Width
enum class SEW : uint32_t {
    e8  = 0b000,
    e16 = 0b001,
    e32 = 0b010,
    e64 = 0b011
};

// Vector Length Multiplier
enum class LMUL : uint32_t {
    mf8 = 0b101,
    mf4 = 0b110,
    mf2 = 0b111,
    m1  = 0b000,
    m2  = 0b001,
    m4  = 0b010,
    m8  = 0b011
};

// Vector Mask Agnostic
enum class VMA : uint32_t {
    mu = 0, // undisturbed
    ma = 1, // agnostic
};

// Vector Tail Agnostic
enum class VTA : uint32_t {
    tu = 0, // undisturbed
    ta = 1, // agnostic
};

enum class VectorAddressingMode : uint32_t {
    unitStride       = 0b00,
    indexedUnordered = 0b01,
    strided          = 0b10,
    indexedOrdered   = 0b11
    // other encodings are reserved
};

enum class UnitStrideVectorAddressingModeLoad : uint32_t {
    load              = 0b00000, // unit-stride load
    wholeRegisterLoad = 0b01000, // unit-stride, whole register load
    maskLoad          = 0b01011, // unit-stride, mask load, EEW=8
    faultOnlyFirst    = 0b10000  // unit-stride fault-only-first
    // other encodings are reserved
};

enum class UnitStrideVectorAddressingModeStore : uint32_t {
    store              = 0b00000, // unit-stride store
    wholeRegisterStore = 0b01000, // unit-stride, whole register store
    maskStore          = 0b01011  // unit-stride, mask store, EEW=8
    // other encodings are reserved
};

enum class WidthEncoding : uint32_t {
    e8  = 0b000, // Vector 8-bit  element
    e16 = 0b101, // Vector 16-bit element
    e32 = 0b110, // Vector 32-bit element
    e64 = 0b111, // Vector 64-bit element
};

enum class VM : uint32_t {
    unmasked = 1,
    masked = 0
};

} // Xbyak_riscv
