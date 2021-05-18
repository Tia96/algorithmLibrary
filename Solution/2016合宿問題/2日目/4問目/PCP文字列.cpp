#include <iostream>
#include <algorithm>
#include <string>

const int maxN = 100005;

int n, k;
std::string s;

int pcp[maxN], cpc[maxN];

bool isStr(int i, std::string str) {
	if (s.substr(i, 3) == str)return true;
	return false;
}

int main() {
	std::cin >> n >> k >> s;
	s = "AA" + s;
	n += 2;
	
	for (int i = 2; i < n; ++i) {
		if (isStr(i - 2, "PCP"))++pcp[i];
	}

	for (int i = 1; i < n;++i) {
		pcp[i] += pcp[i - 1];
	}

	for (int i = 0; i < k; ++i) {
		int a, b;
		std::cin >> a >> b;
		++a, ++b;
		std::cout << pcp[b] - pcp[a - 1] - isStr(a - 1, "PCP") - isStr(a - 2, "PCP") << std::endl;
	}

	return 0;
}