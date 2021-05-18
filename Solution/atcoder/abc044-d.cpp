#include <iostream>
#include <string>

#define INF 100000000001

typedef long long ll;

ll n, s;

ll f(ll x, ll k){
	ll ret = 0;
	while(x){
		ret += (x % k);
		x /= k;
	}
	return ret;
}

int main(){
	std::cin >> n >> s;
	
	if(n == s){
		std::cout << n + 1 << std::endl;
		return 0;
	}
	
	if(s > n){
		std::cout << -1 << std::endl;
		return 0;
	}
	
	for(ll i = 2; i * i <= n; ++i){
		if(f(n, i) == s){
			std::cout << i << std::endl;
			return 0;			
		}
	}
	
	ll ans = INF;
	for(ll p = 1; p * p <= n; ++p){
		ll b = (n - s) / p + 1;
		if(b == 1)continue;
		if(f(n, b) == s)ans = std::min(ans, b);
	}
	
	if(ans != INF){
		std::cout << ans << std::endl;
		return 0;
	}
	
	std::cout << -1 << std::endl;
	
	return 0;
}