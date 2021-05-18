#include <iostream>
#include <algorithm>
#include <vector>

int main() {
	int n;
	std::cin >> n;
	std::vector<int> vec(n);
	for (auto&& v : vec)
		std::cin >> v;

	std::vector<int> copy = vec;
	std::sort(copy.begin(), copy.end());

	int before = copy.front();
	while (before != copy.back()) {
		for (int i = 0; i < n; ++i)
			if (vec[i] > before)
				std::cout << vec[i] - before << (i + 1 == n ? "" : " ");

		std::cout << std::endl;
		before = *std::upper_bound(copy.begin(), copy.end(), before);
	}
}