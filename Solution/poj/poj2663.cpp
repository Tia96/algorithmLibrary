//bitDP(敷き詰める系)

#include <iostream>
#include <algorithm>
#include <bitset>

int n;
long long dp[31][3][1 << 3];
//i行目のj番目でその行の状態がk

int main(){
	while(true){
		std::cin >> n;
		if(n == -1)break;
		
		if(n == 0){
			std::cout << 1 << std::endl;
			continue;
		}
		
		for(int i = 0; i < 31; ++i){
			for(int j = 0; j < 3; ++j){
				for(int k = 0; k < (1 << 3); ++k){
					dp[i][j][k] = 0;
				}
			}
		}
		
		dp[0][0][0] = 1;
		for(int i = 0; i < n; ++i){
			for(int j = 0; j < 3; ++j){
				for(int used = 0; used < (1 << 3); ++used){
					int next = used & ~(1 << j);
					if((used >> j) & 1){
						if(j + 1 < 3)dp[i][j + 1][next] += dp[i][j][used];
						else dp[i + 1][0][next] += dp[i][j][used];
					}
					else{
						if(j + 1 < 3 && !((used >> (j + 1)) & 1)){
							int next = used | (1 << (j + 1));
							dp[i][j + 1][next] += dp[i][j][used];
						}
						if(i + 1 < n){
							int next = used | (1 << j);
							if(j + 1 < 3)dp[i][j + 1][next] += dp[i][j][used];
							else dp[i + 1][0][next] += dp[i][j][used];
						}
					}
				}
			}
		}
		
		std::cout << dp[n - 1][2][1 << 2] << std::endl;
	}
	
	return 0;
}
