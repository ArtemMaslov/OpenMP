#pragma once

#include <exception>
#include <iomanip>
#include <stdexcept>
#include <string>
#include <fstream>
#include <chrono>

#include <Mas/Matrix/Matrix.h>
#include <Mas/Utils/UtilsIO.h>
#include <Mas/Utils/StringBuilder.h>

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

namespace Mas
{
namespace LinAlg
{
    template <typename T>
    void MatrixFactory<T>::ReadPreprocessingRow
    (
        const char* const filePath,
        std::ifstream& ifs,
        size_t& outColumnsCount
    )
    {
        size_t columnsCount = 0;
        int curSym = '\0';
        
        Utils::IO::SkipSpaces(ifs);
        // Начало строки матрицы
        if ((curSym = ifs.get()) != '[')
        {
            Utils::StringBuilder err {};
            err << "Ошибка при чтении матрицы Mas::LinAlg::Matrix из файла \"" << filePath <<
                    "\".\nОжидалось начало строки \"[\", а прочитано \"" << curSym << "\"";
            throw std::runtime_error(err);
        }

        Utils::IO::SkipSpaces(ifs);
        // Читаем строку и определяем количество столбцов.
        curSym = ifs.peek();
        while (curSym != ']' && curSym != std::char_traits<char>::eof())
        {
            T data {};
            ifs >> data;
            columnsCount++;

            Utils::IO::SkipSpaces(ifs);
            curSym = ifs.peek();
        }

        if (curSym != ']')
        {
            Utils::StringBuilder err {};
            err << "Ошибка при чтении матрицы Mas::LinAlg::Matrix из файла \"" << filePath <<
                    "\".\nОжидалось окончание строки \"]\", а достигнут конец файла";
            throw std::runtime_error(err);
        }
        ifs.get(); // ']'

        outColumnsCount = columnsCount;
    }


    template <typename T>
    void MatrixFactory<T>::ReadPreprocessing
    (
        const char* const filePath,
        std::ifstream& ifs,
        size_t& outRowsCount,
        size_t& outColumnsCount
    )
    {
        size_t rowsCount = 0;
        size_t columnsCount = 0;

        Utils::IO::SkipSpaces(ifs);
        int curSym = '\0';

        if ((curSym = ifs.get()) != '[')
        {
            Utils::StringBuilder err {};
            err << "Ошибка при чтении матрицы Mas::LinAlg::Matrix из файла \"" << filePath << "\"."
                   "\nОжидалось начало матрицы \"[\", а прочитано \"" << curSym << "\"";
            throw std::runtime_error(err);
        }

        // Читаем первую строку и запоминаем количество столбцов.
        ReadPreprocessingRow(filePath, ifs, columnsCount);
        rowsCount++;

        Utils::IO::SkipSpaces(ifs);
        // Читаем матрицу до конца.
        curSym = ifs.peek();
        while (curSym != ']' && curSym != std::char_traits<char>::eof())
        {
            size_t curColumnsCount = 0;
            ReadPreprocessingRow(filePath, ifs, curColumnsCount);
            rowsCount++;

            if (curColumnsCount != columnsCount)
            {
                Utils::StringBuilder err {};
                err << "Ошибка при чтении матрицы Mas::LinAlg::Matrix из файла \"" << filePath << "\"."
                    "\nВ матрице во всех строках должно быть одинаковое количество столбцов.";
                throw std::runtime_error(err);
            }

            Utils::IO::SkipSpaces(ifs);
            curSym = ifs.peek();
        }

        if (curSym != ']')
        {
            Utils::StringBuilder err {};
            err << "Ошибка при чтении матрицы Mas::LinAlg::Matrix из файла \"" << filePath <<
                    "\".\nОжидалось окончание матрицы \"]\", а достигнут конец файла";
            throw std::runtime_error(err);
        }
        ifs.get(); // ']'

        outRowsCount = rowsCount;
        outColumnsCount = columnsCount;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::ReadRow
    (
        std::ifstream& ifs,
        const size_t rowIndex
    )
    {
        size_t columnIndex = 0;
        int curSym = '\0';
        
        Utils::IO::SkipSpaces(ifs);
        // Начало строки матрицы
        curSym = ifs.get();
        assert (curSym == '[');
        
        Utils::IO::SkipSpaces(ifs);
        // Читаем строку и определяем количество столбцов.
        for (size_t columnIndex = 0; columnIndex < columnsCount_; columnIndex++)
        {
            T data {};
            ifs >> data;
            (*this)[rowIndex][columnIndex] = data;

            Utils::IO::SkipSpaces(ifs);
        }

        ifs.get(); // ']'
    }

    template <typename T>
    Matrix<T> MatrixFactory<T>::Read(const char* const filePath)
    {
        std::ifstream ifs(filePath);

        if (!ifs.good())
        {
            Utils::StringBuilder err {};
            err << "Не удалось открыть файл для чтения \"" << filePath << "\".";
            throw std::runtime_error(err);
        }

        int curSym = '\0';

        size_t rowsCount = 0;
        size_t columnsCount = 0;
        ReadPreprocessing(filePath, ifs, rowsCount, columnsCount);
        ifs.seekg(0, std::ios::beg);

        Matrix<T> matrix{rowsCount, columnsCount};

        Utils::IO::SkipSpaces(ifs);
        
        curSym = ifs.get();
        assert(curSym == '[');

        for (size_t rowIndex = 0; rowIndex  < rowsCount; rowIndex++)
        {
            matrix.ReadRow(ifs, rowIndex);
        }

        Utils::IO::SkipSpaces(ifs);
        
        curSym = ifs.get();
        assert(curSym == ']');

        return matrix;
    }

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///

    template <typename T>
    void Matrix<T>::Write(const char* const filePath)
    {
        std::ofstream out(filePath);
        out << std::setprecision(12);
        out << "[\n";
        for (size_t rI = 0; rI < rowsCount_; rI++)
        {
            out << "\t[";
            size_t cI = 0;
            for (; cI < columnsCount_ - 1; cI++)
            {
                out << (*this)[rI][cI] << " ";
            }
            out << (*this)[rI][cI] << "]\n";
        }
        out <<  "]";
        out.close();
    }

    template <typename T>
    Matrix<T> MatrixFactory<T>::CreateRandomFloat
    (
        const size_t rowsCount,
        const size_t columnsCount,
        const T lowBound,
        const T highBound
    )
    {
        Matrix<T> m {rowsCount, columnsCount};

        unsigned int milliseconds_since_epoch = static_cast<unsigned int>(
            std::chrono::system_clock::now().time_since_epoch() / 
            std::chrono::milliseconds(1));
        
        std::srand(milliseconds_since_epoch);

        const T normalize = (highBound - lowBound) / static_cast<T>(RAND_MAX);

        for (size_t rI = 0; rI < rowsCount; rI++)
        {
            for (size_t cI = 0; cI < columnsCount; cI++)
            {
                const T mantissa = static_cast<T>(std::rand()) / static_cast<T>(RAND_MAX);
                const T n1 = static_cast<T>(std::rand());
                const T n2 = n1 * normalize;
                const T elem = lowBound + n2 + mantissa;
                m[rI][cI] = elem;
            }
        }

        return m;
    }
}
}

///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///
///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///***\\\***///