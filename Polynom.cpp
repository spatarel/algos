#include <iostream>
#include <algorithm>

using namespace std;

template<class T>
class Polynom {
private:
    int degree;
    T* coefficients;
public:
    Polynom() {
        this->degree = -1;
        this->coefficients = NULL;
    }

    Polynom(const T& arg) {
        this->degree = 0;
        this->coefficients = new T[1];
        this->coefficients[0] = arg;
    }

    Polynom(const Polynom& arg) {
        int i;
        this->degree = arg.degree;
        if (this->degree >= 0) {
            this->coefficients = new T[this->degree + 1];
        } else {
            this->coefficients = NULL;
        }
        for (i = 0; i <= arg.degree; ++i) {
            this->coefficients[i] = arg.coefficients[i];
        }
    }

    Polynom& operator =(const Polynom& arg) {
        int i;
        if (this->coefficients != NULL) {
            delete this->coefficients;
            this->coefficients = NULL;
        }
        this->degree = arg.degree;
        if (this->degree >= 0) {
            this->coefficients = new T[this->degree + 1];
        } else {
            this->coefficients = NULL;
        }
        for (i = 0; i <= arg.degree; ++i) {
            this->coefficients[i] = arg.coefficients[i];
        }
        return *this;
    }

    int getDegree() const {
        return this->degree;
    }

    T& operator [](unsigned int arg) const {
        return this->coefficients[arg];
    }

    Polynom operator <<(unsigned int arg) const {
        int i;
        Polynom answer;
        if (this->degree < 0) {
            arg = 0;
        }
        answer.degree = this->degree + arg;
        if (answer.degree >= 0) {
            answer.coefficients = new T[answer.degree + 1];
        } else {
            answer.coefficients = NULL;
        }
        for (i = 0; i < (int)arg; ++i) {
            answer.coefficients[i] = (T)0;
        }
        for (i = 0; i <= this->degree; ++i) {
            answer.coefficients[i + arg] = this->coefficients[i];
        }
        return answer;
    }

    Polynom& operator <<=(unsigned int arg) {
        return *this = *this << arg;
    }

    const Polynom& operator +() const {
        return *this;
    }

    Polynom operator +(const Polynom& arg) const {
        int i, j;
        Polynom answer;
        answer.degree = max(this->degree, arg.degree);
        if (answer.degree >= 0) {
            answer.coefficients = new T[answer.degree + 1];
        } else {
            answer.coefficients = NULL;
        }
        for (i = 0, j = 0; i <= this->degree && j <= arg.degree; ++i, ++j) {
            answer.coefficients[i] = this->coefficients[i] + arg.coefficients[j];
        }
        for (; i <= this->degree; ++i) {
            answer.coefficients[i] = this->coefficients[i];
        }
        for (; j <= arg.degree; ++j) {
            answer.coefficients[j] = arg.coefficients[j];
        }
        while (answer.degree >= 0 && answer.coefficients[answer.degree] == (T)0) {
            --answer.degree;
        }
        return answer;
    }

    Polynom& operator +=(const Polynom& arg) {
        return *this = *this + arg;
    }

    Polynom operator -() const {
        int i;
        Polynom answer;
        answer.degree = this->degree;
        if (answer.degree >= 0) {
            answer.coefficients = new T[answer.degree + 1];
        } else {
            answer.coefficients = NULL;
        }
        for (i = 0; i <= this->degree; ++i) {
            answer.coefficients[i] = -this->coefficients[i];
        }
        return answer;
    }

    Polynom operator -(const Polynom& arg) const {
        int i, j;
        Polynom answer;
        answer.degree = max(this->degree, arg.degree);
        if (answer.degree >= 0) {
            answer.coefficients = new T[answer.degree + 1];
        } else {
            answer.coefficients = NULL;
        }
        for (i = 0, j = 0; i <= this->degree && j <= arg.degree; ++i, ++j) {
            answer.coefficients[i] = this->coefficients[i] - arg.coefficients[j];
        }
        for (; i <= this->degree; ++i) {
            answer.coefficients[i] = this->coefficients[i];
        }
        for (; j <= arg.degree; ++j) {
            answer.coefficients[j] = -arg.coefficients[j];
        }
        while (answer.degree >= 0 && answer.coefficients[answer.degree] == (T)0) {
            --answer.degree;
        }
        return answer;
    }

    Polynom& operator -=(const Polynom& arg) {
        return *this = *this - arg;
    }

    Polynom operator *(const Polynom& arg) const {
        int i, j;
        Polynom answer;
        if (this->degree < 0 || arg.degree < 0) {
            answer.degree = -1;
        } else {
            answer.degree = this->degree + arg.degree;
        }
        if (answer.degree >= 0) {
            answer.coefficients = new T[answer.degree + 1];
        } else {
            answer.coefficients = NULL;
        }
        for (i = 0; i <= answer.degree; ++i) {
            answer.coefficients[i] = 0;
        }
        for (i = 0; i <= this->degree; ++i) {
            for (j = 0; j <= arg.degree; ++j) {
                answer.coefficients[i + j] += this->coefficients[i] * arg.coefficients[j];
            }
        }
        return answer;
    }

    Polynom& operator *=(const Polynom& arg) {
        return *this = *this * arg;
    }

    T operator ()(const T& value) const {
        int i;
        T answer;
        if (0 <= this->degree) {
            answer = this->coefficients[0];
        } else {
            answer = 0;
        }
        T powX = value;
        for (i = 1; i <= this->degree; ++i) {
            answer += powX * this->coefficients[i];
            powX *= value;
        }
        return answer;
    }

    Polynom operator ()(const Polynom& value) const {
        int i;
        Polynom answer;
        if (0 <= this->degree) {
            answer = this->coefficients[0];
        } else {
            answer = (T)0;
        }
        Polynom powX = value;
        for (i = 1; i <= this->degree; ++i) {
            answer += powX * this->coefficients[i];
            powX *= value;
        }
        return answer;
    }

    friend ostream& operator << (ostream& stream, const Polynom& arg) {
        int i;
        if (arg.getDegree() == -1) {
            stream << '0';
        }
        for (i = (int)arg.getDegree(); i >= 0; --i) {
            stream << arg[i];
            if (i > 0) {
                stream << ' ';
            }
        }
        return stream;
    }

    ~Polynom() {
        if (this->coefficients != NULL) {
            delete this->coefficients;
        }
    }
};
