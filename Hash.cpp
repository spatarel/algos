#include <cstdio>
#include <cstdlib>
#include <algorithm>

using namespace std;

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

    bool operator != (const ModInteger& arg) const {
        return this->value != arg.value;
    }

    ModInteger operator + (const ModInteger& arg) const {
        return ModInteger(this->value + arg.value);
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

    ModInteger& operator -= (const ModInteger& arg) {
        //this->value = (this->value + (-arg).value) % MOD;
        this->value = (this->value + (MOD - arg.value)) % MOD;
        return *this;
    }

    ModInteger operator * (const ModInteger& arg) const {
        return ModInteger(this->value * arg.value);
    }

    ModInteger& operator *= (const ModInteger& arg) {
        this->value = (this->value * arg.value) % MOD;
        return *this;
    }

    ModInteger pow(unsigned int exp) const {
        unsigned long long answer = 1;
        unsigned long long power = this->value;
        for(; exp > 0; exp >>= 1) {
            if ((exp & 1) > 0) {
                answer = (answer * power) % MOD;
            }
            power = (power * power) % MOD;
        }
        return answer;
    }

    ModInteger inverse() const {
        return this->pow(MOD - 2);
    }

    ModInteger operator / (const ModInteger& arg) const {
        return ModInteger(this->value * arg.inverse().hash);
    }

    ModInteger& operator /= (const ModInteger& arg) {
        this->value = (this->value * arg.inverse().hash) % MOD;
        return *this;
    }
};

class Hash {
private:
    ModInteger<1000000007> h1;
    ModInteger<1000000009> h2;
    ModInteger<1000000011> h3;

public:
    Hash() {
        this->h1 = 0;
        this->h2 = 0;
        this->h3 = 0;
    }

    Hash(int value) {
        this->h1 = value;
        this->h2 = value;
        this->h3 = value;
    }

    Hash pow(unsigned int exp) const {
        Hash answer = *this;
        answer.h1 = answer.h1.pow(exp);
        answer.h2 = answer.h2.pow(exp);
        answer.h3 = answer.h3.pow(exp);
        return answer;
    }

    Hash operator * (const Hash& arg) const {
        Hash answer = *this;
        answer.h1 = this->h1 * arg.h1;
        answer.h2 = this->h2 * arg.h2;
        answer.h3 = this->h3 * arg.h3;
        return answer;
    }

    Hash operator *= (const Hash& arg) {
        this->h1 *= arg.h1;
        this->h2 *= arg.h2;
        this->h3 *= arg.h3;
    	return *this;
    }

    Hash operator + (const Hash& arg) const {
        Hash answer = *this;
        answer.h1 = this->h1 + arg.h1;
        answer.h2 = this->h2 + arg.h2;
        answer.h3 = this->h3 + arg.h3;
        return answer;
    }

    Hash operator += (const Hash& arg) {
        this->h1 += arg.h1;
        this->h2 += arg.h2;
        this->h3 += arg.h3;
    	return *this;
    }

    Hash operator - (const Hash& arg) const {
        Hash answer = *this;
        answer.h1 = this->h1 - arg.h1;
        answer.h2 = this->h2 - arg.h2;
        answer.h3 = this->h3 - arg.h3;
        return answer;
    }

    Hash operator -= (const Hash& arg) {
        this->h1 -= arg.h1;
        this->h2 -= arg.h2;
        this->h3 -= arg.h3;
    	return *this;
    }

    bool operator < (const Hash &arg) const {
        return this->h1.getllu() < arg.h1.getllu() ||
                (this->h1.getllu() == arg.h1.getllu() && this->h2.getllu() < arg.h2.getllu()) ||
                (this->h1.getllu() == arg.h1.getllu() && this->h2.getllu() == arg.h2.getllu() && this->h3.getllu() < arg.h3.getllu());
    }

    bool operator == (const Hash &arg) const {
        return this->h1 == arg.h1 && this->h2 == arg.h2 && this->h3 == arg.h3;
    }

    void dump() {
    	printf("(%llu,%llu,%llu)", this->h1.getllu(), this->h2.getllu(), this->h3.getllu());
    }
};

template<int SIGMA = 26, char FIRST_LETTER = 'a'>
class RollingHash {
private:
	Hash hash;
	Hash base;

public:
	RollingHash() {
		this->hash = 0;
		this->base = 0;
	}

	void clear() {
		this->hash = 0;
		this->base = 0;
	}

	void add(char letter) {
		this->hash = (this->hash * SIGMA) + (letter - FIRST_LETTER);
		if (this->base == 0) {
			this->base = 1;
		} else {
			this->base *= SIGMA;
		}
	}

	void roll(char newLetter, char oldLetter) {
		this->hash = (this->hash - (this->base * (oldLetter - FIRST_LETTER))) * SIGMA + (newLetter - FIRST_LETTER);
	}

	Hash getHash() const {
		return this->hash;
	}
};

class HashWithID {
public:
    int id;
    Hash hash;

    HashWithID(Hash hash, int id) {
    	this->hash = hash;
    	this->id = id;
    }

    bool operator < (const HashWithID &arg) const {
        return this->hash < arg.hash;
    }

    bool operator == (const HashWithID &arg) const {
        return this->hash == arg.hash;
    }
};
