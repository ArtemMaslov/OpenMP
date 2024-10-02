#pragma once

#include <algorithm>
#include <cassert>
#include <stdexcept>

#include <iostream>

#include <Mas/Matrix/Matrix.h>
#include <Mas/Utils/StringBuilder.h>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
namespace LinAlg
{
    template <typename T>
    Matrix<T>::Matrix(size_t rowsCount, size_t columnsCount) :
        data_(new T[rowsCount * columnsCount]),
        rowsCount_(rowsCount),
        columnsCount_(columnsCount)
    {
    }

    template <typename T>
    template <typename Iterator>
    Matrix<T>::Matrix(Iterator begin, const Iterator end, const size_t rowsCount, const size_t columnsCount) :
        // Нет утечки памяти.
        Matrix(rowsCount, columnsCount)

        // Вариант 2. Утечка памяти, если в конструкторе произойдёт исключение.
        // data_(new T[rowsCount * columnsCount]),
        // rowsCount_(rowsCount),
        // columnsCount_(columnsCount)

        // Вариант 3. Утечка памяти, если в конструкторе произойдёт исключение.
        // data_(nullptr),
        // rowsCount_(rowsCount),
        // columnsCount_(columnsCount)
        // При этом в коде:
        // data_ = new T[rowsCount * columnsCount];

        // Для вариантов 2 или 3 необходимо перед созданием исключения вызывать:
        // delete [] data_;
    {
        size_t index = 0;
        const size_t matrixSize = rowsCount * columnsCount;
        while (begin != end)
        {
            if (index >= matrixSize)
            {
                // Если используются варианты 2 или 3.
                // delete [] data_;

                Mas::Utils::StringBuilder err {};
                err << "Mas::LinAlg::Matrix размер входных данных " << index << " не равен размеру матрицы "
                    "(" << rowsCount << " x " << columnsCount << ").";
                throw std::runtime_error(err);
            }
            
            data_[index++] = *begin;
            ++begin;
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    Matrix<T>::Matrix(const Matrix& m)
    {
        rowsCount_    = m.rowsCount_;
        columnsCount_ = m.columnsCount_;
        const size_t size = rowsCount_ * columnsCount_;
        data_         = new T[size];
        std::copy(m.data_, m.data_ + size, data_);
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
        const size_t size = rowsCount_ * columnsCount_;
        data_         = new T[size];
        std::copy(m.data_, m.data_ + size, data_);

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
        if (rowIndex >= rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "Mas::LinAlg::Matrix (rowIndex = " << rowIndex 
                << ") >= (rowsCount_ = " << rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        if (columnIndex >= columnsCount_)
        {
            Utils::StringBuilder err {};
            err << "Mas::LinAlg::Matrix (columnIndex = " << columnIndex 
                << ") >= (columnsCount_ = " << columnsCount_ << ")";
            throw std::runtime_error(err);
        }

        return data_[GetRowStartIndex(rowIndex) + columnIndex];
    }

    template <typename T>
    T& Matrix<T>::GetElem(size_t rowIndex, size_t columnIndex)
    {
        return const_cast<T&>
        (
            (const_cast<const Matrix<T>*>(this))->GetElem(rowIndex, columnIndex)
        );
    }

    template <typename T>
    const MatrixRow<T> Matrix<T>::operator [] (size_t rowIndex) const
    {
        if constexpr (LogMatrixReadWrite)
        {
            std::cout << "Matrix: data_ " << data_ << "\nrowIndex = " << rowIndex << std::endl;
        }
        return MatrixRow<T>(&(data_[GetRowStartIndex(rowIndex)]), columnsCount_);
    }

    template <typename T>
    MatrixRow<T> Matrix<T>::operator [] (size_t rowIndex)
    {
        return (const_cast<const Matrix<T>*>(this))->operator[](rowIndex);
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


    template <typename T>
    Matrix<T> Matrix<T>::CreateTranspose() const
    {
        Matrix<T> transposed(columnsCount_, rowsCount_);

        for (size_t rI = 0; rI < rowsCount_; rI++)
        {
            for (size_t cI = 0; cI < columnsCount_; cI++)
            {
                transposed[cI][rI] = (*this)[rI][cI];
            }
        }

        return transposed;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    T* Matrix<T>::GetArray()
    {
        return data_;
    }

    template <typename T>
    bool Matrix<T>::CompareDetailed(const Matrix<T>& m, const T eps)
    {
        if (rowsCount_ != m.rowsCount_)
        {
            std::cout << "this.rowsCount_ = " << rowsCount_ << " m.rowsCount_ = " << m.rowsCount_;
            return false;
        }

        if (columnsCount_ != m.columnsCount_)
        {
            std::cout << "this.columnsCount_ = " << columnsCount_
                      << " m.columnsCount_ = "   << m.columnsCount_;
            return false;
        }

        for (size_t rI = 0; rI < rowsCount_; rI++)
        {
            for (size_t cI = 0; cI < columnsCount_; cI++)
            {
                T elem1 = (*this)[rI][cI];
                T elem2 = m[rI][cI];
                if (std::abs(elem2 - elem1) > eps)
                {
                    std::cout << "(*this)[" << rI << "][" << cI << "] = " << elem1
                              << ", ожидалось " << elem2 << "." << std::endl;
                    return false;
                }
            }
        }

        return true;
    }

    template <typename T>
    void Matrix<T>::Clear(T value)
    {
        const size_t size = rowsCount_ * columnsCount_;
        for (size_t index = 0; index < size; index++)
        {
            data_[index] = value;
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    bool operator == (const Matrix<T>& m1, const Matrix<T>& m2)
    {
        if (m1.rowsCount_ != m2.rowsCount_)
            return false;
        if (m1.columnsCount_ != m2.columnsCount_)
            return false;

        const size_t rowsCount = m1.rowsCount_;
        const size_t columnsCount = m1.columnsCount_;

        for (size_t rI = 0; rI < rowsCount; rI++)
        {
            for (size_t cI = 0; cI < columnsCount; cI++)
            {
                if (m1[rI][cI] != m2[rI][cI])
                    return false;
            }
        }

        return true;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    MatrixRow<T>::MatrixRow(T* row, size_t rowSize) :
        size(rowSize),
        data_(row)
    {
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    const T& MatrixRow<T>::operator [] (size_t index) const
    {
        if (index >= size)
        {
            Utils::StringBuilder err {};
            err << "Mas::LinAlg::MatrixRow (index = " << index 
                << ") >= (sizes = " << size << ")";
            throw std::runtime_error(err);
        }

        if constexpr (LogMatrixReadWrite)
        {
            std::cout << "data_ = " << data_ << std::endl
                << "idx = " << index << "\n" << std::endl;
        }

        return data_[index];
    }

    template <typename T>
    T& MatrixRow<T>::operator [] (size_t index)
    {
        return const_cast<T&>
        (
            (const_cast<const MatrixRow<T>*>(this))->operator[](index)
        );
    }
}
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///