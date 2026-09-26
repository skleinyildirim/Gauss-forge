Complex::Complex() : _real(0.0), _imag(0.0) {}

Complex::Complex(double real, double imag) : _real(real), _imag(imag) {}

Complex Complex::operator+(const Complex& c) const {
    double r = _real + c._real;
    double i = _imag + c._imag;
    Complex result(r, i);
    return (result);
}

Complex Complex::operator-(const Complex& c) const {
    double r = _real - c._real;
    double i = _imag - c._imag;
    Complex result(r, i);
    return (result);
}

Complex Complex::operator*(const Complex& c) const {
    double r = _real * c._real - _imag * c._imag;
    double i = _real * c._imag + _imag * c._real;
    Complex result(r, i);
    return (result);
}

Complex Complex::operator/(const Complex& c) const {
    double denom = c._real * c._real + c._imag * c._imag;
    double r = _real * c._real + _imag * c._imag;
    double i = _imag * c._real - _real * c._imag;
    Complex result(r / denom, i / denom);
    return (result);
}

Complex& Complex::operator+=(const Complex& c) {
    *this = *this + c;
    return (*this);
}

Complex& Complex::operator-=(const Complex& c) {
    *this = *this - c;
    return (*this);
}

Complex& Complex::operator*=(const Complex& c) {
    *this = *this * c;
    return (*this);
}

Complex& Complex::operator/=(const Complex& c) {
    *this = *this / c;
    return (*this);
}

bool Complex::operator==(const Complex& c) const {
    if (_real == c._real && _imag == c._imag)
        return (true);
    return (false);
}

bool Complex::operator!=(const Complex& c) const {
    return (!(*this == c));
}

Complex Complex::conj() const {
    Complex result(_real, -_imag);
    return (result);
}

double Complex::modulus() const {
    return (std::pow((_real * _real + _imag * _imag), 0.5));
}

double Complex::getReal() const {
    return (_real);
}

double Complex::getImag() const {
    return (_imag);
}

std::ostream& operator<<(std::ostream& out, const Complex& c) {
    if (c.getImag() < 0)
        out << c.getReal() << " - " << -c.getImag() << "i";
    else
        out << c.getReal() << " + " << c.getImag() << "i";
    return (out);
}

Complex fma(const Complex& a, const Complex& b, const Complex& c) {
    return (a * b + c);
}

Complex conj_helper(const Complex& c) {
    return (c.conj());
}

double pow_helper(const Complex& c, double exponent) {
    return (std::pow(c.getReal(), exponent));
}

double to_real_helper(const Complex& c) {
    return (c.getReal());
}

double abs_helper(const Complex& c) {
    return (c.modulus());
}
