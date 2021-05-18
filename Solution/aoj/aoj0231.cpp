#include <iostream>
#include <map>

int n;
std::map<int, int> map;

int main(){
	while(true){
		map.clear();
		
		std::cin >> n;
		if(n == 0)break;
		
		for(int i = 0; i < n; ++i){
			int a, b, c;
			std::cin >> a >> b >> c;
			map[b] = a + map.find(b) ->second;
			map[c] = -a + map.find(c)->second;
		}
		
		auto it = map.begin();
		int bef = it->second;
		++it;
		while(it != map.end()){
			it->second += bef;
			bef = it->second;
			++it;
		}
		
		bool f = true;
		for(it = map.begin(); it != map.end(); ++it){
			if(it->second > 150)f = false;
		}
		
		if(f)std::cout << "OK" << std::endl;
		else std::cout << "NG" << std::endl;
	}
	
	return 0;
}