#include <stdio.h>
#include <stdlib.h>

template <unsigned long long MOD>
class ModInteger {
private:
    unsigned long long V;

    unsigned long long powPrivate(unsigned int exp) const {
        unsigned long long pows[33];
        int i;
        unsigned long long answer = 1;
        pows[0] = this->V;
        for(i = 0; exp > 0; exp >>= 1, ++i) {
            if ((exp & 1) > 0) {
                answer = (answer * pows[i]) % MOD;
            }
            pows[i + 1] = (pows[i] * pows[i]) % MOD;
        }
        return answer;
    }

public:
    ModInteger() {
        this->V = 0;
    }

    ModInteger(unsigned long long V) {
        this->V = V % MOD;
    }

    unsigned long long getllu() const {
        return this->V;
    }

    long long getlld() const {
        return this->V;
    }

    unsigned int getu() const {
        return this->V;
    }

    int getd() const {
        return this->V;
    }

    bool operator == (const ModInteger<MOD> &B) const {
        return this->V == B.V;
    }

    bool operator != (const ModInteger<MOD> &B) const {
        return this->V != B.V;
    }

    ModInteger<MOD> operator + (const ModInteger<MOD> &B) const {
        ModInteger<MOD> sol(this->V + B.V);
        return sol;
    }

    ModInteger<MOD> operator += (const ModInteger<MOD> &B) {
        this->V = (this->V + B.V) % MOD;
        return *this;
    }

    ModInteger<MOD> operator - () const {
        ModInteger<MOD> sol(MOD - this->V);
        return sol;
    }

    ModInteger<MOD> operator - (const ModInteger<MOD> &B) const {
        ModInteger<MOD> sol(this->V + (-B).V);
        return sol;
    }

    ModInteger<MOD> operator -= (const ModInteger<MOD> &B) {
        this->V = (this->V + (-B).V) % MOD;
        return *this;
    }

    ModInteger<MOD> operator * (const ModInteger<MOD> &B) const {
        ModInteger<MOD> sol(this->V * B.V);
        return sol;
    }

    ModInteger<MOD> operator *= (const ModInteger<MOD> &B) {
        this->V = (this->V * B.V) % MOD;
        return *this;
    }

    ModInteger<MOD> pow(const unsigned int exp) const {
        return this->powPrivate(exp);
    }

    ModInteger<MOD> inverse() const {
        return this->pow(MOD - 2);
    }

    ModInteger<MOD> operator / (const ModInteger<MOD> &B) const {
        ModInteger<MOD> sol(this->V * B.inverse().V);
        return sol;
    }

    ModInteger<MOD> operator /= (const ModInteger<MOD> &B) {
        this->V = (this->V * B.inverse().V) % MOD;
        return *this;
    }
};

int main(void) {
    unsigned long long a = 1000;
    unsigned long long c = a * a * a * a * a * a * a;
    ModInteger<1000000007> A = 1000;
    ModInteger<1000000007> B = 6;
    //ModInteger<1000000007> C = (A * A * A) * (A * A * A) * (A * A * A);
    ModInteger<1000000007> C = ((((((((A * A) * A) * A) * A) * A) * A) * A) * A);
    //C = A;
    //C -= B;
    printf("%llu\n", c);
    printf("%llu\n", C.getllu());
    return 0;
}
