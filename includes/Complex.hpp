#pragma once 

#include <iostream>
#include <cmath>

class Complex
{
    private:
        double _real;
        double _imag;
    public:
        Complex();
        Complex(double real, double imag = 0.0);
        Complex operator+(const Complex& c) const;
        Complex operator-(const Complex& c) const;
        Complex operator*(const Complex& c) const;
        Complex operator/(const Complex& c) const;

        Complex& operator+=(const Complex& c);
        Complex& operator-=(const Complex& c);
        Complex& operator*=(const Complex& c);
        Complex& operator/=(const Complex& c);

        bool operator==(const Complex& c) const;
        bool operator!=(const Complex& c) const;

        double getReal() const;
        double getImag() const;

        Complex conj() const;
        double modulus() const;

};

std::ostream& operator<<(std::ostream& out, const Complex& c);

Complex fma(const Complex& a, const Complex& b, const Complex& c);

Complex conj(const Complex& c);

Complex conj_helper(const Complex& c);

double pow_helper(const Complex& c, double exponent);

double to_real_helper(const Complex& c);

#include "Complex.tpp"
