#include <iostream>

template<typename T>
class Count {
	public :
	static int created;
	static int alive;

	Count() {
		created++;
		alive++;
	}
	~Count() {
		alive--;
	}
};

template <typename T>
int Count<T>::created(0);
template <typename T>
int Count<T>::alive(0);

class Derived : public Count<Derived> {
	public:
	Derived() {
		std::cout << Count::created << std::endl;
		std::cout << Count::alive << std::endl;
	}
	~Derived() {

	}
};

int main() {
	Derived();
	return 0;
}
