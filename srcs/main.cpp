#include "Matrix.hpp"
#include "Vector.hpp"
#include "Complex.hpp"
#include "LinearAlgebra.hpp"
#include "Colors.hpp"
#include <fstream>

#define RESULT_COLOR CYAN

typedef Vector<double>  Vec;
typedef Matrix<double>  Mat;
typedef Vector<Complex> CVec;
typedef Matrix<Complex> CMat;
typedef Complex         C;

static int g_pass = 0;
static int g_fail = 0;

/* ---------------------------------------------------------------- display */

static void title(const char* ex, const char* name)
{
    std::cout << std::endl << BOLDBLUE << "=== " << ex << " - " << name << " ===" << RESET << std::endl;
}

static void section(const char* name)
{
    std::cout << std::endl << MAGENTA << "  " << name << RESET << std::endl;
}

static void space()
{
    std::cout << std::endl;
}

/* Inputs: plain. */
static void show(const char* label, double x)
{
    std::cout << label << ": " << x << std::endl;
}

static void show(const char* label, const Complex& x)
{
    std::cout << label << ": " << x << std::endl;
}

template <typename K>
static void show(const char* label, const Vector<K>& v)
{
    std::cout << label << ":" << std::endl << v;
}

template <typename K>
static void show(const char* label, const Matrix<K>& m)
{
    std::cout << label << ":" << std::endl << m;
}

/* Results: colored. */
static void showResult(const char* label, double x)
{
    std::cout << label << ": " << RESULT_COLOR << x << RESET << std::endl;
}

static void showResult(const char* label, const Complex& x)
{
    std::cout << label << ": " << RESULT_COLOR << x << RESET << std::endl;
}

template <typename K>
static void showResult(const char* label, const Vector<K>& v)
{
    std::cout << label << ":" << std::endl << RESULT_COLOR << v << RESET;
}

template <typename K>
static void showResult(const char* label, const Matrix<K>& m)
{
    std::cout << label << ":" << std::endl << RESULT_COLOR << m << RESET;
}

/* ------------------------------------------------------ comparison helpers */

static bool approx(double a, double b)
{
    double d = a - b;
    if (d < 0)
        d = -d;
    return (d < 1e-4);
}

static bool approx(const Complex& a, const Complex& b)
{
    return (approx(a.getReal(), b.getReal()) && approx(a.getImag(), b.getImag()));
}

template <typename K>
static bool approx(const Vector<K>& a, const Vector<K>& b)
{
    if (a.getSize() != b.getSize())
        return (false);
    for (size_t i = 0; i < a.getSize(); i++)
        if (!approx(a.getVector()[i], b.getVector()[i]))
            return (false);
    return (true);
}

template <typename K>
static bool approx(const Matrix<K>& a, const Matrix<K>& b)
{
    if (a.getShape() != b.getShape())
        return (false);
    for (size_t i = 0; i < a.getNumberRows(); i++)
        for (size_t j = 0; j < a.getNumberCols(); j++)
            if (!approx(a.getMatrix()[i][j], b.getMatrix()[i][j]))
                return (false);
    return (true);
}

/* Prints the (colored) result, then [OK] or [KO] with the expected value. */
template <typename T>
static void check(const char* label, const T& got, const T& expected)
{
    showResult(label, got);
    if (approx(got, expected))
    {
        g_pass++;
        std::cout << GREEN << "[OK]" << RESET << std::endl;
    }
    else
    {
        g_fail++;
        std::cout << RED << "[KO]" << RESET << " ";
        show("expected", expected);
    }
}

/* ------------------------------------------------------------- test cases */

static void caseDot(const Vec& a, const Vec& b, double e)
{
    show("u", a);
    show("v", b);
    check("u . v", a.dot(b), e);
    space();
}

static void caseNorms(const Vec& v, double n1, double n2, double ninf)
{
    show("v", v);
    check("norm_1",   v.norm_1(),   n1);
    check("norm",     v.norm(),     n2);
    check("norm_inf", v.norm_inf(), ninf);
    space();
}

static void caseCos(const Vec& a, const Vec& b, double e)
{
    show("u", a);
    show("v", b);
    check("cos(u, v)", angle_cos(a, b), e);
    space();
}

static void caseCross(const Vec& a, const Vec& b, const Vec& e)
{
    show("u", a);
    show("v", b);
    check("u x v", cross_product(a, b), e);
    space();
}

static void caseMulVec(const Mat& m, const Vec& v, const Vec& e)
{
    show("A", m);
    show("u", v);
    check("A * u", m.mul_vec(v), e);
    space();
}

static void caseMulMat(const Mat& a, const Mat& b, const Mat& e)
{
    show("A", a);
    show("B", b);
    check("A * B", a.mul_mat(b), e);
    space();
}

static void caseTrace(const Mat& m, double e)
{
    show("A", m);
    check("trace(A)", m.trace(), e);
    space();
}

static void caseTranspose(const Mat& m, const Mat& e)
{
    show("A", m);
    check("transpose(A)", m.transpose(), e);
    space();
}

static void caseRowEchelon(const Mat& m, const Mat& e)
{
    show("A", m);
    check("row_echelon(A)", m.row_echelon(), e);
    space();
}

static void caseDet(const Mat& m, double e)
{
    show("A", m);
    check("determinant(A)", m.determinant(), e);
    space();
}

static void caseRank(const Mat& m, double e)
{
    show("A", m);
    check("rank(A)", static_cast<double>(m.rank()), e);
    space();
}

/* ------------------------------------------------------------------ tests */

static void ex00()
{
    title("ex00", "Add, Subtract and Scale");

    section("Vector");
    Vec u({2.0, 3.0});
    Vec v({5.0, 7.0});
    show("u", u);
    show("v", v);
    Vec a(u); a.add(v);   check("u + v", a, Vec({7.0, 10.0}));
    Vec s(u); s.sub(v);   check("u - v", s, Vec({-3.0, -4.0}));
    Vec m(u); m.scl(2.0); check("2 * u", m, Vec({4.0, 6.0}));

    section("Matrix");
    Mat mu({{1.0, 2.0}, {3.0, 4.0}});
    Mat mv({{7.0, 4.0}, {-2.0, 2.0}});
    show("u", mu);
    show("v", mv);
    Mat ma(mu); ma.add(mv);   check("u + v", ma, Mat({{8.0, 6.0}, {1.0, 6.0}}));
    Mat ms(mu); ms.sub(mv);   check("u - v", ms, Mat({{-6.0, -2.0}, {5.0, 2.0}}));
    Mat mm(mu); mm.scl(2.0);  check("2 * u", mm, Mat({{2.0, 4.0}, {6.0, 8.0}}));
}

static void ex01()
{
    title("ex01", "Linear combination");

    Vec e1({1.0, 0.0, 0.0});
    Vec e2({0.0, 1.0, 0.0});
    Vec e3({0.0, 0.0, 1.0});
    show("e1", e1);
    show("e2", e2);
    show("e3", e3);
    std::vector<Vec> basis = {e1, e2, e3};
    std::vector<double> c1 = {10.0, -2.0, 0.5};
    std::cout << "coefs: [10, -2, 0.5]" << std::endl;
    check("10*e1 - 2*e2 + 0.5*e3", linear_combination(basis, c1), Vec({10.0, -2.0, 0.5}));
    space();

    Vec v1({1.0, 2.0, 3.0});
    Vec v2({0.0, 10.0, -100.0});
    show("v1", v1);
    show("v2", v2);
    std::vector<Vec> vecs = {v1, v2};
    std::vector<double> c2 = {10.0, -2.0};
    std::cout << "coefs: [10, -2]" << std::endl;
    check("10*v1 - 2*v2", linear_combination(vecs, c2), Vec({10.0, 0.0, 230.0}));
}

static void ex02()
{
    title("ex02", "Linear interpolation");

    section("Scalars");
    check("lerp(0, 1, 0)",     lerp(0.0, 1.0, 0.0),    0.0);
    check("lerp(0, 1, 1)",     lerp(0.0, 1.0, 1.0),    1.0);
    check("lerp(0, 1, 0.5)",   lerp(0.0, 1.0, 0.5),    0.5);
    check("lerp(21, 42, 0.3)", lerp(21.0, 42.0, 0.3), 27.3);

    section("Vector");
    Vec u({2.0, 1.0});
    Vec v({4.0, 2.0});
    show("u", u);
    show("v", v);
    std::cout << "t: 0.3" << std::endl;
    check("lerp(u, v, t)", lerp(u, v, 0.3), Vec({2.6, 1.3}));

    section("Matrix");
    Mat mu({{2.0, 1.0}, {3.0, 4.0}});
    Mat mv({{20.0, 10.0}, {30.0, 40.0}});
    show("u", mu);
    show("v", mv);
    std::cout << "t: 0.5" << std::endl;
    check("lerp(u, v, t)", lerp(mu, mv, 0.5), Mat({{11.0, 5.5}, {16.5, 22.0}}));
}

static void ex03()
{
    title("ex03", "Dot product");

    caseDot(Vec({0.0, 0.0}),  Vec({1.0, 1.0}), 0.0);
    caseDot(Vec({1.0, 1.0}),  Vec({1.0, 1.0}), 2.0);
    caseDot(Vec({-1.0, 6.0}), Vec({3.0, 2.0}), 9.0);
}

static void ex04()
{
    title("ex04", "Norm");

    caseNorms(Vec({0.0, 0.0, 0.0}), 0.0, 0.0, 0.0);
    caseNorms(Vec({1.0, 2.0, 3.0}), 6.0, 3.74165738, 3.0);
    caseNorms(Vec({-1.0, -2.0}),    3.0, 2.236067977, 2.0);
}

static void ex05()
{
    title("ex05", "Cosine");

    caseCos(Vec({1.0, 0.0}),       Vec({1.0, 0.0}),        1.0);
    caseCos(Vec({1.0, 0.0}),       Vec({0.0, 1.0}),        0.0);
    caseCos(Vec({-1.0, 1.0}),      Vec({1.0, -1.0}),      -1.0);
    caseCos(Vec({2.0, 1.0}),       Vec({4.0, 2.0}),        1.0);
    caseCos(Vec({1.0, 2.0, 3.0}),  Vec({4.0, 5.0, 6.0}),   0.974631846);
}

static void ex06()
{
    title("ex06", "Cross product");

    caseCross(Vec({0.0, 0.0, 1.0}), Vec({1.0, 0.0, 0.0}),   Vec({0.0, 1.0, 0.0}));
    caseCross(Vec({1.0, 2.0, 3.0}), Vec({4.0, 5.0, 6.0}),   Vec({-3.0, 6.0, -3.0}));
    caseCross(Vec({4.0, 2.0, -3.0}), Vec({-2.0, -5.0, 16.0}), Vec({17.0, -58.0, -16.0}));
}

static void ex07()
{
    title("ex07", "Linear map, Matrix multiplication");

    Vec u({4.0, 2.0});

    section("mul_vec");
    caseMulVec(Mat({{1.0, 0.0}, {0.0, 1.0}}),    u, Vec({4.0, 2.0}));
    caseMulVec(Mat({{2.0, 0.0}, {0.0, 2.0}}),    u, Vec({8.0, 4.0}));
    caseMulVec(Mat({{2.0, -2.0}, {-2.0, 2.0}}),  u, Vec({4.0, -4.0}));

    section("mul_mat");
    Mat id({{1.0, 0.0}, {0.0, 1.0}});
    Mat b({{2.0, 1.0}, {4.0, 2.0}});
    caseMulMat(id, id, id);
    caseMulMat(id, b,  b);
    caseMulMat(Mat({{3.0, -5.0}, {6.0, 8.0}}), b, Mat({{-14.0, -7.0}, {44.0, 22.0}}));
}

static void ex08()
{
    title("ex08", "Trace");

    caseTrace(Mat({{1.0, 0.0}, {0.0, 1.0}}), 2.0);
    caseTrace(Mat({{2.0, -5.0, 0.0}, {4.0, 3.0, 7.0}, {-2.0, 3.0, 4.0}}), 9.0);
    caseTrace(Mat({{-2.0, -8.0, 4.0}, {1.0, -23.0, 4.0}, {0.0, 6.0, 4.0}}), -21.0);
}

static void ex09()
{
    title("ex09", "Transpose");

    caseTranspose(Mat({{-2.0, -8.0, 4.0}, {1.0, -23.0, 4.0}, {0.0, 6.0, 4.0}}),
                  Mat({{-2.0, 1.0, 0.0}, {-8.0, -23.0, 6.0}, {4.0, 4.0, 4.0}}));
    caseTranspose(Mat({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}}),
                  Mat({{1.0, 4.0}, {2.0, 5.0}, {3.0, 6.0}}));
}

static void ex10()
{
    title("ex10", "Row-echelon form");

    section("Identity");
    caseRowEchelon(Mat({{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}),
                   Mat({{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}));

    section("Invertible matrix -> identity");
    caseRowEchelon(Mat({{1.0, 2.0}, {3.0, 4.0}}),
                   Mat({{1.0, 0.0}, {0.0, 1.0}}));

    section("Singular matrix -> zero row");
    caseRowEchelon(Mat({{1.0, 2.0}, {2.0, 4.0}}),
                   Mat({{1.0, 2.0}, {0.0, 0.0}}));

    section("3x5 matrix");
    caseRowEchelon(Mat({{8.0, 5.0, -2.0, 4.0, 28.0}, {4.0, 2.5, 20.0, 4.0, -4.0}, {8.0, 5.0, 1.0, 4.0, 17.0}}),
                   Mat({{1.0, 0.625, 0.0, 0.0, -12.1666667}, {0.0, 0.0, 1.0, 0.0, -3.6666667}, {0.0, 0.0, 0.0, 1.0, 29.5}}));
}

static void ex11()
{
    title("ex11", "Determinant");

    section("Singular matrix (det = 0)");
    caseDet(Mat({{1.0, -1.0}, {-1.0, 1.0}}), 0.0);

    section("2 * I3 (volume x 8)");
    caseDet(Mat({{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 2.0}}), 8.0);

    section("3x3");
    caseDet(Mat({{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}}), -174.0);

    section("4x4");
    caseDet(Mat({{8.0, 5.0, -2.0, 4.0}, {4.0, 2.5, 20.0, 4.0}, {8.0, 5.0, 1.0, 4.0}, {28.0, -4.0, 17.0, 1.0}}), 1032.0);

    section("Row swap (sign check)");
    caseDet(Mat({{0.0, 1.0}, {1.0, 0.0}}), -1.0);
}

static void ex12()
{
    title("ex12", "Inverse");

    Mat id3({{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}});

    Mat i1(id3);
    show("A", i1);
    check("inverse(A)", i1.inverse(), id3);
    space();

    Mat i2({{2.0, 0.0, 0.0}, {0.0, 2.0, 0.0}, {0.0, 0.0, 2.0}});
    show("A", i2);
    check("inverse(A)", i2.inverse(), Mat({{0.5, 0.0, 0.0}, {0.0, 0.5, 0.0}, {0.0, 0.0, 0.5}}));
    space();

    Mat a({{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}});
    show("A", a);
    showResult("inverse(A)", a.inverse());
    check("A * inverse(A)  (must be the identity)", a.mul_mat(a.inverse()), id3);

    section("Singular matrix");
    Mat s({{1.0, -1.0}, {-1.0, 1.0}});
    show("A", s);
    try
    {
        s.inverse();
        g_fail++;
        std::cout << RED << "[KO]" << RESET << " no exception thrown" << std::endl;
    }
    catch (const std::exception& e)
    {
        g_pass++;
        std::cout << "exception: " << RESULT_COLOR << e.what() << RESET << std::endl;
        std::cout << GREEN << "[OK]" << RESET << std::endl;
    }
}

static void ex13()
{
    title("ex13", "Rank");

    caseRank(Mat({{1.0, 0.0, 0.0}, {0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}}), 3.0);
    caseRank(Mat({{1.0, 2.0, 0.0, 0.0}, {2.0, 4.0, 0.0, 0.0}, {-1.0, 2.0, 1.0, 1.0}}), 2.0);
    caseRank(Mat({{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}, {21.0, 18.0, 7.0}}), 3.0);
    caseRank(Mat({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}}), 2.0);   // row3 = 2*row2 - row1
}

static void ex14()
{
    title("ex14", "Projection matrix (bonus)");

    const double near = 1.0;
    const double far = 100.0;
    std::cout << "fov = 60 deg (1.0472 rad), ratio = 16/9, near = 1, far = 100" << std::endl;
    Mat proj = projection(1.0472, 16.0 / 9.0, near, far);
    showResult("P", proj);

    section("Depth check: near -> 0, far -> 1");
    Vec pn = proj.mul_vec(Vec({0.0, 0.0, near, 1.0}));
    Vec pf = proj.mul_vec(Vec({0.0, 0.0, far, 1.0}));
    check("z_ndc at near", pn.getVector()[2] / pn.getVector()[3], 0.0);
    check("z_ndc at far",  pf.getVector()[2] / pf.getVector()[3], 1.0);

    // The display tool reads the matrix in column-major order:
    // each line of the file is a column of P, i.e. a row of P^T.
    Mat projT = proj.transpose();
    std::ofstream file("proj");
    for (size_t i = 0; i < projT.getNumberRows(); i++)
    {
        for (size_t j = 0; j < projT.getNumberCols(); j++)
        {
            file << projT.getMatrix()[i][j];
            if (j != projT.getNumberCols() - 1)
                file << ", ";
        }
        file << std::endl;
    }
    file.close();
    std::cout << std::endl << "Matrix written to ./proj (column-major) for ./display" << std::endl;
}

static void ex15()
{
    title("ex15", "Complex vector spaces (bonus)");

    CVec u({C(2.0, 3.0), C(4.0, 8.0)});
    CVec v({C(1.0, 1.0), C(2.0, -1.0)});

    section("Vector: add / sub / scl");
    show("u", u);
    show("v", v);
    CVec a(u); a.add(v);           check("u + v", a, CVec({C(3.0, 4.0), C(6.0, 7.0)}));
    CVec s(u); s.sub(v);           check("u - v", s, CVec({C(1.0, 2.0), C(2.0, 9.0)}));
    CVec m(u); m.scl(C(2.0, 0.0)); check("2 * u", m, CVec({C(4.0, 6.0), C(8.0, 16.0)}));

    section("Vector: dot / norms / cos");
    show("u", u);
    show("v", v);
    check("u . v  (u * conj(v))", u.dot(v), C(5.0, 21.0));
    check("norm_1(u)   = |2+3i| + |4+8i|", u.norm_1(),  12.5499);
    check("norm_inf(u) = |4+8i|",          u.norm_inf(), 8.9443);
    showResult("cos(u, v)", angle_cos(u, v));
    space();
    CVec w({C(3.0, 4.0), C(0.0, 0.0)});
    show("w", w);
    check("norm(w)", w.norm(), 5.0);

    section("Vector: linear_combination / lerp");
    std::vector<CVec> vecs = {u, v};
    std::vector<C> coefs = {C(2.0, 0.0), C(0.0, 1.0)};
    show("u", u);
    show("v", v);
    std::cout << "coefs: [2, i]" << std::endl;
    showResult("2*u + i*v", linear_combination(vecs, coefs));
    std::cout << "t: 0.5" << std::endl;
    showResult("lerp(u, v, t)", lerp(u, v, 0.5));

    section("Vector: cross_product");
    CVec ez({C(0.0), C(0.0), C(1.0)});
    CVec ex({C(1.0), C(0.0), C(0.0)});
    show("u", ez);
    show("v", ex);
    check("u x v", cross_product(ez, ex), CVec({C(0.0), C(1.0), C(0.0)}));

    CMat p({{C(1.0, 1.0), C(2.0, 0.0)}, {C(0.0, -1.0), C(3.0, 2.0)}});
    CMat q({{C(1.0, 0.0), C(0.0, 1.0)}, {C(1.0, 1.0), C(2.0, -2.0)}});

    section("Matrix: add / sub / scl");
    show("P", p);
    show("Q", q);
    CMat ma(p); ma.add(q);           showResult("P + Q", ma);
    CMat ms(p); ms.sub(q);           showResult("P - Q", ms);
    CMat mm(p); mm.scl(C(0.0, 1.0)); showResult("i * P", mm);

    section("Matrix: mul_vec / mul_mat / transpose");
    CVec x({C(1.0, 0.0), C(0.0, 1.0)});
    show("P", p);
    show("x", x);
    check("P * x", p.mul_vec(x), CVec({C(1.0, 3.0), C(-2.0, 2.0)}));
    space();
    show("P", p);
    show("Q", q);
    check("P * Q", p.mul_mat(q), CMat({{C(3.0, 3.0), C(3.0, -3.0)}, {C(1.0, 4.0), C(11.0, -2.0)}}));
    space();
    show("P", p);
    showResult("transpose(P)", p.transpose());

    section("Matrix: trace / determinant / rank / row_echelon / inverse");
    show("P", p);
    check("trace(P)",       p.trace(),       C(4.0, 3.0));
    check("determinant(P)", p.determinant(), C(1.0, 7.0));
    check("rank(P)", static_cast<double>(p.rank()), 2.0);
    showResult("row_echelon(P)", p.row_echelon());
    showResult("inverse(P)", p.inverse());
}

static void checkTrue(const char* label, bool ok)
{
    std::cout << label << std::endl;
    if (ok)
    {
        g_pass++;
        std::cout << GREEN << "[OK]" << RESET << std::endl;
    }
    else
    {
        g_fail++;
        std::cout << RED << "[KO]" << RESET << std::endl;
    }
}

static Mat identity(size_t n)
{
    std::vector<std::vector<double> > data(n, std::vector<double>(n, 0.0));
    for (size_t i = 0; i < n; i++)
        data[i][i] = 1.0;
    return (Mat(data));
}

/* Harder cases: edge cases and mathematical properties. */
static void extra()
{
    title("extra", "Harder cases and properties");

    Mat a({{8.0, 5.0, -2.0}, {4.0, 7.0, 20.0}, {7.0, 6.0, 1.0}});   // det = -174
    Mat b({{2.0, 0.0, 1.0}, {1.0, 3.0, 0.0}, {0.0, 1.0, 4.0}});     // det = 25

    section("Vectors: norms, cos, cross");
    caseNorms(Vec({3.0, 4.0, 12.0}), 19.0, 13.0, 12.0);
    Vec u({1.0, 2.0, 3.0});
    show("u", u);
    check("norm(-3 * u) = 3 * norm(u)  (homogeneity)", (u * -3.0).norm(), 11.2249722);
    Vec p({1.0, 2.0, 3.0});
    Vec q({3.0, 0.0, -1.0});
    caseCos(p, q, 0.0);                                              // 3 + 0 - 3 = 0
    caseCos(Vec({1.0, 2.0, 3.0}), Vec({40.0, 50.0, 60.0}), 0.974631846);   // scale does not matter
    Vec w({4.0, 2.0, -3.0});
    Vec z({-2.0, -5.0, 16.0});
    show("u", w);
    show("v", z);
    check("u x v = -(v x u)  (anticommutative)", cross_product(w, z), cross_product(z, w) * -1.0);
    check("(u x v) . u = 0  (perpendicular to u)", cross_product(w, z).dot(w), 0.0);
    check("u x u = 0", cross_product(w, w), Vec({0.0, 0.0, 0.0}));
    space();
    Vec t1({3.0, 0.0});
    Vec t2({0.0, 4.0});
    show("u", t1);
    show("v", t2);
    checkTrue("triangle inequality: norm(u + v) <= norm(u) + norm(v)",
              (t1 + t2).norm() <= t1.norm() + t2.norm());

    section("lerp: extrapolation and consistency");
    check("lerp(0, 10, 2)",  lerp(0.0, 10.0, 2.0),  20.0);
    check("lerp(0, 10, -1)", lerp(0.0, 10.0, -1.0), -10.0);
    Vec lu({0.0, 0.0});
    Vec lv({2.0, 4.0});
    show("u", lu);
    show("v", lv);
    check("lerp(u, v, 1.5)", lerp(lu, lv, 1.5), Vec({3.0, 6.0}));
    Vec cu({2.0, 1.0});
    Vec cv({4.0, 2.0});
    std::vector<Vec> pair = {cu, cv};
    std::vector<double> mix = {0.7, 0.3};
    check("lerp(u, v, 0.3) = linear_combination([u, v], [0.7, 0.3])",
          lerp(cu, cv, 0.3), linear_combination(pair, mix));
    space();
    std::vector<Vec> single = {Vec({1.0, 2.0, 3.0}), Vec({4.0, 5.0, 6.0})};
    std::vector<double> zeros = {0.0, 0.0};
    check("linear_combination with zero coefficients", linear_combination(single, zeros), Vec({0.0, 0.0, 0.0}));

    section("Matrix multiplication");
    Mat m23({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}});
    Mat m32({{7.0, 8.0}, {9.0, 10.0}, {11.0, 12.0}});
    caseMulMat(m23, m32, Mat({{58.0, 64.0}, {139.0, 154.0}}));       // (2x3) * (3x2) = 2x2
    caseMulVec(m23, Vec({1.0, 0.0, -1.0}), Vec({-2.0, -2.0}));       // (2x3) * 3 = 2
    Mat s({{1.0, 2.0}, {3.0, 4.0}});
    Mat sw({{0.0, 1.0}, {1.0, 0.0}});
    caseMulMat(s, sw, Mat({{2.0, 1.0}, {4.0, 3.0}}));                // A * B
    caseMulMat(sw, s, Mat({{3.0, 4.0}, {1.0, 2.0}}));                // B * A is different
    show("A", a);
    show("B", b);
    check("transpose(A * B) = transpose(B) * transpose(A)",
          a.mul_mat(b).transpose(), b.transpose().mul_mat(a.transpose()));
    space();
    show("A", s);
    show("B", sw);
    check("trace(A * B) = trace(B * A)", s.mul_mat(sw).trace(), sw.mul_mat(s).trace());
    check("transpose(transpose(A)) = A", m23.transpose().transpose(), m23);

    section("Row-echelon: zero in the first column, missing pivot");
    caseRowEchelon(Mat({{0.0, 2.0}, {3.0, 4.0}}), Mat({{1.0, 0.0}, {0.0, 1.0}}));
    caseRowEchelon(Mat({{1.0, 0.0, 2.0}, {0.0, 0.0, 3.0}}), Mat({{1.0, 0.0, 0.0}, {0.0, 0.0, 1.0}}));
    caseRowEchelon(Mat(2, 3), Mat({{0.0, 0.0, 0.0}, {0.0, 0.0, 0.0}}));

    section("Determinant: swaps, size 5, properties");
    caseDet(Mat({{0.0, 1.0, 0.0}, {0.0, 0.0, 1.0}, {1.0, 0.0, 0.0}}), 1.0);    // cyclic permutation (2 swaps)
    caseDet(Mat({{0.0, 0.0, 1.0}, {0.0, 1.0, 0.0}, {1.0, 0.0, 0.0}}), -1.0);   // 1 swap
    caseDet(Mat({{1.0, 0.0, 0.0, 0.0, 0.0}, {0.0, 2.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 3.0, 0.0, 0.0},
                 {0.0, 0.0, 0.0, 4.0, 0.0}, {0.0, 0.0, 0.0, 0.0, 5.0}}), 120.0);  // diagonal 5x5
    Mat tri({{2.0, 1.0, 0.0, 0.0, 0.0}, {1.0, 2.0, 1.0, 0.0, 0.0}, {0.0, 1.0, 2.0, 1.0, 0.0},
             {0.0, 0.0, 1.0, 2.0, 1.0}, {0.0, 0.0, 0.0, 1.0, 2.0}});
    caseDet(tri, 6.0);                                                          // tridiagonal 5x5: n + 1
    caseDet(Mat({{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}}), 0.0);     // singular, rounding errors
    show("A", a);
    show("B", b);
    check("det(B)", b.determinant(), 25.0);
    check("det(A * B) = det(A) * det(B) = -4350", a.mul_mat(b).determinant(), -4350.0);
    check("det(2A) = 2^3 * det(A) = -1392", (a * 2.0).determinant(), -1392.0);
    check("det(transpose(A)) = det(A)", a.transpose().determinant(), -174.0);

    section("Inverse: harder cases");
    Mat sys({{2.0, 3.0}, {-7.0, 4.0}});
    show("A  (system 2x + 3y = 8, -7x + 4y = 2)", sys);
    check("inverse(A)", sys.inverse(), Mat({{4.0 / 29.0, -3.0 / 29.0}, {7.0 / 29.0, 2.0 / 29.0}}));
    check("x = inverse(A) * [8, 2]", sys.inverse().mul_vec(Vec({8.0, 2.0})), Vec({26.0 / 29.0, 60.0 / 29.0}));
    space();
    caseMulMat(sw, sw, identity(2));                                           // a swap is its own inverse
    check("inverse([[0,1],[1,0]]) (needs a row swap)", sw.inverse(), sw);
    check("inverse([[4]])  (1x1)", Mat({{4.0}}).inverse(), Mat({{0.25}}));
    show("A", tri);
    check("A * inverse(A) = I  (5x5)", tri.mul_mat(tri.inverse()), identity(5));
    check("inverse(inverse(A)) = A", a.inverse().inverse(), a);
    check("inverse(A * B) = inverse(B) * inverse(A)",
          a.mul_mat(b).inverse(), b.inverse().mul_mat(a.inverse()));
    space();
    Mat sing({{1.0, 2.0, 3.0}, {4.0, 5.0, 6.0}, {7.0, 8.0, 9.0}});
    show("A", sing);
    bool thrown = false;
    try { sing.inverse(); } catch (const std::exception&) { thrown = true; }
    checkTrue("inverse of a singular 3x3 throws an exception", thrown);

    section("Rank: harder cases");
    caseRank(Mat(3, 3), 0.0);                                                   // zero matrix
    caseRank(Mat({{1.0, 2.0, 3.0}, {2.0, 4.0, 6.0}, {3.0, 6.0, 9.0}}), 1.0);    // all rows proportional
    caseRank(Mat({{1.0, 2.0}, {2.0, 4.0}, {3.0, 5.0}, {4.0, 8.0}, {0.0, 1.0}}), 2.0);   // 5x2
    caseRank(Mat({{0.1, 0.2, 0.3}, {0.4, 0.5, 0.6}, {0.7, 0.8, 0.9}}), 2.0);    // rounding errors
    check("rank(A) = rank(transpose(A))",
          static_cast<double>(m23.rank()), static_cast<double>(m23.transpose().rank()));
    check("rank of the 5x5 tridiagonal matrix", static_cast<double>(tri.rank()), 5.0);

    section("Complex: harder cases");
    CMat cp({{C(1.0, 1.0), C(2.0, 0.0)}, {C(0.0, -1.0), C(3.0, 2.0)}});
    CMat cid({{C(1.0, 0.0), C(0.0, 0.0)}, {C(0.0, 0.0), C(1.0, 0.0)}});
    show("P", cp);
    check("P * inverse(P) = I", cp.mul_mat(cp.inverse()), cid);
    CVec cx({C(1.0, 2.0), C(3.0, -1.0)});
    show("x", cx);
    check("x . x is real and positive  (|1+2i|^2 + |3-i|^2 = 5 + 10)", cx.dot(cx), C(15.0, 0.0));
    check("norm(x)^2 = x . x", cx.norm() * cx.norm(), 15.0);
}

int main()
{
    ex00();
    ex01();
    ex02();
    ex03();
    ex04();
    ex05();
    ex06();
    ex07();
    ex08();
    ex09();
    ex10();
    ex11();
    ex12();
    ex13();
    ex14();
    ex15();
    extra();

    std::cout << std::endl << BOLDBLUE << "=== Summary ===" << RESET << std::endl;
    std::cout << GREEN << "  passed: " << g_pass << RESET << std::endl;
    std::cout << (g_fail ? RED : GREEN) << "  failed: " << g_fail << RESET << std::endl;
    return (g_fail ? 1 : 0);
}
