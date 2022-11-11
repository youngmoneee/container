#include <vector>
#include "../map.hpp"
#include "iostream"

//using namespace std;

int main() {
	ft::map<std::string, int> name;
	ft::map<std::string, int>::iterator it = name.begin();
	name["hi"] = 1;
	name["hihi"] = 2;
	for (; it != name.end(); ++it) std::cout << it->second << std::endl;
	//vector<int> a = {1, 2, 3, 4, 5};
	//vector<char> b = {'a', 'b', 'c', 'd', 'e'};

	//a.erase(a.begin() + 2, b.end());
	return 0;
}
