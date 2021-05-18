//BIT

const int maxN = 101;

//1:indexed
class Bit{
public:
	int n;
	int dat[maxN + 1];

	void init(int x) { n = x; }

	int sum(int k){
		int ret = 0;
		while (k > 0){
			ret += dat[k];
			k -= k & -k;
		}
		return ret;
	}

	void add(int k, int x){
		while (k <= n){
			dat[k] += x;
			k += k & -k;
		}
	}
};

int n;
int a[101];
Bit b;

int main(){
	std::cin >> n;
	b.init(n);
	rep(i, n)std::cin >> a[i];
	int ans = 0;
	rep(i, n)ans += (i - b.sum(a[i])), b.add(a[i], 1);
	std::sort(a, a + n);
	std::cout << a[0];
	REP(i, 1, n)std::cout << " " << a[i];
	std::cout << std::endl;
	std::cout << ans << std::endl;

	return 0;
}