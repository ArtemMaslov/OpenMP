#include <iostream>
#include <cmath>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    const size_t matrixSizes[] = {10, 100, 512, 1024};
    const size_t matrixSizesCount = sizeof(matrixSizes) / sizeof(size_t);
    size_t mulsCounts[matrixSizesCount] = {100000, 100, 2, 1};

    for (size_t st = 0; st < matrixSizesCount; st++)
    {
        std::cout 
            << "Matrix size           = " << matrixSizes[st] << "\n"
            << "Multiplications count = " << mulsCounts[st] << "\n\n";
    }
    std::cout << std::endl;

    using scalar = double;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    for (size_t sizeIndex = 0; sizeIndex < matrixSizesCount; sizeIndex++)
    {
        const size_t matrixSize = matrixSizes[sizeIndex];

        std::cout
            << "Matrix size = " << matrixSize << "\n" << std::endl;

        Matrix<scalar> A = MatrixFactory<scalar>::CreateRandomFloat
        (
            matrixSize,
            matrixSize,
            -1e6,
            1e6
        );
        Matrix<scalar> B = MatrixFactory<scalar>::CreateRandomFloat
        (
            matrixSize,
            matrixSize,
            -1e6,
            1e6
        ).CreateTranspose();
        Matrix<scalar> C = Matrix<scalar>(matrixSize, matrixSize);

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par started." << std::endl;

        auto time1 = std::chrono::high_resolution_clock::now();
        size_t mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par(C, A, B);
        }
        auto time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par2 started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par2(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par3 started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par3(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par4 started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par4(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par5 started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par5(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Par6 started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Par6(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

        std::cout << "\tMulABT_Seq started." << std::endl;

        time1 = std::chrono::high_resolution_clock::now();
        mulsCount = mulsCounts[sizeIndex];
        for (size_t st = 0; st < mulsCount; st++)
        {
            Matrix<scalar>::MulABT_Seq(C, A, B);
        }
        time2 = std::chrono::high_resolution_clock::now();

        std::cout
            << std::fixed
            << std::setprecision(6)
            << "\tTime = " << std::chrono::duration<double>(time2 - time1).count() << " seconds.\n"
            << std::endl;
    }

    return 0;
}