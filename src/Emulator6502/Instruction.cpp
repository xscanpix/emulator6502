#include "Instruction.h"

#include "Instruction.h"
#include "Interpreter.h"

namespace ISA_6502
{
    static void undoc(u8 op, const char *mnemonic)
    {
        InstructionDescriptor &d = desc_table[op];

        d.handler = &Interpreter::Undocumented;
        d.format = Undocumented;
        d.mnemonic = mnemonic;
    }

    static void build(u8 op, const char *mnemonic, InstructionFormat format, InstructionHandler handler)
    {
        InstructionDescriptor &d = desc_table[op];

        d.handler = handler;
        d.format = format;
        d.mnemonic = mnemonic;
    }

    static void build_descriptor_table()
    {

        build(0x00, "BRK", OP, &Interpreter::BRK);
        build(0x01, "ORA", OP_indirect_x, &Interpreter::ORA_INDX);
        undoc(0x02, "HALT");
        undoc(0x03, "ASL-ORA");
        undoc(0x04, "NOP");
        build(0x05, "ORA", OP_zero_page, &Interpreter::ORA_ZP);
        build(0x06, "ASL", OP_zero_page, &Interpreter::ASL_ZP);
        build(0x07, "ASL-ORA", OP_zero_page, &Interpreter::Undocumented);
        build(0x08, "PHP", OP, &Interpreter::PHP);
        build(0x09, "ORA", OP_immediate, &Interpreter::ORA_IMM);
        build(0x0A, "ASL", OP_accumulator, &Interpreter::ASL_A);
        undoc(0x0B, "AND");
        undoc(0x0C, "NOP");
        build(0x0D, "ORA", OP_absolute, &Interpreter::ORA_ABS);
        build(0x0E, "ASL", OP_absolute, &Interpreter::ASL_ABS);
        undoc(0x0F, "ASL-ORA");

        build(0x10, "BPL", OP_relative, &Interpreter::BPL);
        build(0x11, "ORA", OP_indirect_y, &Interpreter::ORA_INDY);
        undoc(0x12, "HALT");
        undoc(0x13, "ASL-ORA");
        undoc(0x14, "NOP");
        build(0x15, "ORA", OP_zero_page_x, &Interpreter::ORA_ZPX);
        build(0x16, "ASL", OP_zero_page_x, &Interpreter::ASL_ZPX);
        undoc(0x17, "ASL-ORA");
        build(0x18, "CLC", OP, &Interpreter::CLC);
        build(0x19, "ORA", OP_absolute_y, &Interpreter::ORA_ABSY);
        undoc(0x1A, "NOP");
        undoc(0x1B, "ASL-ORA");
        undoc(0x1C, "NOP");
        build(0x1D, "ORA", OP_absolute_x, &Interpreter::ORA_ABSX);
        build(0x1E, "ASL", OP_absolute_x, &Interpreter::ASL_ABSX);
        undoc(0x1F, "ASL-ORA");

        build(0x20, "JSR", OP_absolute, &Interpreter::JSR);
        build(0x21, "AND", OP_indirect_x, &Interpreter::AND_INDX);
        undoc(0x22, "HALT");
        undoc(0x23, "ROL-AND");
        build(0x23, "BIT", OP_zero_page, &Interpreter::BIT_ZP);
        build(0x25, "AND", OP_zero_page, &Interpreter::AND_ZP);
        build(0x26, "ROL", OP_zero_page, &Interpreter::ROL_ZP);
        undoc(0x27, "ROL-AND");
        build(0x28, "PLP", OP, &Interpreter::PLP);
        build(0x29, "AND", OP_immediate, &Interpreter::AND_IMM);
        build(0x2A, "ROL", OP_accumulator, &Interpreter::ROL_A);
        undoc(0x2B, "AND");
        build(0x2C, "BIT", OP_absolute, &Interpreter::BIT_ABS);
        build(0x2D, "AND", OP_absolute, &Interpreter::AND_ABS);
        build(0x2E, "ROL", OP_absolute, &Interpreter::ROL_ABS);
        undoc(0x2F, "ROL-AND");

        build(0x30, "BMI", OP_relative, &Interpreter::BMI);
        build(0x31, "AND", OP_indirect_y, &Interpreter::AND_INDY);
        undoc(0x32, "HALT");
        undoc(0x33, "ROL-AND");
        undoc(0x34, "NOP");
        build(0x35, "AND", OP_zero_page_x, &Interpreter::AND_ZPX);
        build(0x36, "ROL", OP_zero_page_x, &Interpreter::ROL_ZPX);
        undoc(0x37, "ROL-AND");
        build(0x38, "SEC", OP, &Interpreter::SEC);
        build(0x39, "AND", OP_absolute_y, &Interpreter::AND_ABSY);
        undoc(0x3A, "NOP");
        undoc(0x3B, "ROL-AND");
        undoc(0x3C, "NOP");
        build(0x3D, "ORA", OP_absolute_x, &Interpreter::ORA_ABSX);
        build(0x3E, "ASL", OP_absolute_x, &Interpreter::ASL_ABSX);
        undoc(0x3F, "ROL-AND");

        build(0x40, "RTI", OP, &Interpreter::RTI);
        build(0x41, "EOR", OP_indirect_x, &Interpreter::EOR_INDX);
        undoc(0x42, "HALT");
        undoc(0x43, "LSR-EOR");
        undoc(0x44, "NOP");
        build(0x45, "EOR", OP_zero_page, &Interpreter::EOR_ZP);
        build(0x46, "LSR", OP_zero_page, &Interpreter::LSR_ZP);
        undoc(0x47, "LSR-EOR");
        build(0x48, "PHA", OP, &Interpreter::PHA);
        build(0x49, "EOR", OP_immediate, &Interpreter::EOR_IMM);
        build(0x4A, "LSR", OP_accumulator, &Interpreter::LSR_A);
        undoc(0x4B, "AND");
        build(0x4C, "JMP", OP_absolute, &Interpreter::JMP_ABS);
        build(0x4D, "EOR", OP_absolute, &Interpreter::EOR_ABS);
        build(0x4E, "LSR", OP_absolute, &Interpreter::LSR_ABS);
        undoc(0x4F, "LSR-EOR");

        build(0x50, "BVC", OP_relative, &Interpreter::BVC);
        build(0x51, "EOR", OP_indirect_y, &Interpreter::EOR_INDY);
        undoc(0x52, "HALT");
        undoc(0x53, "LST-EOR");
        undoc(0x54, "NOP");
        build(0x55, "EOR", OP_zero_page_x, &Interpreter::EOR_ZPX);
        build(0x56, "LSR", OP_zero_page_x, &Interpreter::LSR_ZPX);
        undoc(0x57, "LSR-EOR");
        build(0x58, "CLI", OP, &Interpreter::CLI);
        build(0x59, "EOR", OP_absolute_y, &Interpreter::EOR_ABSY);
        undoc(0x5A, "NOP");
        undoc(0x5B, "LSR-EOR");
        undoc(0x5C, "NOP");
        build(0x5D, "EOR", OP_absolute_x, &Interpreter::EOR_ABSX);
        build(0x5E, "LSR", OP_absolute_x, &Interpreter::LSR_ABSX);
        undoc(0x5F, "LSR-EOR");

        build(0x60, "RTS", OP, &Interpreter::RTS);
        build(0x61, "ADC", OP_indirect_x, &Interpreter::ADC_INDX);
        undoc(0x62, "HALT");
        undoc(0x63, "ROR-ADC");
        undoc(0x64, "NOP");
        build(0x65, "ADC", OP_zero_page, &Interpreter::ADC_ZP);
        build(0x66, "ROR", OP_zero_page, &Interpreter::ROR_ZP);
        undoc(0x67, "ROR-ADC");
        build(0x68, "PLA", OP, &Interpreter::PLA);
        build(0x69, "ADC", OP_immediate, &Interpreter::ADC_IMM);
        build(0x6A, "ROR", OP_accumulator, &Interpreter::ROR_A);
        undoc(0x6B, "AND");
        build(0x6C, "JMP", OP_indirect, &Interpreter::JMP_IND);
        build(0x6D, "ADC", OP_absolute, &Interpreter::ADC_ABS);
        build(0x6E, "ROR", OP_absolute, &Interpreter::ROR_ABS);
        undoc(0x6F, "ROR-ADC");

        build(0x70, "BCS", OP_relative, &Interpreter::BCS);
        build(0x71, "ADC", OP_indirect_y, &Interpreter::ADC_INDY);
        undoc(0x72, "HALT");
        undoc(0x73, "ROR-ADC");
        undoc(0x74, "NOP");
        build(0x75, "ADC", OP_zero_page_x, &Interpreter::ADC_ZPX);
        build(0x76, "ROR", OP_zero_page_x, &Interpreter::ROR_ZPX);
        undoc(0x77, "ROR-ADC");
        build(0x78, "SEI", OP, &Interpreter::SEI);
        build(0x79, "ADC", OP_absolute_y, &Interpreter::ADC_ABSY);
        undoc(0x7A, "NOP");
        undoc(0x7B, "ROR-ADC");
        undoc(0x7C, "NOP");
        build(0x7D, "ADC", OP_absolute_x, &Interpreter::ADC_ABSX);
        build(0x7E, "ROR", OP_absolute_x, &Interpreter::ROR_ABSX);
        undoc(0x7F, "ROR-ADC");

        undoc(0x80, "NOP");
        build(0x81, "STA", OP_indirect_x, &Interpreter::STA_INDX);
        undoc(0x82, "HALT");
        undoc(0x83, "STA-STX");
        build(0x84, "STY", OP_zero_page, &Interpreter::STY_ZP);
        build(0x85, "STA", OP_zero_page, &Interpreter::STX_ZP);
        build(0x86, "STX", OP_zero_page, &Interpreter::STX_ZP);
        undoc(0x87, "STA-STX");
        build(0x88, "DEY", OP, &Interpreter::DEY);
        undoc(0x89, "NOP");
        build(0x8A, "TXA", OP_accumulator, &Interpreter::TXA);
        undoc(0x8B, "TXA-AND");
        build(0x8C, "STY", OP_absolute, &Interpreter::STY_ABS);
        build(0x8D, "STA", OP_absolute, &Interpreter::STA_ABS);
        build(0x8E, "STX", OP_absolute, &Interpreter::STX_ABS);
        undoc(0x8F, "STA-STX");

        build(0x90, "BCC", OP_relative, &Interpreter::BCC);
        build(0x91, "STA", OP_indirect_y, &Interpreter::STA_INDY);
        undoc(0x92, "HALT");
        undoc(0x93, "STA-STX");
        build(0x94, "STY", OP_zero_page, &Interpreter::STY_ZP);
        build(0x95, "STA", OP_zero_page_x, &Interpreter::STA_ZPX);
        build(0x96, "STX", OP_zero_page_y, &Interpreter::STX_ZPY);
        undoc(0x97, "STA-STX");
        build(0x98, "TYA", OP, &Interpreter::TYA);
        build(0x99, "STA", OP_absolute_y, &Interpreter::STA_ABSY);
        build(0x9A, "TXS", OP, &Interpreter::TXS);
        undoc(0x9B, "STA-STX");
        undoc(0x9C, "STA-STX");
        build(0x9D, "STA", OP_absolute_x, &Interpreter::STA_ABSX);
        undoc(0x9E, "STA-STX");
        undoc(0x9F, "STA-STX");

        build(0xA0, "LDY", OP_immediate, &Interpreter::LDY_IMM);
        build(0xA1, "LDA", OP_indirect_x, &Interpreter::LDA_INDX);
        build(0xA2, "LDX", OP_immediate, &Interpreter::LDX_IMM);
        undoc(0xA3, "LDA-LDX");
        build(0xA4, "LDY", OP_zero_page, &Interpreter::LDY_ZP);
        build(0xA5, "LDA", OP_zero_page, &Interpreter::LDA_ZP);
        build(0xA6, "LDX", OP_zero_page, &Interpreter::LDX_ZP);
        undoc(0xA7, "LDA-LDX");
        build(0xA8, "TAY", OP, &Interpreter::TAY);
        build(0xA9, "LDA", OP_immediate, &Interpreter::LDA_IMM);
        build(0xAA, "TAX", OP, &Interpreter::TAX);
        undoc(0xAB, "LDA-LDX");
        build(0xAC, "LDY", OP_absolute, &Interpreter::LDY_ABS);
        build(0xAD, "LDA", OP_absolute, &Interpreter::LDA_ABS);
        build(0xAE, "LDX", OP_absolute, &Interpreter::LDX_ABS);
        undoc(0xAF, "LDA-LDX");

        build(0xB0, "BCS", OP_relative, &Interpreter::BCS);
        build(0xB1, "LDA", OP_indirect_y, &Interpreter::LDA_INDY);
        undoc(0xB2, "HALT");
        undoc(0xB3, "LDA-LDX");
        build(0xB4, "LDY", OP_zero_page, &Interpreter::LDY_ZP);
        build(0xB5, "LDA", OP_zero_page_x, &Interpreter::LDA_ZPX);
        build(0xB6, "LDX", OP_zero_page_y, &Interpreter::LDX_ZPY);
        undoc(0xB7, "LDA-LDX");
        build(0xB8, "CLV", OP, &Interpreter::CLV);
        build(0xB9, "LDA", OP_absolute_y, &Interpreter::LDA_ABSY);
        build(0xBA, "TSX", OP, &Interpreter::TSX);
        undoc(0xBB, "LDA-LDX");
        build(0xBC, "LDY", OP_absolute_x, &Interpreter::LDY_ABSX);
        build(0xBD, "LDA", OP_absolute_x, &Interpreter::LDA_ABSX);
        build(0xBE, "LDX", OP_absolute_y, &Interpreter::LDX_ABSY);
        undoc(0xBF, "LDA-LDX");

        build(0xC0, "CPY", OP_immediate, &Interpreter::CPY_IMM);
        build(0xC1, "CMP", OP_indirect_x, &Interpreter::CMP_INDX);
        undoc(0xC2, "HALT");
        undoc(0xC3, "DEC-CMP");
        build(0xC4, "CPY", OP_zero_page, &Interpreter::CPY_ZP);
        build(0xC5, "CMP", OP_zero_page, &Interpreter::CMP_ZP);
        build(0xC6, "DEC", OP_zero_page, &Interpreter::DEC_ZP);
        undoc(0xC7, "DEC-CMP");
        build(0xC8, "INY", OP, &Interpreter::INY);
        build(0xC9, "CMP", OP_immediate, &Interpreter::CMP_IMM);
        build(0xCA, "DEX", OP, &Interpreter::DEX);
        undoc(0xCB, "SBX");
        build(0xCC, "CPY", OP_absolute, &Interpreter::CPY_ABS);
        build(0xCD, "CMP", OP_absolute, &Interpreter::CMP_ABS);
        build(0xCE, "DEC", OP_absolute, &Interpreter::DEC_ABS);
        undoc(0xCF, "DEC-CMP");

        build(0xD0, "BNE", OP_relative, &Interpreter::BNE);
        build(0xD1, "CMP", OP_indirect_y, &Interpreter::CMP_INDY);
        undoc(0xD2, "HALT");
        undoc(0xD3, "DEC-CMP");
        undoc(0xD4, "NOP");
        build(0xD5, "CMP", OP_zero_page_x, &Interpreter::CMP_ZPX);
        build(0xD6, "DEC", OP_zero_page_x, &Interpreter::DEC_ZPX);
        undoc(0xD7, "DEC-CMP");
        build(0xD8, "CLD", OP, &Interpreter::CLD);
        build(0xD9, "CMP", OP_absolute_y, &Interpreter::CMP_ABSY);
        undoc(0xDA, "NOP");
        undoc(0xDB, "DEC-CMP");
        undoc(0xDC, "NOP");
        build(0xDD, "CMP", OP_absolute_x, &Interpreter::CMP_ABSX);
        build(0xDE, "DEC", OP_absolute_x, &Interpreter::DEC_ABSX);
        undoc(0xDF, "DEC-CMP");

        build(0xE0, "CPX", OP_immediate, &Interpreter::CPX_IMM);
        build(0xE1, "SBC", OP_indirect_x, &Interpreter::SBC_INDX);
        undoc(0xE2, "HALT");
        undoc(0xE3, "INC-SBC");
        build(0xE4, "CPX", OP_zero_page, &Interpreter::CPX_ZP);
        build(0xE5, "SBC", OP_zero_page, &Interpreter::SBC_ZP);
        build(0xE6, "INC", OP_zero_page, &Interpreter::INC_ZP);
        undoc(0xE7, "INC-SBC");
        build(0xE8, "INX", OP, &Interpreter::INX);
        build(0xE9, "SBC", OP_immediate, &Interpreter::SBC_IMM);
        build(0xEA, "NOP", OP, &Interpreter::NOP);
        build(0xEB, "SBC", OP_immediate, &Interpreter::SBC_IMM);
        build(0xEC, "CPX", OP_absolute, &Interpreter::CPX_ABS);
        build(0xED, "SBC", OP_absolute, &Interpreter::SBC_ABS);
        build(0xEE, "INC", OP_absolute, &Interpreter::INC_ABS);
        undoc(0xEF, "INC-SBC");

        build(0xF0, "BEQ", OP_relative, &Interpreter::BEQ);
        build(0xF1, "SBC", OP_indirect_y, &Interpreter::SBC_INDY);
        undoc(0xF2, "HALT");
        undoc(0xF3, "INC-SBC");
        undoc(0xF4, "NOP");
        build(0xF5, "SBC", OP_zero_page_x, &Interpreter::SBC_ZPX);
        build(0xF6, "INC", OP_zero_page_x, &Interpreter::INC_ZPX);
        undoc(0xF7, "INC-SBC");
        build(0xF8, "SED", OP, &Interpreter::SED);
        build(0xF9, "SBC", OP_absolute_y, &Interpreter::SBC_ABSY);
        undoc(0xFA, "NOP");
        undoc(0xFB, "INC-SBC");
        undoc(0xFC, "NOP");
        build(0xFD, "SBC", OP_absolute_x, &Interpreter::SBC_ABSX);
        build(0xFE, "INC", OP_absolute_x, &Interpreter::INC_ABSX);
        undoc(0xFF, "INC-SBC");
    }

}