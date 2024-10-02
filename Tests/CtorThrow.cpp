#include <Mas/Matrix/Matrix.h>
#include <array>
#include <iostream>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    const size_t actualColumnsCount = 5;
    const size_t erroredColumnsCount = 4;
    std::array<int, 3*actualColumnsCount> array
    {
         1,  2,  3,  4,  5,
         6,  7,  8,  9, 10,
        11, 12, 13, 14, 15
    };
    std::cout << "Prepare for ctor throw." << std::endl;
    try
    {
        Matrix<int> m = Matrix<int>(array.begin(), array.end(), 3, erroredColumnsCount);
        std::cout << "No throw detected" << std::endl;
        return 1;
    }
    catch(...)
    {
        std::cout << "Throw detected. Check address sanitizer for memory leakage" << std::endl;
        return 0;
    }
}