#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <functional>

const int inf = 1000000000;

typedef std::pair<int, int> P;
typedef std::pair<P, int> PP;

const int maxN = 100001, maxM = 200001, maxQ = 200001;

P cost[maxN]; //cost, time
std::vector<PP> g[maxN]; //(cost, time), to
int n, m, q;
int u[maxM], v[maxM], t[maxM];
int r[maxQ];
int ans[maxQ];

void dijkstra(int k){
	std::priority_queue < PP, std::vector<PP>, std::greater<PP> > que; //(cost, time), n
	for (int i = 0; i < n; ++i)cost[i] = P(inf, inf);
	cost[k].first = 0;
	que.push(PP(P(0, inf), k));
	while (!que.empty()){
		PP pp = que.top();
		que.pop();
		int v = pp.second;
		if (cost[v].first < pp.first.first)continue;
		for (int i = 0; i < g[v].size(); ++i){
			PP e = g[v][i];
			if (cost[e.second].first > cost[v].first + e.first.first){
				cost[e.second].first = cost[v].first + e.first.first;
				cost[e.second].second = std::min(cost[v].second, e.first.second);
				que.push(PP(cost[e.second], e.second));
			}
			else if(cost[e.second].first == cost[v].first + e.first.first && cost[e.second].second < std::min(cost[v].second, e.first.second)){
				cost[e.second].second = std::min(cost[v].second, e.first.second);
				que.push(PP(cost[e.second], e.second));
			}
		}
	}
}

int main(){
	std::cin >> n >> m >> q;
	for(int i = 0; i < m; ++i){
		std::cin >> u[i] >> v[i];
		--u[i], --v[i];
		t[i] = inf;
	}
	for(int i = 0; i < q; ++i){
		std::cin >> r[i];
		t[r[i] - 1] = i;
	}
	
	for(int i = 0; i < m; ++i){
		g[u[i]].push_back(PP(P(1, t[i]), v[i]));
		g[v[i]].push_back(PP(P(1, t[i]), u[i]));
	}
	
	dijkstra(0);
	for(int i = 0; i < n; ++i){
		if(cost[i].second != inf)++ans[cost[i].second];
	}
	
	for(int i = 1; i < q; ++i){
		ans[i] += ans[i - 1];
	}
	
	for(int i = 0; i < q; ++i){
		std::cout << ans[i] << std::endl;
	}
	
	return 0;
}