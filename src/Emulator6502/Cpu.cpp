#include "Cpu.h"

#include <assert.h>
#include <sstream>
#include <iomanip>

namespace Emulator
{
    std::string Cpu::cpu_state() const
    {
        std::stringstream ss;

        ss << "Flags:  "
           << "CZIDBON "
           << "\n";
        ss << "        "
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

    std::string Cpu::cpu_stack() const
    {
        std::stringstream ss;

        ss << std::uppercase << std::setfill('0') << std::hex;

        size_t row = 0;
        size_t index = 0;

        auto stream_line = [&]() {
            ss << std::setw(8) << row << ": ";
            row += 0x10;
            for (size_t ii = 0; ii < 0x10; ++ii)
            {
                ss << std::setw(2) << (int)m_mem.data[0x100 + index + ii];
            }
            index += 0x10;
            ss << "\n";
        };

        while (index < 0xFFFF)
        {
            stream_line();
        }

        return ss.str();
    }

    void Cpu::reset()
    {
        // Set CPU to a known initial state
        m_regs.PC = 0x400;

        m_flags.C = 0;
        m_flags.Z = 0;
        m_flags.I = 0;
        m_flags.D = 0;
        m_flags.O = 0;
        m_flags.N = 0;
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

    void Cpu::set_flags(const u8 new_flags)
    {
        m_flags.C = (new_flags >> 0) & 1;
        m_flags.Z = (new_flags >> 1) & 1;
        m_flags.I = (new_flags >> 2) & 1;
        m_flags.D = (new_flags >> 3) & 1;
        m_flags.O = (new_flags >> 6) & 1;
        m_flags.N = (new_flags >> 7) & 1;
    }

    u8 Cpu::get_flags()
    {
        return m_flags.C << 0 |
               m_flags.Z << 1 |
               m_flags.I << 2 |
               m_flags.D << 3 |
               m_flags.O << 6 |
               m_flags.N << 7;
    }

    void Cpu::set_ZN_reg_A()
    {
        m_flags.Z = m_regs.A == 0 ? 1 : 0;
        m_flags.N = (m_regs.A >> 7) & 1;
    }

    void Cpu::set_ZN_reg_X()
    {
        m_flags.Z = m_regs.X == 0 ? 1 : 0;
        m_flags.N = (m_regs.X >> 7) & 1;
    }

    void Cpu::set_ZN_reg_Y()
    {
        m_flags.Z = m_regs.Y == 0 ? 1 : 0;
        m_flags.N = (m_regs.Y >> 7) & 1;
    }

    void Cpu::set_flags_after_compare_reg_A(const u8 value)
    {
        const int result = m_regs.A - value;

        if (result < 0)
        {
            m_flags.C = 0;
            m_flags.Z = 0;
        }
        else if (result == 0)
        {
            m_flags.C = 1;
            m_flags.Z = 1;
        }
        else
        {
            m_flags.Z = 0;
            m_flags.C = 1;
        }

        m_flags.N = (result >> 7) & 1;
    }

    void Cpu::set_flags_after_compare_reg_X(const u8 value)
    {
        const int result = m_regs.X - value;

        if (result < 0)
        {
            m_flags.C = 0;
            m_flags.Z = 0;
        }
        else if (result == 0)
        {
            m_flags.C = 1;
            m_flags.Z = 1;
        }
        else
        {
            m_flags.Z = 0;
            m_flags.C = 1;
        }

        m_flags.N = (result >> 7) & 1;
    }

    void Cpu::set_flags_after_compare_reg_Y(const u8 value)
    {
        const int result = m_regs.Y - value;

        if (result < 0)
        {
            m_flags.C = 0;
            m_flags.Z = 0;
        }
        else if (result == 0)
        {
            m_flags.C = 1;
            m_flags.Z = 1;
        }
        else
        {
            m_flags.Z = 0;
            m_flags.C = 1;
        }

        m_flags.N = (result >> 7) & 1;
    }

    void Cpu::ADC_IMM(const Instruction &insn)
    {
        const u16 result = m_regs.A + m_flags.C + insn.operand();

        if (m_flags.D)
        {
            assert(false);
        }

        m_flags.O = ((m_regs.A ^ result) & (insn.operand() ^ result) & 0x80) == 0x80 ? 1 : 0;
        m_flags.C = (result & 0x100) == 0x100 ? 1 : 0;
        m_flags.Z = result == 0 ? 1 : 0;
        m_flags.N = (result >> 7) & 1;
        m_regs.A = result & 0xFF;
    }
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
    void Cpu::BCC(const Instruction &insn)
    {
        if (!m_flags.C)
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
    void Cpu::BCS(const Instruction &insn)
    {
        if (m_flags.C)
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
    void Cpu::BMI(const Instruction &insn)
    {
        if (m_flags.N)
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
    void Cpu::BPL(const Instruction &insn)
    {
        if (!m_flags.N)
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
    void Cpu::BVC(const Instruction &insn)
    {
        if (!m_flags.O)
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
    void Cpu::BVS(const Instruction &insn)
    {
        if (m_flags.O)
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
    void Cpu::BIT_ZP(const Instruction &) { assert(false); }
    void Cpu::BIT_ABS(const Instruction &) { assert(false); }
    void Cpu::BRK(const Instruction &)
    {
        m_mem.data[0x100 + m_regs.SP] = (m_regs.PC >> 8);
        m_regs.SP--;
        m_mem.data[0x100 + m_regs.SP] = (m_regs.PC & 0xFF);
        m_regs.SP--;
        m_mem.data[0x100 + m_regs.SP] = get_flags();
        m_regs.SP--;

        u16 lsb = m_mem.data[0xFFFE];
        u16 msb = m_mem.data[0xFFFF] << 8;

        m_regs.PC = msb | lsb;

        m_flags.B = 1;
    }
    void Cpu::CLC(const Instruction &)
    {
        m_flags.C = 0;
    }
    void Cpu::CLD(const Instruction &)
    {
        m_flags.D = 0;
    }
    void Cpu::CLI(const Instruction &) { assert(false); }
    void Cpu::CLV(const Instruction &) { assert(false); }
    void Cpu::CMP_IMM(const Instruction &insn)
    {
        set_flags_after_compare_reg_A(insn.operand());
    }
    void Cpu::CMP_ZP(const Instruction &) { assert(false); }
    void Cpu::CMP_ZPX(const Instruction &) { assert(false); }
    void Cpu::CMP_ABS(const Instruction &insn)
    {
        set_flags_after_compare_reg_A(m_mem.data[insn.operand()]);
    }
    void Cpu::CMP_ABSX(const Instruction &) { assert(false); }
    void Cpu::CMP_ABSY(const Instruction &) { assert(false); }
    void Cpu::CMP_INDX(const Instruction &) { assert(false); }
    void Cpu::CMP_INDY(const Instruction &) { assert(false); }
    void Cpu::CPX_IMM(const Instruction &insn)
    {
        set_flags_after_compare_reg_X(insn.operand());
    }
    void Cpu::CPX_ZP(const Instruction &) { assert(false); }
    void Cpu::CPX_ABS(const Instruction &) { assert(false); }
    void Cpu::CPY_IMM(const Instruction &insn)
    {
        set_flags_after_compare_reg_Y(insn.operand());
    }
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
    void Cpu::DEY(const Instruction &)
    {
        m_regs.Y--;
        set_ZN_reg_Y();
    }
    void Cpu::EOR_IMM(const Instruction &insn)
    {
        m_regs.A = m_regs.A ^ (u8)insn.operand();

        m_flags.Z = m_regs.A == 0 ? 1 : 0;
        m_flags.N = (m_regs.A >> 7) & 1;
    }
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
    void Cpu::INX(const Instruction &)
    {
        m_regs.X++;
        set_ZN_reg_X();
    }
    void Cpu::INY(const Instruction &)
    {
        m_regs.Y++;
        set_ZN_reg_Y();
    }
    void Cpu::JMP_ABS(const Instruction &insn)
    {
        m_regs.PC = insn.operand();
    }
    void Cpu::JMP_IND(const Instruction &insn)
    {
        u16 target = 0;

        if ((insn.operand() & 0xFF) == 0xFF)
        {
            // Original 6502 does not correctly compute target address if LSB is 0xFF
            u8 lsb = m_mem.data[insn.operand()];
            u8 msb = m_mem.data[insn.operand() & 0xFF00];

            target = (msb << 8) | lsb;
        }
        else
        {
            target |= m_mem.data[insn.operand()];
            target |= m_mem.data[insn.operand() + 1] << 8;
        }

        m_regs.PC = target;
    }
    void Cpu::JSR(const Instruction &insn)
    {
        std::cout << cpu_state();
        const u16 return_addr = m_regs.PC - 1;

        m_mem.data[0x100 + m_regs.SP] = (return_addr >> 8) & 0xFF;
        m_regs.SP--;
        m_mem.data[0x100 + m_regs.SP] = return_addr & 0xFF;
        m_regs.SP--;

        m_regs.PC = insn.operand();
    }
    void Cpu::LDA_IMM(const Instruction &insn)
    {
        m_regs.A = (u8)insn.operand();
        set_ZN_reg_A();
    }
    void Cpu::LDA_ZP(const Instruction &) { assert(false); }
    void Cpu::LDA_ZPX(const Instruction &) { assert(false); }
    void Cpu::LDA_ABS(const Instruction &insn)
    {
        m_regs.A = m_mem.data[insn.operand()];
        set_ZN_reg_A();
    }
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
    void Cpu::LDY_IMM(const Instruction &insn)
    {
        m_regs.Y = (u8)insn.operand();
        set_ZN_reg_Y();
    }
    void Cpu::LDY_ZP(const Instruction &) { assert(false); }
    void Cpu::LDY_ZPX(const Instruction &) { assert(false); }
    void Cpu::LDY_ABS(const Instruction &) { assert(false); }
    void Cpu::LDY_ABSX(const Instruction &) { assert(false); }
    void Cpu::LSR_A(const Instruction &) { assert(false); }
    void Cpu::LSR_ZP(const Instruction &) { assert(false); }
    void Cpu::LSR_ZPX(const Instruction &) { assert(false); }
    void Cpu::LSR_ABS(const Instruction &) { assert(false); }
    void Cpu::LSR_ABSX(const Instruction &) { assert(false); }
    void Cpu::NOP(const Instruction &) {}
    void Cpu::ORA_IMM(const Instruction &) { assert(false); }
    void Cpu::ORA_ZP(const Instruction &) { assert(false); }
    void Cpu::ORA_ZPX(const Instruction &) { assert(false); }
    void Cpu::ORA_ABS(const Instruction &) { assert(false); }
    void Cpu::ORA_ABSX(const Instruction &) { assert(false); }
    void Cpu::ORA_ABSY(const Instruction &) { assert(false); }
    void Cpu::ORA_INDX(const Instruction &) { assert(false); }
    void Cpu::ORA_INDY(const Instruction &) { assert(false); }
    void Cpu::PHA(const Instruction &)
    {
        m_mem.data[0x100 + m_regs.SP] = m_regs.A;
        m_regs.SP--;
    }
    void Cpu::PHP(const Instruction &)
    {
        auto flags = get_flags();
        flags |= (1 << 4);
        flags |= (1 << 5);
        m_mem.data[0x100 + m_regs.SP] = flags;
        m_regs.SP--;
    }
    void Cpu::PLA(const Instruction &)
    {
        m_regs.SP++;
        m_regs.A = m_mem.data[0x100 + m_regs.SP];
        set_ZN_reg_A();
    }
    void Cpu::PLP(const Instruction &)
    {
        m_regs.SP++;
        set_flags(m_mem.data[0x100 + m_regs.SP]);
    }
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
    void Cpu::RTS(const Instruction &)
    {
        m_regs.SP++;
        const u16 lsb = m_mem.data[0x100 + m_regs.SP];
        m_regs.SP++;
        const u16 msb = m_mem.data[0x100 + m_regs.SP];

        m_regs.PC = ((msb << 8) | lsb) + 1;
    }
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
    void Cpu::TAX(const Instruction &)
    {
        m_regs.X = m_regs.A;
        set_ZN_reg_X();
    }
    void Cpu::TAY(const Instruction &)
    {
        m_regs.Y = m_regs.A;
        set_ZN_reg_Y();
    }
    void Cpu::TSX(const Instruction &)
    {
        m_regs.X = m_regs.SP;
        set_ZN_reg_X();
    }
    void Cpu::TXA(const Instruction &)
    {
        m_regs.A = m_regs.X;
        set_ZN_reg_A();
    }
    void Cpu::TXS(const Instruction &)
    {
        m_regs.SP = m_regs.X;
    }
    void Cpu::TYA(const Instruction &)
    {
        m_regs.A = m_regs.Y;
        set_ZN_reg_A();
    }
    void Cpu::Undocumented(const Instruction &) { assert(false); }
}