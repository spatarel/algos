#include <stdio.h>
#include <string.h>

class HugeInt {
public:
    int Semn;
    int Cont;
    int V[100];

    HugeInt() {
        *this = 0;
    }

    HugeInt& operator =(long long Val) {
        this->V[0] = this->Cont = 0;
        if (Val < 0) {
            Val = -Val;
            this->Semn = -1;
        } else {
            this->Semn = 1;
        }
        for (; Val; ) {
            this->V[this->Cont++] = (int)(Val % 100000000);
            Val -= Val % 100000000;
            Val /= 100000000;
        }
        if (this->Cont) --this->Cont;
        return *this;
    }

    HugeInt& operator =(const HugeInt& B) {
        this->Cont = B.Cont;
        this->Semn = B.Semn;
        memcpy(this->V, B.V, sizeof(int) * (this->Cont + 1));
        return *this;
    }

    /*returneaza 1 daca A>B
                 0 daca A=B
                -1 daca A<B
    */
    int Comparare(const HugeInt &A, const HugeInt &B) const {
        if (A.Semn != B.Semn) {
            if (A.Semn==1) return 1;
            else return -1;
        } else {
            if (A.Cont > B.Cont) {
                if (A.Semn == 1) return 1;
                else return -1;
            } else if (A.Cont < B.Cont) {
                if (A.Semn == 1) return -1;
                else return 1;
            } else {
                int i;
                for (i = A.Cont; A.V[i] == B.V[i] && i >= 0; --i);
                if (i >= 0) {
                    if (A.V[i] > B.V[i]) {
                        if (A.Semn == 1) return 1;
                        else return -1;
                    } else {
                        if (A.Semn == 1) return -1;
                        else return 1;
                    }
                } else {
                    return 0;
                }
            }
        }
    }

    bool operator >(const HugeInt& B) const {
        return Comparare(*this, B) == 1;
    }

    bool operator <(const HugeInt& B) const {
        return Comparare(*this, B) == -1;
    }

    bool operator >=(const HugeInt& B) const {
        return Comparare(*this, B) != -1;
    }

    bool operator <=(const HugeInt& B) const {
        return Comparare(*this, B) != 1;
    }

    bool operator ==(const HugeInt& B) const {
        return Comparare(*this, B) == 0;
    }

    bool operator !=(const HugeInt& B) const {
        return Comparare(*this, B) != 0;
    }

    bool operator >(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) == 1;
    }

    bool operator <(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) == -1;
    }

    bool operator >=(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) != -1;
    }

    bool operator <=(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) != 1;
    }

    bool operator ==(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) == 0;
    }

    bool operator !=(const long long& b) const {
        HugeInt B;
        B = b;
        return Comparare(*this, B) != 0;
    }

    HugeInt operator +() const {
        return *this;
    }

    HugeInt operator -() const {
        HugeInt A = *this;
        A.Semn = -A.Semn;
        return A;
    }

    HugeInt operator -(HugeInt C);
    HugeInt operator +(HugeInt C);

    HugeInt operator -(long long c) {
        HugeInt C;
        C = c;
        return *this - C;
    }

    HugeInt operator +(long long c) {
        HugeInt C;
        C = c;
        return *this + C;
    }

    HugeInt& operator ++() {
        int i;
        if (this->Semn == 1) {
            ++this->V[0];
            for (i = 0; this->V[i] == 100000000; ++i) {
                this->V[i] = 0;
                ++this->V[i + 1];
            }
            if (this->Cont < i) {
                this->Cont = i;
            }
        } else {
            --this->V[0];
            for (i = 0; this->V[i] == -1; ++i) {
                this->V[i] += 100000000;
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

    HugeInt& operator --() {
        int i;
        if (this->Semn == -1) {
            ++this->V[0];
            for (i = 0; this->V[i] == 100000000; ++i) {
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
                    this->V[i] += 100000000;
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

    HugeInt operator *(int Val) const {
        HugeInt A;
        if (Val < 0) {
            Val = -Val;
            if (this->Semn == -1) A.Semn = 1;
            else A.Semn = -1;
        } else {
            A.Semn = this->Semn;
        }
        int i;
        long long tmp;
        for (i = 0; i <= this->Cont + 1; ++i) {
            A.V[i] = 0;
        }
        for (i = 0; i <= this->Cont; ++i) {
            tmp = (long long)this->V[i] * Val + A.V[i];
            A.V[i] = (int)(tmp % 100000000);
            //A.V[i + 1] = (tmp - A.V[a]) / 100000000;
            A.V[i + 1] = (int)(tmp / 100000000);
        }
        if (A.V[this->Cont + 1]) {
            A.Cont = this->Cont + 1;
        } else {
            A.Cont = this->Cont;
        }
        return A;
    }

    HugeInt operator *(const HugeInt& C) const {
        HugeInt A;
        if (this->Semn == 1) {
            A.Semn = C.Semn;
        } else {
            if (C.Semn == -1) A.Semn = 1;
            else A.Semn = -1;
        }
        HugeInt Tmp;
        int i, j;
        for (i = 0; i <= this->Cont + C.Cont + 1; ++i) {
            A.V[i] = 0;
        }
        for (i = 0; i <= C.Cont; ++i) {
            Tmp = (*this) * C.V[i];
            for(j = 0; j <= Tmp.Cont; ++j) {
                A.V[i + j] += Tmp.V[j];
                A.Cont = i + j;
                if (A.V[i + j] >= 100000000) {
                    A.V[i + j] -= 100000000;
                    ++A.V[i + j + 1];
                    A.Cont = i + j + 1;
                }
            }
        }
        return A;
    }

    HugeInt operator /(int Val) const {
        HugeInt A;
        if (Val < 0) {
            Val = -Val;
            if (this->Semn == -1) A.Semn = 1;
            else A.Semn = -1;
        } else {
            A.Semn = this->Semn;
        }
        int i;
        long long tmp1, tmp2;
        tmp1 = this->V[this->Cont];
        for (i = this->Cont; i >= 0; --i) {
            tmp2 = tmp1 % Val;
            tmp1 -= tmp2;
            A.V[i] = (int)(tmp1 / Val);
            if (i) tmp1 = tmp2 * 100000000 + this->V[i - 1];
        }
        if (A.V[this->Cont]) {
            A.Cont = this->Cont;
        } else {
            A.Cont = this->Cont - 1;
        }
        return A;
    }

    int operator %(int Val) const {
        long long tmp = 0;
        int i;
        for(i = this->Cont; i >= 0; --i) {
            tmp *= 100000000;
            tmp += this->V[i];
            tmp %= Val;
        }
        return (int)tmp;
    }

    HugeInt& operator +=(HugeInt B) {
        *this = *this + B;
        return *this;
    }

    HugeInt& operator -=(HugeInt B) {
        *this = *this - B;
        return *this;
    }

    HugeInt& operator +=(long long B) {
        *this = *this + B;
        return *this;
    }

    HugeInt& operator -=(long long B) {
        *this = *this - B;
        return *this;
    }

    HugeInt& operator *=(HugeInt& B) {
        *this = *this * B;
        return *this;
    }

    HugeInt& operator *=(int B) {
        *this = *this * B;
        return *this;
    }

    HugeInt& operator /=(int B) {
        *this = *this / B;
        return *this;
    }

    void afisare(FILE *output) {
        int i;
        if (this->Semn == -1) fprintf(output, "-");
        fprintf(output, "%d", this->V[this->Cont]);
        for(i = this->Cont - 1; i >= 0; --i) {
            fprintf(output, "%.8d", this->V[i]);
        }
    }

    void afisare() {
        afisare(stdout);
    }

    void citire(FILE *input) {
        int  Nr0;
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
            for(j = 1; j <= 8 && i >= stop; ++j) {
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

HugeInt HugeInt::operator +(HugeInt C) {
    HugeInt A;
    if ((this->Semn == -1 && C.Semn== -1) ||
        (this->Semn ==  1 && C.Semn==  1)) {
        A.Semn = this->Semn;
        int i;
        int tmp;
        int MAX = this->Cont + 1;
        if (MAX < C.Cont + 1) {
            MAX = C.Cont + 1;
        }
        for (i = 0; i <= MAX; ++i) {
            A.V[i] = 0;
        }
        for(i = this->Cont + 1; i <= MAX; ++i) {
            this->V[i] = 0;
        }
        for(i = C.Cont + 1; i <= MAX; ++i) {
            C.V[i] = 0;
        }
        for(i = 0; i <= MAX - 1; ++i) {
            tmp = A.V[i] + this->V[i] + C.V[i];
            //A.V[i] = tmp % 100000000;
            //A.V[i + 1] = tmp / 100000000;
            if (tmp < 100000000) {
                A.V[i] = tmp;
            } else {
                A.V[i] = tmp - 100000000;
                A.V[i + 1] = 1;
            }
        }
        if (A.V[MAX]){
            A.Cont = MAX;
        } else {
            A.Cont = MAX - 1;
        }
    } else {
        if (this->Semn == -1) {
            this->Semn =  1;
            A = C - *this;
            this->Semn = -1;
        } else {
            C.Semn =  1;
            A = *this - C;
            C.Semn = -1;
        }
    }
    return A;
}

HugeInt HugeInt::operator -(HugeInt C) {
    HugeInt A;
    if (this->Semn == -1 && C.Semn == -1) {
        this->Semn = 1;
        C.Semn = 1;
        A = C - *this;
        this->Semn = -1;
        C.Semn = -1;
    } else if (this->Semn == -1 && C.Semn ==  1) {
        this->Semn = 1;
        A = *this + C;
        this->Semn = -1;
        A.Semn = -1;
    } else if (this->Semn ==  1 && C.Semn == -1) {
        C.Semn = 1;
        A = *this + C;
        C.Semn = -1;
    } else if (this->Semn ==  1 && C.Semn ==  1) {
        if (*this >= C) {
            A.Semn = 1;
            int i;
            int tmp;
            int MAX = this->Cont + 1;
            if (MAX < C.Cont + 1) {
                MAX = C.Cont + 1;
            }
            for (i = 0; i <= MAX; ++i) {
                A.V[i] = 0;
                if (i > this->Cont) this->V[i] = 0;
                if (i > C.Cont) C.V[i] = 0;
            }
            for (i = 0; i <= MAX - 1; ++i) {
                tmp = A.V[i] + this->V[i] - C.V[i];
                if (tmp >= 0) {
                    A.V[i] = tmp;
                } else {
                    A.V[i] = tmp + 100000000;
                    A.V[i + 1] = -1;
                }
            }
            for (A.Cont = MAX; !A.V[A.Cont] && A.Cont; --A.Cont);
        } else {
            A = C - *this;
            A.Semn = -1;
        }
    }
    return A;
}

HugeInt fct(HugeInt nr) {
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

// Program scris special pentru depanarea functiilor.
int main(void) {
    FILE *e, *ee;
    int r;
    int a, b, c, d;
    HugeInt A, B, C, D, E, F, G, H;
    e = fopen("NrMari.in", "r");
    A.citire(e);
    B.citire(e);
    fclose(e);
    A.afisare(stdout);
    printf("\n");
    B.afisare(stdout);
    printf("\n");
    a = 123456789;
    b = -123456789;
    c = 987654321;
    d = -987654321;
    A = a;
    B = b;
    C = c;
    D = d;
    ee=fopen("NrMari.out","w");
    A.afisare(ee);
    fprintf(ee, "\n");
    B.afisare(ee);
    fprintf(ee, "\n");
    C.afisare(ee);
    fprintf(ee, "\n");
    D.afisare(ee);
    fclose(ee);
    A.afisare(stdout);
    printf("\n");
    B.afisare(stdout);
    printf("\n");
    C.afisare(stdout);
    printf("\n");
    D.afisare(stdout);
    printf("\n");

    E = A + A;
    F = A + B;
    G = A + C;
    H = A + D;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = A - A;
    F = A - B;
    G = A - C;
    H = A - D;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = B + A;
    F = B + B;
    G = B + C;
    H = B + D;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = B - A;
    F = B - B;
    G = B - C;
    H = B - D;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = A * 100;
    F = B * 100;
    G = C * 100;
    H = D * 100;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = A * -100;
    F = B * -100;
    G = C * -100;
    H = D * -100;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = A * A;
    F = B * A;
    G = C * A;
    H = D * A;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    E = A * B;
    F = B * B;
    G = C * B;
    H = D * B;

    E.afisare(stdout);
    printf("\n");
    F.afisare(stdout);
    printf("\n");
    G.afisare(stdout);
    printf("\n");
    H.afisare(stdout);
    printf("\n");

    G.afisare(stdout);
    printf("\n");
    A.afisare(stdout);
    printf("\n");
    G = A;
    G.afisare(stdout);
    printf("\n");
    A.afisare(stdout);
    printf("\n");

    H.afisare(stdout);
    printf("\n");
    G = H / 10;
    r = H % 10;
    G.afisare(stdout);
    printf(" - %d\n", r);
    H = G / 10;
    r = G % 10;
    H.afisare(stdout);
    printf(" - %d\n", r);
    G = H / 10;
    r = H % 10;
    G.afisare(stdout);
    printf(" - %d\n", r);
    H = G / 10;
    r = G % 10;
    H.afisare(stdout);
    printf(" - %d\n", r);

    A = 2;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");

    A = 100000002;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    --A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");
    ++A;
    A.afisare(stdout);
    printf("\n");

    return 0;
}

