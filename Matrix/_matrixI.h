#pragma once

#include <algorithm>
#include <cassert>
#include <exception>

#include "Matrix.h"

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
    template <typename T>
    Matrix<T>::Matrix(int_t rowsCount, int_t columnsCount) :
        rowsCount_(rowsCount),
        columnsCount_(columnsCount),
        data_(nullptr)
    {
        data_ = new T[rowsCount_ * columnsCount_];
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    Matrix<T>::Matrix(const Matrix& m)
    {
        rowsCount_    = m.rowsCount_;
        columnsCount_ = m.columnsCount_;
        data_         = new T[rowsCount_ * columnsCount_];
        std::copy(data_, m.data_);
    }

    template <typename T>
    Matrix<T>::Matrix(Matrix&& m)
    {
        rowsCount_      = m.rowsCount_;
        columnsCount_   = m.columnsCount_;
        data_           = m.data_;

        m.rowsCount_    = 0;
        m.columnsCount_ = 0;
        m.data_         = nullptr;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator = (const Matrix& m)
    {
        rowsCount_    = m.rowsCount_;
        columnsCount_ = m.columnsCount_;
        data_         = new T[rowsCount_ * columnsCount_];
        std::copy(data_, m.data_);

        return *this;
    }

    template <typename T>
    Matrix<T>& Matrix<T>::operator = (Matrix&& m)
    {
        rowsCount_      = m.rowsCount_;
        columnsCount_   = m.columnsCount_;
        data_           = m.data_;

        m.rowsCount_    = 0;
        m.columnsCount_ = 0;
        m.data_         = nullptr;

        return *this;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    Matrix<T>::~Matrix()
    {
        delete [] data_;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    const T& Matrix<T>::GetElem(size_t rowIndex, size_t columnIndex) const
    {
        assert(rowIndex < rowsCount_);
        assert(columnIndex < columnsCount_);
        return data_[GetRowStartIndex(rowIndex) + columnIndex];
    }

    template <typename T>
    T& Matrix<T>::GetElem(size_t rowIndex, size_t columnIndex)
    {
        return const_cast<T&>
        (
            const_cast<const Matrix<T>*>(this)->GetElem(rowIndex, columnIndex)
        );
    }

    template <typename T>
    const MatrixRow<T> Matrix<T>::operator [] (size_t rowIndex) const
    {
        return MatrixRow<T>(data_ + GetRowStartIndex(rowIndex), columnsCount_);
    }

    template <typename T>
    MatrixRow<T> Matrix<T>::operator [] (size_t rowIndex)
    {
        return const_cast<MatrixRow<T>>
        (
            const_cast<const Matrix<T>*>(this)->operator[](rowIndex)
        );
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    size_t Matrix<T>::GetRowsCount() const
    {
        return rowsCount_;
    }

    template <typename T>
    size_t Matrix<T>::GetColumnsCount() const
    {
        return columnsCount_;
    }

    template <typename T>
    size_t Matrix<T>::GetRowStartIndex(size_t rowIndex) const
    {
        return rowIndex * columnsCount_;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    MatrixRow<T>::MatrixRow(T* row, size_t rowSize)
    {

    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    const T& MatrixRow<T>::operator [] (size_t index) const
    {

    }

    template <typename T>
    T& MatrixRow<T>::operator [] (size_t index)
    {

    }
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///