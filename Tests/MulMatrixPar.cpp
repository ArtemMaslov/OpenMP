#include <iostream>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

using scalar = double;

using MatrixI = Matrix<int>;
using MatrixS = Matrix<scalar>;
using intMethod = void (*)(MatrixI& dst, const MatrixI& A, const MatrixI& B);
using scalarMethod = void (*)(MatrixS& dst, const MatrixS& A, const MatrixS& B);

void TestMethod(intMethod IntMethod, scalarMethod ScalarMethod, const char* const methodName)
{
    std::cout << methodName << std::endl;

    Matrix<int> A1 = MatrixFactory<int>::Read("../../Tests/Matrices/A1.txt");
    Matrix<int> B1 = MatrixFactory<int>::Read("../../Tests/Matrices/B1.txt");
    Matrix<int> C1 = Matrix<int>(A1.GetRowsCount(), B1.GetColumnsCount());
    Matrix<int> rightAnswer = MatrixFactory<int>::Read("../../Tests/Matrices/C1.txt");

    Matrix<int> B1T = B1.CreateTranspose();

    IntMethod(C1, A1, B1T);
    if (C1.CompareDetailed(rightAnswer) == false)
        exit(1);
    std::cout << "Int multiplication passed" << std::endl;

    const size_t matrixSize = 100;
    const size_t testsCount = 10;

    for (size_t st = 0; st < testsCount; st++)
    {
        Matrix<scalar> A = MatrixFactory<scalar>::CreateRandomFloat
        (
            matrixSize,
            matrixSize,
            -1e6,
            1e6
        );
        Matrix<scalar> BT = MatrixFactory<scalar>::CreateRandomFloat
        (
            matrixSize,
            matrixSize,
            -1e6,
            1e6
        ).CreateTranspose();
        Matrix<scalar> CrightAnswer = Matrix<scalar>(matrixSize, matrixSize);
        Matrix<scalar> Ctest = Matrix<scalar>(matrixSize, matrixSize);

        Matrix<scalar>::MulABT_Seq(CrightAnswer, A, BT);
        ScalarMethod(Ctest, A, BT);
        if (Ctest.CompareDetailed(CrightAnswer, 1e-7) == false)
            exit(1);

        std::cout << "Scalar multiplication " << st + 1 << " passed" << std::endl;
    }
}

int main(int argc, char* argv[])
{
    intMethod methodsI[] = 
    {
        &MatrixI::MulABT_Par,
        &MatrixI::MulABT_Par2,
        &MatrixI::MulABT_Par3,
        &MatrixI::MulABT_Par4,
        &MatrixI::MulABT_Par5,
        &MatrixI::MulABT_Par6
    };
    const size_t count = sizeof(methodsI) / sizeof(intMethod);
    scalarMethod methodsS[count] = 
    {
        &MatrixS::MulABT_Par,
        &MatrixS::MulABT_Par2,
        &MatrixS::MulABT_Par3,
        &MatrixS::MulABT_Par4,
        &MatrixS::MulABT_Par5,
        &MatrixS::MulABT_Par6
    };
    const char* const names[count] =
    {
        "MulABT_Par",
        "MulABT_Par2",
        "MulABT_Par3",
        "MulABT_Par4",
        "MulABT_Par5",
        "MulABT_Par6",
    };

    for (size_t st = 0; st < count; st++)
    {
        TestMethod(methodsI[st], methodsS[st], names[st]);
    }
    return 0;
}