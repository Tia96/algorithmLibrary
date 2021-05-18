//StarrySky

ll seg[max * 4], all[max * 4]; //max * 2 - 1はだめ
int sz;

const ll inf = (1ll << 50);

void init(int x){
	sz = 1;
	while(sz < x)sz <<= 1;
}

///////////// MIN, MAX /////////////////
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

///////////// SUM /////////////////
void add(int a, int b, int x, int k, int l, int r){
	if(b <= l || r <= a)return;
	else if(a <= l && r <= b) {
		all[k] += x;
		return;
	}
	seg[k] += (std::min(b, r) - std::max(a, l)) * x;
	add(a, b, x, k * 2 + 1, l, (l + r) / 2);
	add(a, b, x, k * 2 + 2, (l + r) / 2, r);
}

ll query(int a, int b, int k, int l ,int r){
	if(b <= l || r <= a)return inf;
	else if(a <= l && r <= b)return all[k] * (r - l) + seg[k];
	ll res;
	res = (std::min(b, r) - std::max(a, l)) * all[k];
	res += query(a, b, k * 2 + 1, l, (l + r) / 2);
	res += query(a, b, k * 2 + 2, (l + r) / 2, r);
	return res;
}

