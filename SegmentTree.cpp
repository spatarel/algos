#include <cstdio>

class UpdateType {
    long long val;

public:
    UpdateType(const long long arg) {
        this->val = arg;
    }

    UpdateType& operator = (const long long arg) {
        this->val = arg;
        return *this;
    }

    UpdateType& operator += (const UpdateType arg) {
        this->val += arg.val;
        return *this;
    }

    long long get_val() const {
        return this->val;
    }
};

class QueryType {
    long long n;
    long long sum;
    long long fsus;
    long long fjos;
    long long f;

public:
    QueryType(const long long n) {
        this->n    = n;
        this->sum  = 0;
        this->fsus = 0;
        this->fjos = 0;
        this->f    = 0;
    }

    QueryType& operator += (const UpdateType arg) {
        this->sum  += arg.get_val() * this->n;
        this->fsus += arg.get_val() * (this->n * (this->n + 1) / 2);
        this->fjos += arg.get_val() * (this->n * (this->n + 1) / 2);
        this->f    += arg.get_val() * (this->n * (this->n + 1) * (this->n + 2) / 6);

        return *this;
    }

    QueryType operator + (const UpdateType arg) {
        QueryType nod(this->n);

        nod.sum  = this->sum  + arg.get_val() * this->n;
        nod.fsus = this->fsus + arg.get_val() * (this->n * (this->n + 1) / 2);
        nod.fjos = this->fjos + arg.get_val() * (this->n * (this->n + 1) / 2);
        nod.f    = this->f    + arg.get_val() * (this->n * (this->n + 1) * (this->n + 2) / 6);

        return nod;
    }

    QueryType operator * (const QueryType arg) {
        QueryType nod(this->n + arg.n);

        nod.sum  = this->sum + arg.sum;
        nod.fsus = this->fsus + arg.fsus + this->n * arg.sum;
        nod.fjos = this->fjos + arg.fjos + arg.n * this->sum;
        nod.f    = this->f + arg.f + arg.n * this->fsus + this->n * arg.fjos;

        return nod;
    }

    QueryType operator + (const QueryType arg) {
        //assert(this->n == arg.n);

        QueryType nod(this->n);

        nod.sum  = this->sum  + arg.sum;
        nod.fsus = this->fsus + arg.fsus;
        nod.fjos = this->fjos + arg.fjos;
        nod.f    = this->f    + arg.f;

        return nod;
    }

    double get_f() const {
        return (double)this->f / (this->n * (this->n + 1) / 2);
    }
};


template<class UpdateType, class QueryType>
class SegmentTree {
private:
    int x1;
    int x2;
    UpdateType** tree;
    QueryType** comb;
    bool* updated;

    void real_init(int pos, int start, int stop) {
        this->tree[pos] = new UpdateType(0);
        this->comb[pos] = new QueryType(stop - start + 1);
        if (start == stop) {
            return;
        }
        int med = (start + stop) / 2;
        this->real_init(2 * pos, start, med);
        this->real_init(2 * pos + 1, med + 1, stop);
    }

    void real_update_interval(int pos, int start, int stop, int x1, int x2, UpdateType u) {
        if (start == x1 && stop == x2) {
            *this->tree[pos] += u;
            return;
        }
        int med = (start + stop) / 2;
        if (x2 <= med) { // we go only left
            this->real_update_interval(2 * pos, start, med, x1, x2, u);
        } else if (med < x1) { // we go only right
            this->real_update_interval(2 * pos + 1, med + 1, stop, x1, x2, u);
        } else { // we go both ways
            this->real_update_interval(2 * pos, start, med, x1, med, u);
            this->real_update_interval(2 * pos + 1, med + 1, stop, med + 1, x2, u);
        }
        this->updated[pos] = false;
    //    *comb[pos] = (*comb[2 * pos] + *tree[2 * pos]) *
    //            (*comb[2 * pos + 1] + *tree[2 * pos + 1]);
    }

    QueryType real_lazy_query(int pos) {
        if (!this->updated[pos]) {
            this->updated[pos] = true;
            *this->comb[pos] = (this->real_lazy_query(2 * pos) + *this->tree[2 * pos]) *
                    (this->real_lazy_query(2 * pos + 1) + *this->tree[2 * pos + 1]);
        }
        return *this->comb[pos];
    }

    QueryType real_query_interval(int pos, int start, int stop, int x1, int x2) {
        if (start == x1 && stop == x2) {
            return this->real_lazy_query(pos) + *this->tree[pos];
        }
        int med = (start + stop) / 2;
        // ASSERT
        if (x2 <= med) { // we go only left
            return this->real_query_interval(2 * pos, start, med, x1, x2) +
                    *this->tree[pos];
        } else if (med < x1) { // we go only right
            return this->real_query_interval(2 * pos + 1, med + 1, stop, x1, x2) +
                    *this->tree[pos];
        } else { // we go both ways
            return (this->real_query_interval(2 * pos, start, med, x1, med) *
                    this->real_query_interval(2 * pos + 1, med + 1, stop, med + 1, x2)) +
                    *this->tree[pos];
        }
    }

public:
    SegmentTree(int x1, int x2) {
        int i;

        int n;
        int limit = 2;
        for (n = (x2 - x1 + 1) - 1; n > 0; n >>= 1) limit <<= 1;

        this->x1 = x1;
        this->x2 = x2;
        this->tree = new UpdateType*[limit];
        this->comb = new QueryType*[limit];
        this->updated = new bool[limit];

        this->real_init(1, x1, x2);
        for (i = 0; i < limit; ++i) {
            this->updated[i] = true;
        }
    }

    void update_interval(int x1, int x2, UpdateType u) {
        this->real_update_interval(1, this->x1, this->x2, x1, x2, u);
    }

    QueryType query_interval(int x1, int x2) {
        return this->real_query_interval(1, this->x1, this->x2, x1, x2);
    }
};

int main(void) {
    int i;
    char Q[20];
    int A, B, D;

    int N, M;

    // citirea datelor
    scanf("%d %d", &N, &M);
    --N;
    SegmentTree<UpdateType, QueryType> *ST = new SegmentTree<UpdateType, QueryType>(1, N);
    for (i = 0; i < M; ++i) {
        scanf("\n%s", Q);
        if (Q[0] == 'c') {
            scanf("%d %d %d", &A, &B, &D);
            ST->update_interval(A, B - 1, (UpdateType)D);
        } else {
            scanf("%d %d", &A, &B);
            printf("%.8lf\n", ST->query_interval(A, B - 1).get_f());
        }
    }

    return 0;
}

