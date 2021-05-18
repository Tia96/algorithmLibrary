#include <iostream>
#include <algorithm>
#include <string>

int n, k, q;
int start, end;
std::string str;

int main() {
	std::cin >> n >> k >> q >> str;
	
	start = 1, end = n;

	for (int i = 0; i < k; ++i) {
		if (str[i] == 'L')end = start, ++start;
		else if (str[i] == 'R')start = end, --end;
	}

	for (int i = 0; i < q; ++i) {
		int x;
		std::cin >> x;
		int ans = start + x - 1;
		while (ans > n)ans -= n;
		while (0 < ans)ans += n;
		std::cout << ans << std::endl;
	}

	return 0;
}