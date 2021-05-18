#include <iostream>
#include <cstdio>

typedef long long ll;

const ll mod = 1000000007;

ll mpow(ll a, ll b, ll m){
	if(b == 0)return 1;
	
	if(b % 2)return a % m * mpow(a, b - 1, m) % m;
	else return mpow((a % m) * (a % m) % m, b / 2, m);
}

int main(){
	ll a, b, c;
	scanf("%lld^%lld^%lld", &a, &b, &c);
	
	std::cout << mpow(mpow(a, b, mod), c, mod) << " ";
	
	if(a % mod == 0)std::cout << 0 << std::endl;
	else std::cout << mpow(a, mpow(b, c, mod - 1), mod) << std::endl;
	
	return 0;
}