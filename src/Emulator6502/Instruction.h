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
              m_opcode(opcode),
              m_operand_bytes(1) {}

        Instruction(const u8 opcode, const u16 operand, const u32 operand_bytes)
            : m_descriptor(DescriptorTables::the()[opcode]),
              m_opcode(opcode),
              m_operand(operand),
              m_operand_bytes(operand_bytes) {}

        u16 operand() const { return m_operand; }
        u8 opcode() const { return m_opcode; }
        u32 operand_bytes() const { return m_operand_bytes; }
        auto handler() const { return m_descriptor->handler; }

        friend std::ostream &operator<<(std::ostream &, const Instruction &);
        std::string to_string();

    private:
        const InstructionDescriptor *const m_descriptor{nullptr};
        const u8 m_opcode{0};
        u16 m_operand{0};
        const u32 m_operand_bytes{0};
    };
}