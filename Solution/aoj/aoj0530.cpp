#include <iostream>
#include <vector>
#include <algorithm>

typedef std::pair<int, int> P;
typedef long long ll;

const ll inf = (1ll << 30);

int n, m;
std::vector<P> map[205];
ll dp[205][11][105];

int main(){
	while(true){
		std::cin >> n >> m;
		if(n == 0 && m == 0)break;
		
		for(int i = 0; i < 205; ++i)map[i].clear();
		
		for(int i = 0; i < 205; ++i){
			for(int j = 0; j < 11; ++j){
				for(int k = 0; k < 105; ++k){
					dp[i][j][k] = inf;
				}
			}
		}
		
		map[0].push_back(P(-1, -1));
		for(int i = 1; i <= n; ++i){
			int k;
			std::cin >> k;
			for(int j = 0; j < k; ++j){
				int a, b;
				std::cin >> a >> b;
				map[i].push_back(P(a - 1, b));
			}
		}
		map[n + 1].push_back(P(-1, -1));
		
		dp[0][0][0] = 0;
		for(int i = 0; i <= n; ++i){
			for(int j = 0; j < map[i].size(); ++j){
				for(int k = 0; k <= m; ++k){
					if(dp[i][j][k] == inf)continue;
					
					int v = i + 1;
					for(int p = 0; p < map[v].size(); ++p){
						int cost = (map[i][j].second + map[v][p].second) * std::abs(map[i][j].first - map[v][p].first);
						if(map[i][j].first == -1 || map[v][p].first == -1)cost = 0;
						
						dp[v][p][k] = std::min(dp[v][p][k], dp[i][j][k] + cost);
					}
					
					v = i + 2;
					for(int p = 0; p < map[v].size(); ++p){
						int cost = (map[i][j].second + map[v][p].second) * std::abs(map[i][j].first - map[v][p].first);
						if(map[i][j].first == -1 || map[v][p].first == -1)cost = 0;
						
						dp[v][p][k + 1] = std::min(dp[v][p][k + 1], dp[i][j][k] + cost);
					}
				}
			}
		}
		
		ll ans = inf;
		for(int i = 0; i <= m; ++i){
			ans = std::min(ans, dp[n + 1][0][i]);
		}
		
		std::cout << ans << std::endl;
	}
	
	return 0;
}