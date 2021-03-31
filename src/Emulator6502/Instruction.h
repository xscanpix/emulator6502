#pragma once

#include "common.h"

namespace ISA_6502
{
    class Instruction;
    class Interpreter;

    typedef void (Interpreter::*InstructionHandler)(const Instruction &);

    enum InstructionFormat
    {
        InvalidFormat = 0,
        op_accumulator,
        op_immediate,
        op_zero_page,
        op_zero_page_x,
        op_zero_page_y,
        op_relative,
        op_absolute,
        op_absolute_x,
        op_absolute_y,
        op_indirect,
        op_indexed_indirect,
        op_indirect_indexed
    };

    struct InstructionDescriptor
    {
        InstructionHandler handler{nullptr};
        const char *mnemonic{nullptr};
        InstructionFormat format{InvalidFormat};
    };

    InstructionDescriptor desc_table[256];

    enum Registers
    {
        Invalid = 0,
        X,
        Y
    };

    class Instruction
    {
    public:
    private:
        InstructionDescriptor *descriptor{nullptr};

        u8 m_op{0};
        u16 m_imm{0};
        u8 m_reg_index{0};
    };
}