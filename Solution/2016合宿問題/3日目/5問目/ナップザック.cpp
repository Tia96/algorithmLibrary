#include <iostream>
#include <algorithm>
#include <functional>

int n, k;
int v[10001], w[10001];

int main() {
	std::cin >> n >> k;

	for (int i = 0; i < n; ++i) {
		std::cin >> v[i] >> w[i];
	}

	double l = 0, r = 100000000;
	for (int i = 0; i < 100; ++i) {
		double m = (l + r) / 2;

		double p[10001];
		for (int j = 0; j < n; ++j) p[j] = v[j] - m * w[j];

		std::sort(p, p + n, std::greater<double>());

		double sum = 0;
		for (int j = 0; j < k; ++j) sum += p[j];

		if (sum >= 0)l = m;
		else r = m;
	}

	printf("%.7f\n", l);

	return 0;
}