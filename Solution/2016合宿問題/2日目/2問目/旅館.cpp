#include <iostream>
#include <algorithm>
#include <functional>

const int maxN = 100001;

int n, m;
int a[maxN], b[maxN];
bool flg = true;

int main() {
	std::cin >> n >> m;

	for (int i = 0; i < n; ++i)std::cin >> a[i];
	for (int i = 0; i < m; ++i)std::cin >> b[i];

	if (m > n) flg = false;
	else {
		std::sort(a, a + n, std::greater<int>());
		std::sort(b, b + m, std::greater<int>());

		for (int i = 0; i < m; ++i) {
			if (a[i] < b[i])flg = false;
		}
	}

	if (flg)std::cout << "YES" << std::endl;
	else std::cout << "NO" << std::endl;

	return 0;
}