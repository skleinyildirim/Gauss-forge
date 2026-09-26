template <typename V>
V lerp(V u, V v, double t) {
    return(u + (v - u) * t);
}

template <typename K>
double angle_cos(const Vector<K>& u, const Vector<K>& v) {
    double dot_product = to_real_helper(u.dot(v));
    double norm_u = u.norm();
    double norm_v = v.norm();
    return (dot_product / (norm_u * norm_v));
}

//ex06
template <typename K>
Vector<K> cross_product(const Vector<K>& u, const Vector<K>& v) {
    assert(u.getSize() == 3);
    assert(v.getSize() == 3);
    std::vector<K> vect_u = u.getVector();
    std::vector<K> vect_v = v.getVector();
    std::vector<K> res(u.getSize(), K());
    res[0] = vect_u[1] * vect_v[2] - vect_u[2] * vect_v[1];
    res[1] = vect_u[2] * vect_v[0] - vect_u[0] * vect_v[2];
    res[2] = vect_u[0] * vect_v[1] - vect_u[1] * vect_v[0];
    Vector<K> result(res);
    return (result);
}

//ex14
template <typename K>
Matrix<K> projection(K fov, K ratio, K near, K far) {
    std::vector<std::vector<K>> data(4, std::vector<K>(4, K()));

    K scale = 1 / std::tan(fov / 2);
    data[0][0] = - (scale / ratio);
    data[1][1] = scale;
    data[2][2] = far / (far - near);
    data[2][3] = -(far * near) / (far - near);
    data[3][2] = 1;

    return (Matrix<K>(data));
}
