#include <iostream>

#include <Mas/Matrix/Matrix.h>

using namespace Mas::LinAlg;

int main(int argc, char* argv[])
{
    Matrix<int> m = MatrixFactory<int>::Read("../../Tests/Matrices/m1.txt");

    if (m.GetRowsCount() != 3 ||
        m.GetColumnsCount() != 5)
    {
        std::cout << "m.rowsCount_ = " << m.GetRowsCount() << ", ожидалось 3.\n"
            << "m.columnsCount_ = " << m.GetColumnsCount() << ", ожидалось 5."
            << std::endl;
        return 1;
    }

    for (size_t rI = 0; rI < m.GetRowsCount(); rI++)
    {
        for (size_t cI = 0; cI < m.GetColumnsCount(); cI++)
        {
            int rightElem = static_cast<int>(1 + cI + rI * 5);
            if (m[rI][cI] != rightElem)
            {
                std::cout << "m[" << rI << "][" << cI << "] = " << m[rI][cI] << ", ожидалось "
                    << rightElem << "." << std::endl;
                return 1;
            }
        }
    }

    return 0;
}