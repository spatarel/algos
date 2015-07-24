#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

class HugeInt {
public:
    int sign;
    int size;
    int *V;

private:
    static const int BASE;
    static const int SCAN_POWER;
    static const char* PRINT_FORMAT;

    HugeInt unsignedAddition(const HugeInt& arg, int newSign) const {
        HugeInt answer;
        answer.alloc(max(this->size, arg.size) + 2);
        int i;
        int min = this->size < arg.size ? this->size : arg.size;
        for (i = 0; i <= min; ++i) {
            answer.V[i] = this->V[i] + arg.V[i];
        }
        for (; i <= this->size; ++i) {
            answer.V[i] = this->V[i];
        }
        for (; i <= arg.size; ++i) {
            answer.V[i] = arg.V[i];
        }
        answer.V[i] = 0;
        answer.size = i - 1;
        for (i = 0; i <= answer.size; ++i) {
            if (answer.V[i] >= BASE) {
                answer.V[i] -= BASE;
                ++answer.V[i + 1];
            }
        }
        if (answer.V[i] > 0) {
            ++answer.size;
        }
        answer.sign = newSign;
        return answer;
    }

    HugeInt unsignedSubtraction(const HugeInt& arg, int newSign) const {
        HugeInt answer;
        answer.alloc(max(this->size, arg.size) + 2);
        int i;
        int min = this->size < arg.size ? this->size : arg.size;
        for (i = 0; i <= min; ++i) {
            answer.V[i] = this->V[i] - arg.V[i];
        }
        for (; i <= this->size; ++i) {
            answer.V[i] = this->V[i];
        }
        for (; i <= arg.size; ++i) {
            answer.V[i] = -arg.V[i];
        }
        answer.size = i - 1;
        for (i = 0; i <= answer.size; ++i) {
            if (answer.V[i] < 0) {
                answer.V[i] += BASE;
                --answer.V[i + 1];
            }
        }
        for (; answer.V[answer.size] == 0 && answer.size > 0; --answer.size);
        answer.sign = newSign;
        return answer;
    }

    HugeInt digitMultiplication(const int& arg) const {
        HugeInt answer;
        answer.alloc(this->size + 3);
        int myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            if (this->sign == -1) answer.sign = 1;
            else answer.sign = -1;
        } else {
            answer.sign = this->sign;
        }
        int i;
        long long tmp;
        for (i = 0; i <= this->size + 1; ++i) {
            answer.V[i] = 0;
        }
        for (i = 0; i <= this->size; ++i) {
            tmp = (long long)this->V[i] * myArg + answer.V[i];
            answer.V[i] = (int)(tmp % BASE);
            //A.V[i + 1] = (tmp - A.V[a]) / BASE;
            answer.V[i + 1] = (int)(tmp / BASE);
        }
        if (answer.V[this->size + 1]) {
            answer.size = this->size + 1;
        } else {
            answer.size = this->size;
        }
        return answer;
    }

public:
    HugeInt baseMultiplication(const int& arg) const {
        if (this->size == 0 && this->V[0] == 0) {
            return *this;
        }
        int i, j;
        HugeInt answer;
        if (this->size + arg >= 0) {
            answer.alloc(this->size + arg + 2);
            answer.sign = this->sign;
            answer.size = this->size + arg;
            for (i = answer.size, j = this->size; j >= 0 && i >= 0; --i, --j) {
                answer.V[i] = this->V[j];
            }
            for (; i >= 0; --i) {
                answer.V[i] = 0;
            }
        } else {
            answer = 0;
        }
        return answer;
    }

private:
    HugeInt digitDivision(const int& arg) const {
        HugeInt answer;
        answer.alloc(this->size + 2);
        int myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            if (this->sign == -1) answer.sign = 1;
            else answer.sign = -1;
        } else {
            answer.sign = this->sign;
        }
        int i;
        long long tmp1, tmp2;
        tmp1 = this->V[this->size];
        for (i = this->size; i >= 0; --i) {
            tmp2 = tmp1 % myArg;
            tmp1 -= tmp2;
            answer.V[i] = (int)(tmp1 / myArg);
            if (i) tmp1 = tmp2 * BASE + this->V[i - 1];
        }
        if (answer.V[this->size] > 0) {
            answer.size = this->size;
        } else {
            if (this->size > 0) {
                answer.size = this->size - 1;
            } else {
                answer.size = this->size;
            }
        }
        return answer;
    }

    int digitRemainder(const int& arg) const {
        long long answer = 0;
        int i;
        for(i = this->size; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
            answer %= arg;
        }
        return (int)answer;
    }

    void alloc(int size) {
        if (this->V != NULL) {
            delete this->V;
        }
        this->V = new int[size];
    }

    void realloc(int oldSize, int newSize) {
        if (this->V == NULL) {
            this->V = new int[newSize];
        } else {
            int i;
            int* oldV = this->V;
            this->V = new int[newSize];
            for (i = 0; i < oldSize; ++i) {
                this->V[i] = oldV[i];
            }
            delete oldV;
        }
    }

public:
    HugeInt() {
        this->V = NULL;
        *this = 0;
    }

    HugeInt(const long long& arg) {
        this->V = NULL;
        *this = arg;
    }

    HugeInt(const HugeInt& arg) {
        this->V = NULL;
        this->alloc(arg.size + 1);
        this->size = arg.size;
        this->sign = arg.sign;
        memcpy(this->V, arg.V, sizeof(int) * (this->size + 1));
    }

    HugeInt& operator =(const long long& arg) {
        this->alloc(3);
        this->V[0] = this->size = 0;
        long long myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            this->sign = -1;
        } else {
            this->sign = 1;
        }
        while (myArg > 0) {
            this->V[this->size++] = (int)(myArg % BASE);
            myArg /= BASE;
        }
        if (this->size > 0) {
            --this->size;
        }
        return *this;
    }

    HugeInt& operator =(const HugeInt& arg) {
        this->alloc(arg.size + 1);
        this->size = arg.size;
        this->sign = arg.sign;
        memcpy(this->V, arg.V, sizeof(int) * (this->size + 1));
        return *this;
    }

    /*returneaza 1 daca A>B
                 0 daca A=B
                -1 daca A<B
    */
    static int compare(const HugeInt &arg1, const HugeInt &arg2) {
        if (arg1.sign != arg2.sign) {
            if (arg1.sign==1) return 1;
            else return -1;
        } else {
            if (arg1.size > arg2.size) {
                if (arg1.sign == 1) return 1;
                else return -1;
            } else if (arg1.size < arg2.size) {
                if (arg1.sign == 1) return -1;
                else return 1;
            } else {
                int i;
                for (i = arg1.size; arg1.V[i] == arg2.V[i] && i >= 0; --i);
                if (i >= 0) {
                    if (arg1.V[i] > arg2.V[i]) {
                        if (arg1.sign == 1) return 1;
                        else return -1;
                    } else {
                        if (arg1.sign == 1) return -1;
                        else return 1;
                    }
                } else {
                    return 0;
                }
            }
        }
    }

    bool operator <(const HugeInt& arg) const {
        return compare(*this, arg) < 0;
    }

    friend bool operator <(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 < arg2;
    }

    bool operator >(const HugeInt& arg) const {
        return compare(*this, arg) > 0;
    }

    friend bool operator >(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 > arg2;
    }

    bool operator <=(const HugeInt& arg) const {
        return compare(*this, arg) <= 0;
    }

    friend bool operator <=(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 <= arg2;
    }

    bool operator >=(const HugeInt& arg) const {
        return compare(*this, arg) >= 0;
    }

    friend bool operator >=(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 >= arg2;
    }

    bool operator ==(const HugeInt& arg) const {
        return compare(*this, arg) == 0;
    }

    friend bool operator ==(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 == arg2;
    }

    bool operator !=(const HugeInt& arg) const {
        return compare(*this, arg) != 0;
    }

    friend bool operator !=(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 != arg2;
    }

    const HugeInt& operator +() const {
        return *this;
    }

    HugeInt operator -() const {
        HugeInt answer = *this;
        answer.sign = -answer.sign;
        return answer;
    }

    HugeInt operator +(const HugeInt& arg) const {
        if (this->sign == -1 && arg.sign == -1) {
            return this->unsignedAddition(arg, -1);
        } else if (this->sign == -1 && arg.sign == 1) {
            if (-*this > arg) {
                return this->unsignedSubtraction(arg, -1);
            } else {
                return arg.unsignedSubtraction(*this, 1);
            }
        } else if (this->sign == 1 && arg.sign == -1) {
            if (*this >= -arg) {
                return this->unsignedSubtraction(arg, 1);
            } else {
                return arg.unsignedSubtraction(*this, -1);
            }
        } else { // if (this->sign == 1 && arg.sign == 1) {
            return this->unsignedAddition(arg, 1);
        }
    }

    friend HugeInt operator +(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 + arg2;
    }

    HugeInt operator -(const HugeInt& arg) const {
        if (this->sign == -1 && arg.sign == -1) {
            if (*this >= arg) { // |this| < |B|
                return arg.unsignedSubtraction(*this, 1);
            } else {
                return this->unsignedSubtraction(arg, -1);
            }
        } else if (this->sign == -1 && arg.sign ==  1) {
            return this->unsignedAddition(arg, -1);
        } else if (this->sign ==  1 && arg.sign == -1) {
            return this->unsignedAddition(arg, 1);
        } else { // if (this->sign ==  1 && arg.sign ==  1) {
            if (*this >= arg) {
                return this->unsignedSubtraction(arg, 1);
            } else {
                return arg.unsignedSubtraction(*this, -1);
            }
        }
    }

    friend HugeInt operator -(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 - arg2;
    }

    HugeInt& operator ++() { // prefix ++
        int i;
        if (this->sign == 1) {
            ++this->V[0];
            for (i = 0; this->V[i] == BASE; ++i) {
                this->V[i] = 0;
                ++this->V[i + 1];
            }
            if (this->size < i) {
                this->size = i;
            }
        } else {
            --this->V[0];
            for (i = 0; this->V[i] == -1; ++i) {
                this->V[i] += BASE;
                --this->V[i + 1];
            }
            if (this->V[this->size] == 0) {
                --this->size;
            }
            if (this->size == -1) {
                this->sign = 1;
                this->size = 0;
            }
        }
        return *this;
    }

    HugeInt operator ++(int) { // postfix ++
        HugeInt answer = *this;
        ++(*this);
        return answer;
    }

    HugeInt& operator --() { // prefix --
        int i;
        if (this->sign == -1) {
            ++this->V[0];
            for (i = 0; this->V[i] == BASE; ++i) {
                this->V[i] = 0;
                ++this->V[i + 1];
            }
            if (this->size < i) {
                this->size = i;
            }
        } else {
            if (this->size == 0 && this->V[0] == 0) {
                this->sign = -1;
                this->V[0] = 1;
            } else {
                --this->V[0];
                for (i = 0; this->V[i] == -1; ++i) {
                    this->V[i] += BASE;
                    --this->V[i + 1];
                }
                if (this->V[this->size] == 0) {
                    --this->size;
                }
                if (this->size == -1) {
                    this->size = 0;
                }
            }
        }
        return *this;
    }

    HugeInt operator --(int) { // postfix --
        HugeInt answer = *this;
        --(*this);
        return answer;
    }

    HugeInt operator *(const HugeInt& arg) const {
        if (arg == 0 || *this == 0) {
            return 0;
        }
        HugeInt answer;
        answer.alloc(this->size + arg.size + 4);
        answer.sign = this->sign * arg.sign;
        HugeInt Tmp;
        int i, j;
        for (i = 0; i <= this->size + arg.size + 1; ++i) {
            answer.V[i] = 0;
        }
        for (i = 0; i <= arg.size; ++i) {
            Tmp = this->digitMultiplication(arg.V[i]);
            for(j = 0; j <= Tmp.size; ++j) {
                answer.V[i + j] += Tmp.V[j];
                answer.size = i + j;
                if (answer.V[i + j] >= BASE) {
                    answer.V[i + j] -= BASE;
                    ++answer.V[i + j + 1];
                    answer.size = i + j + 1;
                }
            }
        }
        return answer;
    }

    HugeInt operator *(const int& arg) const {
        if (0 <= arg && arg < BASE) {
            return this->digitMultiplication(arg);
        } else {
            return this->operator *((HugeInt)arg);
        }
    }

    friend HugeInt operator *(const long long& arg1, const HugeInt& arg2) {
        return arg2 * (HugeInt)arg1;
    }

    HugeInt operator /(const HugeInt& arg) const {
        if (arg.size == 0 && this->sign == 1 && arg.sign == 1) {
            return this->digitDivision(arg.V[0]);
        }
        int nrCifre = (this->size + 1) - (arg.size + 1);
        if (nrCifre <= 0) {
            nrCifre = 1;
        }

        int i;
        HugeInt answer;
        answer.alloc(nrCifre + 2);
        HugeInt tmp;
        HugeInt thisAbs = this->abs();
        HugeInt argAbs = arg.abs();
        int start, med, stop;

        for (i = nrCifre; i >= 0; --i) {
            start = 0;
            stop = BASE - 1;
            while (start < stop) {
                med = (start + stop) / 2 + 1;
                tmp = (med * argAbs).baseMultiplication(i);
                if (tmp <= thisAbs) {
                    start = med;
                } else {
                    stop = med - 1;
                }
            }
            answer.V[i] = start;
            thisAbs -= (start * argAbs).baseMultiplication(i);
        }
        for (answer.size = nrCifre; answer.size > 0 && answer.V[answer.size] == 0; --answer.size);

        answer.sign = this->sign * arg.sign;
        if (answer.size == 0 && answer.V[0] == 0) {
            answer.sign = 1;
        }
        return answer;
    }

    friend HugeInt operator /(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 / arg2;
    }

    HugeInt operator %(const HugeInt& arg) const {
        if (arg.size == 0 && this->sign == 1 && arg.sign == 1) {
            return this->digitRemainder(arg.V[0]);
        }
        return *this - (*this / arg) * arg;
    }

    friend HugeInt operator %(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 % arg2;
    }

    HugeInt& operator +=(const HugeInt& arg) {
        *this = *this + arg;
        return *this;
    }

    HugeInt& operator -=(const HugeInt& arg) {
        *this = *this - arg;
        return *this;
    }

    HugeInt& operator *=(const HugeInt& arg) {
        *this = *this * arg;
        return *this;
    }

    HugeInt& operator /=(const HugeInt& arg) {
        *this = *this / arg;
        return *this;
    }

    HugeInt& operator %=(const HugeInt& arg) {
        *this = *this % arg;
        return *this;
    }

    HugeInt abs() const {
        HugeInt answer = *this;
        answer.sign = 1;
        return answer;
    }

    HugeInt pow(unsigned int exp) const {
        HugeInt answer = 1;
        HugeInt power = *this;
        for(; exp > 0; exp >>= 1) {
            if ((exp & 1) > 0) {
                answer *= power;
            }
            if (exp > 1) {
                power *= power;
            }
        }
        return answer;
    }

    HugeInt root(const unsigned int& deg) const {
        HugeInt start, stop;
        int nrCifre = ((this->size + 1) - 1) / deg + 1;
        start.alloc(nrCifre + 2);
        stop.alloc(nrCifre + 2);
        start.size = nrCifre - 1;
        stop.size = nrCifre - 1;
        int i;
        for (i = 0; i < nrCifre; ++i) {
            start.V[i] = 0;
            stop.V[i] = BASE - 1;
        }
        start.V[start.size] = 1;

        HugeInt med;
        while (start < stop) {
            med = (start + stop) / 2 + 1;
            if (med.pow(deg) <= *this) {
                start = med;
            } else {
                stop = med - 1;
            }
        }

        start.sign = this->sign;
        return start;
    }

    unsigned long long getllu() const {
        unsigned long long answer = 0;
        int i;
        for (i = this->size; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
        }
        return answer;
    }

    long long getlld() const {
        long long answer = 0;
        int i;
        for (i = this->size; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
        }
        if (this->sign == -1) {
            answer = -answer;
        }
        return answer;
    }

    unsigned int getu() const {
        return this->getllu();
    }

    int getd() const {
        return this->getlld();
    }

    void afisare(FILE* output) const {
        int i;
        if (this->sign == -1) fprintf(output, "-");
        fprintf(output, "%d", this->V[this->size]);
        for(i = this->size - 1; i >= 0; --i) {
            fprintf(output, PRINT_FORMAT, this->V[i]);
        }
    }

    void afisare() const {
        afisare(stdout);
    }

    void citire(FILE *input) {
        int allocated = 4;
        this->alloc(allocated + 2);
        int Nr0;
        char Nr[1000];
        int stop;
        int i, j;
        int tmp, tmpc;
        fscanf(input, "%s", Nr);
        Nr0 = strlen(Nr);
        if (Nr[0] == '-') {
            stop = 1;
            this->sign = -1;
        } else {
            stop = 0;
            this->sign = 1;
        }
        this->V[this->size = 0] = 0;
        for(i = Nr0 - 1; i >= stop; ) {
            tmp = 0;
            tmpc = 0;
            for(j = 1; j <= SCAN_POWER && i >= stop; ++j) {
                tmp *= 10;
                tmp += Nr[i] - '0';
                --i;
                ++tmpc;
            }
            for(j = 1; j <= tmpc; ++j) {
                this->V[this->size] *= 10;
                this->V[this->size] += tmp % 10;
                tmp /= 10;
            }
            this->V[++this->size] = 0;
            if (this->size == allocated) {
                allocated *= 2;
                this->realloc(allocated / 2 + 2, allocated + 2);
            }
        }
        if (this->V[this->size] == 0) {
            --this->size;
        }
        if (this->size == 0 && this->V[0] == 0 && this->sign == -1) this->sign = 0;
    }

    void citire() {
        citire(stdin);
    }

    ~HugeInt() {
        if (this->V != NULL) {
            delete this->V;
        }
    }
};

const int HugeInt::BASE = 1000000000;
const int HugeInt::SCAN_POWER = 9;
const char* HugeInt::PRINT_FORMAT = "%.9d";


template<int DECIMALS>
class HugeDecimal {
private:
    static const int BASE;
    static const int SCAN_POWER;
    static const char* PRINT_FORMAT;
    static const char* ZERO_PRINT_FORMAT;

    HugeInt value;
public:
    HugeDecimal(const int &value = 0) {
        this->value = value;
        this->value = this->value.baseMultiplication(DECIMALS);
    }

    HugeDecimal(const HugeInt &value) {
        this->value = value;
        this->value = this->value.baseMultiplication(DECIMALS);
    }

    HugeDecimal operator + (const HugeDecimal& arg) const {
        HugeDecimal answer;
        answer.value = this->value + arg.value;
        return answer;
    }

    HugeDecimal operator - () const {
        HugeDecimal answer;
        answer.value = -this->value;
        return answer;
    }

    HugeDecimal operator - (const HugeDecimal& arg) const {
        HugeDecimal answer;
        answer.value = this->value - arg.value;
        return answer;
    }

    HugeDecimal operator * (const HugeDecimal& arg) const {
        HugeDecimal answer;
        answer.value = (this->value * arg.value).baseMultiplication(-DECIMALS);
        return answer;
    }

    HugeDecimal operator / (const HugeDecimal& arg) const {
        HugeDecimal answer;
        answer.value = (this->value.baseMultiplication(DECIMALS)) / arg.value;
        return answer;
    }

    HugeDecimal& operator += (const HugeDecimal& arg) {
        this->value += arg.value;
        return *this;
    }

    HugeDecimal& operator -= (const HugeDecimal& arg) {
        this->value -= arg.value;
        return *this;
    }

    HugeDecimal& operator *= (const int& arg) {
        this->value = this->value * arg;
        return *this;
    }

    HugeDecimal& operator *= (const HugeDecimal& arg) {
        this->value = (this->value * arg.value).baseMultiplication(-DECIMALS);
        return *this;
    }

    HugeDecimal& operator *= (const HugeInt& arg) {
        this->value = (this->value * arg);
        return *this;
    }

    HugeDecimal& operator /= (const int& arg) {
        this->value = this->value / arg;
        return *this;
    }

    HugeDecimal& operator /= (const HugeDecimal& arg) {
        this->value = (this->value.baseMultiplication(DECIMALS)) / arg.value;
        return *this;
    }

    HugeDecimal& operator /= (const HugeInt& arg) {
        this->value = (this->value / arg);
        return *this;
    }

    bool operator != (const HugeDecimal& arg) const {
        return this->value != arg.value;
    }

    bool operator == (const HugeDecimal& arg) const {
        return this->value == arg.value;
    }

    bool operator < (const HugeDecimal& arg) const {
        return this->value < arg.value;
    }

    bool operator <= (const HugeDecimal& arg) const {
        return this->value <= arg.value;
    }

    bool operator > (const HugeDecimal& arg) const {
        return this->value > arg.value;
    }

    bool operator >= (const HugeDecimal& arg) const {
        return this->value >= arg.value;
    }

    HugeDecimal root(const unsigned int& deg) const {
        HugeDecimal answer;
        answer.value = (this->value).baseMultiplication(DECIMALS * (deg - 1)).root(deg);
        return answer;
    }

    void afisare(FILE* output) const {
        int i;
        if (this->value.sign == -1) fprintf(output, "-");
        if (this->value.size >= DECIMALS) {
            fprintf(output, "%d", this->value.V[this->value.size]);
            for(i = this->value.size - 1; i >= 0; --i) {
                if (i + 1 == DECIMALS) {
                    fprintf(output, ".");
                }
                fprintf(output, HugeDecimal::PRINT_FORMAT, this->value.V[i]);
            }
        } else {
            fprintf(output, "0.");
            for(i = DECIMALS - 1; i >= this->value.size; --i) {
                fprintf(output, HugeDecimal::ZERO_PRINT_FORMAT, this->value.V[this->value.size]);
            }
            for(i = this->value.size - 1; i >= 0; --i) {
                fprintf(output, HugeDecimal::PRINT_FORMAT, this->value.V[i]);
            }
        }
    }

    void afisare() const {
        afisare(stdout);
    }
};

template<int DECIMALS>
const int HugeDecimal<DECIMALS>::BASE = 1000000000;
template<int DECIMALS>
const int HugeDecimal<DECIMALS>::SCAN_POWER = 9;
template<int DECIMALS>
const char* HugeDecimal<DECIMALS>::ZERO_PRINT_FORMAT = "%.09d";
template<int DECIMALS>
const char* HugeDecimal<DECIMALS>::PRINT_FORMAT = "%.9d";

template<int DECIMALS>
HugeDecimal<DECIMALS> sqrt(HugeDecimal<DECIMALS> arg) {
    return arg.root(2);
}



HugeInt fct(const HugeInt nr) {
    int C;
    int k;
    HugeInt tmp;
    HugeInt F;
    for (tmp = nr, C = 0; tmp > 0; tmp /= 10, ++C);
    for (tmp = 1, k = 0; k < C - 1; tmp *= 10, ++k);
    F = (nr - tmp + 1) * C + tmp * (C - 1);
    for (tmp /= 10; tmp > 0; tmp /= 10) {
        F -= tmp;
    }
    return F;
}

#include <ctime>
#include <assert.h>

// Program scris special pentru depanarea functiilor.
int main(void) {
    long long lA, lB = -456, lC = 123, lD;
    HugeInt hA, hB = -456, hC = 123, hD;
    lA = -7891234567890LL;
    hA = -7891234567890LL;
    lD = 9432932474329LL;
    hD = 9432932474329LL;

    assert(hA == lA);
    assert(hB == lB);
    assert(hC == lC);
    assert(hD == lD);

    assert(lA == hA);
    assert(lB == hB);
    assert(lC == hC);
    assert(lD == hD);

    assert(hA <= lA);
    assert(hB <= lB);
    assert(hC <= lC);
    assert(hD <= lD);

    assert(lA >= hA);
    assert(lB >= hB);
    assert(lC >= hC);
    assert(lD >= hD);

    assert(lA != lB && lB != lC && lC != lD);
    assert(hA != hB && hB != hC && hC != hD);
    assert(hA != lB && hB != lC && hC != lD);
    assert(lA != hB && lB != hC && lC != hD);

    assert(lA < lB && lB < lC && lC < lD);
    assert(hA < hB && hB < hC && hC < hD);
    assert(hA < lB && hB < lC && hC < lD);
    assert(lA < hB && lB < hC && lC < hD);

    assert(!(lB < lA) && !(lC < lB) && !(lD < lC));
    assert(!(hB < hA) && !(hC < hB) && !(hD < hC));
    assert(!(hB < lA) && !(hC < lB) && !(hD < lC));
    assert(!(lB < hA) && !(lC < hB) && !(lD < hC));

    assert(lD > lC && lC > lB && lB > lA);
    assert(hD > hC && hC > hB && hB > hA);
    assert(hD > lC && hC > lB && hB > lA);
    assert(lD > hC && lC > hB && lB > hA);

    assert(!(lC > lD) && !(lB > lC) && !(lA > lB));
    assert(!(hC > hD) && !(hB > hC) && !(hA > hB));
    assert(!(hC > lD) && !(hB > lC) && !(hA > lB));
    assert(!(lC > hD) && !(lB > hC) && !(lA > hB));

    assert(lA <= lB && lB <= lC && lC <= lD);
    assert(hA <= hB && hB <= hC && hC <= hD);
    assert(hA <= lB && hB <= lC && hC <= lD);
    assert(lA <= hB && lB <= hC && lC <= hD);

    assert(!(lB <= lA) && !(lC <= lB) && !(lD <= lC));
    assert(!(hB <= hA) && !(hC <= hB) && !(hD <= hC));
    assert(!(hB <= lA) && !(hC <= lB) && !(hD <= lC));
    assert(!(lB <= hA) && !(lC <= hB) && !(lD <= hC));

    assert(lD >= lC && lC >= lB && lB >= lA);
    assert(hD >= hC && hC >= hB && hB >= hA);
    assert(hD >= lC && hC >= lB && hB >= lA);
    assert(lD >= hC && lC >= hB && lB >= hA);

    assert(!(lC >= lD) && !(lB >= lC) && !(lA >= lB));
    assert(!(hC >= hD) && !(hB >= hC) && !(hA >= hB));
    assert(!(hC >= lD) && !(hB >= lC) && !(hA >= lB));
    assert(!(lC >= hD) && !(lB >= hC) && !(lA >= hB));

    assert(lA + lB == lA + hB);
    assert(lA + lB == hA + lB);
    assert(lA + lB == hA + hB);
    assert(lA + lB == lB + hA);
    assert(lA + lB == hB + lA);
    assert(lA + lB == hB + hA);

    assert(lA - lB == lA - hB);
    assert(lA - lB == hA - lB);
    assert(lA - lB == hA - hB);
    assert(lB - lA == lB - hA);
    assert(lB - lA == hB - lA);
    assert(lB - lA == hB - hA);

    assert(lC - lB == lC - hB);
    assert(lC - lB == hC - lB);
    assert(lC - lB == hC - hB);
    assert(lB - lC == lB - hC);
    assert(lB - lC == hB - lC);
    assert(lB - lC == hB - hC);

    assert(lC - lD == lC - hD);
    assert(lC - lD == hC - lD);
    assert(lC - lD == hC - hD);
    assert(lD - lC == lD - hC);
    assert(lD - lC == hD - lC);
    assert(lD - lC == hD - hC);

    lA = +lB;
    hA = +hB;
    assert(lA == lB);
    assert(hA == hB);

    for (lA = -100; lA < 100; ++lA) {
        for (lB = -100; lB < 100; ++lB) {
            lC = lA + lB;
            hA = lA;
            hB = lB;
            hC = hA + hB;
            assert(hC == lC);
        }
    }
    //*
    for (lA = -100, hA = -100; lA <= 100; ++lA, ++hA) {
        assert(hA == lA);
        assert(hA <= 100);
        for (lB = -100, hB = -100; lB <= 100; ++lB, ++hB) {
            assert(hB == lB);
            assert(hB <= 100);
            printf("%lld %lld\n", lA, lB);
            fflush(stdout);

            lC = lA + lB;
            hC = hA + hB;
            assert(hC == lC);
            assert(hA + hB == lA + lB);
            assert(hA + lB == lA + lB);
            assert(lA + hB == lA + lB);

            lC = lA * lB;
            hC = hA * hB;
            assert(hC == lC);
            assert(hA * hB == lA * lB);
            assert(hA * lB == lA * lB);
            assert(lA * hB == lA * lB);

            if (lA != 0) {
                lD = lC / lA;
                hD = hC / hA;
                assert(hD == lD);
                assert(hC / hA == lC / lA);
                assert(hC / lA == lC / lA);
                assert(lC / hA == lC / lA);
            }
            if (lB != 0) {
                lD = lC / lB;
                hD = hC / hB;
                assert(hD == lD);
                assert(hC / hB == lC / lB);
                assert(hC / lB == lC / lB);
                assert(lC / hB == lC / lB);
            }
        }
    }//*/
    printf("Division:\n");
    fflush(stdout);


    HugeInt hhA, hhB, hhC, hhD;
    hhA = 10;
    hhB = hhA.pow(30000);
    hhA = 10;
    hhC = hhA.pow(10000);
    hhA = 10;
    hhA = hhA.pow(20000);

    clock_t begin = clock();
    hhD = hhB / hhC;
    clock_t end = clock();
    double elapsed_secs = double(end - begin) / CLOCKS_PER_SEC;
    printf("Time: %lf\n", elapsed_secs);

    assert(hhA == hhD);


    printf("Success!"); fflush(stdout);
    return 0;
}
