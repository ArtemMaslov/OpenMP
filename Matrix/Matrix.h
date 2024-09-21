#pragma once

#include <cstdint>
#include <cstddef>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
    typedef int int_t;

    template <typename T>
    class MatrixRow;

    template <typename T>
    class Matrix
    {
    public:
        Matrix(int_t rowsCount, int_t columnsCount);

        Matrix(const Matrix& m);
        Matrix(Matrix&& m);
        Matrix& operator = (const Matrix& m);
        Matrix& operator = (Matrix&& m);

        ~Matrix();

        const T& GetElem(size_t rowIndex, size_t columnIndex) const;
        T& GetElem(size_t rowIndex, size_t columnIndex);
        const MatrixRow<T> operator [] (size_t rowIndex) const;
        MatrixRow<T> operator [] (size_t rowIndex);

        size_t GetRowsCount() const;
        size_t GetColumnsCount() const;
        size_t GetRowStartIndex(size_t rowIndex) const;

        void MulSeq1(const Matrix<T>& m);
        void MulSeq1T(const Matrix<T>& mT);

    private:
        T* data_;

        size_t rowsCount_;
        size_t columnsCount_;
    };

    template <typename T>
    class MatrixRow
    {
    public:
        MatrixRow(T* row, size_t rowSize);

        const T& operator [] (size_t index) const;
        T& operator [] (size_t index);

    public:
        const size_t Size;

    private:
        T* data;
    };
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

#include "_matrixI.h"

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///