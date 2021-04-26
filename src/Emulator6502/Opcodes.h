#pragma once

#include "common.h"

namespace Emulator
{
    enum Opcode : u8
    {
        /*0x00 = */ BRK = 0x00,
        /*0x01 = */ ORA_INDX,
        /*0x02 = */ HALT_UNDOCUMENTED_02,
        /*0x03 = */ ASL_ORA_ZPX_UNDOCUMENTED_03,
        /*0x04 = */ NOP_ZP_UNDOCUMENTED_04,
        /*0x05 = */ ORA_ZP,
        /*0x06 = */ ASL_ZP,
        /*0x07 = */ ASL_ORA_ZP_UNDOCUMENTED_07,
        /*0x08 = */ PHP,
        /*0x09 = */ ORA_IMM,
        /*0x0A = */ ASL_A,
        /*0x0B = */ AND_IMM_MOV_UNDOCUMENTED_0B,
        /*0x0C = */ NOP_ABS_UNDOCUMENTED_0C,
        /*0x0D = */ ORA_ABS,
        /*0x0E = */ ASL_ABS,
        /*0x0F = */ ASL_ORA_ABS_UNDOCUMENTED_0F,
        /*0x10 = */ BPL_REL,
        /*0x11 = */ ORA_INDY,
        /*0x12 = */ HALT_UNDOCUMENTED_12,
        /*0x13 = */ ASL_ORA_ZPY_UNDOCUMENTED_13,
        /*0x14 = */ NOP_ZP_UNDOCUMENTED_14,
        /*0x15 = */ ORA_ZPX,
        /*0x16 = */ ASL_ZPX,
        /*0x17 = */ ASL_ORA_ABSX_UNDOCUMENTED_17,
        /*0x18 = */ CLC,
        /*0x19 = */ ORA_ABSY,
        /*0x1A = */ NOP_UNDOCUMENTED_1A,
        /*0x1B = */ ASL_ORA_ABSY_UNDOCUMENTED_1B,
        /*0x1C = */ NOP_ABS_UNDOCUMENTED_1C,
        /*0x1D = */ ORA_ABSX_1D,
        /*0x1E = */ ASL_ABSX_1E,
        /*0x1F = */ ASL_ORA_ABSX_UNDOCUMENTED_1F,
        /*0x20 = */ JSR,
        /*0x21 = */ AND_INDX,
        /*0x22 = */ HALT_UNDOCUMENTED_22,
        /*0x23 = */ ROL_AND_ZPX_UNDOCUMENTED_23,
        /*0x23 = */ BIT_ZP,
        /*0x25 = */ AND_ZP,
        /*0x26 = */ ROL_ZP,
        /*0x27 = */ ROL_AND_ZP_UNDOCUMENTED_27,
        /*0x28 = */ PLP,
        /*0x29 = */ AND_IMM,
        /*0x2A = */ ROL_A,
        /*0x2B = */ AND_IMM_MOV_UNDOCUMENTED_2B,
        /*0x2C = */ BIT_ABS,
        /*0x2D = */ AND_ABS,
        /*0x2E = */ ROL_ABS,
        /*0x2F = */ ROL_AND_ABS_UNDOCUMENTED_2F,
        /*0x30 = */ BMI_REL,
        /*0x31 = */ AND_INDY,
        /*0x32 = */ HALT_UNDOCUMENTED_32,
        /*0x33 = */ ROL_AND_ZPY_UNDOCUMENTED_33,
        /*0x34 = */ NOP_UNDOCUMENTED_34,
        /*0x35 = */ AND_ZPX,
        /*0x36 = */ ROL_ZPX,
        /*0x37 = */ ROL_AND_ZPX_UNDOCUMENTED_37,
        /*0x38 = */ SEC,
        /*0x39 = */ AND_ABSY,
        /*0x3A = */ NOP_UNDOCUMENTED_3A,
        /*0x3B = */ ROL_AND_ABSY_UNDOCUMENTED_3B,
        /*0x3C = */ NOP_ABS_UNDOCUMENTED_3C,
        /*0x3D = */ ORA_ABSX_3D,
        /*0x3E = */ ASL_ABSX_3E,
        /*0x3F = */ ROL_AND_ABSX_UNDOCUMENTED_3F,
        /*0x40 = */ RTI,
        /*0x41 = */ EOR_INDX,
        /*0x42 = */ HALT_UNDOCUMENTED_42,
        /*0x43 = */ LSR_EOR_ZPX_UNDOCUMENTED_43,
        /*0x44 = */ NOP_ZP_UNDOCUMENTED_44,
        /*0x45 = */ EOR_ZP,
        /*0x46 = */ LSR_ZP,
        /*0x47 = */ LSR_EOR_ZP_UNDOCUMENTED_47,
        /*0x48 = */ PHA,
        /*0x49 = */ EOR_IMM,
        /*0x4A = */ LSR_A,
        /*0x4B = */ AND_IMM_LSR_UNDOCUMENTED_4B,
        /*0x4C = */ JMP_ABS,
        /*0x4D = */ EOR_ABS,
        /*0x4E = */ LSR_ABS,
        /*0x4F = */ LSR_EOR_ABS_UNDOCUMENTED_4F,
        /*0x50 = */ BVC_REL,
        /*0x51 = */ EOR_INDY,
        /*0x52 = */ HALT_UNDOCUMENTED_52,
        /*0x53 = */ LSR_EOR_ZPY_UNDOCUMENTED_53,
        /*0x54 = */ NOP_ZP_UNDOCUMENTED_54,
        /*0x55 = */ EOR_ZPX,
        /*0x56 = */ LSR_ZPX,
        /*0x57 = */ LSR_EOR_ABSX_UNDOCUMENTED_57,
        /*0x58 = */ CLI,
        /*0x59 = */ EOR_ABSY,
        /*0x5A = */ NOP_UNDOCUMENTED_5A,
        /*0x5B = */ LSR_EOR_ABSY_UNDOCUMENTED_5B,
        /*0x5C = */ NOP_ABS_UNDOCUMENTED_5C,
        /*0x5D = */ EOR_ABSX,
        /*0x5E = */ LSR_ABSX,
        /*0x5F = */ LSR_EOR_ABSX_UNDOCUMENTED_5F,
        /*0x60 = */ RTS,
        /*0x61 = */ ADC_INDX,
        /*0x62 = */ HALT_UNDOCUMENTED_62,
        /*0x63 = */ ROR_ADC_ZPX_UNDOCUMENTED_63,
        /*0x64 = */ NOP_ZP_UNDOCUMENTED_64,
        /*0x65 = */ ADC_ZP,
        /*0x66 = */ ROR_ZP,
        /*0x67 = */ ROR_ADC_ZP_UNDOCUMENTED_67,
        /*0x68 = */ PLA,
        /*0x69 = */ ADC_IMM,
        /*0x6A = */ ROR_A,
        /*0x6B = */ AND_IMM_ROR_UNDOCUMENTED_6B,
        /*0x6C = */ JMP_IND,
        /*0x6D = */ ADC_ABS,
        /*0x6E = */ ROR_ABS,
        /*0x6F = */ ROR_ADC_ABS_UNDOCUMENTED_6F,
        /*0x70 = */ BVS_REL,
        /*0x71 = */ ADC_INDY,
        /*0x72 = */ HALT_UNDOCUMENTED_72,
        /*0x73 = */ ROR_ADC_ZPY_UNDOCUMENTED_73,
        /*0x74 = */ NOP_ZP_UNDOCUMENTED_74,
        /*0x75 = */ ADC_ZPX,
        /*0x76 = */ ROR_ZPX,
        /*0x77 = */ ROR_ADC_ABSX_UNDOCUMENTED_77,
        /*0x78 = */ SEI,
        /*0x79 = */ ADC_ABSY,
        /*0x7A = */ NOP_UNDOCUMENTED_7A,
        /*0x7B = */ ROR_ADC_ABSY_UNDOCUMENTED_7B,
        /*0x7C = */ NOP_ABS_UNDOCUMENTED_7C,
        /*0x7D = */ ADC_ABSX,
        /*0x7E = */ ROR_ABSX,
        /*0x7F = */ ROR_ADC_ABSX_UNDOCUMENTED_7F,
        /*0x80 = */ NOP_ZP_UNDOCUMENTED_80,
        /*0x81 = */ STA_INDX,
        /*0x82 = */ HALT_UNDOCUMENTED_82,
        /*0x83 = */ STA_STX_ZPX_UNDOCUMENTED_83,
        /*0x84 = */ STY_ZP_84,
        /*0x85 = */ STA_ZP,
        /*0x86 = */ STX_ZP,
        /*0x87 = */ STA_STX_ZP_UNDOCUMENTED_87,
        /*0x88 = */ DEY,
        /*0x89 = */ NOP_ZP_UNDOCUMENTED_89,
        /*0x8A = */ TXA,
        /*0x8B = */ TXA_AND_IMM_UNDOCUMENTED_8B,
        /*0x8C = */ STY_ABS,
        /*0x8D = */ STA_ABS,
        /*0x8E = */ STX_ABS,
        /*0x8F = */ STA_STX_ABS_UNDOCUMENTED_8F,
        /*0x90 = */ BCC_REL,
        /*0x91 = */ STA_INDY,
        /*0x92 = */ HALT_UNDOCUMENTED_92,
        /*0x93 = */ STA_STX_ZPY_UNDOCUMENTED_93,
        /*0x94 = */ STY_ZP_94,
        /*0x95 = */ STA_ZPX,
        /*0x96 = */ STX_ZPY,
        /*0x97 = */ STA_STX_ZPY_UNDOCUMENTED_97,
        /*0x98 = */ TYA,
        /*0x99 = */ STA_ABSY,
        /*0x9A = */ TXS,
        /*0x9B = */ STA_STX_ABSY_UNDOCUMENTED_9B,
        /*0x9C = */ STA_STX_ABSX_UNDOCUMENTED_9C,
        /*0x9D = */ STA_ABSX,
        /*0x9E = */ STA_STX_ABSX_UNDOCUMENTED_9E,
        /*0x9F = */ STA_STX_ABSX_UNDOCUMENTED_9F,
        /*0xA0 = */ LDY_IMM,
        /*0xA1 = */ LDA_INDX,
        /*0xA2 = */ LDX_IMM,
        /*0xA3 = */ LDA_LDX_ZPX_UNDOCUMENTED_A3,
        /*0xA4 = */ LDY_ZP_A4,
        /*0xA5 = */ LDA_ZP,
        /*0xA6 = */ LDX_ZP,
        /*0xA7 = */ LDA_LDX_ZP_UNDOCUMENTED_A7,
        /*0xA8 = */ TAY,
        /*0xA9 = */ LDA_IMM,
        /*0xAA = */ TAX,
        /*0xAB = */ LDA_LDX_UNDOCUMENTED_AB,
        /*0xAC = */ LDY_ABS,
        /*0xAD = */ LDA_ABS,
        /*0xAE = */ LDX_ABS,
        /*0xAF = */ LDA_LDX_ABS_UNDOCUMENTED_AF,
        /*0xB0 = */ BCS_REL_B0,
        /*0xB1 = */ LDA_INDY,
        /*0xB2 = */ HALT_UNDOCUMENTED_B2,
        /*0xB3 = */ LDA_LDX_ZPY_UNDOCUMENTED_B3,
        /*0xB4 = */ LDY_ZP_B4,
        /*0xB5 = */ LDA_ZPX,
        /*0xB6 = */ LDX_ZPY,
        /*0xB7 = */ LDA_LDX_ZPY_UNDOCUMENTED_B7,
        /*0xB8 = */ CLV,
        /*0xB9 = */ LDA_ABSY,
        /*0xBA = */ TSX,
        /*0xBB = */ LDA_LDX_ABSY_UNDOCUMENTED_BB,
        /*0xBC = */ LDY_ABSX,
        /*0xBD = */ LDA_ABSX,
        /*0xBE = */ LDX_ABSY,
        /*0xBF = */ LDA_LDX_ABSY_UNDOCUMENTED_BF,
        /*0xC0 = */ CPY_IMM,
        /*0xC1 = */ CMP_INDX,
        /*0xC2 = */ HALT_UNDOCUMENTED_C2,
        /*0xC3 = */ DEC_CMP_ZPX_UNDOCUMENTED_C3,
        /*0xC4 = */ CPY_ZP,
        /*0xC5 = */ CMP_ZP,
        /*0xC6 = */ DEC_ZP,
        /*0xC7 = */ DEC_CMP_ZP_UNDOCUMENTED_C7,
        /*0xC8 = */ INY,
        /*0xC9 = */ CMP_IMM,
        /*0xCA = */ DEX,
        /*0xCB = */ SBX_IMM_UNDOCUMENTED_CB,
        /*0xCC = */ CPY_ABS,
        /*0xCD = */ CMP_ABS,
        /*0xCE = */ DEC_ABS,
        /*0xCF = */ DEC_CMP_ABS_UNDOCUMENTED_CF,
        /*0xD0 = */ BNE_REL,
        /*0xD1 = */ CMP_INDY,
        /*0xD2 = */ HALT_UNDOCUMENTED_D2,
        /*0xD3 = */ DEC_CMP_ZPY_UNDOCUMENTED_D3,
        /*0xD4 = */ NOP_ZP_UNDOCUMENTED_D4,
        /*0xD5 = */ CMP_ZPX,
        /*0xD6 = */ DEC_ZPX,
        /*0xD7 = */ DEC_CMP_ZPX_UNDOCUMENTED_D7,
        /*0xD8 = */ CLD,
        /*0xD9 = */ CMP_ABSY,
        /*0xDA = */ NOP_UNDOCUMENTED_DA,
        /*0xDB = */ DEC_CMP_ABSY_UNDOCUMENTED_DB,
        /*0xDC = */ NOP_ABS_UNDOCUMENTED_DC,
        /*0xDD = */ CMP_ABSX,
        /*0xDE = */ DEC_ABSX,
        /*0xDF = */ DEC_CMP_ABSX_UNDOCUMENTED_DF,
        /*0xE0 = */ CPX_IMM,
        /*0xE1 = */ SBC_INDX,
        /*0xE2 = */ HALT_UNDOCUMENTED_E2,
        /*0xE3 = */ INC_SBC_ZPX_UNDOCUMENTED_E3,
        /*0xE4 = */ CPX_ZP,
        /*0xE5 = */ SBC_ZP,
        /*0xE6 = */ INC_ZP,
        /*0xE7 = */ INC_SBC_ZP_UNDOCUMENTED_E7,
        /*0xE8 = */ INX,
        /*0xE9 = */ SBC_IMM_E9,
        /*0xEA = */ NOP,
        /*0xEB = */ SBC_IMM_EB,
        /*0xEC = */ CPX_ABS,
        /*0xED = */ SBC_ABS,
        /*0xEE = */ INC_ABS,
        /*0xEF = */ INC_SBC_ABS_UNDOCUMENTED_EF,
        /*0xF0 = */ BEQ_REL,
        /*0xF1 = */ SBC_INDY,
        /*0xF2 = */ HALT_UNDOCUMENTED_F2,
        /*0xF3 = */ INC_SBC_ZPY_UNDOCUMENTED_F3,
        /*0xF4 = */ NOP_ZP_UNDOCUMENTED_F4,
        /*0xF5 = */ SBC_ZPX,
        /*0xF6 = */ INC_ZPX,
        /*0xF7 = */ INC_SBC_ZPX_UNDOCUMENTED_F7,
        /*0xF8 = */ SED,
        /*0xF9 = */ SBC_ABSY,
        /*0xFA = */ NOP_UNDOCUMENTED_FA,
        /*0xFB = */ INC_SBC_ABSY_UNDOCUMENTED_FB,
        /*0xFC = */ NOP_ABS_UNDOCUMENTED_FC,
        /*0xFD = */ SBC_ABSX,
        /*0xFE = */ INC_ABSX,
        /*0xFF = */ INC_SBC_ABSX_UNDOCUMENTED_FF
    };
}