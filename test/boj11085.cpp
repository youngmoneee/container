#include <algorithm>
#include <iostream>
#include "../vector.hpp"
#include "../pair.hpp"

using namespace std;
using conn = ft::pair<int, ft::pair<int, int>>;

ft::vector<int> parent;
ft::vector<conn> conns;

int find(int node) {
	if (node == parent[node]) return node;
	return parent[node] = find(parent[node]);
}

void merge(int lhs, int rhs) {
	lhs = find(lhs);
	rhs = find(rhs);

	if (lhs > rhs) parent[lhs] = rhs;
	else parent[rhs] = lhs;
}

int main() {
	int n, w, c, v;
	
	cin >> n >> w >> c >> v;
	parent.resize(n);
	conns.resize(w);
	
	for (conn& i : conns) cin >> i.second.first >> i.second.second >> i.first;
	for (int i = 0; i < n; i++) parent[i] = i;

	sort(conns.begin(), conns.end());
	int ret;
	while (find(c) != find(v)) {
		ret = conns.back().first;
		merge(conns.back().second.first, conns.back().second.second);
		conns.pop_back();
	}
	cout << ret << endl;
	return 0;
}
