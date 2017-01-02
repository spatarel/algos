#include <cstdio>
#include <cctype>

template<int SIZE>
class ReadStream {
private:
  FILE* stream;

  char buffer[SIZE];
  char* begin;
  char* end;

  void readBuffer() {
    this->begin = this->buffer;
    this->end = this->begin + fread(this->buffer, sizeof(char), SIZE, this->stream);
  }

  char currentChar() {
    return *this->begin;
  }

  void advance() {
    this->begin++;
    if (this->begin == this->end)
      this->readBuffer();
  }

public:
  ReadStream(FILE* stream = stdin) {
    this->stream = stream;
    this->begin = NULL;
    this->end = NULL;
    this->readBuffer();
  }

  int nextInt() {
    while (isspace(this->currentChar()))
      this->advance();
    int answer = 0;
    while (isdigit(this->currentChar())) {
      answer *= 10;
      answer += this->currentChar() - '0';
      this->advance();
    }
    return answer;
  }

  char nextChar() {
    char answer = this->currentChar();
    this->advance();
    return answer;
  }
};
