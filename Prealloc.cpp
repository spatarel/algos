template <class Type, int size>
class Prealloc {
private:
	Type data[size];
	Type* addresses[size];
	int available;

public:
	Prealloc() {
		this->available = size;
		int i;
		for (i = 0; i < size; ++i) {
			this->addresses[i] = &this->data[i];
		}
	}

	Type* newType() {
		--this->available;
		return this->addresses[this->available];
	}

	void deleteType(Type* address) {
		this->addresses[this->available] = address;
		++this->available;
	}
};
