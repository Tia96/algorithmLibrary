#include <iostream>
#include <cstdio>

const double inf = 1000;

int n, m;
double g[101][101];
double dp[101][101]; //i回目に前回j,今回kを与えた時の最大値

int main(){
	while(true){
		for(int i = 0; i < 101; ++i){
			for(int j = 0; j < 101; ++j){
				dp[i][j] = -1;
			}
		}
		
		std::cin >> n >> m;
		if(n == 0 && m == 0)break;
		
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < n; ++j){
				std::cin >> g[i][j];
			}
		}
		
		for(int i = 0; i < n; ++i)dp[0][i] = 1.0;
		
		for(int i = 0; i < m - 1; ++i){
			for(int j = 0; j < n; ++j){
				for(int k = 0; k < n; ++k){
					dp[i + 1][k] = std::max(dp[i + 1][k], dp[i][j] * g[j][k]);
				}
			}
		}
		
		double ans = 0;
		for(int i = 0; i < n; ++i){
			if(dp[m - 1][i] > ans)ans = dp[m - 1][i];
		}
		
		printf("%.2f\n", ans);
	}
	
	return 0;
}