template<class T>
class QueueStack {
private:
    int maxSize;

    int start;
    int stop;

    T* data;

public:
    QueueStack(const unsigned int maxSize) {
        //assert(maxSize > 0);
        this->maxSize = maxSize;

        this->start = 1;
        this->stop = 0;

        this->data = new T[this->maxSize];
    }

    void pushBack(const T &value) {
        ++this->stop;
        this->data[this->stop % this->maxSize] = value;
    }

    void pushFront(const T &value) {
        --this->start;
        if (this->start < 0) {
            this->start += maxSize;
            this->stop += maxSize;
        }
        this->data[this->start % this->maxSize] = value;
    }

    T popBack() {
        return this->data[this->stop-- % this->maxSize];
    }

    T popFront() {
        return this->data[this->start++ % this->maxSize];
    }

    const T peekBack() const {
        return this->data[this->stop % this->maxSize];
    }

    const T peekFront() const {
        return this->data[this->start % this->maxSize];
    }

    int getSize() const {
        return this->stop - this->start + 1;
    }

    bool isEmpty() const {
        return this->getSize() == 0;
    }

    ~QueueStack() {
        delete[] this->data;
    }
};
