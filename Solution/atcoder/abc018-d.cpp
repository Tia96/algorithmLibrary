#include <iostream>
#include <algorithm>
#include <functional>

int n, m, p, q, r;
int x[400], y[400], z[400];
int ans;

int count(int x){
	int ret = 0;
	while(x){
		if(x & 1)++ret;
		x >>= 1;
	}
	return ret;
}

int main(){
	std::cin >> n >> m >> p >> q >> r;
	for(int i = 0; i < r; ++i){
		std::cin >> x[i] >> y[i] >> z[i];
		--x[i], --y[i];
	}
	
	for(int i = 0; i < (1 << n); ++i){
		if(count(i) != p)continue;
		
		int cho[21];
		for(int j = 0; j < 21; ++j)cho[j] = 0;
		
		for(int j = 0; j < r; ++j){
			if((i >> x[j]) & 1){
				cho[y[j]] += z[j];
			}
		}
		
		std::sort(cho, cho + m, std::greater<int>());
		
		int sum = 0;
		for(int j = 0; j < q; ++j){
			sum += cho[j];
		}
		
		ans = std::max(ans, sum);
	}
	
	std::cout << ans << std::endl;
	
	return 0;
}