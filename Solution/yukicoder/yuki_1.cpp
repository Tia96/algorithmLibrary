#include <iostream>
#include <algorithm>
#include <vector>

#define INF 10000000

struct Edge{
	int to, cost, time;
};

int n, c, v;
int s[1501], t[1501], y[1501], m[1501];
int dp[51][301];
std::vector<Edge> g[51];

int main(){
	std::cin >> n >> c >> v;
	for(int i = 0; i < v; ++i)std::cin >> s[i];
	for(int i = 0; i < v; ++i)std::cin >> t[i];
	for(int i = 0; i < v; ++i)std::cin >> y[i];
	for(int i = 0; i < v; ++i)std::cin >> m[i];
	
	for(int i = 0; i < v; ++i){
		Edge e;
		--s[i]; --t[i];
		e.to = t[i]; e.cost = y[i]; e.time = m[i];
		g[s[i]].push_back(e);
	}
	
	for(int i = 0; i < 51; ++i){
		for(int j = 0; j < 301; ++j)dp[i][j] = INF;
	}
	
	dp[0][0] = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < 301; ++j){
			if(dp[i][j] == INF)continue;
			
			for(int k = 0; k < g[i].size(); ++k){
				int to = g[i][k].to, cost = j + g[i][k].cost;
				if(cost < 301)dp[to][cost] = std::min(dp[to][cost], dp[i][j] + g[i][k].time);
			}
		}
	}
	
	int ans = INF;
	for(int i = 0; i <= c; ++i){
		ans = std::min(ans, dp[n - 1][i]);
	}
	
	std::cout << (ans == INF ? -1 : ans) << std::endl;
	
	return 0;
}