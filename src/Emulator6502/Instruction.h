#pragma once

#include <string>
#include <iostream>

#include "Types.h"
#include "DescriptorTable.h"

namespace Emulator
{
    class Instruction;
    class Interpreter;

    typedef void (Interpreter::*InstructionHandler)(const Instruction &);

    class Instruction
    {
    public:
        Instruction(const u8 opcode)
            : m_descriptor(DescriptorTables::the()[opcode]),
              m_opcode(opcode) {}

        Instruction(const u8 opcode, const u16 operand)
            : m_descriptor(DescriptorTables::the()[opcode]),
              m_opcode(opcode),
              m_operand(operand) {}

        u16 operand() const { return m_operand; }
        u8 opcode() const { return m_opcode; }
        auto handler() const { return m_descriptor->handler; }

        friend std::ostream &operator<<(std::ostream &, const Instruction &);
        std::string to_string();

    private:
        const InstructionDescriptor *const m_descriptor{nullptr};
        const u8 m_opcode{0};
        const u16 m_operand{0};
        const u32 m_operand_bytes{0};
    };
}