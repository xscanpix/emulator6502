#pragma once

#include "Types.h"

#include <sstream>
#include <memory>

namespace Emulator
{
    class FileLoader
    {
    public:
        static size_t from_binary(FileLoader &loader, const char *file_path);

        friend std::ostream &operator<<(std::ostream &, const FileLoader &);

        auto data() const { return m_data.get(); }
        auto size() const { return m_size; }

    private:
        size_t m_size{0};
        std::unique_ptr<u8[]> m_data{nullptr};
    };
}