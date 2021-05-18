#include <iostream>
#include <algorithm>

const int maxN = 100005;

int n, k;
int cnt[maxN];

int main() {
	std::cin >> n >> k;
	
	for(int i = 0; i < n; ++i) {
		for (int j = 0; j < k; ++j) {
			int a, b, c, d;
			char ch;
			std::cin >> a >> ch >> b >> c >> ch >> d;
			int s = 60 * a + b, t = 60 * c + d;

			if (60 * 10 <= s && s <= 60 * 13 && 60 * 14 <= t && t <= 60 * 17 && t - s >= 60 * 4)++cnt[j];
		}
	}

	for (int i = 0; i < k; ++i) {
		std::cout << cnt[i] << std::endl;
	}

	return 0;
}