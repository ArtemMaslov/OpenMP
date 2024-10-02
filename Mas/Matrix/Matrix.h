#pragma once

#include <cstdint>
#include <cstddef>
#include <fstream>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
namespace LinAlg
{
    template <typename T>
    class MatrixRow;

    template <typename T>
    class Matrix;

    constexpr bool LogMatrixReadWrite = false;

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    class MatrixFactory
    {
    public:
        static Matrix<T> Read(const char* const filePath);

        static Matrix<T> CreateRandomFloat
        (
            const size_t rowsCount,
            const size_t columnsCount,
            const T lowBound,
            const T highBound
        );

    private:
        static void ReadPreprocessing
        (
            const char* const filePath,
            std::ifstream& ifs,
            size_t& outRowsCount,
            size_t& outColumnsCount
        );

        static void ReadPreprocessingRow
        (
            const char* const filePath,
            std::ifstream& ifs,
            size_t& outColumnsCount
        );
    };

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    class Matrix
    {
    public:
        Matrix(size_t rowsCount, size_t columnsCount);

        template <typename Iterator>
        Matrix(Iterator begin, const Iterator end, const size_t rowsCount, const size_t columnsCount);

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

        Matrix<T> CreateTranspose() const;

        static void MulAB_Seq1(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& B);
        static void MulAB_Seq2(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& B);
        static void MulABT_Seq(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);

        static void MulABT_Par(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);
        static void MulABT_Par2(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);
        static void MulABT_Par3(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);
        static void MulABT_Par4(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);
        static void MulABT_Par5(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);
        static void MulABT_Par6(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);

        void Write(const char* const filePath);
        
        T* GetArray();

        bool CompareDetailed(const Matrix<T>& m, const T eps = 0);

        void Clear(T value);

    private:
        void ReadRow
        (
            std::ifstream& ifs,
            const size_t rowIndex
        );

        static void CheckMulABT(const Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT);

    private:
        T* data_;

        size_t rowsCount_;
        size_t columnsCount_;

        friend class MatrixFactory<T>;

        template <typename T1>
        friend bool operator == (const Matrix<T1>& m1, const Matrix<T1>& m2);
    };

    template <typename T>
    bool operator == (const Matrix<T>& m1, const Matrix<T>& m2);

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    class MatrixRow
    {
    public:
        MatrixRow(T* row, size_t rowSize);

        const T& operator [] (size_t index) const;
        T& operator [] (size_t index);

    public:
        const size_t size;

    private:
        T* data_;
    };
}
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

#include <Mas/Matrix/_matrixI.h>
#include <Mas/Matrix/_matrixMulI.h>
#include <Mas/Matrix/_matrixIO.h>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///