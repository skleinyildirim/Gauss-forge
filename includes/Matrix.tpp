template <typename K>
Matrix<K>::Matrix() {}


template <typename K>
Matrix<K>::Matrix(const std::vector<std::vector<K>> &values) : _matrix(values) {}

template <typename K>
Matrix<K>::Matrix(size_t rows, size_t cols) : _matrix(rows, std::vector<K>(cols, K())) {}

template <typename K>
Matrix<K>& Matrix<K>::operator=(const std::vector<std::vector<K>> &values) {
    _matrix = values;
    return (*this);
}

template <typename K>
const std::vector<std::vector<K>>&   Matrix<K>::getMatrix() const
{
    return _matrix;
}


template <typename K>
size_t Matrix<K>::getNumberRows() const {
    return (_matrix.size());
}

template <typename K>
size_t Matrix<K>::getNumberCols() const {
    if (_matrix.empty())
        return (0);
    return (_matrix[0].size());
}

template <typename K>
std::pair<size_t, size_t> Matrix<K>::getShape() const
{
    return (std::pair<size_t, size_t>(getNumberRows(), getNumberCols()));
}

template <typename K>
bool Matrix<K>::isSquare() const
{
    return (getNumberRows() == getNumberCols());
}

template <typename K>
Matrix<K> Matrix<K>::operator+(const Matrix<K>& v) const {
    assert(getShape() == v.getShape());
    Matrix<K> mat(getNumberRows(), getNumberCols());
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            mat._matrix[i][j] = _matrix[i][j] + v._matrix[i][j];
        }
    }
    return (mat);
}

template <typename K>
Matrix<K> Matrix<K>::operator-(const Matrix<K>& v) const {
    assert(getShape() == v.getShape());
    Matrix<K> mat(getNumberRows(), getNumberCols());
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            mat._matrix[i][j] = _matrix[i][j] - v._matrix[i][j];
        }
    }
    return (mat);
}

template <typename K>
Matrix<K> Matrix<K>::operator*(K a) const {
    Matrix<K> mat(getNumberRows(), getNumberCols());
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            mat._matrix[i][j] = _matrix[i][j] * a;
        }
    }
    return (mat);
}

template <typename K>
std::ostream& operator<<(std::ostream& out, const Matrix<K>& m)
{
    const std::vector<std::vector<K>>& mat = m.getMatrix();
    for (size_t i = 0; i < m.getNumberRows(); i++)
    {
        out << "[ ";
        for (size_t j = 0; j < m.getNumberCols(); j++)
        {
            out << mat[i][j] << " ";
        }
        out << "]" << std::endl;
    }
    return (out);
}


//ex00
template <typename K>
void Matrix<K>::add(const Matrix<K>& m) {
    const std::vector<std::vector<K>>& mat = m.getMatrix();

    assert(getShape() == m.getShape());
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            _matrix[i][j] += mat[i][j];
        }
    }
}

template <typename K>
void Matrix<K>::sub(const Matrix<K>& m) {
    const std::vector<std::vector<K>>& mat = m.getMatrix();
    assert(getShape() == m.getShape());
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            _matrix[i][j] -= mat[i][j];
        }
    }
}

template <typename K>
void Matrix<K>::scl(K a) {
    for (size_t i = 0; i < getNumberRows(); i++)
    {
        for (size_t j = 0; j < getNumberCols(); j++)
        {
            _matrix[i][j] *= a;
        }
    }
}

//ex07
template <typename K>
Vector<K> Matrix<K>::mul_vec(const Vector<K>& vec) const {
    assert(getNumberCols() == vec.getSize());
    std::vector<K> result(getNumberRows(), K());
    for (size_t i = 0; i < getNumberRows(); i++) {
        result[i] = vec.dot(_matrix[i]);
    }
    Vector<K> v(result);
    return (v);
}

template <typename K>
Matrix<K> Matrix<K>::mul_mat(const Matrix<K>& mat) const {
    assert(getNumberCols() == mat.getNumberRows());
    Matrix<K> result(getNumberRows(), mat.getNumberCols());
    for (size_t i = 0; i < getNumberRows(); i++) {
        for (size_t j = 0; j < mat.getNumberCols(); j++) {
            for (size_t k = 0; k < getNumberCols(); k++) {
                result._matrix[i][j] += _matrix[i][k] * mat._matrix[k][j];
            }
        }
    }
    return (result);
}

template <typename K>
K Matrix<K>::trace() const {
    assert(getNumberCols() == getNumberRows());
    K result = 0;
    for (size_t i = 0; i < getNumberRows(); i++) {
        result += _matrix[i][i];
    }
    return (result);
}
