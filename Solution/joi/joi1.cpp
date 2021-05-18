#include <iostream>
#include <algorithm>

typedef long long ll;

const ll inf = (ll)1e+17 + 7;

int n, m;
ll k;
ll a[20001];
ll dp[20001];

int main(){
	std::cin >> n >> m >> k;
	for(int i = 0; i < n; ++i)std::cin >> a[i];
	
	for(int i = 0; i < 20001; ++i){
		dp[i] = inf;
	}
	
	dp[0] = 0;
	for(int i = 0; i < n; ++i){
		ll small = inf, large = -inf;
		for(int j = 0; j < m; ++j){
			if(i + j + 1 > n)continue;
			
			small = std::min(small, a[i + j]);
			large = std::max(large, a[i + j]);
			
			dp[i + j + 1] = std::min(dp[i + j + 1], dp[i] + k + (j + 1) * (large - small));
		}
	}
	
	std::cout << dp[n] << std::endl;
	
	return 0;
}