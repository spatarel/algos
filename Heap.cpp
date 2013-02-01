class Heap {
private:
    int Vec0;
    int* Vec;

    inline void swap(int &a, int &b) {
        a ^= b;
        b ^= a;
        a ^= b;
    }

    void rise(int pos) {
        while (pos > 1 && Vec[pos] < Vec[pos>>1]) {
            swap(Vec[pos], Vec[pos>>1]);
            pos>>=1;
        }
    }

    void sink() {
        int pos = 1;
        while ((pos<<1 <= Vec0 && Vec[pos] > Vec[pos<<1]) || ((pos<<1) + 1 <= Vec0 && Vec[pos] > Vec[(pos<<1) + 1])) {
            if ((pos<<1) + 1 <= Vec0 && Vec[(pos<<1) + 1] < Vec[pos<<1]) {
                swap(Vec[pos], Vec[(pos<<1) + 1]);
                pos = (pos<<1) + 1;
            }else{
                swap(Vec[pos], Vec[pos<<1]);
                pos = pos<<1;
            }
        }
    }

public:
    Heap(int size) {
        Vec0 = 0;
        Vec = new int[size + 1];
    }

    void add(int val) {
        Vec[++Vec0] = val;
        rise(Vec0);
    }

    void remove() {
        Vec[1] = Vec[Vec0--];
        sink();
    }

    int getMin() {
        return Vec[1];
    }

    ~Heap() {
        delete Vec;
    }
};

