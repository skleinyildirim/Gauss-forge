#include "Matrix.hpp"
#include "Vector.hpp"
#include "LinearAlgebra.hpp"
#include "Colors.hpp"
#include <fstream>

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
    std::cout << "add:" << std::endl << RED << vAdd1 << RESET;   // attendu: 7 / 10

    Vector<double> vSub1({2.0, 3.0});
    Vector<double> vSub2({5.0, 7.0});
    vSub1.sub(vSub2);
    std::cout << "sub:" << std::endl << RED << vSub1 << RESET;   // attendu: -3 / -4

    Vector<double> vScl({2.0, 3.0});
    vScl.scl(2.0);
    std::cout << "scl:" << std::endl << RED << vScl << RESET;    // attendu: 4 / 6

    std::cout << std::endl << MAGENTA << "\t\tMatrix:" << RESET << std::endl;

    Matrix<double> mAdd1({{1.0, 2.0}, {3.0, 4.0}});
    Matrix<double> mAdd2({{7.0, 4.0}, {-2.0, 2.0}});
    mAdd1.add(mAdd2);
    std::cout << "add:" << std::endl << RED << mAdd1 << RESET;   // attendu: 8 6 / 1 6

    Matrix<double> mSub1({{1.0, 2.0}, {3.0, 4.0}});
    Matrix<double> mSub2({{7.0, 4.0}, {-2.0, 2.0}});
    mSub1.sub(mSub2);
    std::cout << "sub:" << std::endl << RED << mSub1 << RESET;   // attendu: -6 -2 / 5 2

    Matrix<double> mScl({{1.0, 2.0}, {3.0, 4.0}});
    mScl.scl(2.0);
    std::cout << "scl:" << std::endl << RED << mScl << RESET;    // attendu: 2 4 / 6 8

    std::cout << std::endl << BLUE << "ex01" << RESET << std::endl;

    std::cout << std::endl << MAGENTA << "\t\tlinear_combination:" << RESET << std::endl;

    std::vector<Vector<double>> basis = {
        Vector<double>({1.0, 0.0, 0.0}),
        Vector<double>({0.0, 1.0, 0.0}),
        Vector<double>({0.0, 0.0, 1.0})
    };
    std::vector<double> basisCoefs = {10.0, -2.0, 0.5};
    Vector<double> combBasis = linear_combination(basis, basisCoefs);
    std::cout << RED << combBasis << RESET << std::endl;   // attendu: 10 / -2 / 0.5

    std::vector<Vector<double>> vecs = {
        Vector<double>({1.0, 2.0, 3.0}),
        Vector<double>({0.0, 10.0, -100.0})
    };
    std::vector<double> vecsCoefs = {10.0, -2.0};
    Vector<double> combVecs = linear_combination(vecs, vecsCoefs);
    std::cout << RED << combVecs << RESET << std::endl;   // attendu: 10 / 0 / 230


    std::cout << std::endl << BLUE << "ex02" << RESET << std::endl;

    std::cout << std::endl << MAGENTA << "\t\tScalaires:" << RESET << std::endl;

    std::cout << RED << lerp(0.0, 1.0, 0.0) << RESET << std::endl;    // attendu: 0.0
    std::cout << RED << lerp(0.0, 1.0, 1.0) << RESET << std::endl;    // attendu: 1.0
    std::cout << RED << lerp(0.0, 1.0, 0.5) << RESET << std::endl;    // attendu: 0.5
    std::cout << RED << lerp(21.0, 42.0, 0.3) << RESET << std::endl;  // attendu: 27.3

    std::cout << std::endl << MAGENTA << "\t\tVector:" << RESET << std::endl;

    Vector<double> lerpU({2.0, 1.0});
    Vector<double> lerpV({4.0, 2.0});
    std::cout << RED << lerp(lerpU, lerpV, 0.3) << RESET;   // attendu: 2.6 / 1.3

    std::cout << std::endl << MAGENTA << "\t\tMatrix:" << RESET << std::endl;

    Matrix<double> lerpMu({{2.0, 1.0}, {3.0, 4.0}});
    Matrix<double> lerpMv({{20.0, 10.0}, {30.0, 40.0}});
    std::cout << RED << lerp(lerpMu, lerpMv, 0.5) << RESET; // attendu: 11 5.5 / 16.5 22


    std::cout << std::endl << BLUE << "ex03" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tDot product:" << RESET << std::endl;

    Vector<double> a({0.0, 0.0});
    Vector<double> b({1.0, 1.0});

    std::cout << "vector a: " << std::endl << a << "vector b:" << std::endl << b;
    std::cout << "result : " << RED << a.dot(b) << RESET << std::endl;

    a = {1.0, 1.0};
    std::cout << "vector a: " << std::endl << a << "vector b:" << std::endl << b;
    std::cout << "result : " << RED << a.dot(b) << RESET << std::endl;

    a = {-1.0, 6.0};
    b = {3.0, 2.0};
    std::cout << "vector a: " << std::endl << a << "vector b:" << std::endl << b;
    std::cout << "result : " << RED << a.dot(b) << RESET << std::endl;


    std::cout << std::endl << BLUE << "ex04" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tNorm:" << RESET << std::endl;

    Vector<double> c({0.0, 0.0, 0.0});

    std::cout << "vector c: " << std::endl << c << std::endl;
    std::cout << "result : " << std::endl;
    std::cout << "\t\tManhattan norm: " << RED << c.norm_1() << RESET << std::endl;
    std::cout << "\t\tEuclidean norm: " << RED << c.norm() << RESET << std::endl;
    std::cout << "\t\tSupremum norm: " << RED << c.norm_inf() << RESET << std::endl;
    std::cout << std::endl;

    c = {1.0, 2.0, 3.0};
    std::cout << "vector c: " << std::endl << c << std::endl;
    std::cout << "result : " << std::endl;
    std::cout << "\t\tManhattan norm: " << RED << c.norm_1() << RESET << std::endl;
    std::cout << "\t\tEuclidean norm: " << RED << c.norm() << RESET << std::endl;
    std::cout << "\t\tSupremum norm: " << RED << c.norm_inf() << RESET << std::endl;
    std::cout << std::endl;


    a = {-1.0, -2.0};
    std::cout << "vector a: " << std::endl << a << std::endl;
    std::cout << "result : " << std::endl;
    std::cout << "\t\tManhattan norm: " << RED << a.norm_1() << RESET << std::endl;
    std::cout << "\t\tEuclidean norm: " << RED << a.norm() << RESET << std::endl;
    std::cout << "\t\tSupremum norm: " << RED << a.norm_inf() << RESET << std::endl;
    std::cout << std::endl;

    std::cout << std::endl << BLUE << "ex05" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tCosine:" << RESET << std::endl;

    Vector<double> u({1.0, 0.0});
    Vector<double> v({1.0, 0.0});

    std::cout << "vector u: " << std::endl << u << "vector v:" << std::endl << v;
    std::cout << "Result: " << RED << angle_cos(u, v) << RESET << std::endl;
    std::cout << std::endl;

    v = {0.0, 1.0};
    std::cout << "vector u: " << std::endl << u << "vector v:" << std::endl << v;
    std::cout << "Result: " << RED << angle_cos(u, v) << RESET << std::endl;
    std::cout << std::endl;


    u = {-1.0, 1.0};
    v = {1.0, -1.0};
    std::cout << "vector u: " << std::endl << u << "vector v:" << std::endl << v;
    std::cout << "Result: " << RED << angle_cos(u, v) << RESET << std::endl;
    std::cout << std::endl;


    u = {2.0, 1.0};
    v = {4.0, 2.0};
    std::cout << "vector u: " << std::endl << u << "vector v:" << std::endl << v;
    std::cout << "Result: " << RED << angle_cos(u, v) << RESET << std::endl;
    std::cout << std::endl;

    Vector<double> u1({1.0, 2.0, 3.0});
    Vector<double> v1({4.0, 5.0, 6.0});
    std::cout << "vector u: " << std::endl << u1 << "vector v:" << std::endl << v1;
    std::cout << "Result: " << RED << angle_cos(u1, v1) << RESET << std::endl;
    std::cout << std::endl;

    std::cout << std::endl << BLUE << "ex06" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tCross product:" << RESET << std::endl;

    u1 = {0.0, 0.0, 1.0};
    v1 = {1.0, 0.0, 0.0};
    std::cout << "vector u: " << std::endl << u1 << "vector v:" << std::endl << v1;
    std::cout << "Result: " << std::endl << RED << cross_product(u1, v1) << RESET << std::endl;

    u1 = {1.0, 2.0, 3.0};
    v1 = {4.0, 5.0, 6.0};
    std::cout << "vector u: " << std::endl << u1 << "vector v:" << std::endl << v1;
    std::cout << "Result: " << std::endl << RED << cross_product(u1, v1) << RESET << std::endl;

    u1 = {4.0, 2.0, -3.0};
    v1 = {-2.0, -5.0, 16.0};
    std::cout << "vector u: " << std::endl << u1 << "vector v:" << std::endl << v1;
    std::cout << "Result: " << std::endl << RED << cross_product(u1, v1) << RESET << std::endl;


    std::cout << std::endl << BLUE << "ex07" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tLinear map, Matrix multiplication:" << RESET << std::endl;
    
    std::cout << std::endl << MAGENTA << "\t\tmul_vec:" << RESET << std::endl;
    
    Matrix<double> mat_a({{1.0, 0.0}, {0.0, 1.0}});
    u = {4.0, 2.0};

    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "vector u: " << std::endl << u;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_vec(u) << RESET << std::endl;

    mat_a = {{2.0, 0.0}, {0.0, 2.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "vector u: " << std::endl << u;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_vec(u) << RESET << std::endl;

    mat_a = {{2.0, -2.0}, {-2.0, 2.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "vector u: " << std::endl << u;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_vec(u) << RESET << std::endl;

    std::cout << std::endl << MAGENTA << "\t\tmul_mat:" << RESET << std::endl;

    mat_a = {{1.0, 0.0}, {0.0, 1.0}};
    Matrix<double> mat_b({{1.0, 0.0}, {0.0, 1.0}});
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "matrix b: " << std::endl << mat_b;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_mat(mat_b) << RESET << std::endl;

    mat_b = {{2.0, 1.0}, {4.0, 2.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "matrix b: " << std::endl << mat_b;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_mat(mat_b) << RESET << std::endl;

    mat_a = {{3.0, -5.0}, {6.0, 8.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "matrix b: " << std::endl << mat_b;
    std::cout << "Result: " << std::endl << RED << mat_a.mul_mat(mat_b) << RESET << std::endl;
    
    std::cout << std::endl << BLUE << "ex08" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tTrace: " << RESET << std::endl;

    mat_a = {{1.0, 0.0}, {0.0, 1.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "Result: " << std::endl << RED << mat_a.trace() << RESET << std::endl;

    Matrix<double> mat_c({{2.0, -5.0, 0.0}, {4.0, 3.0, 7.0}, {-2.0, 3.0, 4.0}});
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.trace() << RESET << std::endl;

    mat_c = {{-2.0, -8.0, 4.0}, {1.0, -23.0, 4.0}, {0.0, 6.0, 4.0}};
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.trace() << RESET << std::endl;

    std::cout << std::endl << BLUE << "ex09" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tTranspose: " << RESET << std::endl;

    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.transpose() << RESET << std::endl;

    std::cout << std::endl << BLUE << "ex10" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tRow-echelon form: " << RESET << std::endl;

    mat_c = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.row_echelon() << RESET << std::endl;

    mat_a = {{1.0, 2.0}, {3.0, 4.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "Result: " << std::endl << RED << mat_a.row_echelon() << RESET << std::endl;

    mat_a = {{1.0, 2.0}, {2.0, 4.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "Result: " << std::endl << RED << mat_a.row_echelon() << RESET << std::endl;

    Matrix<double> mat_d({{8.0, 5.0, -2.0, 4.0, 28.0}, {4.0, 2.5, 20.0, 4.0, -4.0}, {8.0, 5.0, 1.0, 4.0, 17.0}});
    std::cout << "matrix c: " << std::endl << mat_d;
    std::cout << "Result: " << std::endl << RED << mat_d.row_echelon() << RESET << std::endl;

    std::cout << std::endl << BLUE << "ex11" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tDeterminant: " << RESET << std::endl;

    mat_a = {{1.0, -1.0}, {-1.0, 1.0}};
    std::cout << "matrix a: " << std::endl << mat_a;
    std::cout << "Result: " << std::endl << RED << mat_a.determinant() << RESET << std::endl;

    mat_c = {{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 2.0}};
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.determinant() << RESET << std::endl;

    mat_c = {{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}};
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.determinant() << RESET << std::endl;

    Matrix<double> mat_e({{8.0, 5.0, -2.0, 4.0}, {4.0, 2.5, 20.0, 4.0}, {8.0, 5.0, 1.0, 4.0}, {28.0, -4.0, 17.0, 1.0}});
    std::cout << "matrix e: " << std::endl << mat_e;
    std::cout << "Result: " << std::endl << RED << mat_e.determinant() << RESET << std::endl;

    {
        std::cout << std::endl << BLUE << "ex12" << RESET << std::endl;
        std::cout << std::endl << MAGENTA << "\t\tInverse: " << RESET << std::endl;

        try {
            Matrix<double> mat_u({{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}});
            std::cout << "matrix u: " << std::endl << mat_u;
            std::cout << "Result: " << std::endl << RED << mat_u.inverse() << RESET << std::endl;
            
            mat_u = {{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 2.0}};
            std::cout << "matrix u: " << std::endl << mat_u;
            std::cout << "Result: " << std::endl << RED << mat_u.inverse() << RESET << std::endl;

            mat_u = {{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}};
            std::cout << "matrix u: " << std::endl << mat_u;
            std::cout << "Result: " << std::endl << RED << mat_u.inverse() << RESET << std::endl;

            std::cout << std::endl << MAGENTA << "\tsingular matrix: " << RESET << std::endl;
            Matrix<double> mat_v({{1.0, -1.0}, {-1.0, 1.0}});
            std::cout << "matrix v: " << std::endl << mat_v;
            std::cout << "Result: " << std::endl << RED << mat_v.inverse() << RESET << std::endl;
            
        }
        catch (const std::exception& e) {
            std::cout << "Error : " << e.what() << std::endl;
        }
    }

    std::cout << std::endl << BLUE << "ex13" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tRank: " << RESET << std::endl;

    mat_c = {{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}};
    std::cout << "matrix c: " << std::endl << mat_c;
    std::cout << "Result: " << std::endl << RED << mat_c.rank() << RESET << std::endl;

    Matrix<double> mat_f({{1.0, 2.0, 0.0, 0.0}, {2.0, 4.0, 0.0, 0.0}, {-1.0, 2.0, 1.0, 1.0}});
    std::cout << "matrix f: " << std::endl << mat_f;
    std::cout << "Result: " << std::endl << RED << mat_f.rank() << RESET << std::endl;

    Matrix<double> mat_g({{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}, {21.0, 18.0, 7.0}});
    std::cout << "matrix f: " << std::endl << mat_g;
    std::cout << "Result: " << std::endl << RED << mat_g.rank() << RESET << std::endl;
    
    std::cout << std::endl << BLUE << "ex14" << RESET << std::endl;
    std::cout << std::endl << MAGENTA << "\t\tProjection matrix: " << RESET << std::endl;
    Matrix<double> proj = projection(1.0472, 16.0/9.0, 1.0, 100.0);   // fov ~60° en radians
    std::cout << proj;

    Matrix<double> projT = proj.transpose();
    const std::vector<std::vector<double>>& projTData = projT.getMatrix();

    std::ofstream file("proj");
    for (size_t i = 0; i < projT.getNumberRows(); i++) {
        for (size_t j = 0; j < projT.getNumberCols(); j++) {
            file << projTData[i][j];
            if (j != projT.getNumberCols() - 1)
                file << ", ";
        }
        file << std::endl;
    }
    file.close();

    return 0;
}
