template <typename K>
Matrix<K>::Matrix() {}


template <typename K>
Matrix<K>::Matrix(const std::vector<std::vector<K>> &values) : _matrix(values) {}

template <typename K>
Matrix<K>::Matrix(size_t rows, size_t cols) : _matrix(rows, std::vector<K>(cols, K())) {}



template <typename K>
std::vector<std::vector<K>>   Matrix<K>::getMatrix() const
{
    return _matrix;
}

// template <typename K>
// void    Matrix<K>::setMatrix(std::vector<std::vector<K>> value) 
// { 
//     _matrix(value)
// }