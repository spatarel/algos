#include <cstdio>
#include <cstdlib>
#include <cassert>

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

    Matrix<T> operator *= (const T &b) const {
        int i, j;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->b; ++j) {
                (*this)[i][j] *= b;
            }
        }
        return *this;
    }

    Matrix<T> operator *= (const Matrix<T> &b) {
        return *this = *this * b;
    }

    Matrix<T> operator * (const T &b) const {
        int i, j;
        Matrix<T> sol(this->a, this->b);
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->b; ++j) {
                sol[i][j] = (*this)[i][j] * b;
            }
        }
        return sol;
    }

    Matrix<T> friend operator * (const T &b, const Matrix<T> &a) {
        return a * b;
    }

    Matrix<T> operator * (const Matrix<T> &b) const {
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

    Matrix<T> operator += (const Matrix<T> &b) const {
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

    void LUDecompose(Matrix<T> &L, Matrix<T> &U) const {
        assert(this->a == b);
        assert(L.a == this->a && L.b == this->b);
        assert(U.a == this->a && U.b == this->b);
        int i, j, k;
        for (i = 0; i < this->a; ++i) {
            for (j = 0; j < this->a; ++j) {
                L[i][j] = 0;
                U[i][j] = (*this)[i][j];
            }
        }
        for (j = 0; j < this->a; ++j) { // j = coloana care se face 0
            L[j][j] = 1;
            for (i = j + 1; i < this->a; ++i) { // i = linia care se face 0
                L[i][j] = U[i][j] / U[j][j];
                for (k = j + 1; k < this->a; ++k) { // k = coloana care se scade
                    U[i][k] = U[i][k] - U[j][k] * L[i][j];
                }
                U[i][j] = 0;
            }
        }
    }

    T determinant() const {
        // assert(this->a == this->b)
        int i;
        Matrix<T> L(this->a, this->b), U(this->a, this->b);
        this->LUDecompose(L, U);
        T answer = U[0][0];
        for (i = 1; i < this->a; ++i) {
            answer *= U[i][i];
        }
        return answer;
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
    C = 5 * C;
    C = C * 5;
    C = A;
    C = A + -A;

    int i, j;
    for (i = 0; i < 2; ++i) {
        for (j = 0; j < 2; ++j) {
            printf("%lld ", C[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    Matrix<float> M(3, 3), L(3, 3), U(3, 3);
    M[0][0] = 2; M[0][1] = 5; M[0][2] = 3;
    M[1][0] = 3; M[1][1] = 1; M[1][2] =-2;
    M[2][0] =-1; M[2][1] = 2; M[2][2] = 1;
    M.LUDecompose(L, U);
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%lf ", L[i][j]);
        }
        printf("\n");
    }
    printf("\n");
    for (i = 0; i < 3; ++i) {
        for (j = 0; j < 3; ++j) {
            printf("%lf ", U[i][j]);
        }
        printf("\n");
    }
    printf("\n");

    printf("%lf\n", M.determinant());

    return 0;
}
