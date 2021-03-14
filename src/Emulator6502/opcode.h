#pragma once

#include "common.h"

namespace Emulator6502
{
    enum Opcode : u8
    {
        ADC_IMM  = 0x69,
        ADC_ZP   = 0x65,
        ADC_ZPX  = 0x75,
        ADC_ABS  = 0x6D,
        ADC_ABSX = 0x7D,
        ADC_ABSY = 0x79,
        ADC_INDX = 0x61,
        ADC_INDY = 0x71,

        AND_IMM  = 0x29,
        AND_ZP   = 0x25,
        AND_ZPX  = 0x35,
        AND_ABS  = 0x2D,
        AND_ABSX = 0x3D,
        AND_ABSY = 0x39,
        AND_INDX = 0x21,
        AND_INDY = 0x31,

        ASL_A    = 0x0A,
        ASL_ZP   = 0x06,
        ASL_ZPX  = 0x16,
        ASL_ABS  = 0x0E,
        ASL_ABSX = 0x1E,

        BCC      = 0x90,
        BCS      = 0xB0,
        BEQ      = 0xF0,
        BMI      = 0x30,
        BNE      = 0xD0,
        BPL      = 0x10,
        BVC      = 0x50,
        BVS      = 0x70,

        BIT_ZP   = 0x24,
        BIT_ABS  = 0x2C,

        BRK      = 0x00,

        CLC      = 0x18,
        CLD      = 0xD8,
        CLI      = 0x58,
        CLV      = 0xB8,

        CMP_IMM  = 0xC9,
        CMP_ZP   = 0xC5,
        CMP_ZPX  = 0xD5,
        CMP_ABS  = 0xCD,
        CMP_ABSX = 0xDD,
        CMP_ABSY = 0xD9,
        CMP_INDX = 0xC1,
        CMP_INDY = 0xD1,

        CPX_IMM  = 0xE0,
        CPX_ZP   = 0xE4,
        CPX_ABS  = 0xEC,

        CPY_IMM  = 0xC0,
        CPY_ZP   = 0xC4,
        CPY_ABS  = 0xCC,

        DEC_ZP   = 0xC6,
        DEC_ZPX  = 0xD6,
        DEC_ABS  = 0xCE,
        DEC_ABSX = 0xDE,

        DEX      = 0xCA,
        DEY      = 0x88,

        EOR_IMM  = 0x49,
        EOR_ZP   = 0x45,
        EOR_ZPX  = 0x55,
        EOR_ABS  = 0x4D,
        EOR_ABSX = 0x5D,
        EOR_ABSY = 0x59,
        EOR_INDX = 0x41,
        EOR_INDY = 0x51,

        INC_ZP   = 0xE6,
        INC_ZPX  = 0xF6,
        INC_ABS  = 0xEE,
        INC_ABSX = 0xFE,

        INX      = 0xE8,
        INY      = 0xC8,

        JMP_ABS  = 0x4C,
        JMP_IND  = 0x6C,

        JSR      = 0x20,

        LDA_IMM  = 0xA9,
        LDA_ZP   = 0xA5,
        LDA_ZPX  = 0xB5,
        LDA_ABS  = 0xAD,
        LDA_ABSX = 0xBD,
        LDA_ABSY = 0xB9,
        LDA_INDX = 0xA1,
        LDA_INDY = 0xB1,

        LDX_IMM  = 0xA2,
        LDX_ZP   = 0xA6,
        LDX_ZPY  = 0xB6,
        LDX_ABS  = 0xAE,
        LDX_ABSY = 0xBE,

        LDY_IMM  = 0xA0,
        LDY_ZP   = 0xA4,
        LDY_ZPX  = 0xB4,
        LDY_ABS  = 0xAC,
        LDY_ABSX = 0xBC,

        LSR_A    = 0x4A,
        LSR_ZP   = 0x46,
        LSR_ZPX  = 0x56,
        LSR_ABS  = 0x4E,
        LSR_ABSX = 0x5E,

        NOP      = 0xEA,

        ORA_IMM  = 0x09,
        ORA_ZP   = 0x05,
        ORA_ZPX  = 0x15,
        ORA_ABS  = 0x0D,
        ORA_ABSX = 0x1D,
        ORA_ABSY = 0x19,
        ORA_INDX = 0x01,
        ORA_INDY = 0x11,

        PHA      = 0x48,
        PHP      = 0x08,
        PLA      = 0x68,
        PLP      = 0x28,

        ROL_A    = 0x2A,
        ROL_ZP   = 0x26,
        ROL_ZPX  = 0x36,
        ROL_ABS  = 0x2E,
        ROL_ABSX = 0x3E,

        ROR_A    = 0x6A,
        ROR_ZP   = 0x66,
        ROR_ZPX  = 0x76,
        ROR_ABS  = 0x6E,
        ROR_ABSX = 0x7E,

        RTI      = 0x40,
        RTS      = 0x60,

        SBC_IMM  = 0xE9,
        SBC_ZP   = 0xE5,
        SBC_ZPX  = 0xF5,
        SBC_ABS  = 0xED,
        SBC_ABSX = 0xFD,
        SBC_ABSY = 0xF9,
        SBC_INDX = 0xE1,
        SBC_INDY = 0xF1,

        SEC      = 0x38,
        SED      = 0xF8,
        SEI      = 0x78,

        STA_ZP   = 0x85,
        STA_ZPX  = 0x95,
        STA_ABS  = 0x8D,
        STA_ABSX = 0x9D,
        STA_ABSY = 0x99,
        STA_INDX = 0x81,
        STA_INDY = 0x91,

        STX_ZP   = 0x86,
        STX_ZPY  = 0x96,
        STX_ABS  = 0x8E,

        STY_ZP   = 0x84,
        STY_ZPX  = 0x94,
        STY_ABS  = 0x8C,

        TAX      = 0xAA,
        TAY      = 0xA8,
        TSX      = 0xBA,
        TXA      = 0x8A,
        TXS      = 0x9A,
        TYA      = 0x98,
    };
    typedef enum Opcode Opcode;

    struct op_info 
    {
        const u16 bytes;
        const u16 cycles;
    };
    typedef struct op_info op_info_t;

    constexpr op_info_t OperandInfo(Opcode op)
    {
        switch(op)
        {
            case ADC_IMM:   { return {2, 2}; }
            case ADC_ZP:    { return {2, 3}; }
            case ADC_ZPX:   { return {2, 4}; }
            case ADC_ABS:   { return {3, 4}; }
            case ADC_ABSX:  { return {3, 4}; }
            case ADC_ABSY:  { return {3, 6}; }
            case ADC_INDX:  { return {2, 5}; }
            case ADC_INDY:  { return {2, 2}; }

            case AND_IMM:   { return {2, 2}; }
            case AND_ZP:    { return {2, 3}; }
            case AND_ZPX:   { return {2, 4}; }
            case AND_ABS:   { return {3, 4}; }
            case AND_ABSX:  { return {3, 4}; }
            case AND_ABSY:  { return {3, 4}; }
            case AND_INDX:  { return {2, 6}; }
            case AND_INDY:  { return {2, 5}; }

            case ASL_A:     { return {1, 2}; }
            case ASL_ZP:    { return {2, 5}; }
            case ASL_ZPX:   { return {2, 6}; }
            case ASL_ABS:   { return {3, 6}; }
            case ASL_ABSX:  { return {3, 7}; }

            case BCC:       { return {2, 2}; }
            case BCS:       { return {2, 2}; }
            case BEQ:       { return {2, 2}; }
            case BMI:       { return {2, 2}; }
            case BNE:       { return {2, 2}; }
            case BPL:       { return {2, 2}; }
            case BVC:       { return {2, 2}; }
            case BVS:       { return {2, 2}; }

            case BIT_ZP:    { return {2, 3}; }
            case BIT_ABS:   { return {3, 4}; }

            case BRK:       { return {1, 7}; }

            case CLC:       { return {1, 2}; }
            case CLD:       { return {1, 2}; }
            case CLI:       { return {1, 2}; }
            case CLV:       { return {1, 2}; }

            case CMP_IMM:   { return {2, 2}; }
            case CMP_ZP:    { return {2, 3}; }
            case CMP_ZPX:   { return {2, 4}; }
            case CMP_ABS:   { return {3, 4}; }
            case CMP_ABSX:  { return {3, 4}; }
            case CMP_ABSY:  { return {3, 4}; }
            case CMP_INDX:  { return {2, 6}; }
            case CMP_INDY:  { return {2, 5}; }

            case CPX_IMM:   { return {2, 2}; }
            case CPX_ZP:    { return {2, 3}; }
            case CPX_ABS:   { return {3, 4}; }

            case CPY_IMM:   { return {2, 2}; }
            case CPY_ZP:    { return {2, 3}; }
            case CPY_ABS:   { return {3, 4}; }
            
            case DEC_ZP:    { return {2, 5}; }
            case DEC_ZPX:   { return {2, 6}; }
            case DEC_ABS:   { return {3, 6}; }
            case DEC_ABSX:  { return {3, 7}; }

            case DEX:       { return {1, 2}; }
            case DEY:       { return {1, 2}; }
            
            case EOR_IMM:   { return {2, 2}; }
            case EOR_ZP:    { return {2, 3}; }
            case EOR_ZPX:   { return {2, 4}; }
            case EOR_ABS:   { return {3, 4}; }
            case EOR_ABSX:  { return {3, 4}; }
            case EOR_ABSY:  { return {3, 4}; }
            case EOR_INDX:  { return {2, 6}; }
            case EOR_INDY:  { return {2, 5}; }
            
            case INC_ZP:    { return {2, 5}; }
            case INC_ZPX:   { return {2, 6}; }
            case INC_ABS:   { return {3, 6}; }
            case INC_ABSX:  { return {3, 7}; }

            case INX:       { return {1, 2}; }
            case INY:       { return {1, 2}; }
            
            case JMP_ABS:   { return {3, 3}; }
            case JMP_IND:   { return {3, 5}; }
            
            case JSR:       { return {3, 6}; }
            
            case LDA_IMM:   { return {2, 2}; }
            case LDA_ZP:    { return {2, 3}; }
            case LDA_ZPX:   { return {2, 4}; }
            case LDA_ABS:   { return {3, 4}; }
            case LDA_ABSX:  { return {3, 4}; }
            case LDA_ABSY:  { return {3, 4}; }
            case LDA_INDX:  { return {2, 6}; }
            case LDA_INDY:  { return {2, 5}; }

            case LDX_IMM:   { return {2, 2}; }
            case LDX_ZP:    { return {2, 3}; }
            case LDX_ZPY:   { return {2, 4}; }
            case LDX_ABS:   { return {3, 4}; }
            case LDX_ABSY:  { return {3, 4}; }

            case LDY_IMM:   { return {2, 2}; }
            case LDY_ZP:    { return {2, 3}; }
            case LDY_ZPX:   { return {2, 4}; }
            case LDY_ABS:   { return {3, 4}; }
            case LDY_ABSX:  { return {3, 4}; }
            
            case LSR_A:     { return {1, 2}; }
            case LSR_ZP:    { return {2, 5}; }
            case LSR_ZPX:   { return {2, 6}; }
            case LSR_ABS:   { return {3, 6}; }
            case LSR_ABSX:  { return {3, 7}; }

            case NOP:       { return {1, 2}; }

            case ORA_IMM:   { return {2, 2}; }
            case ORA_ZP:    { return {2, 3}; }
            case ORA_ZPX:   { return {2, 4}; }
            case ORA_ABS:   { return {3, 4}; }
            case ORA_ABSX:  { return {3, 4}; }
            case ORA_ABSY:  { return {3, 4}; }
            case ORA_INDX:  { return {2, 6}; }
            case ORA_INDY:  { return {2, 5}; }

            case PHA:       { return {1, 3}; }
            case PHP:       { return {1, 3}; }
            case PLA:       { return {1, 4}; }
            case PLP:       { return {1, 4}; }

            case ROL_A:     { return {1, 2}; }
            case ROL_ZP:    { return {2, 5}; }
            case ROL_ZPX:   { return {2, 6}; }
            case ROL_ABS:   { return {3, 6}; }
            case ROL_ABSX:  { return {3, 7}; }

            case ROR_A:     { return {1, 2}; }
            case ROR_ZP:    { return {2, 5}; }
            case ROR_ZPX:   { return {2, 6}; }
            case ROR_ABS:   { return {3, 6}; }
            case ROR_ABSX:  { return {3, 7}; }

            case RTI:       { return {1, 6}; }
            case RTS:       { return {1, 6}; }

            case SBC_IMM:   { return {2, 2}; }
            case SBC_ZP:    { return {2, 3}; }
            case SBC_ZPX:   { return {2, 4}; }
            case SBC_ABS:   { return {3, 4}; }
            case SBC_ABSX:  { return {3, 4}; }
            case SBC_ABSY:  { return {3, 4}; }
            case SBC_INDX:  { return {2, 6}; }
            case SBC_INDY:  { return {2, 5}; }

            case SEC:       { return {1, 2}; }
            case SED:       { return {1, 2}; }
            case SEI:       { return {1, 2}; }

            case STA_ZP:    { return {2, 3}; }
            case STA_ZPX:   { return {2, 4}; }
            case STA_ABS:   { return {3, 4}; }
            case STA_ABSX:  { return {3, 5}; }
            case STA_ABSY:  { return {3, 5}; }
            case STA_INDX:  { return {2, 6}; }
            case STA_INDY:  { return {2, 6}; }

            case STX_ZP:    { return {2, 3}; }
            case STX_ZPY:   { return {2, 4}; }
            case STX_ABS:   { return {3, 4}; }

            case STY_ZP:    { return {2, 3}; }
            case STY_ZPX:   { return {2, 4}; }
            case STY_ABS:   { return {3, 4}; }

            case TAX:       { return {1, 2}; }
            case TAY:       { return {1, 2}; }
            case TSX:       { return {1, 2}; }
            case TXA:       { return {1, 2}; }
            case TXS:       { return {1, 2}; }
            case TYA:       { return {1, 2}; } 

            default:
            {
                // TODO: Handle invalid opcode
                return {0, 0};
            } 
        }
    }
}