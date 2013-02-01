#include <stdio.h>
#include <string.h>
#include <algorithm>

using namespace std;

class Set {
private:
    int size;
    int *values;

public:
    Set() {
        this->size = 0;
        this->values = NULL;
    }

    Set(const Set& arg) {
        this->size = arg.size;
        this->values = new int[this->size];
        memcpy(this->values, arg.values, sizeof(int) * this->size);
    }

    Set(const int size, const int *values) {
        this->size = size;
        this->values = new int[this->size];
        memcpy(this->values, values, sizeof(int) * this->size);
    }

    Set operator = (const Set& arg) {
        if (this->values != NULL) {
            delete this->values;
        }
        this->size = arg.size;
        this->values = new int[this->size];
        memcpy(this->values, arg.values, sizeof(int) * this->size);
        return *this;
    }

    Set join(const Set& arg) const {
        int i, j;

        int answerSize;
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
        printf("answerSize = %d\n", answerSize);
        Set set = Set(answerSize, answer);
        delete answer;
        return set;
    }

    Set intersect(const Set& arg) const {
        int i, j;

        int answerSize;
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
        int i, j;

        int answerSize;
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

    ~Set() {
        if (this->values != NULL) {
            delete this->values;
        }
    }
};

Set readSet() {
    int i;
    int size;
    scanf("%d", &size);
    int *values = new int[size];
    for (i = 0; i < size; ++i) {
        scanf("%d", &values[i]);
    }
    Set set = Set(size, values);
    delete values;
    return set;
}

