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
        //std::cout << loader;
    }

    while(true)
    {
        std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
        auto insn = cpu.fetch();
        std::cout <<  insn.stringify();
        (cpu.*insn.handler())(insn);
        std::cout << cpu.cpu_state();
    
        if(cpu.cpu_pc() == 0x0f65)
        {
            std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
            auto insn1 = cpu.fetch();
            std::cout <<  insn1.stringify();
            (cpu.*insn1.handler())(insn1);
            std::cout << cpu.cpu_state();

            std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
            auto insn2 = cpu.fetch();
            std::cout <<  insn2.stringify();
            (cpu.*insn2.handler())(insn2);
            std::cout << cpu.cpu_state();

            std::cout << "[" << std::hex << cpu.cpu_pc() << "]: ";
            auto insn3 = cpu.fetch();
            std::cout <<  insn3.stringify();
            (cpu.*insn3.handler())(insn3);
            std::cout << cpu.cpu_state();

            //std::cout << cpu.cpu_stack();

            assert(false);

        }
        
    }

    return 0;
}