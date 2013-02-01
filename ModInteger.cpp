#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

template <unsigned long long MOD>
class ModInteger {
private:
    unsigned long long V;

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

