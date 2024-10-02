#include <Mas/Utils/StringBuilder.h>

using namespace Mas::Utils;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

StringBuilder::StringBuilder() : std::string()
{
}

StringBuilder::StringBuilder(const std::string& str) : std::string(str)
{
}

StringBuilder::StringBuilder(std::string&& str) : std::string(std::move(str))
{
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///