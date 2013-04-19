template<class T>
class QueueStack {
private:
    int maxSize;

    int start;
    int stop;

    T* queueStack;

public:
    QueueStack(const unsigned int maxSize) {
        //assert(maxSize > 0);
        this->maxSize = maxSize;

        this->start = 1;
        this->stop = 0;

        this->queueStack = new T[this->maxSize];
    }

    void pushBack(const T &value) {
        ++this->stop;
        this->queueStack[this->stop % this->maxSize] = value;
    }

    void pushFront(const T &value) {
        --this->start;
        if (this->start < 0) {
            this->start += maxSize;
            this->stop += maxSize;
        }
        this->queueStack[this->start % this->maxSize] = value;
    }

    T pop() {
        return this->queueStack[this->start++ % this->maxSize];
    }

    const T peek() const {
        return this->queueStack[this->start % this->maxSize];
    }

    int getSize() const {
        return this->stop - this->start + 1;
    }

    bool isEmpty() const {
        return this->getSize() == 0;
    }
};
