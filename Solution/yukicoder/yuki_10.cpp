#include <iostream>
#include <string>
#include <algorithm>

int n, total;
int a[51];

std::string min(std::string l, std::string r){
	if(l.size() > r.size())return l;
	if(l.size() < r.size())return r;
	
	for(int i = 0; i < l.size(); ++i){
		if(l[i] == '*' && r[i] == '+')return r;
		if(l[i] == '+' && r[i] == '*')return l;
	}
}

std::string memo[51][100001];
std::string solve(int k, int sum){
	
	if(k == n)return "";
	
	if(memo[k][sum] != "")return memo[k][sum];
	
	if((k == n - 1 && sum + a[k] == total) || (k != n - 1 && sum + a[k] <= total))memo[k][sum] = min(memo[k][sum], "+" + solve(k + 1, sum + a[k]));
	if((k == n - 1 && sum * a[k] == total) || (k != n - 1 && sum * a[k] <= total))memo[k][sum] = min(memo[k][sum], "*" + solve(k + 1, sum * a[k]));
	
	return memo[k][sum];
}


int main(){
	std::cin >> n >> total;
	for(int i = 0; i < n; ++i){
		std::cin >> a[i];
	}
	
	for(int i = 0; i < 51; ++i){
		for(int j = 0; j < 100001; ++j)memo[i][j] = "";
	}
	
	std::cout << solve(1, a[0]) << std::endl;

	return 0;
}