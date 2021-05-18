//dijkstra

const int max = 21;
int cost[max];
std::vector<P> g[max];
int n, m;

void dijkstra(int k){
	std::priority_queue < P, std::vector<P>, std::greater<P> > que;
	for (int i = 0; i < n; ++i)cost[i] = infi;
	cost[k] = 0;
	que.push(P(0, k));
	while (!que.empty()){
		P p = que.top();
		que.pop();
		int v = p.second;
		if (cost[v] < p.first)continue;
		for (int i = 0; i < g[v].size(); ++i){
			P e = g[v][i];
			if (cost[e.first] > cost[v] + e.second){
				cost[e.first] = cost[v] + e.second;
				que.push(P(cost[e.first], e.first));
			}
		}
	}
}

int main(){
	std::cin >> n >> m;
	rep(i, m){
		int a, b, c, d;
		char ch;
		std::cin >> a >> ch >> b >> ch >> c >> ch >> d;
		--a, --b;
		P p(b, c), q(a, d);
		g[a].push_back(p);
		g[b].push_back(q);
	}
	int x1, x2, y1, y2;
	char ch;
	std::cin >> x1 >> ch >> x2 >> ch >> y1 >> ch >> y2;
	--x1, --x2;
	dijkstra(x1);
	y1 -= cost[x2];
	dijkstra(x2);
	y1 -= cost[x1];
	y1 -= y2;
	std::cout << y1 << std::endl;
	return 0;
}