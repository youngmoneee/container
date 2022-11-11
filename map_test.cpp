#include "map.hpp"
#include <iostream>

using std::cout;
using std::endl;
using namespace ft;

int main() {
	map<std::string, int> mp;

	mp["a"] = 65;
	mp["b"] = 66;

	cout << mp.size() << endl;
	mp.erase("a");
	cout << mp.size() << endl;
	mp.clear();
	cout << mp.size() << endl;
	return 0;
}
