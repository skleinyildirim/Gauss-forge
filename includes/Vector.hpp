#pragma once 
#include <vector>
#include <iostream>
#include <utility>
#include <cassert>
#include <cmath>

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

};

template <typename K>
std::ostream& operator<<(std::ostream& out, const Vector<K>& v);

//ex01
template <typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs);


#include "Vector.tpp"