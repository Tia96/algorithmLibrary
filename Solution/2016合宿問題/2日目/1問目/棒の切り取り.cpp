#include <iostream>
#include <algorithm>
#include <vector>

const int maxN = 1001;

int n;
int x[maxN];

int main() {
	std::cin >> n;

	for (int i = 0; i < n; ++i)std::cin >> x[i];

	while (true) {
		int min = 10000;
		std::vector<int>ans;

		for (int i = 0; i < n; ++i) {
			if (x[i] && x[i] < min)min = x[i];
		}

		for (int i = 0; i < n; ++i) {
			if(x[i])x[i] -= min;
			if (x[i])ans.push_back(x[i]);
		}

		if (!ans.size())break;

		for (int i = 0; i < ans.size(); ++i) {
			if(i != ans.size() - 1)std::cout << ans[i] << " ";
			else std::cout << ans[i] << std::endl;
		}
	}

	return 0;
}