#include <iostream>

using namespace std;

template<typename T> struct is_int { static const bool val = false; };
template<> struct is_int<int> { static const bool val = true; };

template <typename T>
void func(T v) {
	if (is_int<T>::val)
		cout << "int : " << v << endl;
	else
		cout << "temp : " << v << endl;
}

int main() {
	float a = 42.0;

	func((int)a);
	return 0;
}
