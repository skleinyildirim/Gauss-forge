#pragma once 
#include <vector>
#include <iostream>
#include <utility>

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

        std::vector<K>   getVector() const;
        size_t getSize() const;
};

template <typename K>
std::ostream& operator<<(std::ostream& out, const Vector<K>& v);


#include "Vector.tpp"