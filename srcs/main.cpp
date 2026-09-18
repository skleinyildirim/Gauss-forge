#include "Matrix.hpp"
#include "Vector.hpp"
#include "Colors.hpp"

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

    std::cout << std::endl << "===== Vector =====" << std::endl;

    std::cout << std::endl << "-- constructeur par defaut --" << std::endl;
    Vector<double> emptyVec;
    std::cout << emptyVec;
    std::cout << "size: " << emptyVec.getSize() << std::endl;

    std::cout << std::endl << "-- constructeur par taille (4) --" << std::endl;
    Vector<double> zerosVec(4);
    std::cout << zerosVec;
    std::cout << "size: " << zerosVec.getSize() << std::endl;

    std::cout << std::endl << "-- constructeur a partir d'un vector<K> --" << std::endl;
    std::vector<double> vecValues = {1.0, 2.0, 3.0};
    Vector<double> vectorA(vecValues);
    std::cout << vectorA;
    std::cout << "size: " << vectorA.getSize() << std::endl;

    std::cout << std::endl << "-- operator= --" << std::endl;
    std::vector<double> otherValues = {4.0, 5.0};
    vectorA = otherValues;
    std::cout << vectorA;
    std::cout << "size: " << vectorA.getSize() << std::endl;


    std::cout << std::endl << BLUE << "ex00" << RESET << std::endl;

    std::cout << std::endl << MAGENTA << "\t\tVector:" << RESET << std::endl;

    Vector<double> vAdd1({2.0, 3.0});
    Vector<double> vAdd2({5.0, 7.0});
    std::cout << "u:" << std::endl << vAdd1 << "v:" << std::endl << vAdd2;
    vAdd1.add(vAdd2);
    std::cout << "add:" << std::endl << vAdd1;   // attendu: 7 / 10

    Vector<double> vSub1({2.0, 3.0});
    Vector<double> vSub2({5.0, 7.0});
    vSub1.sub(vSub2);
    std::cout << "sub:" << std::endl << vSub1;   // attendu: -3 / -4

    Vector<double> vScl({2.0, 3.0});
    vScl.scl(2.0);
    std::cout << "scl:" << std::endl << vScl;    // attendu: 4 / 6

    std::cout << std::endl << MAGENTA << "\t\tMatrix:" << RESET << std::endl;

    Matrix<double> mAdd1({{1.0, 2.0}, {3.0, 4.0}});
    Matrix<double> mAdd2({{7.0, 4.0}, {-2.0, 2.0}});
    mAdd1.add(mAdd2);
    std::cout << "add:" << std::endl << mAdd1;   // attendu: 8 6 / 1 6

    Matrix<double> mSub1({{1.0, 2.0}, {3.0, 4.0}});
    Matrix<double> mSub2({{7.0, 4.0}, {-2.0, 2.0}});
    mSub1.sub(mSub2);
    std::cout << "sub:" << std::endl << mSub1;   // attendu: -6 -2 / 5 2

    Matrix<double> mScl({{1.0, 2.0}, {3.0, 4.0}});
    mScl.scl(2.0);
    std::cout << "scl:" << std::endl << mScl;    // attendu: 2 4 / 6 8

    std::cout << std::endl << BLUE << "ex01" << RESET << std::endl;

    std::cout << std::endl << MAGENTA << "\t\tlinear_combination:" << RESET << std::endl;

    std::vector<Vector<double>> basis = {
        Vector<double>({1.0, 0.0, 0.0}),
        Vector<double>({0.0, 1.0, 0.0}),
        Vector<double>({0.0, 0.0, 1.0})
    };
    std::vector<double> basisCoefs = {10.0, -2.0, 0.5};
    Vector<double> combBasis = linear_combination(basis, basisCoefs);
    std::cout << combBasis << std::endl;   // attendu: 10 / -2 / 0.5

    std::vector<Vector<double>> vecs = {
        Vector<double>({1.0, 2.0, 3.0}),
        Vector<double>({0.0, 10.0, -100.0})
    };
    std::vector<double> vecsCoefs = {10.0, -2.0};
    Vector<double> combVecs = linear_combination(vecs, vecsCoefs);
    std::cout << combVecs;   // attendu: 10 / 0 / 230

    return 0;
}
