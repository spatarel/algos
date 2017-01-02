#include <cstdio>

template<int SIZE>
class WriteStream {
private:
    FILE* stream;

    int pos;
    char buffer[SIZE + 15];

public:
    WriteStream(FILE* stream) {
        this->stream = stream;
        this->pos = 0;
    }

    void dump() {
        if (pos > SIZE) {
            fwrite(buffer, sizeof(char), pos, stream);
            pos = 0;
        }
    }

    void writeUnsignedInt(unsigned int value) {
        if (value == 0) {
            buffer[pos] = '0';
            pos++;
        } else {
            int newPos = pos;
            while(value > 0) {
                buffer[newPos] = '0' + (value % 10);
                newPos++;
                value /= 10;
            }
            std::reverse(buffer + pos, buffer + newPos);
            pos = newPos;
        }
        dump();
    }

    void writeChar(char value) {
        buffer[pos] = value;
        pos++;
        dump();
    }

    ~WriteStream() {
        fwrite(buffer, sizeof(char), pos, stream);
    }
};
