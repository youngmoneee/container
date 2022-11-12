#include "../vector.hpp"
#include <iostream>

int main() {
	
	ft::vector<int> vec(5, 4);
	for (int i = 0; i < 5; i++) vec[i] = i;
	for (int i = 4; i >= 0; i--) std::cout << vec[i] << std::endl;
	return 0;
}
