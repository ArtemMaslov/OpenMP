#pragma once

#include <algorithm>
#include <cassert>
#include <exception>

#include "Matrix.h"

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::MulSeq1(const Matrix<T>& m)
    {
        // В this и в m в массиве data элементы хранятся сначала по строкам, а потом по столбцам.

        // Проверяем, что размерности матриц сходятся: A_(m x n1) * B_(n2 x k) => n1 == n2.
        assert(this->columnsCount_ == m.rowsCount_);
        // Так как результат записываем в существующую матрицу, проверяем размерности:
        // A_(m x n) = A_(m x n) * B_(n x k) => n == k.
        assert(m.rowsCount_ == m.columnsCount_);

        for (size_t rowIndex1 = 0; rowIndex1 < this->rowsCount_; rowIndex1++)
        {
            for (size_t columnIndex2 = 0; columnIndex2 < m.columnsCount_; columnIndex2++)
            {
                T sum = 0;
                for (size_t innerIndex = 0; innerIndex < this->columnsCount_; innerIndex++)
                {
                    sum += this[rowIndex1][innerIndex] * m[innerIndex][columnIndex2]; 
                }
                this[rowIndex1][columnIndex2] = sum;
            }
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::MulSeq1T(const Matrix<T>& mT)
    {
        // mT - это транспонированная матрица m. Другая интерпретация: mT - матрица m, в которой в
        // массиве data элементы хранятся сначала по столбцам, а потом по строкам.
        // А в this в массиве data элементы хранятся сначала по строкам, а потом по столбцам.
        // А функция должна умножить this на обычную матрицу m.

        // Проверяем, что размерности матриц сходятся:
        // A_(m x n1) * B_(n2 x k) = A_(m x n1) * B^T_(k x n2) => n1 == n2.
        assert(this->columnsCount_ == mT.columnsCount_);
        // Так как результат записываем в существующую матрицу, проверяем размерности:
        // A_(m x n) = A_(m x n) * B_(n x k) =  A_(m x n) * B^T_(k x n)  => n == k.
        assert(mT.rowsCount_ == mT.rowsCount_);

        for (size_t rowIndex1 = 0; rowIndex1 < this->rowsCount_; rowIndex1++)
        {
            for (size_t columnIndex2 = 0; columnIndex2 < m.columnsCount_; columnIndex2++)
            {
                T sum = 0;
                for (size_t innerIndex = 0; innerIndex < this->columnsCount_; innerIndex++)
                {
                    sum += this[rowIndex1][innerIndex] * m[innerIndex][columnIndex2]; 
                }
                this[rowIndex1][columnIndex2] = sum;
            }
        }

    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///