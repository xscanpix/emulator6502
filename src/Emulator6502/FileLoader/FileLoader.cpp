#include "FileLoader.h"

#include <iostream>
#include <fstream>
#include <iomanip>

namespace Emulator
{
    std::ostream &operator<<(std::ostream &out, const FileLoader &loader)
    {
        out << std::uppercase << std::setfill('0') << std::hex;

        size_t row = 0;
        size_t index = 0;

        auto stream_line = [&]() {
            out << std::setw(8) << row << ": ";
            row += 0x10;
            for (size_t ii = 0; ii < 0x10; ++ii)
            {
                out << std::setw(2) << (int)loader.m_data[index + ii];
            }
            index += 0x10;
            out << "\n";
        };

        while (index < loader.m_size)
        {
            stream_line();
        }

        return out;
    }

    size_t FileLoader::from_binary(FileLoader &loader, const char *file_path)
    {
        std::streampos size;
        std::ifstream ifs;

        std::cout << "Opening file '" << file_path << "'\n";

        ifs.open(file_path, std::ios::binary | std::ios::in | std::ios::ate);

        if (ifs.is_open())
        {
            size = ifs.tellg();

            loader.m_size = size;
            loader.m_data = std::make_unique<u8[]>(size);

            ifs.seekg(0, std::ios::beg);
            ifs.read((char *)loader.m_data.get(), size);
            ifs.close();

            std::cout << "  Read " << loader.m_size << " bytes.\n";
        }
        else
        {
            std::cout << "  Failed to open file. \n";
        }

        return loader.m_size;
    }
}