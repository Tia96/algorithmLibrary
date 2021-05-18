//lazy_segtree

const int MAX_N = 10001;

struct Node{
	int sum, lazy;
};

Node node[MAX_N * 4];
int seg_size;

void init_size(int x){
    seg_size = 1;
    while (seg_size < x) seg_size *= 2;
}

void init_node(){
	for(int i = 0; i < seg_size; ++i){
		node[i].sum = 0;
		node[i].lazy = 0;
	}
}

inline void update_lazy(int k){
	node[k * 2 + 1].lazy += node[k].lazy;
	node[k * 2 + 2].lazy += node[k].lazy;
	node[k].lazy = 0;
}

//[l, r) [a, b)
int add(int l, int r, int k, int a, int b, int v){
	if (r <= a || b <= l) return node[k].sum + node[k].lazy * (r - l);
	if (a <= l && r <= b) return node[k].sum + (node[k].lazy += v) * (r - l);
	update_lazy(k);
	int mid = (l + r) / 2;
	return node[k].sum = add(l, mid, k * 2 + 1, a, b, v) + add(mid, r, k * 2 + 2, a, b, v);
}

int get_sum(int l, int r, int k, int a, int b){
	if (r <= a || b <= l) return 0;
	if (a <= l && r <= b) return node[k].sum + node[k].lazy * (r - l);
	update_lazy(k);
	int mid = (l + r) / 2;
	return get_sum(l, mid, k * 2 + 1, a, b) + get_sum(mid, r, k * 2 + 2, a, b);
}

int n;

int main(){
	std::cin >> n;

	init_size(n);
	init_node();

	add(0, seg_size, 0, 0, 5, 10);

	std::cout << get_sum(0, seg_size, 0, 4, 5) << std::endl;

	int s = 1, p = 0;
	for(int i = 0; i < 2 * seg_size - 1; ++i){
		std::cout << node[i].sum << " ";
		if(i == p)std::cout << std::endl, s *= 2, p += s;
	}

	return 0;
}
