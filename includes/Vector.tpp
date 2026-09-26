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
Vector<K> Vector<K>::operator+(const Vector<K>& v) const{
    assert(getSize() == v.getSize());
    Vector<K> result(getSize());
    for (size_t i = 0; i < getSize(); i++)
    {
        result._vector[i] = _vector[i] + v._vector[i];
    }
    return (result);
}

template <typename K>
Vector<K> Vector<K>::operator-(const Vector<K>& v) const{
    assert(getSize() == v.getSize());
    Vector<K> result(getSize());
    for (size_t i = 0; i < getSize(); i++)
    {
        result._vector[i] = _vector[i] - v._vector[i];
    }
    return (result);
}

template <typename K>
Vector<K> Vector<K>::operator*(K a) const{
    Vector<K> result(getSize());
    for (size_t i = 0; i < getSize(); i++)
    {
        result._vector[i] = _vector[i] * a;
    }
    return (result);
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
    using std::fma;
    for (size_t i = 0; i < u.size(); i++) {
        const std::vector<K>& vect = u[i].getVector();
        for (size_t j = 0; j < u[i].getSize(); j++) {
            result[j] = fma(coefs[i], vect[j], result[j]);
        }
    }
    Vector<K> r(result);
    return(r);
}

//ex03
template <typename K>
K Vector<K>::dot(const Vector<K>& v) const {
    assert(getSize() == v.getSize());
    K result = K();
    using std::fma;
    for (size_t i = 0; i < getSize(); i++){
        result = fma(_vector[i], conj_helper(v._vector[i]), result);
    }
    return (result);
}


//ex04
template <typename K>
double Vector<K>::norm_1() const {
    double result = 0;
    double abs = 0;
    for (size_t i = 0; i < getSize(); i++) {
        abs = abs_helper(_vector[i]);
        result += abs;
    }
    return (result);
}

template <typename K>
double Vector<K>::norm() const {
    double result = pow_helper(dot(*this), 0.5);
    return (result);
}

template <typename K>
double Vector<K>::norm_inf() const {
    double max = 0;
    double abs = 0;
    for (size_t i = 0; i < getSize(); i++) {
        abs = abs_helper(_vector[i]);
        if (abs > max) {
            max = abs;
        }
    }
    return (max);
}

template <typename T>
T conj_helper(const T& x) { 
    return (x);
}

template <typename T>
double pow_helper(const T& x, double exponent) {
    using std::pow;
    return pow(x, exponent);
}

template <typename T>
double to_real_helper(const T& x) { 
    return (x);
}

template <typename T>
T abs_helper(const T& x) {
    return (x < 0 ? -x : x);
}
