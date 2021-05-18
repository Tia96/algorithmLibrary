#include <iostream>
#include <algorithm>
#include <queue>

struct state {
	int num, s1, s2;
	state() :num(0), s1(0), s2(0) {}
};

int a, b, c;
std::queue<state> que;
bool isVisit[1001][1001];

int main() {
	std::cin >> a >> b >> c;

	que.push(state());

	while (!que.empty()) {
		state s = que.front();
		que.pop();

		if (isVisit[s.s1][s.s2])continue;
		isVisit[s.s1][s.s2] = true;

		if (s.s1 == c || s.s2 == c) {
			std::cout << s.num << std::endl;
			return 0;
		}

		++s.num;
		state next = s;
		next.s1 = 0;
		que.push(next);

		next = s;
		next.s1 = a;
		que.push(next);

		next = s;
		next.s2 = 0;
		que.push(next);

		next = s;
		next.s2 = b;
		que.push(next);

		next = s;
		next.s1 = s.s1 - std::min(b - s.s2, s.s1);
		next.s2 = s.s2 + std::min(b - s.s2, s.s1);
		que.push(next);

		next = s;
		next.s1 = s.s1 + std::min(a - s.s1, s.s2);
		next.s2 = s.s2 - std::min(a - s.s1, s.s2);
		que.push(next);
	}

	std::cout << "-1" << std::endl;

	return 0;
}