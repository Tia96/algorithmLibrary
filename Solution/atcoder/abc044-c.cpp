#include <iostream>

typedef long long ll;

int n, a;
int x[51];
ll dp[51][51][3000];

int main(){
	std::cin >> n >> a;
	for(int i = 0; i < n; ++i)std::cin >> x[i];
	
	dp[0][0][0] = 1;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < 2600; ++k){
				if(dp[i][j][k] == 0)continue;
				
				dp[i + 1][j][k] += dp[i][j][k];
				dp[i + 1][j + 1][k + x[i]] += dp[i][j][k];
				
			}
		}
	}
	
	ll ans = 0;
	for(int i = 1; i <= n; ++i){
		ans += dp[n][i][i * a];
	}
	
	std::cout << ans << std::endl;
	
	return 0;
}