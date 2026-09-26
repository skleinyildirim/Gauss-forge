#pragma once 
#include <vector>
#include <iostream>
#include <utility>
#include <cassert>
#include <cmath>
#include "Complex.hpp"

template <typename K>
class Vector
{
    private:
        std::vector<K> _vector;
    public:
        Vector();
        Vector(const std::vector<K> &values);
        Vector(size_t size);
        Vector& operator=(const std::vector<K> &values);

        const std::vector<K>&   getVector() const;
        size_t getSize() const;

        Vector<K> operator+(const Vector<K>& v) const;
        Vector<K> operator-(const Vector<K>& v) const;
        Vector<K> operator*(K a) const;

        //ex00
        void add(const Vector<K>& v);
        void sub(const Vector<K>& v);
        void scl(K a);

        //ex03
        K dot(const Vector<K>& v) const;

        //ex04
        double norm_1() const;
        double norm() const;
        double norm_inf() const;


};

template <typename K>
std::ostream& operator<<(std::ostream& out, const Vector<K>& v);

//ex01
template <typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs);

template <typename T>
T conj_helper(const T& x);

template <typename T>
double pow_helper(const T& x, double exponent);

template <typename T>
double to_real_helper(const T& x);

template <typename T>
T abs_helper(const T& x);

#include "Vector.tpp"