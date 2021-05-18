//セグメントツリー

const int maxN = 200010;

//0:indexed
class RMQ{
private:
	int n;
	P dat[maxN * 4];

	//[a,b),[l,r) //(Max,Min)
	P rec(int a, int b, int k, int l, int r){
		if (b <= l || r <= a)return P(-infi, infi);
		if (a <= l && r <= b)return P(dat[k].first, dat[k].second);
		else {
			P vl = rec(a, b, 2 * k + 1, l, (l + r) / 2), vr = rec(a, b, 2 * k + 2, (l + r) / 2, r);
			return P(std::max(vl.first, vr.first), std::min(vl.second, vr.second));
		}
	}

public:
	void init(int x){
		n = 1;
		while (n < x)n *= 2;
		rep(i, 2 * n - 1)dat[i] = P(-infi, infi);
	}

	void update(int k, int a){
		k += n - 1;
		dat[k] = P(a, a);
		while (k > 0){
			k = (k - 1) / 2;
			dat[k].first = std::max(dat[2 * k + 1].first, dat[2 * k + 2].first);
			dat[k].second = std::min(dat[2 * k + 1].second, dat[2 * k + 2].second);
		}
	}

	//[a,b] //(Max,Min)
	P query(int a, int b){
		return rec(a, b + 1, 0, 0, n);
	}
};

struct Star{ int x, y, b; };
Star star[200001];
int n, d;
RMQ up, right;

bool comp(const Star &lhs, const Star &rhs){
	return lhs.b < rhs.b;
}

int main(){
	std::cin >> n >> d;
	rep(i, n)std::cin >> star[i].x >> star[i].y >> star[i].b;
	std::sort(star, star + n, comp);
	ll ans = 0;
	int first = 0;
	up.init(n), right.init(n);
	rep(i, n){
		up.update(i, star[i].y);
		right.update(i, star[i].x);
		while (star[i].b - star[first].b > d)++first;
		P a = up.query(first, i), b = right.query(first, i);
		ll mul = (ll)(a.first - a.second) * (b.first - b.second);
		ans = std::max(ans, mul);
	}
	std::cout << ans << std::endl;
	return 0;
}

/*
typedef long long lint;

lint all[MAX_SIZE - 1], part[MAX_SIZE - 1]; // segment tree

//区間[a, b)に値xを加算する.
void add(int a, int b, int x, int k, int l, int r)
{
    if (a <= l && r <= b){ //[l, r)が[a, b)に完全に内包されていれば
        all[k] += x; //[l, r)の全ての区間が持つ値としてxを足す.
    }
    else if (l < b && a < r){ //[l, r)と[a, b)が交差していれば
        part[k] += (min(b, r) - max(a, l)) * x;  //交差している分の値を, 部分的な和を持つノードに加算する.
        add(a, b, x, k * 2 + 1, l, (l + r) / 2); //子でも同じ処理を行う.
        add(a, b, x, k * 2 + 2, (l + r) / 2, r); //〃.
    }
}

lint sum(int a, int b, int k, int l, int r)
{
    if (b <= l || r <= a){ //[a, b)と[l, r)が全く交差しない場合
        return (0);
    }
    else if (a <= l && r <= b){ //完全に内包されていれば
        return (all[k] * (r - l) + part[k]);
    }
    else { //[l, r)と[a, b)が交差していれば
        ll res;
        res = (min(b, r) - max(a, l)) * all[k]; //そのノードの全ての要素が持つ値のうち, [a, b)に属すものの分だけを加算する.
        res += sum(a, b, k * 2 + 1, l, (l + r) / 2); //子ノードで和を求める.
        res += sum(a, b, k * 2 + 2, (l + r) / 2, r); //〃
        return (res);
    }
}
*/