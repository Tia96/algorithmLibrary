#include <iostream>
#include <algorithm>
#include <vector>

typedef std::pair<int, int> P;
typedef std::pair<P, int> PP;
typedef long long ll;

const ll inf = (1ll << 58);
const int max = 100010;

int n, A, B;
std::vector<PP> upd[max], que[max], ers[max];
int a[max];
ll ans[max];

ll seg[max * 4], all[max * 4]; //max * 2 - 1はだめ
int sz;

void init(int x){
	sz = 1;
	while(sz < x)sz <<= 1;
}

void add(int a, int b, int x, int k, int l, int r){
	if(b <= l || r <= a)return;
	else if(a <= l && r <= b) {
		all[k] += x;
		return;
	}
	add(a, b, x, k * 2 + 1, l, (l + r) / 2);
	add(a, b, x, k * 2 + 2, (l + r) / 2, r);
	seg[k] = std::min(seg[2 * k + 1] + all[2 * k + 1], seg[2 * k + 2] + all[2 * k + 2]);
}

ll query(int a, int b, int k, int l ,int r){
	if(b <= l || r <= a)return inf;
	else if(a <= l && r <= b)return all[k] + seg[k];
	ll p = query(a, b, k * 2 + 1, l, (l + r) / 2);
	ll q = query(a, b, k * 2 + 2, (l + r) / 2, r);
	return std::min(p, q) + all[k];
}

int main(){
	scanf("%d", &n);
	for(int i = 0; i < n; ++i)scanf("%d", &a[i]);
	
	scanf("%d", &A);
	for(int i = 0; i < n; ++i){
		upd[i].push_back(PP(P(0, A + 1), a[i]));
		upd[i + 1].push_back(PP(P(0, A + 1), -a[i]));
	}
	for(int i = 0; i < A; ++i){
		int l, r, x;
		scanf("%d%d%d", &l, &r, &x);
		upd[l - 1].push_back(PP(P(i + 1, A + 1), x));
		upd[r].push_back(PP(P(i + 1, A + 1), -x));
	}
	
	scanf("%d", &B);
	for(int i = 0; i < B; ++i){
		int s, t, k;
		scanf("%d%d%d", &s, &t, &k);
		que[k - 1].push_back(PP(P(s - 1, t + 1), i));
	}
	
	init(A + 1);

	for(int i = 0; i < n; ++i){
		for(auto p : upd[i]){
			add(p.first.first, p.first.second, p.second, 0, 0, sz);
		}
		
		for(auto p : que[i]){
			ans[p.second] = query(p.first.first, p.first.second, 0, 0, sz);
		}
	}
	
	for(int i = 0; i < B; ++i){
		printf("%lld\n", ans[i]);
	}
	
	return 0;
}