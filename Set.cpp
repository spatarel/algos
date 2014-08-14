#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

template<class T>
class Set {
private:
    unsigned int size;
    T* values;

public:
    Set() {
        this->size = 0;
        this->values = NULL;
    }

    Set(const Set& arg) {
        this->size = arg.size;
        if (this->size == 0) {
            this->values = NULL;
        } else {
            this->values = new int[this->size];
            memcpy(this->values, arg.values, sizeof(int) * this->size);
        }
    }

    Set(const unsigned int& size, const T* values) {
        this->size = size;
        if (this->size == 0) {
            this->values = NULL;
        } else {
            this->values = new T[this->size];
            unsigned int i;
            for (i = 0; i < this->size; ++i) {
                this->values[i] = values[i];
            }
        }
    }

    Set operator = (const Set& arg) {
        delete this->values;

        this->size = arg.size;
        this->values = new int[this->size];
        memcpy(this->values, arg.values, sizeof(int) * this->size);
        return *this;
    }

    Set join(const Set& arg) const {
        unsigned int i, j;

        unsigned int answerSize;
        int* answer = new int[this->size + arg.size];

        answerSize = 0;
        for (i = 0, j = 0; i < this->size && j < arg.size; ) {
            if (this->values[i] < arg.values[j]) {
                answer[answerSize] = this->values[i];
                ++i;
                ++answerSize;
            } else if (this->values[i] > arg.values[j]) {
                answer[answerSize] = arg.values[j];
                ++j;
                ++answerSize;
            } else {
                answer[answerSize] = this->values[i];
                ++i;
                ++j;
                ++answerSize;
            }
        }
        while (i < this->size) {
            answer[answerSize] = this->values[i];
            ++i;
            ++answerSize;
        }
        while (j < arg.size) {
            answer[answerSize] = arg.values[j];
            ++j;
            ++answerSize;
        }
        Set set = Set(answerSize, answer);
        delete answer;
        return set;
    }

    Set intersect(const Set& arg) const {
        unsigned int i, j;

        unsigned int answerSize;
        int* answer = new int[min(this->size, arg.size)];

        answerSize = 0;
        for (i = 0, j = 0; i < this->size && j < arg.size; ) {
            if (this->values[i] < arg.values[j]) {
                ++i;
            } else if (this->values[i] > arg.values[j]) {
                ++j;
            } else {
                answer[answerSize] = this->values[i];
                ++i;
                ++j;
                ++answerSize;
            }
        }
        Set set = Set(answerSize, answer);
        delete answer;
        return set;
    }

    Set subtract(const Set& arg) const {
        unsigned int i, j;

        unsigned int answerSize;
        int* answer = new int[this->size];

        answerSize = 0;
        for (i = 0, j = 0; i < this->size && j < arg.size; ) {
            if (this->values[i] < arg.values[j]) {
                answer[answerSize] = this->values[i];
                ++i;
                ++answerSize;
            } else if (this->values[i] > arg.values[j]) {
                ++j;
            } else {
                ++i;
                ++j;
            }
        }
        while (i < this->size) {
            answer[answerSize] = this->values[i];
            ++i;
            ++answerSize;
        }
        Set set = Set(answerSize, answer);
        delete answer;
        return set;
    }

    int getSize() const {
        return this->size;
    }

    int* getValues() const {
        return this->values;
    }

    bool contains(T arg) const {
        unsigned int i;
        for (i = 0; i < this->size; ++i) { // TODO: replace with binary search
            if (this->values[i] == arg) {
                return true;
            }
        }
        return false;
    }

    ~Set() {
        if (this->values != NULL) {
            delete this->values;
        }
    }
};

Set<int> readSet() {
    int i;
    int size;
    scanf("%d", &size);
    int *values = new int[size];
    for (i = 0; i < size; ++i) {
        scanf("%d", &values[i]);
    }
    Set<int> set = Set<int>(size, values);
    delete values;
    return set;
}
