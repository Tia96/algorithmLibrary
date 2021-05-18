//number

typedef long long ll;

ll mod = (ll)1e+9 + 7;

ll myPow(ll x, ll n){
	if (n == 0) return 1;
	ll ret = myPow(x * x % mod, n / 2);
	if (n & 1) ret = ret * x % mod;
	return ret;
}

void extgcd(int a, int b, int& x, int& y, int &d){
	int u, v, q, tmp;

	x = 1; y = 0; u = 0; v = 1;
	while (b > 0) {
		q = a / b;
		tmp = u; u = x - q * u; x = tmp;
		tmp = v; v = y - q * v; y = tmp;
		tmp = b; b = a - q * b; a = tmp;
	}
	d = a;
}

ll gcd(ll a, ll b){
	if (b == 0)return a;
	else return gcd(b, a % b);
}

ll lcm(ll a, ll b){
	return a / gcd(a, b) * b;
}