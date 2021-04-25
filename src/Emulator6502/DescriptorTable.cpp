#include "DescriptorTable.h"

#include "Opcodes.h"
#include "Instruction.h"
#include "Interpreter.h"

namespace Emulator
{
    void DescriptorTables::undoc(const u8 op, const char *mnemonic, const u32 bytes)
    {
        InstructionDescriptor &d = desc_table[op];

        d.handler = &Interpreter::Undocumented;
        d.format = Undocumented;
        d.mnemonic = mnemonic;
        d.bytes = bytes;
    }

    void DescriptorTables::build(const u8 op, const char *mnemonic, const InstructionFormat format, const InstructionHandler handler)
    {
        InstructionDescriptor &d = desc_table[op];

        d.handler = handler;
        d.format = format;
        d.mnemonic = mnemonic;

        switch (format)
        {
        case OP:
        case OP_accumulator:
            d.bytes = 1;
            break;
        case OP_zero_page:
        case OP_zero_page_x:
        case OP_zero_page_y:
        case OP_immediate:
        case OP_indirect_x:
        case OP_indirect_y:
        case OP_relative:
            d.bytes = 2;
            break;
        case OP_indirect:
        case OP_absolute:
        case OP_absolute_x:
        case OP_absolute_y:
            d.bytes = 3;
            break;
        default:
            // Unreached?
            break;
        }
    }

    void DescriptorTables::build_descriptor_table()
    {
        build(Opcode::BRK, "BRK", OP, &Interpreter::BRK);
        build(Opcode::ORA_INDX, "ORA", OP_indirect_x, &Interpreter::ORA_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_02, "HALT", 1);
        undoc(Opcode::ASL_ORA_ZPX_UNDOCUMENTED_03, "ASL-ORA", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_04, "NOP", 2);
        build(Opcode::ORA_ZP, "ORA", OP_zero_page, &Interpreter::ORA_ZP);
        build(Opcode::ASL_ZP, "ASL", OP_zero_page, &Interpreter::ASL_ZP);
        undoc(Opcode::ASL_ORA_ZP_UNDOCUMENTED_07, "ASL-ORA", 2);
        build(Opcode::PHP, "PHP", OP, &Interpreter::PHP);
        build(Opcode::ORA_IMM, "ORA", OP_immediate, &Interpreter::ORA_IMM);
        build(Opcode::ASL_A, "ASL", OP_accumulator, &Interpreter::ASL_A);
        undoc(Opcode::AND_IMM_MOV_UNDOCUMENTED_0B, "AND", 2);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_0C, "NOP", 3);
        build(Opcode::ORA_ABS, "ORA", OP_absolute, &Interpreter::ORA_ABS);
        build(Opcode::ASL_ABS, "ASL", OP_absolute, &Interpreter::ASL_ABS);
        undoc(Opcode::ASL_ORA_ABS_UNDOCUMENTED_0F, "ASL-ORA", 3);

        build(Opcode::BPL_REL, "BPL", OP_relative, &Interpreter::BPL);
        build(Opcode::ORA_INDY, "ORA", OP_indirect_y, &Interpreter::ORA_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_12, "HALT", 1);
        undoc(Opcode::ASL_ORA_ZPY_UNDOCUMENTED_13, "ASL-ORA", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_14, "NOP", 2);
        build(Opcode::ORA_ZPX, "ORA", OP_zero_page_x, &Interpreter::ORA_ZPX);
        build(Opcode::ASL_ZPX, "ASL", OP_zero_page_x, &Interpreter::ASL_ZPX);
        undoc(Opcode::ASL_ORA_ABSX_UNDOCUMENTED_17, "ASL-ORA", 3);
        build(Opcode::CLC, "CLC", OP, &Interpreter::CLC);
        build(Opcode::ORA_ABSY, "ORA", OP_absolute_y, &Interpreter::ORA_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_1A, "NOP", 1);
        undoc(Opcode::ASL_ORA_ABSY_UNDOCUMENTED_1B, "ASL-ORA", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_1C, "NOP", 3);
        build(Opcode::ORA_ABSX_1D, "ORA", OP_absolute_x, &Interpreter::ORA_ABSX);
        build(Opcode::ASL_ABSX_1E, "ASL", OP_absolute_x, &Interpreter::ASL_ABSX);
        undoc(Opcode::ASL_ORA_ABSX_UNDOCUMENTED_1F, "ASL-ORA", 3);

        build(Opcode::JSR, "JSR", OP_absolute, &Interpreter::JSR);
        build(Opcode::AND_INDX, "AND", OP_indirect_x, &Interpreter::AND_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_22, "HALT", 1);
        undoc(Opcode::ROL_AND_ZPX_UNDOCUMENTED_23, "ROL-AND", 2);
        build(Opcode::BIT_ZP, "BIT", OP_zero_page, &Interpreter::BIT_ZP);
        build(Opcode::AND_ZP, "AND", OP_zero_page, &Interpreter::AND_ZP);
        build(Opcode::ROL_ZP, "ROL", OP_zero_page, &Interpreter::ROL_ZP);
        undoc(Opcode::ROL_AND_ZP_UNDOCUMENTED_27, "ROL-AND", 2);
        build(Opcode::PLP, "PLP", OP, &Interpreter::PLP);
        build(Opcode::AND_IMM, "AND", OP_immediate, &Interpreter::AND_IMM);
        build(Opcode::ROL_A, "ROL", OP_accumulator, &Interpreter::ROL_A);
        undoc(Opcode::AND_IMM_MOV_UNDOCUMENTED_2B, "AND", 2);
        build(Opcode::BIT_ABS, "BIT", OP_absolute, &Interpreter::BIT_ABS);
        build(Opcode::AND_ABS, "AND", OP_absolute, &Interpreter::AND_ABS);
        build(Opcode::ROL_ABS, "ROL", OP_absolute, &Interpreter::ROL_ABS);
        undoc(Opcode::ROL_AND_ABS_UNDOCUMENTED_2F, "ROL-AND", 3);

        build(Opcode::BMI_REL, "BMI", OP_relative, &Interpreter::BMI);
        build(Opcode::AND_INDY, "AND", OP_indirect_y, &Interpreter::AND_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_32, "HALT", 1);
        undoc(Opcode::ROL_AND_ZPY_UNDOCUMENTED_33, "ROL-AND", 2);
        undoc(Opcode::NOP_UNDOCUMENTED_34, "NOP", 2);
        build(Opcode::AND_ZPX, "AND", OP_zero_page_x, &Interpreter::AND_ZPX);
        build(Opcode::ROL_ZPX, "ROL", OP_zero_page_x, &Interpreter::ROL_ZPX);
        undoc(Opcode::ROL_AND_ZPX_UNDOCUMENTED_37, "ROL-AND", 2);
        build(Opcode::SEC, "SEC", OP, &Interpreter::SEC);
        build(Opcode::AND_ABSY, "AND", OP_absolute_y, &Interpreter::AND_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_3A, "NOP", 1);
        undoc(Opcode::ROL_AND_ABSY_UNDOCUMENTED_3B, "ROL-AND", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_3C, "NOP", 3);
        build(Opcode::ORA_ABSX_3D, "ORA", OP_absolute_x, &Interpreter::ORA_ABSX);
        build(Opcode::ASL_ABSX_3E, "ASL", OP_absolute_x, &Interpreter::ASL_ABSX);
        undoc(Opcode::ROL_AND_ABSX_UNDOCUMENTED_3F, "ROL-AND", 3);

        build(Opcode::RTI, "RTI", OP, &Interpreter::RTI);
        build(Opcode::EOR_INDX, "EOR", OP_indirect_x, &Interpreter::EOR_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_42, "HALT", 1);
        undoc(Opcode::LSR_EOR_ZPX_UNDOCUMENTED_43, "LSR-EOR", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_44, "NOP", 2);
        build(Opcode::EOR_ZP, "EOR", OP_zero_page, &Interpreter::EOR_ZP);
        build(Opcode::LSR_ZP, "LSR", OP_zero_page, &Interpreter::LSR_ZP);
        undoc(Opcode::LSR_EOR_ZP_UNDOCUMENTED_47, "LSR-EOR", 2);
        build(Opcode::PHA, "PHA", OP, &Interpreter::PHA);
        build(Opcode::EOR_IMM, "EOR", OP_immediate, &Interpreter::EOR_IMM);
        build(Opcode::LSR_A, "LSR", OP_accumulator, &Interpreter::LSR_A);
        undoc(Opcode::AND_IMM_LSR_UNDOCUMENTED_4B, "AND", 2);
        build(Opcode::JMP_ABS, "JMP", OP_absolute, &Interpreter::JMP_ABS);
        build(Opcode::EOR_ABS, "EOR", OP_absolute, &Interpreter::EOR_ABS);
        build(Opcode::LSR_ABS, "LSR", OP_absolute, &Interpreter::LSR_ABS);
        undoc(Opcode::LSR_EOR_ABS_UNDOCUMENTED_4F, "LSR-EOR", 3);

        build(Opcode::BVC_REL, "BVC", OP_relative, &Interpreter::BVC);
        build(Opcode::EOR_INDY, "EOR", OP_indirect_y, &Interpreter::EOR_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_52, "HALT", 1);
        undoc(Opcode::LSR_EOR_ZPY_UNDOCUMENTED_53, "LSR-EOR", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_54, "NOP", 2);
        build(Opcode::EOR_ZPX, "EOR", OP_zero_page_x, &Interpreter::EOR_ZPX);
        build(Opcode::LSR_ZPX, "LSR", OP_zero_page_x, &Interpreter::LSR_ZPX);
        undoc(Opcode::LSR_EOR_ABSX_UNDOCUMENTED_57, "LSR-EOR", 3);
        build(Opcode::CLI, "CLI", OP, &Interpreter::CLI);
        build(Opcode::EOR_ABSY, "EOR", OP_absolute_y, &Interpreter::EOR_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_5A, "NOP", 1);
        undoc(Opcode::LSR_EOR_ABSY_UNDOCUMENTED_5B, "LSR-EOR", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_5C, "NOP", 1);
        build(Opcode::EOR_ABSX, "EOR", OP_absolute_x, &Interpreter::EOR_ABSX);
        build(Opcode::LSR_ABSX, "LSR", OP_absolute_x, &Interpreter::LSR_ABSX);
        undoc(Opcode::LSR_EOR_ABSX_UNDOCUMENTED_5F, "LSR-EOR", 3);

        build(Opcode::RTS, "RTS", OP, &Interpreter::RTS);
        build(Opcode::ADC_INDX, "ADC", OP_indirect_x, &Interpreter::ADC_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_62, "HALT", 1);
        undoc(Opcode::ROR_ADC_ZPX_UNDOCUMENTED_63, "ROR-ADC", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_64, "NOP", 2);
        build(Opcode::ADC_ZP, "ADC", OP_zero_page, &Interpreter::ADC_ZP);
        build(Opcode::ROR_ZP, "ROR", OP_zero_page, &Interpreter::ROR_ZP);
        undoc(Opcode::ROR_ADC_ZP_UNDOCUMENTED_67, "ROR-ADC", 2);
        build(Opcode::PLA, "PLA", OP, &Interpreter::PLA);
        build(Opcode::ADC_IMM, "ADC", OP_immediate, &Interpreter::ADC_IMM);
        build(Opcode::ROR_A, "ROR", OP_accumulator, &Interpreter::ROR_A);
        undoc(Opcode::AND_IMM_ROR_UNDOCUMENTED_6B, "AND", 2);
        build(Opcode::JMP_IND, "JMP", OP_indirect, &Interpreter::JMP_IND);
        build(Opcode::ADC_ABS, "ADC", OP_absolute, &Interpreter::ADC_ABS);
        build(Opcode::ROR_ABS, "ROR", OP_absolute, &Interpreter::ROR_ABS);
        undoc(Opcode::ROR_ADC_ABS_UNDOCUMENTED_6F, "ROR-ADC", 3);

        build(Opcode::BCS_REL_70, "BCS", OP_relative, &Interpreter::BCS);
        build(Opcode::ADC_INDY, "ADC", OP_indirect_y, &Interpreter::ADC_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_72, "HALT", 1);
        undoc(Opcode::ROR_ADC_ZPY_UNDOCUMENTED_73, "ROR-ADC", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_74, "NOP", 2);
        build(Opcode::ADC_ZPX, "ADC", OP_zero_page_x, &Interpreter::ADC_ZPX);
        build(Opcode::ROR_ZPX, "ROR", OP_zero_page_x, &Interpreter::ROR_ZPX);
        undoc(Opcode::ROR_ADC_ABSX_UNDOCUMENTED_77, "ROR-ADC", 3);
        build(Opcode::SEI, "SEI", OP, &Interpreter::SEI);
        build(Opcode::ADC_ABSY, "ADC", OP_absolute_y, &Interpreter::ADC_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_7A, "NOP", 1);
        undoc(Opcode::ROR_ADC_ABSY_UNDOCUMENTED_7B, "ROR-ADC", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_7C, "NOP", 3);
        build(Opcode::ADC_ABSX, "ADC", OP_absolute_x, &Interpreter::ADC_ABSX);
        build(Opcode::ROR_ABSX, "ROR", OP_absolute_x, &Interpreter::ROR_ABSX);
        undoc(Opcode::ROR_ADC_ABSX_UNDOCUMENTED_7F, "ROR-ADC", 3);

        undoc(Opcode::NOP_ZP_UNDOCUMENTED_80, "NOP", 2);
        build(Opcode::STA_INDX, "STA", OP_indirect_x, &Interpreter::STA_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_82, "HALT", 1);
        undoc(Opcode::STA_STX_ZPX_UNDOCUMENTED_83, "STA-STX", 2);
        build(Opcode::STY_ZP_84, "STY", OP_zero_page, &Interpreter::STY_ZP);
        build(Opcode::STA_ZP, "STA", OP_zero_page, &Interpreter::STX_ZP);
        build(Opcode::STX_ZP, "STX", OP_zero_page, &Interpreter::STX_ZP);
        undoc(Opcode::STA_STX_ZP_UNDOCUMENTED_87, "STA-STX", 2);
        build(Opcode::DEY, "DEY", OP, &Interpreter::DEY);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_89, "NOP", 2);
        build(Opcode::TXA, "TXA", OP_accumulator, &Interpreter::TXA);
        undoc(Opcode::TXA_AND_IMM_UNDOCUMENTED_8B, "TXA-AND", 2);
        build(Opcode::STY_ABS, "STY", OP_absolute, &Interpreter::STY_ABS);
        build(Opcode::STA_ABS, "STA", OP_absolute, &Interpreter::STA_ABS);
        build(Opcode::STX_ABS, "STX", OP_absolute, &Interpreter::STX_ABS);
        undoc(Opcode::STA_STX_ABS_UNDOCUMENTED_8F, "STA-STX", 3);

        build(Opcode::BCC_REL, "BCC", OP_relative, &Interpreter::BCC);
        build(Opcode::STA_INDY, "STA", OP_indirect_y, &Interpreter::STA_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_92, "HALT", 1);
        undoc(Opcode::STA_STX_ZPY_UNDOCUMENTED_93, "STA-STX", 2);
        build(Opcode::STY_ZP_94, "STY", OP_zero_page, &Interpreter::STY_ZP);
        build(Opcode::STA_ZPX, "STA", OP_zero_page_x, &Interpreter::STA_ZPX);
        build(Opcode::STX_ZPY, "STX", OP_zero_page_y, &Interpreter::STX_ZPY);
        undoc(Opcode::STA_STX_ZPY_UNDOCUMENTED_97, "STA-STX", 2);
        build(Opcode::TYA, "TYA", OP, &Interpreter::TYA);
        build(Opcode::STA_ABSY, "STA", OP_absolute_y, &Interpreter::STA_ABSY);
        build(Opcode::TXS, "TXS", OP, &Interpreter::TXS);
        undoc(Opcode::STA_STX_ABSY_UNDOCUMENTED_9B, "STA-STX", 3);
        undoc(Opcode::STA_STX_ABSX_UNDOCUMENTED_9C, "STA-STX", 3);
        build(Opcode::STA_ABSX, "STA", OP_absolute_x, &Interpreter::STA_ABSX);
        undoc(Opcode::STA_STX_ABSX_UNDOCUMENTED_9E, "STA-STX", 3);
        undoc(Opcode::STA_STX_ABSX_UNDOCUMENTED_9F, "STA-STX", 3);

        build(Opcode::LDY_IMM, "LDY", OP_immediate, &Interpreter::LDY_IMM);
        build(Opcode::LDA_INDX, "LDA", OP_indirect_x, &Interpreter::LDA_INDX);
        build(Opcode::LDX_IMM, "LDX", OP_immediate, &Interpreter::LDX_IMM);
        undoc(Opcode::LDA_LDX_ZPX_UNDOCUMENTED_A3, "LDA-LDX", 2);
        build(Opcode::LDY_ZP_A4, "LDY", OP_zero_page, &Interpreter::LDY_ZP);
        build(Opcode::LDA_ZP, "LDA", OP_zero_page, &Interpreter::LDA_ZP);
        build(Opcode::LDX_ZP, "LDX", OP_zero_page, &Interpreter::LDX_ZP);
        undoc(Opcode::LDA_LDX_ZP_UNDOCUMENTED_A7, "LDA-LDX", 2);
        build(Opcode::TAY, "TAY", OP, &Interpreter::TAY);
        build(Opcode::LDA_IMM, "LDA", OP_immediate, &Interpreter::LDA_IMM);
        build(Opcode::TAX, "TAX", OP, &Interpreter::TAX);
        undoc(Opcode::LDA_LDX_UNDOCUMENTED_AB, "LDA-LDX", 1);
        build(Opcode::LDY_ABS, "LDY", OP_absolute, &Interpreter::LDY_ABS);
        build(Opcode::LDA_ABS, "LDA", OP_absolute, &Interpreter::LDA_ABS);
        build(Opcode::LDX_ABS, "LDX", OP_absolute, &Interpreter::LDX_ABS);
        undoc(Opcode::LDA_LDX_ABS_UNDOCUMENTED_AF, "LDA-LDX", 3);

        build(Opcode::BCS_REL_B0, "BCS", OP_relative, &Interpreter::BCS);
        build(Opcode::LDA_INDY, "LDA", OP_indirect_y, &Interpreter::LDA_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_B2, "HALT", 1);
        undoc(Opcode::LDA_LDX_ZPY_UNDOCUMENTED_B3, "LDA-LDX", 2);
        build(Opcode::LDY_ZP_B4, "LDY", OP_zero_page, &Interpreter::LDY_ZP);
        build(Opcode::LDA_ZPX, "LDA", OP_zero_page_x, &Interpreter::LDA_ZPX);
        build(Opcode::LDX_ZPY, "LDX", OP_zero_page_y, &Interpreter::LDX_ZPY);
        undoc(Opcode::LDA_LDX_ZPY_UNDOCUMENTED_B7, "LDA-LDX", 2);
        build(Opcode::CLV, "CLV", OP, &Interpreter::CLV);
        build(Opcode::LDA_ABSY, "LDA", OP_absolute_y, &Interpreter::LDA_ABSY);
        build(Opcode::TSX, "TSX", OP, &Interpreter::TSX);
        undoc(Opcode::LDA_LDX_ABSY_UNDOCUMENTED_BB, "LDA-LDX", 3);
        build(Opcode::LDA_ABSX, "LDY", OP_absolute_x, &Interpreter::LDY_ABSX);
        build(Opcode::LDA_ABSX, "LDA", OP_absolute_x, &Interpreter::LDA_ABSX);
        build(Opcode::LDA_ABSY, "LDX", OP_absolute_y, &Interpreter::LDX_ABSY);
        undoc(Opcode::LDA_LDX_ABSY_UNDOCUMENTED_BF, "LDA-LDX", 3);

        build(Opcode::CPY_IMM, "CPY", OP_immediate, &Interpreter::CPY_IMM);
        build(Opcode::CMP_INDX, "CMP", OP_indirect_x, &Interpreter::CMP_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_C2, "HALT", 1);
        undoc(Opcode::DEC_CMP_ZPX_UNDOCUMENTED_C3, "DEC-CMP", 2);
        build(Opcode::CPY_ZP, "CPY", OP_zero_page, &Interpreter::CPY_ZP);
        build(Opcode::CMP_ZP, "CMP", OP_zero_page, &Interpreter::CMP_ZP);
        build(Opcode::DEC_ZP, "DEC", OP_zero_page, &Interpreter::DEC_ZP);
        undoc(Opcode::DEC_CMP_ZP_UNDOCUMENTED_C7, "DEC-CMP", 2);
        build(Opcode::INY, "INY", OP, &Interpreter::INY);
        build(Opcode::CMP_IMM, "CMP", OP_immediate, &Interpreter::CMP_IMM);
        build(Opcode::DEX, "DEX", OP, &Interpreter::DEX);
        undoc(Opcode::SBX_IMM_UNDOCUMENTED_CB, "SBX", 2);
        build(Opcode::CPY_ABS, "CPY", OP_absolute, &Interpreter::CPY_ABS);
        build(Opcode::CMP_ABS, "CMP", OP_absolute, &Interpreter::CMP_ABS);
        build(Opcode::DEC_ABS, "DEC", OP_absolute, &Interpreter::DEC_ABS);
        undoc(Opcode::DEC_CMP_ABS_UNDOCUMENTED_CF, "DEC-CMP", 3);

        build(Opcode::BNE_REL, "BNE", OP_relative, &Interpreter::BNE);
        build(Opcode::CMP_INDY, "CMP", OP_indirect_y, &Interpreter::CMP_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_D2, "HALT", 1);
        undoc(Opcode::DEC_CMP_ZPY_UNDOCUMENTED_D3, "DEC-CMP", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_D4, "NOP", 2);
        build(Opcode::CMP_ZPX, "CMP", OP_zero_page_x, &Interpreter::CMP_ZPX);
        build(Opcode::DEC_ZPX, "DEC", OP_zero_page_x, &Interpreter::DEC_ZPX);
        undoc(Opcode::DEC_CMP_ZPX_UNDOCUMENTED_D7, "DEC-CMP", 2);
        build(Opcode::CLD, "CLD", OP, &Interpreter::CLD);
        build(Opcode::CMP_ABSY, "CMP", OP_absolute_y, &Interpreter::CMP_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_DA, "NOP", 1);
        undoc(Opcode::DEC_CMP_ABSY_UNDOCUMENTED_DB, "DEC-CMP", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_DC, "NOP", 3);
        build(Opcode::CMP_ABSX, "CMP", OP_absolute_x, &Interpreter::CMP_ABSX);
        build(Opcode::DEC_ABSX, "DEC", OP_absolute_x, &Interpreter::DEC_ABSX);
        undoc(Opcode::DEC_CMP_ABSX_UNDOCUMENTED_DF, "DEC-CMP", 3);

        build(Opcode::CPX_IMM, "CPX", OP_immediate, &Interpreter::CPX_IMM);
        build(Opcode::SBC_INDX, "SBC", OP_indirect_x, &Interpreter::SBC_INDX);
        undoc(Opcode::HALT_UNDOCUMENTED_E2, "HALT", 1);
        undoc(Opcode::INC_SBC_ZPX_UNDOCUMENTED_E3, "INC-SBC", 2);
        build(Opcode::CPX_ZP, "CPX", OP_zero_page, &Interpreter::CPX_ZP);
        build(Opcode::SBC_ZP, "SBC", OP_zero_page, &Interpreter::SBC_ZP);
        build(Opcode::INC_ZP, "INC", OP_zero_page, &Interpreter::INC_ZP);
        undoc(Opcode::INC_SBC_ZP_UNDOCUMENTED_E7, "INC-SBC", 2);
        build(Opcode::INX, "INX", OP, &Interpreter::INX);
        build(Opcode::SBC_IMM_E9, "SBC", OP_immediate, &Interpreter::SBC_IMM);
        build(Opcode::NOP, "NOP", OP, &Interpreter::NOP);
        build(Opcode::SBC_IMM_EB, "SBC", OP_immediate, &Interpreter::SBC_IMM);
        build(Opcode::CPX_ABS, "CPX", OP_absolute, &Interpreter::CPX_ABS);
        build(Opcode::SBC_ABS, "SBC", OP_absolute, &Interpreter::SBC_ABS);
        build(Opcode::INC_ABS, "INC", OP_absolute, &Interpreter::INC_ABS);
        undoc(Opcode::INC_SBC_ABS_UNDOCUMENTED_EF, "INC-SBC", 3);

        build(Opcode::BEQ_REL, "BEQ", OP_relative, &Interpreter::BEQ);
        build(Opcode::SBC_INDY, "SBC", OP_indirect_y, &Interpreter::SBC_INDY);
        undoc(Opcode::HALT_UNDOCUMENTED_F2, "HALT", 1);
        undoc(Opcode::INC_SBC_ZPY_UNDOCUMENTED_F3, "INC-SBC", 2);
        undoc(Opcode::NOP_ZP_UNDOCUMENTED_F4, "NOP", 2);
        build(Opcode::SBC_ZPX, "SBC", OP_zero_page_x, &Interpreter::SBC_ZPX);
        build(Opcode::INC_ZPX, "INC", OP_zero_page_x, &Interpreter::INC_ZPX);
        undoc(Opcode::INC_SBC_ZPX_UNDOCUMENTED_F7, "INC-SBC", 2);
        build(Opcode::SED, "SED", OP, &Interpreter::SED);
        build(Opcode::SBC_ABSY, "SBC", OP_absolute_y, &Interpreter::SBC_ABSY);
        undoc(Opcode::NOP_UNDOCUMENTED_FA, "NOP", 1);
        undoc(Opcode::INC_SBC_ABSY_UNDOCUMENTED_FB, "INC-SBC", 3);
        undoc(Opcode::NOP_ABS_UNDOCUMENTED_FC, "NOP", 3);
        build(Opcode::SBC_ABSX, "SBC", OP_absolute_x, &Interpreter::SBC_ABSX);
        build(Opcode::INC_ABSX, "INC", OP_absolute_x, &Interpreter::INC_ABSX);
        undoc(Opcode::INC_SBC_ABSX_UNDOCUMENTED_FF, "INC-SBC", 3);
    }
}