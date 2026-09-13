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
        out << vect[i] << std::endl;
    }
    return (out);
}
