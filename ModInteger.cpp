#include <cstdio>
#include <cstdlib>

template <unsigned long long MOD>
class ModInteger {
private:
    unsigned long long value;

public:
    ModInteger() {
        this->value = 0;
    }

    ModInteger(const unsigned long long& arg) {
        this->value = arg % MOD;
    }

    unsigned long long getllu() const {
        return this->value;
    }

    long long getlld() const {
        return this->value;
    }

    unsigned int getu() const {
        return this->value;
    }

    int getd() const {
        return this->value;
    }

    bool operator == (const ModInteger& arg) const {
        return this->value == arg.value;
    }

    friend bool operator == (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 == arg2;
    }

    bool operator != (const ModInteger& arg) const {
        return this->value != arg.value;
    }

    friend bool operator != (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 != arg2;
    }

    ModInteger operator + (const ModInteger& arg) const {
        return ModInteger(this->value + arg.value);
    }

    friend ModInteger operator + (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 + arg2;
    }

    ModInteger& operator += (const ModInteger& arg) {
        this->value = (this->value + arg.value) % MOD;
        return *this;
    }

    ModInteger operator - () const {
        return ModInteger(MOD - this->value);
    }

    ModInteger operator - (const ModInteger& arg) const {
        //return ModInteger(this->value + (-arg).value);
        return ModInteger(this->value + (MOD - arg.value));
    }

    friend ModInteger operator - (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 - arg2;
    }

    ModInteger& operator -= (const ModInteger& arg) {
        //this->value = (this->value + (-arg).value) % MOD;
        this->value = (this->value + (MOD - arg.value)) % MOD;
        return *this;
    }

    ModInteger operator * (const ModInteger& arg) const {
        return ModInteger(this->value * arg.value);
    }

    friend ModInteger operator * (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 * arg2;
    }

    ModInteger& operator *= (const ModInteger& arg) {
        this->value = (this->value * arg.value) % MOD;
        return *this;
    }

    ModInteger pow(unsigned long long exp) const {
        unsigned long long answer = 1;
        unsigned long long power = this->value;
        while(exp > 0) {
            if ((exp & 1) > 0) {
                answer = (answer * power) % MOD;
            }
            power = (power * power) % MOD;
            exp >>= 1;
        }
        return answer;
    }

    ModInteger inverse() const {
        return this->pow(MOD - 2);
    }

    ModInteger operator / (const ModInteger& arg) const {
        return ModInteger(this->value * arg.inverse().value);
    }

    friend ModInteger operator / (const unsigned long long& arg1, const ModInteger& arg2) {
        return (const ModInteger)arg1 / arg2;
    }

    ModInteger& operator /= (const ModInteger& arg) {
        this->value = (this->value * arg.inverse().value) % MOD;
        return *this;
    }
};

int main(void) {
    unsigned long long a = 1000;
    unsigned long long c = a * a * a * a * a * a * a;
    ModInteger<1000000007> A = 1000;
    ModInteger<1000000007> B = 6;
    ModInteger<1000000007> C = (A * A * A) * (A * A * A) * (A * A * A);
    //ModInteger<1000000007> C = ((((((((A * A) * A) * A) * A) * A) * A) * A) * A);
    //C = A;
    //C -= B;
    printf("%llu\n", c);
    printf("%llu\n", C.getllu());
    return 0;
}
