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
    using std::fma;
    for (size_t i = 0; i < getNumberRows(); i++) {
        for (size_t k = 0; k < getNumberCols(); k++) {
            result[i] = fma(_matrix[i][k], vec.getVector()[k], result[i]);
        }
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

//ex08
template <typename K>
K Matrix<K>::trace() const {
    assert(getNumberCols() == getNumberRows());
    K result = 0;
    for (size_t i = 0; i < getNumberRows(); i++) {
        result += _matrix[i][i];
    }
    return (result);
}

//ex09
template <typename K>
Matrix<K> Matrix<K>::transpose() const {
    Matrix<K> result(getNumberCols(), getNumberRows());
    for (size_t i = 0; i < getNumberRows(); i++) {
        for (size_t j = 0; j < getNumberCols(); j++) {
            result._matrix[j][i] = _matrix[i][j];
        }
    }
    return (result);
}

//ex10
template <typename K>
Matrix<K> Matrix<K>::row_echelon() const {
    size_t pivot_row = 0;
    Matrix<K> result(*this);
    double eps = 0.000001;
    for (size_t i = 0; i < getNumberCols(); i++) {
        for (size_t j = pivot_row; j < getNumberRows(); j++) {
            if (abs_helper(result._matrix[j][i]) > eps) {
                std::swap(result._matrix[pivot_row], result._matrix[j]);
                K pivotValue = result._matrix[pivot_row][i];   // on sauvegarde AVANT de modifier
                for (size_t k = 0; k < getNumberCols(); k++) {
                    result._matrix[pivot_row][k] /= pivotValue;
                }
                for (size_t r = 0; r < getNumberRows(); r++) {
                    if (r == pivot_row)
                        continue;
                    K factor = result._matrix[r][i];
                    for (size_t k = 0; k < getNumberCols(); k++) {
                        result._matrix[r][k] -= factor * result._matrix[pivot_row][k];
                    }
                }
                pivot_row++;
                break ;
            }
        }

    }
    for (size_t i = 0; i < getNumberRows(); i++) {
        for (size_t j = 0; j < getNumberCols(); j++) {
            if (abs_helper(result._matrix[i][j]) < eps)
                result._matrix[i][j] = 0;
        }
    }
    return (result);
}


//ex11
template <typename K>
Matrix<K> Matrix<K>::getMinor(size_t rowToRemove, size_t colToRemove) const{
    Matrix<K> result(getNumberRows() - 1, getNumberCols() - 1);
    size_t destRow = 0;
    for (size_t i = 0; i < getNumberRows(); i++) {
        if (i == rowToRemove)
            continue;
        size_t destCol = 0;
        for (size_t j = 0; j < getNumberCols(); j++) {
            if (j == colToRemove)
                continue;
            result._matrix[destRow][destCol] = _matrix[i][j];
            destCol++;
        }
        destRow++;
    }
    return (result);
}

template <typename K>
K Matrix<K>::determinant() const {
    assert(isSquare());
    if (getNumberCols() == 1 && getNumberRows() == 1)
        return (_matrix[0][0]);
    Matrix<K> m(*this);
    double eps = 0.000001;
    K det = 1;
    K factor = 0;
    size_t n = m.getNumberCols();
    for (size_t c = 0; c < n; c++) {
        size_t best = c;
        for (size_t r = c + 1; r < n; r++) {
            if (abs_helper(m._matrix[r][c]) > abs_helper(m._matrix[best][c]))
                best = r;
        }
        if (abs_helper(m._matrix[best][c]) < eps)
            return (K(0));
        if (best != c) {
            std::swap(m._matrix[best], m._matrix[c]);
            det = det * -1;
        }
        for (size_t r = c + 1; r < n; r++) {
            factor = m._matrix[r][c] / m._matrix[c][c];
            for (size_t col = c; col < n; col++) {
                m._matrix[r][col] = m._matrix[r][col] - factor * m._matrix[c][col];
            }

        }
        det = det * m._matrix[c][c];
    }
    return (det);
}

//ex12
template <typename K>
Matrix<K> Matrix<K>::inverse() const {
    assert(isSquare());
    if (determinant() == 0)
        throw std::domain_error("Matrix is singular, cannot invert");
    Matrix<K> identity(getNumberRows(), getNumberRows());
    for (size_t i = 0; i < getNumberRows(); i++) {
        identity._matrix[i][i] = 1;
    }
    Matrix<K> result(getNumberRows(), getNumberCols() + identity.getNumberCols());
    for (size_t i = 0; i < getNumberRows(); i++) {
        for (size_t j = 0; j < getNumberCols(); j++)
            result._matrix[i][j] = _matrix[i][j];
        for (size_t j = 0; j < identity.getNumberCols(); j++)
            result._matrix[i][getNumberCols() + j] = identity._matrix[i][j];
    }
    Matrix<K> row_result = result.row_echelon();
    for (size_t i = 0; i < identity.getNumberRows(); i++) {
        for (size_t j = 0; j < identity.getNumberCols(); j++) {
            identity._matrix[i][j] = row_result._matrix[i][getNumberCols() + j];
        }
    }
    return (identity);
}


//ex13
template <typename K>
size_t Matrix<K>::rank() const {
    Matrix<K> row_result = row_echelon();
    size_t result = 0;
    double eps = 0.000001;
    for (size_t i = 0; i < row_result.getNumberRows(); i++) {
        for (size_t j = 0; j < row_result.getNumberCols(); j++) {
            if (abs_helper(row_result._matrix[i][j]) > eps) {
                result++;
                break ;
            }
        }
    }
    return (result);
}
