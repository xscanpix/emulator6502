#include "cpu.h"

namespace Emulator6502
{
    void CPU::IncPC(const u8 val)
    {
        regs.PC += val;
    }

    void CPU::DecPC(const u8 val)
    {
        regs.PC -= val;
    }

    Opcode CPU::FetchInstruction()
    {
        auto inst = mem.data[regs.PC];
        IncPC(1);
        return (Opcode)inst;
    }

    void CPU::Process(const Opcode op)
    {
        auto info = OperandInfo(op);
        (void)info;

        switch (op)
        {
        case ADC_IMM:
        {
        }
        case ADC_ZP:
        {
        }
        case ADC_ZPX:
        {
        }
        case ADC_ABS:
        {
        }
        case ADC_ABSX:
        {
        }
        case ADC_ABSY:
        {
        }
        case ADC_INDX:
        {
        }
        case ADC_INDY:
        {
        }

        case AND_IMM:
        {
        }
        case AND_ZP:
        {
        }
        case AND_ZPX:
        {
        }
        case AND_ABS:
        {
        }
        case AND_ABSX:
        {
        }
        case AND_ABSY:
        {
        }
        case AND_INDX:
        {
        }
        case AND_INDY:
        {
        }

        case ASL_A:
        {
        }
        case ASL_ZP:
        {
        }
        case ASL_ZPX:
        {
        }
        case ASL_ABS:
        {
        }
        case ASL_ABSX:
        {
        }

        case BCC:
        {
        }
        case BCS:
        {
        }
        case BEQ:
        {
        }
        case BMI:
        {
        }
        case BNE:
        {
        }
        case BPL:
        {
        }
        case BVC:
        {
        }
        case BVS:
        {
        }

        case BIT_ZP:
        {
        }
        case BIT_ABS:
        {
        }

        case BRK:
        {
        }

        case CLC:
        {
        }
        case CLD:
        {
        }
        case CLI:
        {
        }
        case CLV:
        {
        }

        case CMP_IMM:
        {
        }
        case CMP_ZP:
        {
        }
        case CMP_ZPX:
        {
        }
        case CMP_ABS:
        {
        }
        case CMP_ABSX:
        {
        }
        case CMP_ABSY:
        {
        }
        case CMP_INDX:
        {
        }
        case CMP_INDY:
        {
        }

        case CPX_IMM:
        {
        }
        case CPX_ZP:
        {
        }
        case CPX_ABS:
        {
        }

        case CPY_IMM:
        {
        }
        case CPY_ZP:
        {
        }
        case CPY_ABS:
        {
        }

        case DEC_ZP:
        {
        }
        case DEC_ZPX:
        {
        }
        case DEC_ABS:
        {
        }
        case DEC_ABSX:
        {
        }

        case DEX:
        {
        }
        case DEY:
        {
        }

        case EOR_IMM:
        {
        }
        case EOR_ZP:
        {
        }
        case EOR_ZPX:
        {
        }
        case EOR_ABS:
        {
        }
        case EOR_ABSX:
        {
        }
        case EOR_ABSY:
        {
        }
        case EOR_INDX:
        {
        }
        case EOR_INDY:
        {
        }

        case INC_ZP:
        {
        }
        case INC_ZPX:
        {
        }
        case INC_ABS:
        {
        }
        case INC_ABSX:
        {
        }

        case INX:
        {
        }
        case INY:
        {
        }

        case JMP_ABS:
        {
        }
        case JMP_IND:
        {
        }

        case JSR:
        {
        }

        case LDA_IMM:
        {
        }
        case LDA_ZP:
        {
        }
        case LDA_ZPX:
        {
        }
        case LDA_ABS:
        {
        }
        case LDA_ABSX:
        {
        }
        case LDA_ABSY:
        {
        }
        case LDA_INDX:
        {
        }
        case LDA_INDY:
        {
        }

        case LDX_IMM:
        {
        }
        case LDX_ZP:
        {
        }
        case LDX_ZPY:
        {
        }
        case LDX_ABS:
        {
        }
        case LDX_ABSY:
        {
        }

        case LDY_IMM:
        {
        }
        case LDY_ZP:
        {
        }
        case LDY_ZPX:
        {
        }
        case LDY_ABS:
        {
        }
        case LDY_ABSX:
        {
        }

        case LSR_A:
        {
        }
        case LSR_ZP:
        {
        }
        case LSR_ZPX:
        {
        }
        case LSR_ABS:
        {
        }
        case LSR_ABSX:
        {
        }

        case NOP:
        {
        }

        case ORA_IMM:
        {
        }
        case ORA_ZP:
        {
        }
        case ORA_ZPX:
        {
        }
        case ORA_ABS:
        {
        }
        case ORA_ABSX:
        {
        }
        case ORA_ABSY:
        {
        }
        case ORA_INDX:
        {
        }
        case ORA_INDY:
        {
        }

        case PHA:
        {
        }
        case PHP:
        {
        }
        case PLA:
        {
        }
        case PLP:
        {
        }

        case ROL_A:
        {
        }
        case ROL_ZP:
        {
        }
        case ROL_ZPX:
        {
        }
        case ROL_ABS:
        {
        }
        case ROL_ABSX:
        {
        }

        case ROR_A:
        {
        }
        case ROR_ZP:
        {
        }
        case ROR_ZPX:
        {
        }
        case ROR_ABS:
        {
        }
        case ROR_ABSX:
        {
        }

        case RTI:
        {
        }
        case RTS:
        {
        }

        case SBC_IMM:
        {
        }
        case SBC_ZP:
        {
        }
        case SBC_ZPX:
        {
        }
        case SBC_ABS:
        {
        }
        case SBC_ABSX:
        {
        }
        case SBC_ABSY:
        {
        }
        case SBC_INDX:
        {
        }
        case SBC_INDY:
        {
        }

        case SEC:
        {
        }
        case SED:
        {
        }
        case SEI:
        {
        }

        case STA_ZP:
        {
        }
        case STA_ZPX:
        {
        }
        case STA_ABS:
        {
        }
        case STA_ABSX:
        {
        }
        case STA_ABSY:
        {
        }
        case STA_INDX:
        {
        }
        case STA_INDY:
        {
        }

        case STX_ZP:
        {
        }
        case STX_ZPY:
        {
        }
        case STX_ABS:
        {
        }

        case STY_ZP:
        {
        }
        case STY_ZPX:
        {
        }
        case STY_ABS:
        {
        }

        case TAX:
        {
        }
        case TAY:
        {
        }
        case TSX:
        {
        }
        case TXA:
        {
        }
        case TXS:
        {
        }
        case TYA:
        {
        }

        default:
        {
            // TODO: Handle invalid opcode
        }
        }
    }
}