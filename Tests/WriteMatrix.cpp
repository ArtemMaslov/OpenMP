#include <iostream>
#include <ostream>
#include <array>

#include <Mas/Matrix/Matrix.h>
#include <Mas/Utils/UtilsIO.h>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    const char* const rightAnswer = 
    "[\n"
        "\t[10 11 12]\n"
        "\t[13 14 15]\n"
        "\t[16 17 18]\n"
        "\t[19 20 21]\n"
    "]";

    std::array<int, 4*3> array
    {
        10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20, 21
    };
    Matrix<int> m = Matrix<int>(array.begin(), array.end(), 4, 3);

    m.Write("tmp.txt");

    std::string data = Mas::Utils::IO::ReadFile("tmp.txt");
    if (data == rightAnswer)
        return 0;

    std::cout
        << "В файл записано:\n"
        << data
        << "\nОжидалось:\n"
        << rightAnswer
        << std::endl;
    return 1;
}