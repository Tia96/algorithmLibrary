#include <iostream>
#include <string>
#include <algorithm>
#include <cmath>
#include <cstdio>
#include <sstream>
#include <iomanip>

int q;

std::string toS(char c){
	std::string ret;
	
	int x = c - '0';
	if(c >= 'a')x = c - 'a' + 10;
	
	while(x){
		ret += ((x % 2) + '0');
		x /= 2;
	}
	
	while(ret.size() < 4)ret += "0";
	
	std::reverse(ret.begin(), ret.end());
	return ret;
}

int main(){
	std::cin >> q;
	for(int i = 0; i < q; ++i){
		long double ans = 0;
		std::string tmp, s;
		std::cin >> tmp;
		
		for(int j = 0; j < tmp.size(); ++j){
			s += toS(tmp[j]);
		}
		std::reverse(s.begin(), s.end());
		
		int b = 7;
		for(int j = 0; j < 24; ++j){
			if(s[b + j] == '1')ans += pow(2, j);
		}
		
		b = 6;
		for(int j = 0; j < 7; ++j){
			if(s[b - j] == '1')ans += pow(2, -j - 1);
		}
		
		if(s[31] == '1')ans *= -1;
		
		std::string sans;
		std::stringstream z;
		z.precision(10);
		z << ans;
		z >> sans;
		
		int p = sans.find('.');
		for(int j = 6; j >= 1; --j){
			std::cout << sans[p + j] << std::endl;
			if(sans[p + j] == '0'){
				if(j != 1)sans.erase(sans.begin() + p + j);
			}
			else break;
		}
		
		std::cout << sans << std::endl;
	}
	
	return 0;
}