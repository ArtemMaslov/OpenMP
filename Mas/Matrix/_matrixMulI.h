#pragma once

#include "Mas/Utils/StringBuilder.h"
#include <algorithm>
#include <cassert>
#include <exception>
#include <omp.h>

#include <Mas/Matrix/Matrix.h>
#include <stdexcept>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
namespace LinAlg
{
    template <typename T>
    void Matrix<T>::MulAB_Seq1(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& B)
    {
        // A и B: элементы хранят сначала по строкам, а потом по столбцам.

        // Проверяем размерности:
        // dst_(r1 x c1) = A_(r2 x c2) * B_(r3 x c3)
        // => c2 == r3
        if (A.columnsCount_ != B.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "A.columnsCount_ (" << A.columnsCount_ << ") != "
                   "B.rowsCount_ (" << B.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => r1 == r2
        if (dst.rowsCount_ != A.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.rowsCount_ (" << dst.rowsCount_ << ") != "
                   "A.rowsCount_ (" << A.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => c1 == c3
        if (dst.columnsCount_ != B.columnsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.columnsCount_ (" << dst.columnsCount_ << ") != "
                   "B.columnsCount_ (" << B.columnsCount_ << ")";
            throw std::runtime_error(err);
        }

        // dst_(s1 x s2) = A_(s1 x s3) * B_(s3 x s2)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        for (size_t rA = 0; rA < s1; rA++)
        {
            for (size_t cB = 0; cB < s2; cB++)
            {
                T sum = 0;
                for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                {
                    T e1 = A[rA][cA_rB];
                    T e2 = B[cA_rB][cB];
                    sum += e1 * e2;
                }
                dst[rA][cB] = sum;
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulAB_Seq2(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& B)
    {
        // A и B: элементы хранят сначала по строкам, а потом по столбцам.

        // Проверяем размерности:
        // dst_(r1 x c1) = A_(r2 x c2) * B_(r3 x c3)
        // => c2 == r3
        if (A.columnsCount_ != B.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "A.columnsCount_ (" << A.columnsCount_ << ") != "
                   "B.rowsCount_ (" << B.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => r1 == r2
        if (dst.rowsCount_ != A.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.rowsCount_ (" << dst.rowsCount_ << ") != "
                   "A.rowsCount_ (" << A.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => c1 == c3
        if (dst.columnsCount_ != B.columnsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.columnsCount_ (" << dst.columnsCount_ << ") != "
                   "B.columnsCount_ (" << B.columnsCount_ << ")";
            throw std::runtime_error(err);
        }

        Matrix<T> BT = B.CreateTranspose();

        // dst_(s1 x s2) = A_(s1 x s3) * B_(s3 x s2)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        for (size_t rA = 0; rA < s1; rA++)
        {
            for (size_t cB = 0; cB < s2; cB++)
            {
                T sum = 0;
                for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                {
                    sum += A[rA][cA_rB] * BT[cB][cA_rB];
                }
                dst[rA][cB] = sum;
            }
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::CheckMulABT(const Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        // A: элементы хранят сначала по строкам, а потом по столбцам.
        // BT: элементы хранят сначала по столбцам, а потом по строкам.

        // Проверяем размерности:
        // dst_(r1 x c1) = A_(r2 x c2) * BT_(r3 x c3)
        // => c2 == c3
        if (A.columnsCount_ != BT.columnsCount_)
        {
            Utils::StringBuilder err {};
            err << "A.columnsCount_ (" << A.columnsCount_ << ") != "
                   "BT.columnsCount_ (" << BT.columnsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => r1 == r2
        if (dst.rowsCount_ != A.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.rowsCount_ (" << dst.rowsCount_ << ") != "
                   "A.rowsCount_ (" << A.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
        // => c1 == r3
        if (dst.columnsCount_ != BT.rowsCount_)
        {
            Utils::StringBuilder err {};
            err << "dst.columnsCount_ (" << dst.columnsCount_ << ") != "
                   "BT.rowsCount_ (" << BT.rowsCount_ << ")";
            throw std::runtime_error(err);
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::MulABT_Seq(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        for (size_t rA = 0; rA < s1; rA++)
        {
            for (size_t cB = 0; cB < s2; cB++)
            {
                T sum = 0;
                for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                {
                    sum += A[rA][cA_rB] * BT[cB][cA_rB];
                }
                dst[rA][cB] = sum;
            }
        }
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::MulABT_Par(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(static) collapse(2)
            for (size_t rA = 0; rA < s1; rA++)
            {
                for (size_t cB = 0; cB < s2; cB++)
                {
                    T sum = 0;
                    for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                    {
                        sum += A[rA][cA_rB] * BT[cB][cA_rB];
                    }
                    dst[rA][cB] = sum;
                }
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulABT_Par2(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(dynamic) collapse(2)
            for (size_t rA = 0; rA < s1; rA++)
            {
                for (size_t cB = 0; cB < s2; cB++)
                {
                    T sum = 0;
                    for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                    {
                        sum += A[rA][cA_rB] * BT[cB][cA_rB];
                    }
                    dst[rA][cB] = sum;
                }
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulABT_Par3(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(static)
            for (size_t rA = 0; rA < s1; rA++)
            {
                #pragma omp parallel
                {
                    #pragma omp for schedule(static)
                    for (size_t cB = 0; cB < s2; cB++)
                    {
                        T sum = 0;
                        for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                        {
                            sum += A[rA][cA_rB] * BT[cB][cA_rB];
                        }
                        dst[rA][cB] = sum;
                    }
                }
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulABT_Par4(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(guided)
            for (size_t rA = 0; rA < s1; rA++)
            {
                for (size_t cB = 0; cB < s2; cB++)
                {
                    T sum = 0;
                    for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                    {
                        sum += A[rA][cA_rB] * BT[cB][cA_rB];
                    }
                    dst[rA][cB] = sum;
                }
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulABT_Par5(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(auto)
            for (size_t rA = 0; rA < s1; rA++)
            {
                for (size_t cB = 0; cB < s2; cB++)
                {
                    T sum = 0;
                    for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                    {
                        sum += A[rA][cA_rB] * BT[cB][cA_rB];
                    }
                    dst[rA][cB] = sum;
                }
            }
        }
    }

    template <typename T>
    void Matrix<T>::MulABT_Par6(Matrix<T>& dst, const Matrix<T>& A, const Matrix<T>& BT)
    {
        CheckMulABT(dst, A, BT);
        // dst_(s1 x s2) = A_(s1 x s3) * BT_(s2 x s3)
        const size_t s1 = dst.rowsCount_;
        const size_t s2 = dst.columnsCount_;
        const size_t s3 = A.columnsCount_;

        #pragma omp parallel
        {
            #pragma omp for schedule(runtime)
            for (size_t rA = 0; rA < s1; rA++)
            {
                for (size_t cB = 0; cB < s2; cB++)
                {
                    T sum = 0;
                    for (size_t cA_rB = 0; cA_rB < s3; cA_rB++)
                    {
                        sum += A[rA][cA_rB] * BT[cB][cA_rB];
                    }
                    dst[rA][cB] = sum;
                }
            }
        }
    }
}
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///