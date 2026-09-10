#pragma once 
#include <vector>

template <typename K>
class Matrix
{
    private:
        std::vector<std::vector<K>> _matrix;
    public:
        Matrix();
        Matrix(const std::vector<std::vector<K>> &values);
        Matrix(size_t rows, size_t cols);
        // Matrix(const Matrix& copy);
        // Matrix& operator=(const Matrix& copy);
        // ~Matrix();

        std::vector<std::vector<K>>   getMatrix() const;
        void    setMatrix(K value);
};

#include "Matrix.tpp"