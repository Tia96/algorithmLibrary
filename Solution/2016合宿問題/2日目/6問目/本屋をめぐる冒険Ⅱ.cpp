#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <queue>

typedef long long ll;
const int infi = (int)1e+9 + 7;

typedef std::pair<int, int> P;

const int maxN = 100005;

int n, m, t;
std::vector<P> g[maxN]; //to,time
int cost[maxN];
ll x[maxN];

void dijkstra(int k) {
	std::priority_queue < P, std::vector<P>, std::greater<P> > que;
	for (int i = 0; i < n; ++i)cost[i] = infi;
	cost[k] = 0;
	que.push(P(0, k));
	while (!que.empty()) {
		P p = que.top();
		que.pop();
		int v = p.second;
		if (cost[v] < p.first)continue;
		for (int i = 0; i < g[v].size(); ++i) {
			P e = g[v][i];
			if (cost[e.first] > cost[v] + e.second) {
				cost[e.first] = cost[v] + e.second;
				que.push(P(cost[e.first], e.first));
			}
		}
	}
}

int main() {
	std::cin >> n >> m >> t;

	for (int i = 0; i < n; ++i) {
		std::cin >> x[i];
	}

	for (int i = 0; i < m; ++i) {
		int a, b, c;
		std::cin >> a >> b >> c;
		--a, --b;
		g[a].push_back(P(b, c));
		g[b].push_back(P(a, c));
	}

	dijkstra(0);

	ll ans = 0;
	for (int i = 0; i < n; ++i) {
		ll time = t - cost[i] - cost[i];
		ans = std::max(ans, x[i] * time);
	}

	std::cout << ans << std::endl;

	return 0;
}