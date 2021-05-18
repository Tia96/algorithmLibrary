#include <iostream>
#include <algorithm>

const int infi = (int)1e+9 + 7;

int n;
double k;
int stock[100005];

int main() {
	std::cin >> n >> k >> stock[0] >> stock[1];

	for (int i = 0; i < n; ++i) {
		stock[i + 2] = k * stock[i + 1] + (1 - k) * stock[i];
	}

	int ans = -infi;
	for (int i = 2; i < n + 2; ++i) {
		ans = std::max(ans, stock[i]);
	}

	std::cout << ans << std::endl;

	return 0;
}