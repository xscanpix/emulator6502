#pragma once

#include <array>

#include "Types.h"

namespace Emulator
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
    typedef struct InstructionDescriptor InstructionDescriptor;

    class DescriptorTables
    {
    public:
        static DescriptorTables &the()
        {
            static DescriptorTables instance;
            return instance;
        }
        InstructionDescriptor *operator[](u8 op)
        {
            return &desc_table[op];
        }

    private:
        InstructionDescriptor desc_table[256];

    private:
        DescriptorTables() { build_descriptor_table(); }
        void undoc(const u8 op, const char *mnemonic);
        void build(const u8 op, const char *mnemonic, const InstructionFormat format, const InstructionHandler handler);
        void build_descriptor_table();
    };

    class Instruction
    {
    public:
        Instruction(const u8 op) : m_descriptor(DescriptorTables::the()[op]), m_op(op) {}

    private:
        InstructionDescriptor *m_descriptor{nullptr};

        u8 m_op{0};
        u16 m_imm{0};
        u8 m_reg_index{0};
    };

}