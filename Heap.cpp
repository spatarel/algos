template<class T>
class Heap {
private:
    int containerSize;
    T* container;

    static inline void swap(T &a, T &b) {
        T tmp = a;
        a = b;
        b = tmp;
    }

    void rise(int position) {
        while (position > 1 && this->container[position] < this->container[position >> 1]) {
            swap(this->container[position], this->container[position >> 1]);
            position >>= 1;
        }
    }

    void sink() {
        int pos = 1;
        while (((pos << 1) <= this->containerSize && this->container[pos << 1] < this->container[pos]) || (((pos << 1) + 1) <= this->containerSize && this->container[(pos << 1) + 1] < this->container[pos])) {
            if ((pos << 1) + 1 <= this->containerSize && this->container[(pos << 1) + 1] < this->container[pos << 1]) {
                swap(this->container[pos], this->container[(pos << 1) + 1]);
                pos = (pos << 1) + 1;
            } else {
                swap(this->container[pos], this->container[pos << 1]);
                pos = pos << 1;
            }
        }
    }

public:
    Heap(int maximumSize) {
        this->containerSize = 0;
        this->container = new T[maximumSize + 1];
    }

    void add(T newValue) {
        this->container[++this->containerSize] = newValue;
        rise(this->containerSize);
    }

    void removeMinimum() {
        this->container[1] = this->container[this->containerSize--];
        sink();
    }

    T getMinimum() {
        return this->container[1];
    }

    int getSize() {
        return this->containerSize;
    }

    ~Heap() {
        delete this->container;
    }
};
