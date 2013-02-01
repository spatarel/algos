class DisjointSet {
private:
    int N;
    int* CompCnx;
    int* CompCard;
    int CompNo;

    int getCompCnx(int nod) {
        if (CompCnx[nod] == nod) {
            return nod;
        } else {
            return CompCnx[nod] = getCompCnx(CompCnx[nod]);
        }
    }

    void mergeCompCnx(int compSmall, int compBig) {
        CompCnx[compSmall] = compBig;
        CompCard[compBig] += CompCard[compSmall];
    }

public:
    DisjointSet(int size) {
        int i;
        this->N = size;
        this->CompCnx = new int[this->N];
        this->CompCard = new int[this->N];
        for (i = 0; i < N; ++i) {
            this->CompCnx[i] = i;
            this->CompCard[i] = 1;
        }
        this->CompNo = size;
    }

    bool join(int A, int B) {
        int compA = getCompCnx(A);
        int compB = getCompCnx(B);
        if (compA != compB) {
            if (this->CompCard[compA] < this->CompCard[compB]) {
                mergeCompCnx(compA, compB);
            } else {
                mergeCompCnx(compB, compA);
            }
            --this->CompNo;
            return true;
        } else {
            return false;
        }
    }

    bool isConnected(int A, int B) {
        int compA = getCompCnx(A);
        int compB = getCompCnx(B);
        return compA == compB;
    }

    ~DisjointSet() {
        delete this->CompCnx;
        delete this->CompCard;
    }
};

