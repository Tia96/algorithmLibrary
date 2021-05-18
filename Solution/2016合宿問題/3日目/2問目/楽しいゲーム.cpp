#include <iostream>
#include <algorithm>
#include <functional>

const int maxN = 10001;

typedef long long ll;
typedef std::pair<ll, int> P;

int n;
ll a[maxN], b[maxN];
P c[maxN];

int main() {
	std::cin >> n;
	for (int i = 0; i < n; ++i) std::cin >> a[i];
	for (int i = 0; i < n; ++i) std::cin >> b[i];
	for (int i = 0; i < n; ++i) c[i] = P(a[i] + b[i], i);

	std::sort(c, c + n, std::greater<P>());

	ll cost[2], k = 0;
	cost[0] = 0, cost[1] = 0;

	for (int i = 0; i < n; ++i) {
		if (k == 0)cost[0] += a[c[i].second];
		else if (k == 1)cost[1] += b[c[i].second];
		k = 1 - k;
	}

	std::cout << (cost[0] > cost[1] ? "Taro" : (cost[0] < cost[1] ? "Jiro" : "Draw")) << std::endl;

	return 0;
}