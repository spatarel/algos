#include <cstdio>
#include <cstring>

template<int size = 100>
class HugeInt {
public:
    int Semn;
    int Cont;
    int V[size];

private:
    static const int BASE;
    static const int SCAN_POWER;
    static const char* PRINT_FORMAT;

    HugeInt unsignedAddition(const HugeInt& arg) const {
        HugeInt answer;
        int i;
        int min = this->Cont < arg.Cont ? this->Cont : arg.Cont;
        for (i = 0; i <= min; ++i) {
            answer.V[i] = this->V[i] + arg.V[i];
        }
        for (; i <= this->Cont; ++i) {
            answer.V[i] = this->V[i];
        }
        for (; i <= arg.Cont; ++i) {
            answer.V[i] = arg.V[i];
        }
        answer.V[i] = 0;
        answer.Cont = i - 1;
        for (i = 0; i <= answer.Cont; ++i) {
            if (answer.V[i] >= BASE) {
                answer.V[i] -= BASE;
                ++answer.V[i + 1];
            }
        }
        if (answer.V[i] > 0) {
            ++answer.Cont;
        }
        return answer;
    }

    HugeInt unsignedSubtraction(const HugeInt& arg) const {
        HugeInt answer;
        int i;
        int min = this->Cont < arg.Cont ? this->Cont : arg.Cont;
        for (i = 0; i <= min; ++i) {
            answer.V[i] = this->V[i] - arg.V[i];
        }
        for (; i <= this->Cont; ++i) {
            answer.V[i] = this->V[i];
        }
        for (; i <= arg.Cont; ++i) {
            answer.V[i] = -arg.V[i];
        }
        answer.Cont = i - 1;
        for (i = 0; i <= answer.Cont; ++i) {
            if (answer.V[i] < 0) {
                answer.V[i] += BASE;
                --answer.V[i + 1];
            }
        }
        for (; answer.V[answer.Cont] == 0 && answer.Cont > 0; --answer.Cont);
        return answer;
    }

    HugeInt digitMultiplication(const int& arg) const {
        HugeInt answer;
        int myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            if (this->Semn == -1) answer.Semn = 1;
            else answer.Semn = -1;
        } else {
            answer.Semn = this->Semn;
        }
        int i;
        long long tmp;
        for (i = 0; i <= this->Cont + 1; ++i) {
            answer.V[i] = 0;
        }
        for (i = 0; i <= this->Cont; ++i) {
            tmp = (long long)this->V[i] * myArg + answer.V[i];
            answer.V[i] = (int)(tmp % BASE);
            //A.V[i + 1] = (tmp - A.V[a]) / BASE;
            answer.V[i + 1] = (int)(tmp / BASE);
        }
        if (answer.V[this->Cont + 1]) {
            answer.Cont = this->Cont + 1;
        } else {
            answer.Cont = this->Cont;
        }
        return answer;
    }

    HugeInt baseMultiplication(const unsigned int& arg) const {
        if (this->Cont == 0 && this->V[0] == 0) {
            return *this;
        }
        int i, j;
        HugeInt answer;
        answer.Semn = this->Semn;
        answer.Cont = this->Cont + arg;
        for (i = answer.Cont, j = this->Cont; j >= 0; --i, --j) {
            answer.V[i] = this->V[j];
        }
        for (; i >= 0; --i) {
            answer.V[i] = 0;
        }
        return answer;
    }

    HugeInt digitDivision(const int& arg) const {
        HugeInt answer;
        int myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            if (this->Semn == -1) answer.Semn = 1;
            else answer.Semn = -1;
        } else {
            answer.Semn = this->Semn;
        }
        int i;
        long long tmp1, tmp2;
        tmp1 = this->V[this->Cont];
        for (i = this->Cont; i >= 0; --i) {
            tmp2 = tmp1 % myArg;
            tmp1 -= tmp2;
            answer.V[i] = (int)(tmp1 / myArg);
            if (i) tmp1 = tmp2 * BASE + this->V[i - 1];
        }
        if (answer.V[this->Cont] > 0) {
            answer.Cont = this->Cont;
        } else {
            if (this->Cont > 0) {
                answer.Cont = this->Cont - 1;
            } else {
                answer.Cont = this->Cont;
            }
        }
        return answer;
    }

    int digitRemainder(const int& arg) const {
        long long answer = 0;
        int i;
        for(i = this->Cont; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
            answer %= arg;
        }
        return (int)answer;
    }

public:
    HugeInt() {
        *this = 0;
    }

    HugeInt(const long long& arg) {
        *this = arg;
    }

    HugeInt& operator =(const long long& arg) {
        this->V[0] = this->Cont = 0;
        long long myArg = arg;
        if (myArg < 0) {
            myArg = -myArg;
            this->Semn = -1;
        } else {
            this->Semn = 1;
        }
        while (myArg > 0) {
            this->V[this->Cont++] = (int)(myArg % BASE);
            myArg /= BASE;
        }
        if (this->Cont > 0) {
            --this->Cont;
        }
        return *this;
    }

    HugeInt& operator =(const HugeInt& arg) {
        this->Cont = arg.Cont;
        this->Semn = arg.Semn;
        memcpy(this->V, arg.V, sizeof(int) * (this->Cont + 1));
        return *this;
    }

    /*returneaza 1 daca A>B
                 0 daca A=B
                -1 daca A<B
    */
    static int compare(const HugeInt &arg1, const HugeInt &arg2) {
        if (arg1.Semn != arg2.Semn) {
            if (arg1.Semn==1) return 1;
            else return -1;
        } else {
            if (arg1.Cont > arg2.Cont) {
                if (arg1.Semn == 1) return 1;
                else return -1;
            } else if (arg1.Cont < arg2.Cont) {
                if (arg1.Semn == 1) return -1;
                else return 1;
            } else {
                int i;
                for (i = arg1.Cont; arg1.V[i] == arg2.V[i] && i >= 0; --i);
                if (i >= 0) {
                    if (arg1.V[i] > arg2.V[i]) {
                        if (arg1.Semn == 1) return 1;
                        else return -1;
                    } else {
                        if (arg1.Semn == 1) return -1;
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
        answer.Semn = -answer.Semn;
        return answer;
    }

    HugeInt operator +(const HugeInt& arg) const {
        HugeInt answer;
        if (this->Semn == -1 && arg.Semn== -1) {
            answer = this->unsignedAddition(arg);
            answer.Semn = -1;
        } else if (this->Semn == -1 && arg.Semn == 1) {
            if (-*this > arg) {
                answer = this->unsignedSubtraction(arg);
                answer.Semn = -1;
            } else {
                answer = arg.unsignedSubtraction(*this);
                answer.Semn = 1;
            }
        } else if (this->Semn == 1 && arg.Semn == -1) {
            if (*this >= -arg) {
                answer = this->unsignedSubtraction(arg);
                answer.Semn = 1;
            } else {
                answer = arg.unsignedSubtraction(*this);
                answer.Semn = -1;
            }
        } else if (this->Semn ==  1 && arg.Semn==  1) {
            answer = this->unsignedAddition(arg);
            answer.Semn = 1;
        }
        return answer;
    }

    friend HugeInt operator +(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 + arg2;
    }

    HugeInt operator -(const HugeInt& arg) const {
        HugeInt answer;
        if (this->Semn == -1 && arg.Semn == -1) {
            if (*this >= arg) { // |this| < |B|
                answer = arg.unsignedSubtraction(*this);
                answer.Semn = 1;
            } else {
                answer = this->unsignedSubtraction(arg);
                answer.Semn = -1;
            }
        } else if (this->Semn == -1 && arg.Semn ==  1) {
            answer = this->unsignedAddition(arg);
            answer.Semn = -1;
        } else if (this->Semn ==  1 && arg.Semn == -1) {
            answer = this->unsignedAddition(arg);
            answer.Semn = 1;
        } else if (this->Semn ==  1 && arg.Semn ==  1) {
            if (*this >= arg) {
                answer = this->unsignedSubtraction(arg);
                answer.Semn = 1;
            } else {
                answer = arg.unsignedSubtraction(*this);
                answer.Semn = -1;
            }
        }
        return answer;
    }

    friend HugeInt operator -(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 - arg2;
    }

    HugeInt& operator ++() { // prefix ++
        int i;
        if (this->Semn == 1) {
            ++this->V[0];
            for (i = 0; this->V[i] == BASE; ++i) {
                this->V[i] = 0;
                ++this->V[i + 1];
            }
            if (this->Cont < i) {
                this->Cont = i;
            }
        } else {
            --this->V[0];
            for (i = 0; this->V[i] == -1; ++i) {
                this->V[i] += BASE;
                --this->V[i + 1];
            }
            if (this->V[this->Cont] == 0) {
                --this->Cont;
            }
            if (this->Cont == -1) {
                this->Semn = 1;
                this->Cont = 0;
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
        if (this->Semn == -1) {
            ++this->V[0];
            for (i = 0; this->V[i] == BASE; ++i) {
                this->V[i] = 0;
                ++this->V[i + 1];
            }
            if (this->Cont < i) {
                this->Cont = i;
            }
        } else {
            if (this->Cont == 0 && this->V[0] == 0) {
                this->Semn = -1;
                this->V[0] = 1;
            } else {
                --this->V[0];
                for (i = 0; this->V[i] == -1; ++i) {
                    this->V[i] += BASE;
                    --this->V[i + 1];
                }
                if (this->V[this->Cont] == 0) {
                    --this->Cont;
                }
                if (this->Cont == -1) {
                    this->Cont = 0;
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
        answer.Semn = this->Semn * arg.Semn;
        HugeInt Tmp;
        int i, j;
        for (i = 0; i <= this->Cont + arg.Cont + 1; ++i) {
            answer.V[i] = 0;
        }
        for (i = 0; i <= arg.Cont; ++i) {
            Tmp = this->digitMultiplication(arg.V[i]);
            for(j = 0; j <= Tmp.Cont; ++j) {
                answer.V[i + j] += Tmp.V[j];
                answer.Cont = i + j;
                if (answer.V[i + j] >= BASE) {
                    answer.V[i + j] -= BASE;
                    ++answer.V[i + j + 1];
                    answer.Cont = i + j + 1;
                }
            }
        }
        return answer;
    }

    friend HugeInt operator *(const long long& arg1, const HugeInt& arg2) {
        return arg2 * (const HugeInt)arg1;
    }

    HugeInt operator /(const HugeInt& arg) const {
        if (arg.Cont == 0 && this->Semn == 1 && arg.Semn == 1) {
            return this->digitDivision(arg.V[0]);
        }
        int nrCifre = (this->Cont + 1) - (arg.Cont + 1);
        if (nrCifre <= 0) {
            nrCifre = 1;
        }

        int i;
        HugeInt answer;
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
        for (answer.Cont = nrCifre; answer.Cont > 0 && answer.V[answer.Cont] == 0; --answer.Cont);

        answer.Semn = this->Semn * arg.Semn;
        if (answer.Cont == 0 && answer.V[0] == 0) {
            answer.Semn = 1;
        }
        return answer;
    }

    friend HugeInt operator /(const long long& arg1, const HugeInt& arg2) {
        return (const HugeInt)arg1 / arg2;
    }

    HugeInt operator %(const HugeInt& arg) const {
        if (arg.Cont == 0 && this->Semn == 1 && arg.Semn == 1) {
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
        answer.Semn = 1;
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
        int nrCifre = ((this->Cont + 1) - 1) / deg + 1;
        start.Cont = nrCifre - 1;
        stop.Cont = nrCifre - 1;
        int i;
        for (i = 0; i < nrCifre; ++i) {
            start.V[i] = 0;
            stop.V[i] = BASE - 1;
        }
        start.V[start.Cont] = 1;

        HugeInt med;
        while (start < stop) {
            med = (start + stop) / 2 + 1;
            if (med.pow(deg) <= *this) {
                start = med;
            } else {
                stop = med - 1;
            }
        }

        start.Semn = this->Semn;
        return start;
    }

    unsigned long long getllu() const {
        unsigned long long answer = 0;
        int i;
        for (i = this->Cont; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
        }
        return answer;
    }

    long long getlld() const {
        long long answer = 0;
        int i;
        for (i = this->Cont; i >= 0; --i) {
            answer *= BASE;
            answer += this->V[i];
        }
        if (this->Semn == -1) {
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
        if (this->Semn == -1) fprintf(output, "-");
        fprintf(output, "%d", this->V[this->Cont]);
        for(i = this->Cont - 1; i >= 0; --i) {
            fprintf(output, PRINT_FORMAT, this->V[i]);
        }
    }

    void afisare() const {
        afisare(stdout);
    }

    void citire(FILE *input) {
        int Nr0;
        char Nr[1000];
        int stop;
        int i, j;
        int tmp, tmpc;
        fscanf(input, "%s", Nr);
        Nr0 = strlen(Nr);
        if (Nr[0] == '-') {
            stop = 1;
            this->Semn = -1;
        } else {
            stop = 0;
            this->Semn = 1;
        }
        this->V[this->Cont = 0] = 0;
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
                this->V[this->Cont] *= 10;
                this->V[this->Cont] += tmp % 10;
                tmp /= 10;
            }
            this->V[++this->Cont] = 0;
        }
        if (this->V[this->Cont] == 0) {
            --this->Cont;
        }
        if (this->Cont == 0 && this->V[0] == 0 && this->Semn == -1) this->Semn = 0;
    }

    void citire() {
        citire(stdin);
    }
};

template<int size>
const int HugeInt<size>::BASE = 1000000000;
template<int size>
const int HugeInt<size>::SCAN_POWER = 9;
template<int size>
const char* HugeInt<size>::PRINT_FORMAT = "%.9d";



HugeInt<> fct(const HugeInt<> nr) {
    int C;
    int k;
    HugeInt<> tmp;
    HugeInt<> F;
    for (tmp = nr, C = 0; tmp > 0; tmp /= 10, ++C);
    for (tmp = 1, k = 0; k < C - 1; tmp *= 10, ++k);
    F = (nr - tmp + 1) * C + tmp * (C - 1);
    for (tmp /= 10; tmp > 0; tmp /= 10) {
        F -= tmp;
    }
    return F;
}

#include <ctime>
#include <cassert>

// Program scris special pentru depanarea functiilor.
int main(void) {
    long long lA, lB = -456, lC = 123, lD;
    HugeInt<> hA, hB = -456, hC = 123, hD;
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
    }
    printf("Division:\n");
    fflush(stdout);


    HugeInt<4000> hhA, hhB, hhC, hhD;
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
