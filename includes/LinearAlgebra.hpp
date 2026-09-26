#pragma once

#include "Matrix.hpp"
#include "Vector.hpp"

//ex02
template <typename V>
V lerp(V u, V v, double t);

//ex05
template <typename K>
double angle_cos(const Vector<K>& u, const Vector<K>& v);

//ex06
template <typename K>
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v);

//ex14
template <typename K>
Matrix<K> projection(K fov, K ratio, K near, K far);

#include "LinearAlgebra.tpp"