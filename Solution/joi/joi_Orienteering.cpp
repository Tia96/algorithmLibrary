#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;

const int maxN = 1001, maxM = 10001;

int n, m;
int s[maxN];
std::vector<P> g;
std::vector<int> vs;
bool visit[maxN];
int cost[maxN];

void topo_sort(int k){
	if(visit[v]) return;
	visit[v] = true;
	for(int i = 0; i < g[k].size(); ++i)topo_sort(g[k][i].first);
	vs.push_back(k);
}

void dijkstra(int k){
	
}

int main(){
	std::cin >> n >> m;
	for(int i = 0; i < n; ++i)std::cin >> s[i];
	for(int i = 0; i < m; ++i){
		int a, b, c;
		g[a - 1].push_back(P(b - 1, c));
	}
	
	topo_sort(0);
	std::reverse(vs.begin(), vs.end());
	
	
	
	
	return 0;
}