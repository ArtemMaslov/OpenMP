#include <iostream>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    Matrix<int> A1 = MatrixFactory<int>::Read("../../Tests/Matrices/A1.txt");
    Matrix<int> B1 = MatrixFactory<int>::Read("../../Tests/Matrices/B1.txt");
    Matrix<int> C1 = Matrix<int>(A1.GetRowsCount(), B1.GetColumnsCount());
    Matrix<int> rightAnswer = MatrixFactory<int>::Read("../../Tests/Matrices/C1.txt");

    Matrix<int> B1T = B1.CreateTranspose();

    std::cout << "MulABT_Seq" << std::endl;
    Matrix<int>::MulABT_Seq(C1, A1, B1T);
    if (C1.CompareDetailed(rightAnswer) == false)
        return 1;

    return 0;
}