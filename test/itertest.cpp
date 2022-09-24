#include <vector>

using namespace std;

int main() {
	vector<int> a = {1, 2, 3, 4, 5};
	vector<char> b = {'a', 'b', 'c', 'd', 'e'};

	a.erase(a.begin() + 2, b.end());
	return 0;
}
