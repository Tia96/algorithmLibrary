#include <iostream>

int main(){
	int n, k, x, y;
	
	std::cin >> n >> k >> x >> y;
	std::cout << std::min(n, k) * x + std::max(0, (n - k)) * y << std::endl;
	
	return 0;
}