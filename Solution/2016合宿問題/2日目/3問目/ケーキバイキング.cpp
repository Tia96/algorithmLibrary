#include <iostream>
#include <algorithm>

const int maxN = 1001;

int n;
int dp[maxN]; //i番目のケーキまで選ぶとき最大値
int v[maxN];

int main() {
	std::cin >> n;

	for (int i = 0; i < n; ++i)std::cin >> v[i];

	for (int i = 0; i < n; ++i)dp[i] = -1;

	dp[0] = v[0];
	dp[1] = std::max(v[0], v[1]);
	for (int i = 2; i < n; ++i) {
		dp[i] = std::max(dp[i - 1], dp[i - 2] + v[i]);
	}

	std::cout << dp[n - 1] << std::endl;

	return 0;
}