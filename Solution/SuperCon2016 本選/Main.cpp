#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <stack>
#include <set>
#include <map>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>
#include <cassert>
#include <sstream>

#define rep(i, a) REP(i, 0, a)
#define REP(i, a, b) for(int i = a; i < b; ++i)
#define rrep(i, a) RREP(i, a, 0)
#define RREP(i, a, b) for(int i = a; i >= b; --i)
#define repll(i, a) REPLL(i, 0, a)
#define REPLL(i, a, b) for(ll i = a; i < b; ++i)
#define rrepll(i, a) RREPLL(i, a, 0)
#define RREPLL(i, a, b) for(ll i = a; i >= b; --i)

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> P;
typedef std::pair<int, P> PP;
const double PI = 3.14159265358979323846;
const double eps = 1e-9;
const int infi = (int)1e+9 + 7;
const ll infll = (ll)1e+17 + 7;

unsigned long seed128[4]; //x,y,z,w‚Æ‚µ‚Ä—˜—p
void seed(unsigned int s) {
	for (int i = 1; i <= 4; i++) {
		seed128[i - 1] = s = 1812433253U * (s ^ (s >> 30)) + i;
	}
}
unsigned long xor128() {
	unsigned long t;
	t = (seed128[0] ^ (seed128[0] << 11));
	seed128[0] = seed128[1];
	seed128[1] = seed128[2];
	seed128[2] = seed128[3];
	return seed128[3] = (seed128[3] ^ (seed128[3] >> 19)) ^ (t ^ (t >> 8));
}

#include <time.h>

const int maxN = 100001;

int n, d;
std::vector<P>g[maxN];
std::vector<int>alive;

void debug() {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < g[i].size(); ++j) {
			std::cout << "i: " << i << " to: " << g[i][j].first << " c: " << g[i][j].second << std::endl;
		}
	}
}

bool used[maxN];
P dfs(int v) {
	used[v] = true;

	P ret = P(0, v);
	for (int i = 0; i < g[v].size(); i++) {
		int u = g[v][i].first;
		int w = g[v][i].second;
		if (used[u]) continue;
		P tmp = dfs(u);
		ret = std::max(ret, P(w + tmp.first, tmp.second));
	}
	return ret;
}

int treeDim() {
	int v = dfs(0).second;
	for (int i = 0;i < n; ++i)used[i] = false;
	return dfs(v).first;
}

int main() {
	std::cin >> n >> d;

	seed(time(NULL));

	for (int i = 0; i < n; ++i) {
		for (int j = g[i].size(); j < d; ++j) {
			alive.clear();
			for (int k = 0; k < n; ++k) {
				if (g[k].size() < d)alive.push_back(k);
			}
			if (alive.size() == 1) {
				std::cout << "Hou" << std::endl;
				//debug();
				return 0;
			}

			int to = 0;

			int cnt = 0;
		again:;
			if (cnt > 10000) {
				std::cout << "Hey" << std::endl;
				//debug();
				return 0;
			}
			to = alive[xor128() % alive.size()];
			if (i == to || g[to].size() == d) {
				++cnt;
				goto again;
			}
			for (int k = 0; k < g[i].size(); ++k) {
				if (g[i][k].first == to) {
					++cnt;
					goto again;
				}
			}

			g[i].push_back(P(to, 1));
			g[to].push_back(P(i, 1));
		}
	}
	std::cout << "yes" << std::endl;
	//debug();

	std::cout << treeDim() << std::endl;

	return 0;
}