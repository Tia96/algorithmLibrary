#include <iostream>
#include <algorithm>

int h, w, d, n;
int cnt[2005][2005];

int main() {
	std::cin >> h >> w >> d >> n;

	for (int i = 0; i < n; ++i) {
		int x, y;
		std::cin >> y >> x;
		cnt[y][x] = 1;
	}

	for (int i = 0; i <= h; ++i) {
		for (int j = 1; j <= w; ++j) {
			cnt[i][j] += cnt[i][j - 1];
		}
	}

	for (int i = 0; i <= w; ++i) {
		for (int j = 1; j <= h; ++j) {
			cnt[j][i] += cnt[j - 1][i];
		}
	}

	int ans = 0;

	for (int i = 1; i <= h - d + 1; ++i) {
		for (int j = 1; j <= w - d + 1; ++j) {
			int nx = j + d - 1, ny = i + d - 1;
			ans = std::max(ans, cnt[ny][nx] - cnt[ny][j - 1] - cnt[i - 1][nx] + cnt[i - 1][j - 1]);
		}
	}

	std::cout << ans << std::endl;

	return 0;
}