#include <iostream>
#include <string>

std::string s;
int ch[26];

int main(){
	std::cin >> s;
	
	for(int i = 0; i < s.size(); ++i)++ch[s[i] - 'a'];
	
	for(int i = 0; i < 26; ++i){
		if(ch[i] % 2){
			std::cout << "No" << std::endl;
			return 0;
		}
	}
	
	std::cout << "Yes" << std::endl;
	
	return 0;
}