#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Instruction.h"
#include "Opcodes.h"
#include "FileLoader/FileLoader.h"

#include "Cpu.h"

using namespace Emulator;

int main(int argc, char *const argv[])
{
    (void)argc;
    (void)argv;

    Cpu cpu = {};

    {
        FileLoader loader;
        FileLoader::from_binary(loader, "./input_binaries/6502_functional_test.bin");
        cpu.load_into_ram(loader.data(), loader.size());
        cpu.reset();
        //std::cout << loader;
    }

    while (true)
    {
        std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
        auto insn = cpu.fetch();
        std::cout << insn.stringify();
        (cpu.*insn.handler())(insn);
        //std::cout << cpu.cpu_state();

        if (cpu.cpu_pc() == 0x0)
        {
            for (int i = 0; i < 1; i++)
            {
                std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
                auto insn1 = cpu.fetch();
                std::cout << insn1.stringify();
                (cpu.*insn1.handler())(insn1);
                std::cout << cpu.cpu_state();
            }
            assert(false);
        }
    }

    return 0;
}