#include <stdio.h>
#include <iomanip>
#include <iostream>
#include <sstream>

#include "Instruction.h"
#include "opcode.h"
#include "FileLoader/FileLoader.h"

#include "Cpu.h"

using namespace Emulator;

int main(int argc, char *const argv[])
{
    (void)argc;
    (void)argv;

    {
        FileLoader loader;
        FileLoader::from_binary(loader, "./input_binaries/6502_functional_test.bin");
        Cpu::the().load_into_ram(loader.data(), loader.size());
        std::cout << loader;
    }

    Cpu::the().reset();

    auto insn = Cpu::the().fetch();

    std::cout << insn << std::endl;

    return 0;
}