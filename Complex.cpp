#include <cmath>

class Complex {
private:
    double real;
    double imaginary;
public:
    Complex(double real = 0, double imaginary = 0) {
        this->real = real;
        this->imaginary = imaginary;
    }

    double getReal() const {
        return this->real;
    }

    double getImaginary() const {
        return this->imaginary;
    }

    bool operator ==(const Complex &arg) const {
        return fabs(this->real - arg.real) < 1e-6 &&
                fabs(this->imaginary - arg.imaginary) < 1e-6;
    }

    bool operator !=(const Complex &arg) const {
        return !(this->real == arg.real);
    }

    Complex operator +(const Complex &arg) const {
        return Complex(
                this->real + arg.real,
                this->imaginary + arg.imaginary);
    }

    Complex operator +() const {
        return *this;
    }

    Complex operator -(const Complex &arg) const {
        return Complex(
                this->real - arg.real,
                this->imaginary - arg.imaginary);
    }

    Complex operator -() const {
        return Complex(
                -this->real,
                -this->imaginary);
    }

    Complex operator *(const Complex &arg) const {
        return Complex(
                this->real * arg.real - this->imaginary * arg.imaginary,
                this->real * arg.imaginary + this->imaginary * arg.real);
    }

    double module() const {
        return sqrt(this->real * this->real + this->imaginary * this->imaginary);
    }

    double moduleSquared() const {
        return this->real * this->real + this->imaginary * this->imaginary;
    }

    Complex conjugate() const {
        return Complex(
                this->real,
                -this->imaginary);
    }

    Complex inverse() const {
        return this->conjugate() / this->moduleSquared();
    }

    Complex operator /(const Complex &arg) const {
        return *this * arg.inverse();
    }

    Complex operator /(const double &arg) const {
        return Complex(
                this->real / arg,
                this->imaginary / arg);
    }

    Complex operator +=(const Complex &arg) {
        return *this = *this + arg;
    }

    Complex operator -=(const Complex &arg) {
        return *this = *this - arg;
    }

    Complex operator *=(const Complex &arg) {
        return *this = *this * arg;
    }

    Complex operator /=(const Complex &arg) {
        return *this = *this / arg;
    }
};

class ComplexInt {
private:
    long long real;
    long long imaginary;
public:
    ComplexInt(long long real = 0, long long imaginary = 0) {
        this->real = real;
        this->imaginary = imaginary;
    }

    long long  getReal() const {
        return this->real;
    }

    long long  getImaginary() const {
        return this->imaginary;
    }

    bool operator ==(const ComplexInt &arg) const {
        return this->real == arg.real &&
                this->imaginary == arg.imaginary;
    }

    bool operator !=(const ComplexInt &arg) const {
        return !(this->real == arg.real);
    }

    ComplexInt operator +(const ComplexInt &arg) const {
        return ComplexInt(
                this->real + arg.real,
                this->imaginary + arg.imaginary);
    }

    ComplexInt operator +() const {
        return *this;
    }

    ComplexInt operator -(const ComplexInt &arg) const {
        return ComplexInt(
                this->real - arg.real,
                this->imaginary - arg.imaginary);
    }

    ComplexInt operator -() const {
        return ComplexInt(
                -this->real,
                -this->imaginary);
    }

    ComplexInt operator *(const ComplexInt &arg) const {
        return ComplexInt(
                this->real * arg.real - this->imaginary * arg.imaginary,
                this->real * arg.imaginary + this->imaginary * arg.real);
    }

    long long moduleSquared() const {
        return this->real * this->real + this->imaginary * this->imaginary;
    }

    ComplexInt conjugate() const {
        return ComplexInt(
                this->real,
                -this->imaginary);
    }

    ComplexInt operator +=(const ComplexInt &arg) {
        return *this = *this + arg;
    }

    ComplexInt operator -=(const ComplexInt &arg) {
        return *this = *this - arg;
    }

    ComplexInt operator *=(const ComplexInt &arg) {
        return *this = *this * arg;
    }
};
