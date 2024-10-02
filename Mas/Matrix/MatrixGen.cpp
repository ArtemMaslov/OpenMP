#include <cstddef>
#include <cstdlib>
#include <iomanip>
#include <iostream>
#include <string>
#include <chrono>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

typedef double scalar;

int main(int argc, char* argv[])
{
    if (argc != 3)
    {
        std::cout << "Первый аргумент командной строки - количество строк матрицы. "
                     "Второй - количество столбцов." << std::endl;
        return 0;
    }

    const size_t rowsCount = std::stoul(argv[1]);
    const size_t columnsCount = std::stoul(argv[2]);
    
    Matrix<scalar> m = MatrixFactory<scalar>::CreateRandomFloat
    (
        rowsCount,
        columnsCount,
        -1e6,
        1e6
    );
    m.Write("randomMatrix.txt");

    return 0;
}