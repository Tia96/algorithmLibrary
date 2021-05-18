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
const int infi = (int)1e+9 + 10;
const ll infll = (ll)1e+17 + 10;

int n, m, l, k, a, h;
std::vector<P> g[105]; //to,time
int cost[105][105];
bool isCold[105];

int main() {
	while (true) {
		std::cin >> n >> m >> l >> k >> a >> h;
		if (n + m + l + k + a + h == 0)break;
		rep(i, 105)g[i].clear(), isCold[i] = false;

		rep(i, l) {
			int x;
			std::cin >> x;
			isCold[x] = true;
		}
		rep(i, k) {
			int x, y, t;
			std::cin >> x >> y >> t;
			g[x].push_back(P(y, t));
			g[y].push_back(P(x, t));
		}

		rep(i, 105)rep(j, 105)cost[i][j] = infi;
		cost[a][m] = 0;

		//PP: cost, (time, n)
		std::priority_queue<PP, std::vector<PP>, std::greater<PP> > que;
		que.push(PP(0, P(m, a)));
		while (!que.empty()) {
			PP pp = que.top();
			que.pop();
			int vv = pp.second.second, vm = pp.second.first;
			if (cost[vv][vm] < pp.first)continue;

			if (isCold[vv]) {
				rep(i, m - vm) {
					int nvm = vm + i + 1;
					if (cost[vv][nvm] > cost[vv][vm] + i + 1) {
						cost[vv][nvm] = cost[vv][vm] + i + 1;
						que.push(PP(cost[vv][nvm], P(nvm, vv)));
					}
				}
			}
			rep(i, g[vv].size()) {
				P e = g[vv][i];
				int tt = vm - e.second;
				if (tt >= 0 && cost[e.first][tt] > cost[vv][vm] + e.second) {
					cost[e.first][tt] = cost[vv][vm] + e.second;
					que.push(PP(cost[e.first][tt], P(tt, e.first)));
				}
			}
		}

		int min = infi;
		rep(i, m + 1)min = std::min(min, cost[h][i]);
		if (min == infi)std::cout << "Help!" << std::endl;
		else std::cout << min << std::endl;
	}

	return 0;
}