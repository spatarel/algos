#include <assert.h>

template<class T>
class Rational {
private:
    T numerator;
    T denominator;

    static T abs(const T& arg) {
        if (arg >= 0) {
            return arg;
        } else {
            return -arg;
        }
    }

    void simplify() {
        if (this->denominator < 0) {
            this->numerator *= -1;
            this->denominator *= -1;
        }
        if (this->numerator == 0) {
            this->denominator = 1;
        }
        T a = Rational::abs(this->numerator);
        T b = Rational::abs(this->denominator);
        T c;
        while (b > 0) {
            c = a % b;
            a = b;
            b = c;
        }
        this->numerator /= a;
        this->denominator /= a;
    }

public:
    Rational() {
        this->numerator = 0;
        this->denominator = 1;
    }

    Rational(const Rational& arg) {
        this->numerator = arg.numerator;
        this->denominator = arg.denominator;
    }

    Rational(const T& value) {
        this->numerator = value;
        this->denominator = 1;
    }

    Rational(const T& numerator, const T& denominator) {
        assert(denominator != 0);
        this->numerator = numerator;
        this->denominator = denominator;
        this->simplify();
    }

    Rational module() const {
        if (*this >= (T)0) {
            return *this;
        } else {
            return -*this;
        }
    }

    Rational& operator = (const Rational& arg) {
        this->numerator = arg.numerator;
        this->denominator = arg.denominator;
        return *this;
    }

    Rational& operator = (const T& value) {
        this->numerator = value;
        this->denominator = 1;
        return *this;
    }

    bool operator == (const Rational& arg) const {
        return this->numerator == arg.numerator && this->denominator == arg.denominator;
    }

    bool operator != (const Rational& arg) const {
        return !(this->numerator == arg.numerator && this->denominator == arg.denominator);
    }

    bool operator > (const Rational& arg) const {
        return this->numerator * arg.denominator > arg.numerator * this->denominator;
    }

    bool operator >= (const Rational& arg) const {
        return this->numerator * arg.denominator >= arg.numerator * this->denominator;
    }

    bool operator < (const Rational& arg) const {
        return this->numerator * arg.denominator < arg.numerator * this->denominator;
    }

    bool operator <= (const Rational& arg) const {
        return this->numerator * arg.denominator <= arg.numerator * this->denominator;
    }

    const Rational& operator + () const {
        return *this;
    }

    Rational operator + (const Rational& arg) const {
        return Rational(
                this->numerator * arg.denominator + arg.numerator * this->denominator,
                this->denominator * arg.denominator);
    }

    Rational operator - () const {
        return Rational(
                -this->numerator,
                this->denominator);
    }

    Rational operator - (const Rational& arg) const {
        return Rational(
                this->numerator * arg.denominator - arg.numerator * this->denominator,
                this->denominator * arg.denominator);
    }

    Rational operator * (const Rational& arg) const {
        return Rational(
                this->numerator * arg.numerator,
                this->denominator * arg.denominator);
    }

    Rational operator / (const Rational& arg) const {
        return Rational(
                this->numerator * arg.denominator,
                this->denominator * arg.numerator);
    }

    Rational& operator += (const Rational& arg) {
        return *this = *this + arg;
    }

    Rational& operator -= (const Rational& arg) {
        return *this = *this - arg;
    }

    Rational& operator *= (const Rational& arg) {
        return *this = *this * arg;
    }

    Rational& operator /= (const Rational& arg) {
        return *this = *this / arg;
    }

    T getNumerator() const {
        return this->numerator;
    }

    T getDenominator() const {
        return this->denominator;
    }
};
