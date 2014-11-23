const int MOD = 1000000007;

class UpdateType {
    long long value;

public:
    UpdateType(long long value = 0) {
        this->value = value;
    }

    UpdateType& operator = (long long value) {
        this->value = value;
        return *this;
    }

    UpdateType& operator += (const UpdateType &arg) {
        this->value += arg.value;
        this->value %= MOD;
        return *this;
    }

    operator long long() const {
        return this->value;
    }
};

class QueryType {
    long long length;
	long long value;

public:
    QueryType(long long length, long long value = 0) {
        this->length = length;
    	this->value = value;
    }

    QueryType& operator += (const UpdateType &arg) {
        this->value += arg;
        this->value %= MOD;

        return *this;
    }

    QueryType operator + (const UpdateType &arg) const {
        return QueryType(this->length,
        		(this->value + arg) % MOD);
    }

    QueryType operator * (const QueryType &arg) const {
        return QueryType(this->length + arg.length,
        		(this->value + arg.value) % MOD);
    }

    QueryType operator + (const QueryType &arg) const {
        return QueryType(this->length,
        		(this->value + arg.value) % MOD);
    }

    operator long long() const {
        return this->value;
    }
};


template<class UpdateType = UpdateType, class QueryType = QueryType>
class SegmentTree {
private:
    int x1;
    int x2;
    UpdateType** tree;
    QueryType** comb;
    bool* updated;

    void real_init(int pos, int start, int stop) {
        this->tree[pos] = new UpdateType;
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
        } else {
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
        }
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

    void update_value(int x, UpdateType u) {
    	this->real_update_interval(1, this->x1, this->x2, x, x, u);
    }

    QueryType query_interval(int x1, int x2) {
        return this->real_query_interval(1, this->x1, this->x2, x1, x2);
    }

    QueryType query_value(int x) {
        return this->real_query_interval(1, this->x1, this->x2, x, x);
    }
};
