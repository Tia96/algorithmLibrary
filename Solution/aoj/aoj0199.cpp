#include <iostream>

int n, m;
int chair[105];

int dist(int k){
	int ret = 1000;
	for(int i = k; i <= n; ++i){
		if(chair[i]){
			ret = i - k;
			break;
		}
	}
	for(int i = k; i >= 1; --i){
		if(chair[i]){
			ret = std::min(ret, k - i);
			break;
		}
	}
	return ret;
}

int main(){
	while(true){
		for(int i = 0; i < 105; ++i)chair[i] = 0;
		
		std::cin >> n >> m;
		if(n == 0 && m == 0)break;

		for(int i = 0; i < m; ++i){
			char ch;
			std::cin >> ch;

			if(ch == 'A'){
				for(int j = 1; j <= n; ++j){
					if(chair[j] == 0){
						chair[j] = 1;
						break;
					}
				}
			}
			else if(ch == 'B'){
				bool f = false;

				for(int j = n; j >= 1; --j){
					if(chair[j] == 0 && chair[j - 1] != 1 && chair[j + 1] != 1){
						chair[j] = 2;
						f = true;
						break;
					}
				}

				if(!f){
					for(int j = 1; j <= n; ++j){
						if(chair[j] == 0){
							chair[j] = 2;
							break;
						}
					}
				}
			}
			else if(ch == 'C'){
				if(i == 0)chair[n % 2 ? ((n + 1) / 2) : (n / 2 + 1)] = 3;
				else{
					for(int j = 1; j <= n; ++j){
						if(chair[j]){
							if(j + 1 <= n && chair[j + 1] == 0){
								chair[j + 1] = 3;
								break;
							}
							if(j - 1 >= 1 && chair[j - 1] == 0){
								chair[j - 1] = 3;
								break;
							}
						}
					}
				}
			}
			else if(ch == 'D'){
				if(i == 0)chair[1] = 4;
				else{
					int maxV = -1000, maxI;
					for(int j = 1; j <= n; ++j){
						if(chair[j] == 0){
							if(dist(j) > maxV)maxV = dist(j), maxI = j;
						}
					}
					chair[maxI] = 4;
				}
			}
		}

		for(int i = 1; i <= n; ++i){
			if(chair[i] == 0)std::cout << "#";
			else std::cout << (char)('A' + chair[i] - 1);
		}
		std::cout << std::endl;
	}
	
	return 0;
}