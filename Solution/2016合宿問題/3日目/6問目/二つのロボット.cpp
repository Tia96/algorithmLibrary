#include <iostream>
#include <algorithm>

const int infi = (int)1e+9 + 7;

int m, n;
int a[1005], b[1005];
int dp[1005][1005]; //dp[n][i] := n番目の仕事をした後にどちらかのロボットがi番目にいるときの最小値
					//すべて0-ind

int main() {
	std::cin >> m >> n;
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			dp[i][j] = infi;
		}
	}

	for (int i = 0; i < n; ++i) {
		std::cin >> a[i] >> b[i];
		--a[i], --b[i];
	}

	for (int i = 0; i < m; ++i) dp[0][i] = std::abs(a[0] - b[0]);

	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			dp[i + 1][b[i]] = std::min(dp[i + 1][b[i]], dp[i][j] + std::abs(j - a[i + 1]) + std::abs(a[i + 1] - b[i + 1]));
			dp[i + 1][j] = std::min(dp[i + 1][j], dp[i][j] + std::abs(b[i] - a[i + 1]) + std::abs(a[i + 1] - b[i + 1]));
		}
	}

	std::cout << *std::min_element(dp[n - 1], dp[n - 1] + m) << std::endl;

	return 0;
}