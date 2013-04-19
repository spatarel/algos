#include <stdio.h>

template<int SIZE>
class ReadStream {
private:
    FILE* stream;

    int pos;
    char buffer[SIZE + 1];

public:
    ReadStream(FILE* stream) {
        this->stream = stream;
        this->pos = SIZE;
    }

    int nextInt() {
        int answer = 0;
        int readSize;

        while (true) {
            if (this->pos == SIZE) {
                readSize = fread(this->buffer, sizeof(char), SIZE, this->stream);
                this->buffer[readSize] = 0;
                this->pos = 0;
            }
            if ('0' <= this->buffer[this->pos] && this->buffer[this->pos] <= '9') {
                break;
            } else {
                ++this->pos;
            }
        }
        while (true) {
            if (this->pos == SIZE) {
                readSize = fread(this->buffer, sizeof(char), SIZE, this->stream);
                this->buffer[readSize] = 0;
                this->pos = 0;
            }
            if (!('0' <= this->buffer[this->pos] && this->buffer[this->pos] <= '9')) {
                break;
            } else {
                answer *= 10;
                answer += this->buffer[this->pos] - '0';
                ++this->pos;
            }
        }

        return answer;
    }
};
