#include <iostream>
#include <algorithm>

int h, w, d, n;
int pos[2005][2005];
int cnt[2005][2005];

int main() {
	std::cin >> h >> w >> d >> n;

	for (int i = 0; i < n; ++i) {
		int x, y;
		std::cin >> y >> x;
		pos[y][x] = 1;
	}

	for (int i = 1; i <= d; ++i) {
		for (int j = 1; j <= d; ++j) {
			cnt[1][1] += pos[i][j];
		}
	}

	for (int i = 2; i <= w - d + 1; ++i) {
		int diff = 0;

		for (int j = 1; j <= d; ++j) diff -= pos[j][i - 1];
		for (int j = 1; j <= d; ++j) diff += pos[j][i + d - 1];

		cnt[1][i] = cnt[1][i - 1] + diff;
	}

	for (int i = 1; i <= w - d + 1; ++i) {
		for (int j = 2; j <= h - d + 1; ++j) {
			int diff = 0;

			for (int k = 0; k < d; ++k) diff -= pos[j - 1][i + k];
			for (int k = 0; k < d; ++k) diff += pos[j + d - 1][i + k];

			cnt[j][i] = cnt[j - 1][i] + diff;
		}
	}

	int max = 0;

	for (int i = 1; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			max = std::max(max, cnt[i][j]);
		}
	}

	std::cout << max << std::endl;

	return 0;
}