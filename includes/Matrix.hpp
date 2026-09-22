#pragma once 
#include <vector>
#include <iostream>
#include <cassert>
#include <utility>
#include "Vector.hpp"
#include <stdexcept>
//verifier si la matrice donnee dans le constructeur a le meme nombre de colonnes sur toutes les lignes 

template <typename K>
class Matrix
{
    private:
        std::vector<std::vector<K>> _matrix;
        Matrix<K> getMinor(size_t rowToRemove, size_t colToRemove) const;
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

        //ex07
        Vector<K> mul_vec(const Vector<K>& vec) const;
        Matrix<K> mul_mat(const Matrix<K>& mat) const;

        //ex08
        K trace() const;

        //ex09
        Matrix<K> transpose() const;

        //ex10
        Matrix<K> row_echelon() const;

        //ex11
        K determinant() const;

        //ex12
        Matrix<K> inverse() const;

};

template <typename K>
std::ostream& operator<<(std::ostream& out, const Matrix<K>& m);


#include "Matrix.tpp"