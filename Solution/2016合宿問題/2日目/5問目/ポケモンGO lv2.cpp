#include <iostream>
#include <algorithm>

typedef long long ll;

const int maxN = 500001;

int n;
ll ans = 0, sum = 0, k = 0;
int maxStock = 0;
int x[maxN];

int main() {
	std::cin >> n;

	for (int i = 0; i < n; ++i) std::cin >> x[i];

	for (int i = n - 1; i >= 0; --i) {
		if (x[i] > maxStock) {
			ans += maxStock * k - sum;
			sum = 0, k = 0;
			maxStock = x[i];
		}
		else sum += x[i], ++k;
	}
	ans += maxStock * k - sum;

	std::cout << ans << std::endl;

	return 0;
}