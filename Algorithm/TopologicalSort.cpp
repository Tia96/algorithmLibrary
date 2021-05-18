//TopologicalSort

int n, m;
std::vector<int> g[100001];
std::vector<int> l;
int used[100001];
bool isClose = false;

//閉路検出可能
void TopologicalSort(int n){
	if (used[n] == 1){
		isClose = true;
		return;
	}
	else if (!used[n]){
		used[n] = 1;
		rep(i, g[n].size())TopologicalSort(g[n][i]);
		l.push_back(n);
		used[n] = 2;
	}
}

int main(){
	std::cin >> n >> m;
	rep(i, m){
		int a, b;
		std::cin >> a >> b;
		g[a].push_back(b);
	}

	rep(i, n)if (!used[i])TopologicalSort(i);
	std::reverse(l.begin(), l.end());
	rep(i, l.size())std::cout << l[i] << std::endl;;
	return 0;
}