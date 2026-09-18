template <typename V>
V lerp(V u, V v, double t) {
    return(u + (v - u) * t);
}