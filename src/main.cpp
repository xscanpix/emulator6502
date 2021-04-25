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
        std::cout << loader;
    }

    for (;;)
    {
        auto insn = cpu.fetch();
        std::cout << insn.stringify();
        (cpu.*insn.handler())(insn);
        //std::cout << cpu.cpu_state();
    }

    return 0;
}