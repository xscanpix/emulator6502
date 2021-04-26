#pragma once

#include "Interpreter.h"
#include "Instruction.h"
#include "Types.h"
#include "common.h"
#include "Opcodes.h"

#include <assert.h>

#include <memory>

namespace Emulator
{
    struct RAM
    {
        u8 data[64 * KB];
        size_t size{0};
    };

    struct Flags
    {
        u8 C : 1;
        u8 Z : 1;
        u8 I : 1;
        u8 D : 1;
        u8 B : 1;
        u8 R : 1;
        u8 V : 1;
        u8 N : 1;
    };

    struct Registers
    {
        u16 PC{0};
        u8 SP{0};
        u8 A{0};
        u8 X{0};
        u8 Y{0};
    };

    class Cpu final : public Interpreter
    {
    public:
        Cpu()
        {
            reset();
        }

        void load_into_ram(const u8 *data, const size_t size);

        Instruction fetch();

        u16 cpu_pc() const;
        std::string cpu_state() const;
        std::string cpu_stack() const;

    private:
        RAM m_mem;
        Registers m_regs;
        Flags m_flags;

    private:
        void reset();
        void inc_PC(const int value = 1) { m_regs.PC += value; }

        void set_flags(const u8 new_flags);
        u8 get_flags();

        u8 zp_addr(const u16 addr);

        void push_stack(const u8 val);
        u8 pop_stack();

        void set_ZN_reg_A();
        void set_ZN_reg_X();
        void set_ZN_reg_Y();

        void set_flags_after_compare_reg_A(const u8 value);
        void set_flags_after_compare_reg_X(const u8 value);
        void set_flags_after_compare_reg_Y(const u8 value);

    private:
        virtual void ADC_IMM(const Instruction &) override;
        virtual void ADC_ZP(const Instruction &) override;
        virtual void ADC_ZPX(const Instruction &) override;
        virtual void ADC_ABS(const Instruction &) override;
        virtual void ADC_ABSX(const Instruction &) override;
        virtual void ADC_ABSY(const Instruction &) override;
        virtual void ADC_INDX(const Instruction &) override;
        virtual void ADC_INDY(const Instruction &) override;
        virtual void AND_IMM(const Instruction &) override;
        virtual void AND_ZP(const Instruction &) override;
        virtual void AND_ZPX(const Instruction &) override;
        virtual void AND_ABS(const Instruction &) override;
        virtual void AND_ABSX(const Instruction &) override;
        virtual void AND_ABSY(const Instruction &) override;
        virtual void AND_INDX(const Instruction &) override;
        virtual void AND_INDY(const Instruction &) override;
        virtual void ASL_A(const Instruction &) override;
        virtual void ASL_ZP(const Instruction &) override;
        virtual void ASL_ZPX(const Instruction &) override;
        virtual void ASL_ABS(const Instruction &) override;
        virtual void ASL_ABSX(const Instruction &) override;
        virtual void BCC(const Instruction &) override;
        virtual void BCS(const Instruction &) override;
        virtual void BEQ(const Instruction &) override;
        virtual void BMI(const Instruction &) override;
        virtual void BNE(const Instruction &) override;
        virtual void BPL(const Instruction &) override;
        virtual void BVC(const Instruction &) override;
        virtual void BVS(const Instruction &) override;
        virtual void BIT_ZP(const Instruction &) override;
        virtual void BIT_ABS(const Instruction &) override;
        virtual void BRK(const Instruction &) override;
        virtual void CLC(const Instruction &) override;
        virtual void CLD(const Instruction &) override;
        virtual void CLI(const Instruction &) override;
        virtual void CLV(const Instruction &) override;
        virtual void CMP_IMM(const Instruction &) override;
        virtual void CMP_ZP(const Instruction &) override;
        virtual void CMP_ZPX(const Instruction &) override;
        virtual void CMP_ABS(const Instruction &) override;
        virtual void CMP_ABSX(const Instruction &) override;
        virtual void CMP_ABSY(const Instruction &) override;
        virtual void CMP_INDX(const Instruction &) override;
        virtual void CMP_INDY(const Instruction &) override;
        virtual void CPX_IMM(const Instruction &) override;
        virtual void CPX_ZP(const Instruction &) override;
        virtual void CPX_ABS(const Instruction &) override;
        virtual void CPY_IMM(const Instruction &) override;
        virtual void CPY_ZP(const Instruction &) override;
        virtual void CPY_ABS(const Instruction &) override;
        virtual void DEC_ZP(const Instruction &) override;
        virtual void DEC_ZPX(const Instruction &) override;
        virtual void DEC_ABS(const Instruction &) override;
        virtual void DEC_ABSX(const Instruction &) override;
        virtual void DEX(const Instruction &) override;
        virtual void DEY(const Instruction &) override;
        virtual void EOR_IMM(const Instruction &) override;
        virtual void EOR_ZP(const Instruction &) override;
        virtual void EOR_ZPX(const Instruction &) override;
        virtual void EOR_ABS(const Instruction &) override;
        virtual void EOR_ABSX(const Instruction &) override;
        virtual void EOR_ABSY(const Instruction &) override;
        virtual void EOR_INDX(const Instruction &) override;
        virtual void EOR_INDY(const Instruction &) override;
        virtual void INC_ZP(const Instruction &) override;
        virtual void INC_ZPX(const Instruction &) override;
        virtual void INC_ABS(const Instruction &) override;
        virtual void INC_ABSX(const Instruction &) override;
        virtual void INX(const Instruction &) override;
        virtual void INY(const Instruction &) override;
        virtual void JMP_ABS(const Instruction &) override;
        virtual void JMP_IND(const Instruction &) override;
        virtual void JSR(const Instruction &) override;
        virtual void LDA_IMM(const Instruction &) override;
        virtual void LDA_ZP(const Instruction &) override;
        virtual void LDA_ZPX(const Instruction &) override;
        virtual void LDA_ABS(const Instruction &) override;
        virtual void LDA_ABSX(const Instruction &) override;
        virtual void LDA_ABSY(const Instruction &) override;
        virtual void LDA_INDX(const Instruction &) override;
        virtual void LDA_INDY(const Instruction &) override;
        virtual void LDX_IMM(const Instruction &) override;
        virtual void LDX_ZP(const Instruction &) override;
        virtual void LDX_ZPY(const Instruction &) override;
        virtual void LDX_ABS(const Instruction &) override;
        virtual void LDX_ABSY(const Instruction &) override;
        virtual void LDY_IMM(const Instruction &) override;
        virtual void LDY_ZP(const Instruction &) override;
        virtual void LDY_ZPX(const Instruction &) override;
        virtual void LDY_ABS(const Instruction &) override;
        virtual void LDY_ABSX(const Instruction &) override;
        virtual void LSR_A(const Instruction &) override;
        virtual void LSR_ZP(const Instruction &) override;
        virtual void LSR_ZPX(const Instruction &) override;
        virtual void LSR_ABS(const Instruction &) override;
        virtual void LSR_ABSX(const Instruction &) override;
        virtual void NOP(const Instruction &) override;
        virtual void ORA_IMM(const Instruction &) override;
        virtual void ORA_ZP(const Instruction &) override;
        virtual void ORA_ZPX(const Instruction &) override;
        virtual void ORA_ABS(const Instruction &) override;
        virtual void ORA_ABSX(const Instruction &) override;
        virtual void ORA_ABSY(const Instruction &) override;
        virtual void ORA_INDX(const Instruction &) override;
        virtual void ORA_INDY(const Instruction &) override;
        virtual void PHA(const Instruction &) override;
        virtual void PHP(const Instruction &) override;
        virtual void PLA(const Instruction &) override;
        virtual void PLP(const Instruction &) override;
        virtual void ROL_A(const Instruction &) override;
        virtual void ROL_ZP(const Instruction &) override;
        virtual void ROL_ZPX(const Instruction &) override;
        virtual void ROL_ABS(const Instruction &) override;
        virtual void ROL_ABSX(const Instruction &) override;
        virtual void ROR_A(const Instruction &) override;
        virtual void ROR_ZP(const Instruction &) override;
        virtual void ROR_ZPX(const Instruction &) override;
        virtual void ROR_ABS(const Instruction &) override;
        virtual void ROR_ABSX(const Instruction &) override;
        virtual void RTI(const Instruction &) override;
        virtual void RTS(const Instruction &) override;
        virtual void SBC_IMM(const Instruction &) override;
        virtual void SBC_ZP(const Instruction &) override;
        virtual void SBC_ZPX(const Instruction &) override;
        virtual void SBC_ABS(const Instruction &) override;
        virtual void SBC_ABSX(const Instruction &) override;
        virtual void SBC_ABSY(const Instruction &) override;
        virtual void SBC_INDX(const Instruction &) override;
        virtual void SBC_INDY(const Instruction &) override;
        virtual void SEC(const Instruction &) override;
        virtual void SED(const Instruction &) override;
        virtual void SEI(const Instruction &) override;
        virtual void STA_ZP(const Instruction &) override;
        virtual void STA_ZPX(const Instruction &) override;
        virtual void STA_ABS(const Instruction &) override;
        virtual void STA_ABSX(const Instruction &) override;
        virtual void STA_ABSY(const Instruction &) override;
        virtual void STA_INDX(const Instruction &) override;
        virtual void STA_INDY(const Instruction &) override;
        virtual void STX_ZP(const Instruction &) override;
        virtual void STX_ZPY(const Instruction &) override;
        virtual void STX_ABS(const Instruction &) override;
        virtual void STY_ZP(const Instruction &) override;
        virtual void STY_ZPX(const Instruction &) override;
        virtual void STY_ABS(const Instruction &) override;
        virtual void TAX(const Instruction &) override;
        virtual void TAY(const Instruction &) override;
        virtual void TSX(const Instruction &) override;
        virtual void TXA(const Instruction &) override;
        virtual void TXS(const Instruction &) override;
        virtual void TYA(const Instruction &) override;
        virtual void Undocumented(const Instruction &) override;
    };
}