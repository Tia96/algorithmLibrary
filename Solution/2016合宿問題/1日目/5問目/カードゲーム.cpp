#include <iostream>
#include <algorithm>

int n;
int x[51];

int main() {
	std::cin >> n;

	for (int i = 0; i < n; ++i)std::cin >> x[i];
	
	std::sort(x, x + n);

	int ans = 0;
	for (int i = 0; i < n; ++i) {
		if (x[i] + 1 == x[i + 1])++i;
		++ans;
	}

	std::cout << ans << std::endl;

	return 0;
}