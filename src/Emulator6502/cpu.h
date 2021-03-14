#pragma once

#include "common.h"
#include "opcode.h"

namespace Emulator6502 
{
    struct registers
    {
        u16 PC;
        u8  SP;
        u8  A;
        u8  X;
        u8  Y;
        u8  PS;
    };
    typedef struct registers registers_t;

    struct memory
    {
        const size_t SIZE = 64 * KB;
        u8 data[64 * KB];
    };
    typedef struct memory memory_t;

    class CPU 
    {
        public:
        Opcode FetchInstruction();
        void Process(const Opcode op);

        private:
        void IncPC(const u8 val);
        void DecPC(const u8 val);

        private:
        registers_t regs;
        memory_t    mem;
    };
}
