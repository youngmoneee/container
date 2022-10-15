#include "vector.hpp"
#include <vector>
#include <iostream>

using namespace std;

int main() {
	ft::vector<int> vct(5);
	ft::vector<int> vct2(5);
	const int cut = 3;

	for (unsigned long int i = 0; i < vct.size(); ++i)
		vct[i] = (vct.size() - i) * 7;
	for (int i = 0; i < vct.size(); i++) cout << vct[i] << ' '; cout << endl;

	vct2.insert(vct2.begin(), vct.begin(), vct.begin() + cut);
	vct2.insert(vct2.begin(), vct.begin() + cut, vct.end());
	vct2.insert(vct2.end(), vct.begin(), vct.begin() + cut);

	std::cout << "insert return:" << std::endl;

	std::cout << *vct2.insert(vct2.end(), 42) << std::endl;
	std::cout << *vct2.insert(vct2.begin() + 5, 84) << std::endl;
	std::cout << "----------------------------------------" << std::endl;

	return 0;
}
