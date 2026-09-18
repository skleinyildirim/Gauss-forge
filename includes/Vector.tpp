template <typename K>
Vector<K>::Vector() {}

template <typename K>
Vector<K>::Vector(const std::vector<K> &values) : _vector(values) {}

template <typename K>
Vector<K>::Vector(size_t size) : _vector(size, K()) {}

template <typename K>
Vector<K>& Vector<K>::operator=(const std::vector<K> &values){
    _vector = values;
    return (*this);
}

template <typename K>
const std::vector<K>&   Vector<K>::getVector() const {
    return (_vector);
}

template <typename K>
size_t Vector<K>::getSize() const {
    return (_vector.size());
}

template <typename K>
std::ostream& operator<<(std::ostream& out, const Vector<K>& v) {
    const std::vector<K>& vect = v.getVector();
    for (size_t i = 0; i < v.getSize(); i++)
    {
        out << "[ " << vect[i] << " ]" << std::endl;
    }
    return (out);
}

//ex00
template <typename K>
void Vector<K>::add(const Vector<K>& v) {
    assert(getSize() == v.getSize());
    for (size_t i = 0; i < getSize(); i++)
    {
        _vector[i] += v._vector[i];
    }
}

template <typename K>
void Vector<K>::sub(const Vector<K>& v) {
    assert(getSize() == v.getSize());
    for (size_t i = 0; i < getSize(); i++)
    {
        _vector[i] -= v._vector[i];
    }
}

template <typename K>
void Vector<K>::scl(K a) {
    for (size_t i = 0; i < getSize(); i++)
    {
        _vector[i] *= a;
    }
}

//ex01
template <typename K>
Vector<K> linear_combination(const std::vector<Vector<K>>& u, const std::vector<K>& coefs) {
    std::vector<K> result(u[0].getSize(), K());
    for (size_t i = 0; i < u.size(); i++) {
        const std::vector<K>& vect = u[i].getVector();
        for (size_t j = 0; j < u[i].getSize(); j++) {
            result[j] = std::fma(coefs[i], vect[j], result[j]);
        }
    }
    Vector<K> r(result);
    return(r);
}
