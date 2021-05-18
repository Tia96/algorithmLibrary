#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

typedef std::pair<int, int> P;

int n;
int p[65001], j[65001];
long long sum, max = 0;

int main(){
	while(true){
		std::cin >> n;
		sum = 0, max = 0;
		
		if(n == 0)break;
		
		for(int i = 0; i < n; ++i){
			std::cin >> p[i];
			sum += p[i];
		}
		
		for(int i = 0; i < n - 1; ++i){
			std::cin >> j[i];
		}
		
		std::sort(j, j + n - 1, std::greater<int>());
		max = sum * n;
		
		for(int i = 0; i < n - 1; ++i){
			long long k = (sum + j[i]) * (n - 1);
			if(k > max){
				max = k;
				sum += j[i], --n;
			}
			else break;
		}
		
		std::cout << max << std::endl;
	}
	
	return 0;
}