#include <iostream>
#include <cmath>

int f(double n){
	return floor((n * n + 4.0) / 8.0);
}

int main(){
	std::cout << f(f(f(20.0))) << std::endl;
	return 0;
}