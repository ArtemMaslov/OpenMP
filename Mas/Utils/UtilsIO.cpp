#include "Mas/Utils/StringBuilder.h"
#include <istream>
#include <fstream>
#include <stdexcept>
#include <string>
#include <string_view>
#include <vector>

#include <Mas/Utils/UtilsIO.h>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

void Mas::Utils::IO::SkipSpaces(std::istream& in)
{
    int c = std::char_traits<char>::eof();
    do
    {
        c = in.get();
    }
    while (c == ' ' || c == '\t' || c == '\n');
    in.unget();
}

std::string Mas::Utils::IO::ReadFile(std::string_view path)
{
    std::ifstream ifs{path.data(), std::ios::in | std::ios::ate};

    if (!ifs)
    {
        StringBuilder err {};
        err << "Ошибка открытия файла для чтения \"" << path << "\".";
        throw std::runtime_error(err);
    }

    std::ifstream::pos_type fileSize = ifs.tellg();
    ifs.seekg(0, std::ios::beg);

    std::vector<char> data {};
    data.reserve(static_cast<size_t>(fileSize));
    ifs.read(data.data(), fileSize);
    return std::string(data.data(), static_cast<size_t>(fileSize));
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///