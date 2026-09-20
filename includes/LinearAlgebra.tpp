template <typename V>
V lerp(V u, V v, double t) {
    return(u + (v - u) * t);
}

template <typename K>
double angle_cos(const Vector<K>& u, const Vector<K>& v) {
    double dot_product = u.dot(v);
    double norm_u = u.norm();
    double norm_v = v.norm();
    return (dot_product / (norm_u * norm_v));
}