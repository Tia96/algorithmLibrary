#include <iostream>
#include <queue>
#include "input.h"

#include <cstdio>
#include <cmath>
#include <cstring>
#include <ctime>

typedef std::pair<int, int> P;

int G[MAX_N][MAX_N];
std::vector<P> g[MAX_N];

unsigned long seed[4];
void rnd_init(unsigned int s){
	for(int i = 1; i <= 4; ++i)seed[i - 1] = s = 1812433253U * (s ^ (s >> 30)) + i;
}

unsigned long xor128(void) {
    unsigned long t;
	t=(seed[0]^(seed[0]<<11));seed[0]=seed[1];seed[1]=seed[2];seed[2]=seed[3]; return( seed[3]=(seed[3]^(seed[3]>>19))^(t^(t>>8)) );
}
int rnd(int k) {
    return xor128() % k;
}

void swap(int *a, int *b) {
    int t = *a;
    *a = *b;
    *b = t;
}

void random_shuffle(int a[], int size) {
    int i, r;
    for (i = size; i > 0; i--) {
        r = rnd(i);
        swap(a+r, a+i-1);
    }
}

int suitable(int potential_edges[], int n) {
    int i, j, flag = 0;
    for (i = 0; i < n; i++) {
        if (potential_edges[i] > 0) {
            flag = 1;
            break;
        }
    }
    if (!flag) return 1;

    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if (potential_edges[i] > 0 && potential_edges[j] > 0 && G[i][j] == 0)
                return 1;
        }
    }
    return 0;
}

int try_creation(int n, int d) {
    int stubs[n*d];
    int potential_edges[n];
    int size = n * d;

    memset(G, 0, sizeof(G));
    int i, j;
    for (i = 0; i < d; i++)
        for (j = 0; j < n; j++)
            stubs[i * n + j] = j;

    int s1, s2;
    while (size > 0) {
        memset(potential_edges, 0, sizeof(potential_edges));
        random_shuffle(stubs, size);
        for (i = 0; i < size; i+=2) {
            s1 = stubs[i]; s2 = stubs[i+1];
            if (s1 != s2 && G[s1][s2] == 0) {
                G[s1][s2] = G[s2][s1] = 1;
            } else {
                potential_edges[s1]++;
                potential_edges[s2]++;
            }
        }

        if (!suitable(potential_edges, n)) return 0;

        size = 0;
        for (i = 0; i < n; i++) {
            for (j = 0; j < potential_edges[i]; j++)
                stubs[size++] = i;
        }
    }
    return 1;
}

// グラフの生成に成功したら1を返す
// 頂点数×次数が偶数でないと正則グラフがつくれないことに注意
int generate_random_graph(int n, int d) {
    if ((n * d) % 2 != 0 || !(0 < d && d < n)) return 0;
    int k = 0;
    while (!try_creation(n, d));
    return 1;
}

int get(int p){
	int sum = 0;
	for(int i = 0; i < c; ++i){
		sum += N[i];
		if(p < sum)return i;
	}
	return -1;
}

int cost[MAX_N];
void dijkstra(int k){
	for (int i = 0; i < n; ++i)cost[i] = INF;
	std::priority_queue < P, std::vector<P>, std::greater<P> > que;
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

void dijkstra_fast(int k){
	for (int i = 0; i < n; ++i)cost[i] = INF;
	std::queue<int> que[10];
	
	cost[k] = 0;
	que[0].push(k);
	
	int r = 0;
	for(int i = 0; i <= r; ++i){
		int m = i % 10;
		while(!que[m].empty()){
			int v = que[m].front();
			que[m].pop();
			if(cost[v] < i)continue;
			for(int k = 0; k < d; ++k){
				int u = g[v][k].first;
				int d = cost[v] + W[get(v)][get(u)];
				if(d < cost[u]){
					cost[u] = d;
					que[d % 10].push(u);
					if(r < d)r = d;
				}
			}
		}
	}
}

int get_ASPL(){
	int ret = 0;
	for(int i = 0; i < n; ++i){
		dijkstra_fast(i);
		for(int j = 0; j < n; ++j){
			ret += cost[j];
		}
	}
	return ret / 2;
}

int main(){
	input();
	
	generate_random_graph(n, d);
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < n; ++j){
			if(G[i][j])g[i].push_back(P(j, W[get(i)][get(j)]));
		}
	}
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < d; ++j){
			//printf("i: %d to: %d cost: %d\n", i, g[i][j].first, g[i][j].second);
		}
	}
	clock_t start = clock();
	printf("%d\n", get_ASPL());
	printf("%ld ms\n", (clock() - start) / 1000);
	
	return 0;
}