#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 100001;

int n, m;
int x[maxN];
std::vector<int> g[maxN];
bool isVisit[maxN];

long long dfs(int k) {
	long long max = 0;
	for (int i = 0; i < g[k].size(); ++i) {
		int next = g[k][i];
		if (!isVisit[next]) {
			isVisit[next] = true;
			max = std::max(max, dfs(next));
			isVisit[next] = false;
		}
	}
	return max + x[k];
}

int main() {
	std::cin >> n >> m;

	for (int i = 0; i < n; ++i) {
		std::cin >> x[i];
	}

	for (int i = 0; i < m; ++i) {
		int a, b;
		std::cin >> a >> b;
		--a, --b;
		g[a].push_back(b);
		g[b].push_back(a);
	}

	isVisit[0] = true;
	std::cout << dfs(0) << std::endl;

	return 0;
}