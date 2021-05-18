#include <iostream>
#include <algorithm>

const int infi = (int)1e+9 + 7;

int h, w, n;
int x[101], y[101];

int main() {
	std::cin >> h >> w;

	for (int i = 0; i < h; ++i) {
		for (int j = 0; j < w; ++j) {
			char c;
			std::cin >> c;
			if (c == 'o')x[n] = j, y[n++] = i;
		}
	}

	std::sort(x, x + n);
	std::sort(y, y + n);

	int ans = infi;

	//Columun
	for (int i = 0; i + n - 1 < h; ++i) {
		for (int j = 0; j < w; ++j) {
			int sum = 0;
			for (int k = 0; k < n; ++k) {
				sum += (std::abs(j - x[k]) + std::abs(i + k - y[k]));
			}

			ans = std::min(ans, sum);
		}
	}

	//Row
	for (int i = 0; i < h; ++i) {
		for (int j = 0; j + n - 1 < w; ++j) {
			int sum = 0;
			for (int k = 0; k < n; ++k) {
				sum += (std::abs(j + k - x[k]) + std::abs(i - y[k]));
			}

			ans = std::min(ans, sum);
		}
	}

	std::cout << ans << std::endl;

	return 0;
}