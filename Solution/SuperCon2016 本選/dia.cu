#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>

#include "input.h"

unsigned long seed[4];

int G[MAX_N][MAX_N]; //隣接グラフ

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

int generate_random_graph(int n, int d) {
    if ((n * d) % 2 != 0 || !(0 < d && d < n)) return 0;
    while (!try_creation(n, d));
    return 1;
}

typedef struct{
	int to, dist;
}P;

P maxP(P l, P r){
	if(l.dist < r.dist)return r;
	else return l;
}

P graph[MAX_N][16]; //隣接リスト
int graphptr[MAX_N];

bool used[MAX_N];
P dfs(int v){
	used[v] = true;
	
	P ret;
	ret.to = v; ret.dist = 0;
	for(int i = 0; i < d; ++i){
		int u = graph[v][i].to;
		int w = graph[u][i].dist;
		if(used[u])continue;
		P tmp = dfs(u);
		P tmp2;
		tmp2.to = tmp.to; tmp2.dist = w + tmp.dist;
		ret = maxP(ret, tmp2);
	}
	return ret;
}

int treeDim(P* ret){
	for(int i = 0; i < n; ++i)used[i] = false;
	int v = dfs(0).to;
	for(int i = 0; i < n; ++i)used[i] = false;
	P p = dfs(v);
	ret->to = v, ret->dist = p.to;
	return p.dist;
}

int getI(int p){
	int sum = 0;
	for(int i = 0; i < c; ++i){
		sum += N[i];
		if(p < sum)return i;
	}
	return -1;
}

bool use[MAX_N];
int change[200];
void Gswap(int p, int q){
	int chSize = 0;
	
	change[chSize++] = p;
	change[chSize++] = q;
	use[p] = true;
	use[q] = true;
	
	int tmp[16];
	for(int i = 0; i < d; ++i)tmp[i] = graph[p][i].to;
	
	for(int i = 0; i < d; ++i){
		graph[p][i].to = graph[q][i].to;
		
		for(int j = 0; j < d; ++j){
			int v = graph[p][i].to;
			if(!use[v])change[chSize++] = v, use[v] = true;
		}
	}
	for(int i = 0; i < d; ++i){
		graph[q][i].to = tmp[i];
		
		for(int j = 0; j < d; ++j){
			int v = graph[q][i].to;
			if(!use[v])change[chSize++] = v, use[v] = true;
		}
	}
	
	for(int i = 0; i < d; ++i)graph[p][i].dist = W[getI(p)][getI(graph[p][i].to)];
	for(int i = 0; i < d; ++i)graph[q][i].dist = W[getI(q)][getI(graph[q][i].to)];
	
	for(int i = 0; i < chSize; ++i){
		int v = change[i];
		use[v] = false;
		for(int j = 0; j < d; ++j){
			if(graph[v][j].to == p)graph[v][j].to = q, graph[v][j].dist = W[getI(v)][getI(q)];
			else if(graph[v][j].to == q)graph[v][j].to = p, graph[v][j].dist = W[getI(v)][getI(p)];
		}
	}
}

int ans[MAX_N * 16];

void debug(void){
	printf("\n");
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < graphptr[i]; ++j){
			printf("i: %d to: %d dist: %d\n", i, graph[i][j].to, graph[i][j].dist);
		}
	}
	printf("\n");
}

void move(void){
	int ansSize = 0;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < d; ++j){
				if(graph[i][j].to > i){
				ans[ansSize++] = i;
				ans[ansSize++] = graph[i][j].to;
			}
		}
	}
}

int get_elapsed_time(struct timeval *begin, struct timeval *end)
{
	return (end->tv_sec - begin->tv_sec) * 1000
	+ (end->tv_usec - begin->tv_usec) / 1000;
}

int main(void) {
	input();
	
	int allMin = INF;
	
	const int BigCnt = 2, smallCnt = 1;
		
	for(int z = 0; z < BigCnt; ++z){
		for(int i = 0; i < n; ++i)graphptr[i] = 0;
		
		rnd_init(time(NULL) + 117 * z);
		
		if (!generate_random_graph(n, d)) {
			printf("Invalid parameter.\n");
			break;
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (G[i][j]){
					graph[i][graphptr[i]].to = j;
					graph[i][graphptr[i]++].dist = W[getI(i)][getI(j)];
					
					graph[j][graphptr[j]].to = i;
					graph[j][graphptr[j]++].dist = W[getI(i)][getI(j)];
				}
			}
		}
		
		for(int zz = 0; zz < smallCnt; ++zz){
			P v;
			int dim = treeDim(&v);
			
			int minV = INF, minI;
			
			for(int i = 0; i < n; ++i){
				if(i == v.to)continue;
				
				Gswap(v.to, i);
				P m;
				
				int ret = treeDim(&m);
				
				if(ret < minV)minV = ret, minI = i;
				Gswap(v.to, i);
			}
			
			if(minV < dim)Gswap(v.to, minI);
			else{
				if(dim < allMin){
					allMin = dim;
					move();
				}
				break;
			}
		}
		if(allMin == INF)move();
	}
	
	for(int i = 0; i < n * d / 2; ++i){
		printf("%d %d\n", ans[i * 2], ans[i * 2 + 1]);
	}
	
	return 0;
}
