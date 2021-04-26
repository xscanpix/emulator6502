#include "Instruction.h"
#include "DescriptorTable.h"

#include <iomanip>

namespace Emulator
{
    std::string Instruction::stringify() const
    {
        std::stringstream ss;

        ss << m_descriptor->mnemonic << "(" << std::hex << (int)m_opcode << ") ";

        switch (m_descriptor->format)
        {
        case OP:
            break;
        case OP_padded_1:
            ss << "[1 byte padded]";
            break;
        case OP_accumulator:
            ss << "A"
               << " [acc]";
            break;
        case OP_immediate:
            ss << "#$" << std::setw(2) << m_operand << " [imm]";
            break;
        case OP_zero_page:
            ss << "$" << std::setw(2) << m_operand << " [zp]";
            break;
        case OP_zero_page_x:
            ss << "$" << std::setw(2) << m_operand << ", X"
               << " [zp, X]";
            break;
        case OP_zero_page_y:
            ss << "$" << std::setw(2) << m_operand << ", Y"
               << " [zp, Y]";
            break;
        case OP_relative:
            ss << "$" << std::setw(2) << m_operand << " [rel]";
            break;
        case OP_absolute:
            ss << "$" << std::setw(4) << m_operand << " [abs]";
            break;
        case OP_absolute_x:
            ss << "$" << std::setw(4) << m_operand << ", X"
               << " [abs, X]";
            break;
        case OP_absolute_y:
            ss << "$" << std::setw(4) << m_operand << ", Y"
               << " [abs, Y]";
            break;
        case OP_indirect:
            ss << "($" << std::setw(4) << m_operand << ")"
               << " [ind]";
            break;
        case OP_indirect_x:
            ss << "($" << std::setw(2) << m_operand << ", X)"
               << " [ind, X]";
            break;
        case OP_indirect_y:
            ss << "($" << std::setw(2) << m_operand << "), Y"
               << " [ind, Y]";
            break;
        default:
            ss << "[UNDOCUMENTED]";
        }

        ss << std::endl;

        return std::move(ss.str());
    }
}