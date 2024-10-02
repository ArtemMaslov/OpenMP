#include <array>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    Matrix<int> m = MatrixFactory<int>::Read("../../Tests/Matrices/m1.txt");
    std::array<int, 3*5> rightArray
    {
         1,  2,  3,  4,  5,
         6,  7,  8,  9, 10,
        11, 12, 13, 14, 15
    };
    Matrix<int> rightMatrix = Matrix<int>(rightArray.begin(), rightArray.end(), 3, 5);
    return (m == rightMatrix) ? 0 : 1;
}