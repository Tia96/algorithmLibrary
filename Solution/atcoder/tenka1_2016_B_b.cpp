#include <iostream>
#include <string>

#define INF 10000000

int n;
std::string s;
int dp[101][101][101];

int main(){
	std::cin >> s;
	n = s.size();
	
	for(int i = 0; i < 101; ++i){
		for(int j = 0; j < 101; ++j){
			for(int k = 0; k < 101; ++k)dp[i][j][k] = INF;
		}
	}
	
	dp[0][0][0] = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			for(int k = 0; k < n; ++k){
				if(dp[i][j][k] == INF)continue;
				
				if(s[i] == '('){
					dp[i + 1][j + 1][k] = std::min(dp[i + 1][j + 1][k], dp[i][j][k]);
					if(j - 1 >= 0)dp[i + 1][j - 1][i] = std::min(dp[i + 1][j - 1][i], dp[i][j][k] + (i - k) + 1);
				}
				else{
					if(j - 1 >= 0)dp[i + 1][j - 1][k] = std::min(dp[i + 1][j - 1][k], dp[i][j][k]);
					dp[i + 1][j + 1][i] = std::min(dp[i + 1][j + 1][i], dp[i][j][k] + (i - k) + 1);
				}
			}
		}
	}
	
	int minV = INF;
	for(int i = 0; i < n; ++i){
		minV = std::min(minV, dp[n][0][i]);
	}
	
	std::cout << minV << std::endl;
	
	return 0;
}