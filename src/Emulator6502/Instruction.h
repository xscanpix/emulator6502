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
        Undocumented,
        OP,
        OP_accumulator,
        OP_immediate,
        OP_zero_page,
        OP_zero_page_x,
        OP_zero_page_y,
        OP_relative,
        OP_absolute,
        OP_absolute_x,
        OP_absolute_y,
        OP_indirect,
        OP_indirect_x,
        OP_indirect_y
    };

    struct InstructionDescriptor
    {
        InstructionHandler handler{nullptr};
        const char *mnemonic{nullptr};
        InstructionFormat format{InvalidFormat};
    };

    extern InstructionDescriptor desc_table[256];

    enum Registers
    {
        PC,
        SP,
        A,
        X,
        Y,
        PS
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