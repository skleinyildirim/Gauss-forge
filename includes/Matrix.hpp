#pragma once 
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>

//verifier si la matrice donnee dans le constructeur a le meme nombre de colonnes sur toutes les lignes 

template <typename K>
class Matrix
{
    private:
        std::vector<std::vector<K>> _matrix;
    public:
        Matrix();
        Matrix(const std::vector<std::vector<K>> &values);
        Matrix(size_t rows, size_t cols);
        Matrix& operator=(const std::vector<std::vector<K>> &values);

        const std::vector<std::vector<K>>&   getMatrix() const;
        size_t getNumberRows() const;
        size_t getNumberCols() const;
        std::pair<size_t, size_t> getShape() const;
        bool isSquare() const;

        Matrix<K> operator+(const Matrix<K>& v) const;
        Matrix<K> operator-(const Matrix<K>& v) const;
        Matrix<K> operator*(K a) const;

        //ex00
        void add(const Matrix<K>& m);
        void sub(const Matrix<K>& m);
        void scl(K a);
};

template <typename K>
std::ostream& operator<<(std::ostream& out, const Matrix<K>& m);


#include "Matrix.tpp"