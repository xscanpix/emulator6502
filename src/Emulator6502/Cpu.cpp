#include "Cpu.h"

#include <assert.h>
#include <sstream>
#include <iomanip>

namespace Emulator
{
    std::string Cpu::cpu_state() const
    {
        std::stringstream ss;

        ss << "Flags: "
           << "CZIDBON"
           << "\n";
        ss << "       "
           << (int)m_flags.C
           << (int)m_flags.Z
           << (int)m_flags.I
           << (int)m_flags.D
           << (int)m_flags.B
           << (int)m_flags.O
           << (int)m_flags.N
           << "\n";

        ss << std::hex << std::setfill('0') << std::setw(4);

        ss << "PC:    " << (int)m_regs.PC << "\n";
        ss << "SP:    " << (int)m_regs.SP << "\n";
        ss << "A:     " << (int)m_regs.A << "\n";
        ss << "X:     " << (int)m_regs.X << "\n";
        ss << "Y:     " << (int)m_regs.Y << "\n";

        ss << "\n";

        return ss.str();
    }

    void Cpu::reset()
    {
        // Set CPU to a known initial state
        m_regs.PC = 0x400;
    }

    void Cpu::load_into_ram(const u8 *data, const size_t size)
    {
        m_mem.size = size;
        for (size_t ii = 0; ii < size; ++ii)
        {
            m_mem.data[ii] = data[ii];
        }
    }

    Instruction Cpu::fetch()
    {
        const u8 op = m_mem.data[m_regs.PC];

        const auto desc = DescriptorTables::the()[op];
        const auto bytes = desc->bytes;

        if (bytes == 2)
        {
            u8 operand = m_mem.data[m_regs.PC + 1];
            inc_PC(2);
            return {op, operand, bytes};
        }
        else if (bytes == 3)
        {
            u16 low = m_mem.data[m_regs.PC + 1];
            u16 high = m_mem.data[m_regs.PC + 2] << 8;
            u16 operand = low | high;
            inc_PC(3);
            return {op, operand, bytes};
        }
        else
        {
            inc_PC(1);
            return {op};
        }
    }

    void Cpu::set_ZN_reg_X()
    {
        if (m_regs.X == 0)
        {
            m_flags.Z = 1;
            m_flags.N = 0;
        }
        else
        {
            m_flags.Z = 0;
            if (m_regs.X >> 7)
            {
                m_flags.N = 1;
            }
        }
    }

    void Cpu::set_ZN_reg_A()
    {
        if (m_regs.A == 0)
        {
            m_flags.Z = 1;
            m_flags.N = 0;
        }
        else
        {
            m_flags.Z = 0;
            if (m_regs.A >> 7)
            {
                m_flags.N = 1;
            }
        }
    }

    void Cpu::ADC_IMM(const Instruction &) { assert(false); }
    void Cpu::ADC_ZP(const Instruction &) { assert(false); }
    void Cpu::ADC_ZPX(const Instruction &) { assert(false); }
    void Cpu::ADC_ABS(const Instruction &) { assert(false); }
    void Cpu::ADC_ABSX(const Instruction &) { assert(false); }
    void Cpu::ADC_ABSY(const Instruction &) { assert(false); }
    void Cpu::ADC_INDX(const Instruction &) { assert(false); }
    void Cpu::ADC_INDY(const Instruction &) { assert(false); }
    void Cpu::AND_IMM(const Instruction &) { assert(false); }
    void Cpu::AND_ZP(const Instruction &) { assert(false); }
    void Cpu::AND_ZPX(const Instruction &) { assert(false); }
    void Cpu::AND_ABS(const Instruction &) { assert(false); }
    void Cpu::AND_ABSX(const Instruction &) { assert(false); }
    void Cpu::AND_ABSY(const Instruction &) { assert(false); }
    void Cpu::AND_INDX(const Instruction &) { assert(false); }
    void Cpu::AND_INDY(const Instruction &) { assert(false); }
    void Cpu::ASL_A(const Instruction &) { assert(false); }
    void Cpu::ASL_ZP(const Instruction &) { assert(false); }
    void Cpu::ASL_ZPX(const Instruction &) { assert(false); }
    void Cpu::ASL_ABS(const Instruction &) { assert(false); }
    void Cpu::ASL_ABSX(const Instruction &) { assert(false); }
    void Cpu::BCC(const Instruction &) { assert(false); }
    void Cpu::BCS(const Instruction &) { assert(false); }
    void Cpu::BEQ(const Instruction &insn)
    {
        if (m_flags.Z)
        {
            if (insn.operand() > 127)
            {
                m_regs.PC += ((int)insn.operand() - 256);
            }
            else
            {
                m_regs.PC += insn.operand();
            }
        }
    }
    void Cpu::BMI(const Instruction &) { assert(false); }
    void Cpu::BNE(const Instruction &insn)
    {

        if (!m_flags.Z)
        {
            if (insn.operand() > 127)
            {
                m_regs.PC += ((int)insn.operand() - 256);
            }
            else
            {
                m_regs.PC += insn.operand();
            }
        }
    }
    void Cpu::BPL(const Instruction &) { assert(false); }
    void Cpu::BVC(const Instruction &) { assert(false); }
    void Cpu::BVS(const Instruction &) { assert(false); }
    void Cpu::BIT_ZP(const Instruction &) { assert(false); }
    void Cpu::BIT_ABS(const Instruction &) { assert(false); }
    void Cpu::BRK(const Instruction &) { assert(false); }
    void Cpu::CLC(const Instruction &) { assert(false); }
    void Cpu::CLD(const Instruction &)
    {
        m_flags.D = 0;
    }
    void Cpu::CLI(const Instruction &) { assert(false); }
    void Cpu::CLV(const Instruction &) { assert(false); }
    void Cpu::CMP_IMM(const Instruction &) { assert(false); }
    void Cpu::CMP_ZP(const Instruction &) { assert(false); }
    void Cpu::CMP_ZPX(const Instruction &) { assert(false); }
    void Cpu::CMP_ABS(const Instruction &) { assert(false); }
    void Cpu::CMP_ABSX(const Instruction &) { assert(false); }
    void Cpu::CMP_ABSY(const Instruction &) { assert(false); }
    void Cpu::CMP_INDX(const Instruction &) { assert(false); }
    void Cpu::CMP_INDY(const Instruction &) { assert(false); }
    void Cpu::CPX_IMM(const Instruction &) { assert(false); }
    void Cpu::CPX_ZP(const Instruction &) { assert(false); }
    void Cpu::CPX_ABS(const Instruction &) { assert(false); }
    void Cpu::CPY_IMM(const Instruction &) { assert(false); }
    void Cpu::CPY_ZP(const Instruction &) { assert(false); }
    void Cpu::CPY_ABS(const Instruction &) { assert(false); }
    void Cpu::DEC_ZP(const Instruction &) { assert(false); }
    void Cpu::DEC_ZPX(const Instruction &) { assert(false); }
    void Cpu::DEC_ABS(const Instruction &) { assert(false); }
    void Cpu::DEC_ABSX(const Instruction &) { assert(false); }
    void Cpu::DEX(const Instruction &)
    {
        m_regs.X--;
        set_ZN_reg_X();
    }
    void Cpu::DEY(const Instruction &) { assert(false); }
    void Cpu::EOR_IMM(const Instruction &) { assert(false); }
    void Cpu::EOR_ZP(const Instruction &) { assert(false); }
    void Cpu::EOR_ZPX(const Instruction &) { assert(false); }
    void Cpu::EOR_ABS(const Instruction &) { assert(false); }
    void Cpu::EOR_ABSX(const Instruction &) { assert(false); }
    void Cpu::EOR_ABSY(const Instruction &) { assert(false); }
    void Cpu::EOR_INDX(const Instruction &) { assert(false); }
    void Cpu::EOR_INDY(const Instruction &) { assert(false); }
    void Cpu::INC_ZP(const Instruction &) { assert(false); }
    void Cpu::INC_ZPX(const Instruction &) { assert(false); }
    void Cpu::INC_ABS(const Instruction &) { assert(false); }
    void Cpu::INC_ABSX(const Instruction &) { assert(false); }
    void Cpu::INX(const Instruction &) { assert(false); }
    void Cpu::INY(const Instruction &) { assert(false); }
    void Cpu::JMP_ABS(const Instruction &insn)
    {
        m_regs.PC = insn.operand();
    }
    void Cpu::JMP_IND(const Instruction &) { assert(false); }
    void Cpu::JSR(const Instruction &) { assert(false); }
    void Cpu::LDA_IMM(const Instruction &insn)
    {
        m_regs.A = (u8)insn.operand();
        set_ZN_reg_A();
    }
    void Cpu::LDA_ZP(const Instruction &) { assert(false); }
    void Cpu::LDA_ZPX(const Instruction &) { assert(false); }
    void Cpu::LDA_ABS(const Instruction &) { assert(false); }
    void Cpu::LDA_ABSX(const Instruction &) { assert(false); }
    void Cpu::LDA_ABSY(const Instruction &) { assert(false); }
    void Cpu::LDA_INDX(const Instruction &) { assert(false); }
    void Cpu::LDA_INDY(const Instruction &) { assert(false); }
    void Cpu::LDX_IMM(const Instruction &insn)
    {
        m_regs.X = (u8)insn.operand();
        set_ZN_reg_X();
    }
    void Cpu::LDX_ZP(const Instruction &) { assert(false); }
    void Cpu::LDX_ZPY(const Instruction &) { assert(false); }
    void Cpu::LDX_ABS(const Instruction &) { assert(false); }
    void Cpu::LDX_ABSY(const Instruction &) { assert(false); }
    void Cpu::LDY_IMM(const Instruction &) { assert(false); }
    void Cpu::LDY_ZP(const Instruction &) { assert(false); }
    void Cpu::LDY_ZPX(const Instruction &) { assert(false); }
    void Cpu::LDY_ABS(const Instruction &) { assert(false); }
    void Cpu::LDY_ABSX(const Instruction &) { assert(false); }
    void Cpu::LSR_A(const Instruction &) { assert(false); }
    void Cpu::LSR_ZP(const Instruction &) { assert(false); }
    void Cpu::LSR_ZPX(const Instruction &) { assert(false); }
    void Cpu::LSR_ABS(const Instruction &) { assert(false); }
    void Cpu::LSR_ABSX(const Instruction &) { assert(false); }
    void Cpu::NOP(const Instruction &) { assert(false); }
    void Cpu::ORA_IMM(const Instruction &) { assert(false); }
    void Cpu::ORA_ZP(const Instruction &) { assert(false); }
    void Cpu::ORA_ZPX(const Instruction &) { assert(false); }
    void Cpu::ORA_ABS(const Instruction &) { assert(false); }
    void Cpu::ORA_ABSX(const Instruction &) { assert(false); }
    void Cpu::ORA_ABSY(const Instruction &) { assert(false); }
    void Cpu::ORA_INDX(const Instruction &) { assert(false); }
    void Cpu::ORA_INDY(const Instruction &) { assert(false); }
    void Cpu::PHA(const Instruction &) { assert(false); }
    void Cpu::PHP(const Instruction &) { assert(false); }
    void Cpu::PLA(const Instruction &) { assert(false); }
    void Cpu::PLP(const Instruction &) { assert(false); }
    void Cpu::ROL_A(const Instruction &) { assert(false); }
    void Cpu::ROL_ZP(const Instruction &) { assert(false); }
    void Cpu::ROL_ZPX(const Instruction &) { assert(false); }
    void Cpu::ROL_ABS(const Instruction &) { assert(false); }
    void Cpu::ROL_ABSX(const Instruction &) { assert(false); }
    void Cpu::ROR_A(const Instruction &) { assert(false); }
    void Cpu::ROR_ZP(const Instruction &) { assert(false); }
    void Cpu::ROR_ZPX(const Instruction &) { assert(false); }
    void Cpu::ROR_ABS(const Instruction &) { assert(false); }
    void Cpu::ROR_ABSX(const Instruction &) { assert(false); }
    void Cpu::RTI(const Instruction &) { assert(false); }
    void Cpu::RTS(const Instruction &) { assert(false); }
    void Cpu::SBC_IMM(const Instruction &) { assert(false); }
    void Cpu::SBC_ZP(const Instruction &) { assert(false); }
    void Cpu::SBC_ZPX(const Instruction &) { assert(false); }
    void Cpu::SBC_ABS(const Instruction &) { assert(false); }
    void Cpu::SBC_ABSX(const Instruction &) { assert(false); }
    void Cpu::SBC_ABSY(const Instruction &) { assert(false); }
    void Cpu::SBC_INDX(const Instruction &) { assert(false); }
    void Cpu::SBC_INDY(const Instruction &) { assert(false); }
    void Cpu::SEC(const Instruction &) { assert(false); }
    void Cpu::SED(const Instruction &) { assert(false); }
    void Cpu::SEI(const Instruction &) { assert(false); }
    void Cpu::STA_ZP(const Instruction &) { assert(false); }
    void Cpu::STA_ZPX(const Instruction &) { assert(false); }
    void Cpu::STA_ABS(const Instruction &insn)
    {
        m_mem.data[insn.operand()] = m_regs.A;
    }
    void Cpu::STA_ABSX(const Instruction &) { assert(false); }
    void Cpu::STA_ABSY(const Instruction &) { assert(false); }
    void Cpu::STA_INDX(const Instruction &) { assert(false); }
    void Cpu::STA_INDY(const Instruction &) { assert(false); }
    void Cpu::STX_ZP(const Instruction &) { assert(false); }
    void Cpu::STX_ZPY(const Instruction &) { assert(false); }
    void Cpu::STX_ABS(const Instruction &) { assert(false); }
    void Cpu::STY_ZP(const Instruction &) { assert(false); }
    void Cpu::STY_ZPX(const Instruction &) { assert(false); }
    void Cpu::STY_ABS(const Instruction &) { assert(false); }
    void Cpu::TAX(const Instruction &) { assert(false); }
    void Cpu::TAY(const Instruction &) { assert(false); }
    void Cpu::TSX(const Instruction &) { assert(false); }
    void Cpu::TXA(const Instruction &) { assert(false); }
    void Cpu::TXS(const Instruction &)
    {
        m_regs.SP = m_regs.X;
    }
    void Cpu::TYA(const Instruction &) { assert(false); }
    void Cpu::Undocumented(const Instruction &) { assert(false); }
}