#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> P;

int n, sum;
P x[2001];
std::vector<int> book[11];
int cnt[11];
int dp[11][2001];

int main(){
	std::cin >> n >> sum;
	for(int i = 0; i < n; ++i){
		int a, b;
		std::cin >> a >> b;
		book[b - 1].push_back(a);
	}
	
	for(int i = 0; i < 10; ++i){
		std::sort(book[i].begin(), book[i].end(), std::greater<int>());
		for(int j = 1; j < book[i].size(); ++j){
			book[i][j] += book[i][j - 1];
		}
		for(int j = 1; j < book[i].size(); ++j){
			book[i][j] += j * (j + 1);
		}
		book[i].insert(book[i].begin(), 0);
	}
	
	for(int i = 0; i < 11; ++i){
		for(int j = 0; j < 2001; ++j)dp[i][j] = -1;
	}
	
	dp[0][0] = 0;
	for(int i = 0; i < 10; ++i){
		for(int j = 0; j <= sum; ++j){
			if(dp[i][j] == -1)continue;
			
			for(int k = 0; k < book[i].size(); ++k){
				if(j + k <= sum)dp[i + 1][j + k] = std::max(dp[i + 1][j + k], dp[i][j] + book[i][k]);
			}
		}
	}
	
	std::cout << dp[10][sum] << std::endl;
	
	return 0;
}