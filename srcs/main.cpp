#include "Matrix.hpp"

int main()
{
    std::cout << "-- constructeur par defaut --" << std::endl;
    Matrix<double> empty;
    std::cout << empty;
    std::cout << "shape: (" << empty.getShape().first << ", "
               << empty.getShape().second << ")" << std::endl;
    std::cout << "is_square: " << empty.isSquare() << std::endl;

    std::cout << std::endl << "-- constructeur par dimensions (2x3) --" << std::endl;
    Matrix<double> zeros(2, 3);
    std::cout << zeros;
    std::cout << "shape: (" << zeros.getShape().first << ", "
               << zeros.getShape().second << ")" << std::endl;
    std::cout << "is_square: " << zeros.isSquare() << std::endl;

    std::cout << std::endl << "-- constructeur a partir d'un vector<vector<K>> --" << std::endl;
    std::vector<std::vector<double>> values = {
        {1.0, 2.0, 3.0},
        {4.0, 5.0, 6.0}
    };
    Matrix<double> matrixA(values);
    std::cout << matrixA;
    std::cout << "shape: (" << matrixA.getShape().first << ", "
               << matrixA.getShape().second << ")" << std::endl;
    std::cout << "is_square: " << matrixA.isSquare() << std::endl;

    std::cout << std::endl << "-- une matrice carree pour verifier is_square --" << std::endl;
    Matrix<double> square(3, 3);
    std::cout << square;
    std::cout << "is_square: " << square.isSquare() << std::endl;
    
    matrixA = values;
    std::cout << matrixA;
    return 0;
}
