#include <iostream>
#include <algorithm>

int n, c;
int a[31], b[31];
int dp[31][1 << 16];

int score(int x){
	int ret = 0;
	while(x){
		if(x & 1)++ret;
		x >>= 1;
	}
	return ret;
}

int main(){
	while(true){
		std::cin >> n >> c;
		
		if(n == 0 && c == 0)break;
		
		for(int i = 0; i < 31; ++i)a[i] = 0, b[i] = 0;
		
		for(int i = 0; i <= n; ++i){
			for(int j = 0; j < (1 << 16); ++j){
				dp[i][j] = -1;
			}
		}

		for(int i = 0; i < n; ++i){
			for(int j = 0; j < 16; ++j){
				int x;
				std::cin >> x;
				if(x == 1)a[i] |= (1 << j);
			}
		}
		
		for(int i = 0; i < c; ++i){
			for(int j = 0; j < 16; ++j){
				int x;
				std::cin >> x;
				if(x == 1)b[i] |= (1 << j);
			}
		}
		
		dp[0][0] = 0;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < (1 << 16); ++j){
				if(dp[i][j] == -1)continue;
				
				int cur = (j | a[i]);
				for(int k = 0; k < c; ++k){
					int x = cur & b[k];
					int next = cur & (~b[k]);

					dp[i + 1][next] = std::max(dp[i + 1][next], dp[i][j] + score(x));
				}
			}
		}
		
		int ans = -1;
		for(int i = 0; i < (1 << 16); ++i){
			ans = std::max(ans, dp[n][i]);
		}
		
		std::cout << ans << std::endl;
	}
	
	return 0;
}