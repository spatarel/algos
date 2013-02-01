#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

template <class T>
class Matrix {
private:
    T** M;
    int a;
    int b;

    static T** aloca(int a, int b) {
        int i, j;
        T** A;
        A = (T**)(malloc(a * sizeof(T*)));
        for (i = 0; i < a; ++i) {
            A[i] = (T*)(malloc(b * sizeof(T)));
            for (j = 0; j < b; ++j) {
                A[i][j] = 0;
            }
        }
        return A;
    }

public:
    static Matrix<T> Id(int a) {
        Matrix<T> A(a, a);
        int i;
        for (i = 0; i < a; ++i) {
            A[i][i] = 1;
        }
        return A;
    }

    Matrix(int a, int b) {
        this->M = Matrix::aloca(a, b);
        this->a = a;
        this->b = b;
    }

    Matrix(const Matrix<T> &B) {
        this->a = B.a;
        this->b = B.b;
        this->M = Matrix<T>::aloca(B.a, B.b);
        int i, j;
        for (i = 0; i < a; ++i) {
            for (j = 0; j < b; ++j) {
                this->M[i][j] = B.M[i][j];
            }
        }
    }

    ~Matrix() {
        int i;
        for (i = 0; i < a; ++i) {
            free(this->M[i]);
        }
        free(this->M);
    }

    T* operator[] (int i) const {
        return this->M[i];
    }

    Matrix<T> operator = (const Matrix<T> &B) {
        this->M = Matrix<T>::aloca(B.a, B.b);
        int i, j;
        for (i = 0; i < a; ++i) {
            for (j = 0; j < b; ++j) {
                this->M[i][j] = B.M[i][j];
            }
        }
        this->a = B.a;
        this->b = B.b;
        return *this;
    }

    Matrix<T> operator *= (const T b) {
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->b; ++j) {
                (*this)[i][j] *= b;
            }
        }
        return *this;
    }

    Matrix<T> operator *= (const Matrix<T> b) {
        return *this = *this * b;
    }

    Matrix<T> operator * (const T b) {
        int i, j;
        Matrix<T> sol(this->a, this->b);
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->b; ++j) {
                sol[i][j] = (*this)[i][j] * b;
            }
        }
        return sol;
    }

    Matrix<T> operator * (const Matrix<T> b) const {
        assert(this->b == b.a);
        Matrix<T> sol(this->a, b.b);
        int i, j, k;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < b.b; ++j) {
                sol[i][j] = 0;
                for (k = 0; k < this->b; ++k) {
                    sol[i][j] += (*this)[i][k] * b[k][j];
                }
            }
        }
        return sol;
    }

    Matrix<T> operator += (const Matrix<T> b) const {
        assert(this->a == b.a && this->b == b.b);
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < b.b; ++j) {
                (*this)[i][j] += b[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator + (const Matrix<T> b) const {
        assert(this->a == b.a && this->b == b.b);
        Matrix<T> sol(this->a, this->b);
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < b.b; ++j) {
                sol[i][j] = (*this)[i][j] + b[i][j];
            }
        }
        return sol;
    }

    Matrix<T> operator - () const {
        Matrix<T> sol(this->a, this->b);
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->b; ++j) {
                sol[i][j] = -(*this)[i][j];
            }
        }
        return sol;
    }

    Matrix<T> operator -= (const Matrix<T> b) const {
        assert(this->a == b.a && this->b == b.b);
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < b.b; ++j) {
                (*this)[i][j] -= b[i][j];
            }
        }
        return *this;
    }

    Matrix<T> operator - (const Matrix<T> b) const {
        assert(this->a == b.a && this->b == b.b);
        Matrix<T> sol(this->a, this->b);
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < b.b; ++j) {
                sol[i][j] = (*this)[i][j] - b[i][j];
            }
        }
        return sol;
    }

    Matrix<T> operator ^ (const unsigned long long exp) const {
        assert(this->a == this->b);
        if (exp == 0) {
            return Matrix<T>::Id(this->a);
        } else if (exp == 1) {
            return *this;
        } else {
            int part = exp / 2;
            int rest = exp % 2;
            Matrix<T> sol = *this ^ part;
            sol *= sol;
            if (rest == 1) {
                sol *= *this;
            }
            return sol;
        }
    }
};

int main(void) {
    Matrix<long long> A(2, 2);
    A[0][0] = 1;
    A[0][1] = 2;
    A[1][0] = 3;
    A[1][1] = 4;
    Matrix<long long> B(2, 2);
    B[0][0] = 0;
    B[0][1] = 1;
    B[1][0] = 1;
    B[1][1] = 0;
    Matrix<long long> C = B * A;
    C = A * A * A * A * A * A * A * A * A * A;
    C = A ^ 1000000000;
    C = A + B;
    C = A;
    C *= A;
    C *= 5;
    C = A;
    C = A + -A;

    int i, j;
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            printf("%lld ", C[i][j]);
        }
        printf("\n");
    }
    return 0;
}

