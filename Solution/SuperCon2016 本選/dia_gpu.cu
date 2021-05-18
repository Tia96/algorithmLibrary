#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <sys/time.h>
#include <stdlib.h>
#include <assert.h>

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

__device__ P maxP(P l, P r){
	if(l.dist < r.dist)return r;
	else return l;
}

P maxP_C(P l, P r){
	if(l.dist < r.dist)return r;
	else return l;
}

P graph[MAX_N][16]; //隣接リスト
int graphptr[MAX_N];

#define CUDA_SAFE_CALL(func) \
do { \
    cudaError_t err = (func); \
    if (err != cudaSuccess) { \
        fprintf(stderr, "[Error] %s (error code: %d) at %s line %d\n", cudaGetErrorString(err), err, __FILE__, __LINE__); \
        exit(err); \
    } \
} while(0)

typedef struct {
	int prior;
	P data;
} node_t;

typedef struct {
	node_t* nodes;
	int len;
	int size;
} heap_t;

__device__ node_t* realloc_g(node_t* ptr, int old_size, int new_size) {
	node_t* old = ptr;
	
	ptr = (node_t*)malloc(sizeof(node_t) * new_size);
	
	assert(ptr != NULL);
	if(old_size)
		memcpy(ptr, old, sizeof(node_t) * old_size);
	
	free(old);
	
	return ptr;
}

__device__ heap_t* calloc_g(int size) {
	heap_t* ptr = (heap_t*)malloc(size * sizeof(heap_t));
	
	assert(ptr != NULL);
	memset(ptr, 0, sizeof(heap_t) * size);
	
	return ptr;
}

__device__ void push(heap_t* h, int prior, P data) {
	if (h->len + 1 >= h->size) {
		int old = h->size;
		h->size = h->size ? h->size * 2 : 4;
		h->nodes = realloc_g(h->nodes, old, h->size);
	}
	int i = h->len + 1;
	int j = i / 2;
	
	while(i > 1 && h->nodes[j].prior > prior) {
		h->nodes[i] = h->nodes[j];
		i = j;
		j /= 2;
	}
	
	h->nodes[i].prior = prior;
	h->nodes[i].data = data;
	++h->len;
}

__device__ P pop(heap_t* h) {
	int i, j, k;
	if(!h->len) {
		P p;
		p.to = -1, p.dist = -1;
		return p;
	}
	
	P data = h->nodes[1].data;
	h->nodes[1] = h->nodes[h->len];
	--h->len;
	i = 1;
	
	while(true) {
		k = i;
		j = 2 * i;
		
		if(j <= h->len && h->nodes[j].prior < h->nodes[k].prior)
			k = j;
		
		if (j + 1 <= h->len && h->nodes[j + 1].prior < h->nodes[k].prior)
			k = j + 1;
		
		if(k == i)
			break;
		
		h->nodes[i] = h->nodes[k];
		i = k;
	}
	
	h->nodes[i] = h->nodes[h->len + 1];
	
	return data;
}

__device__ void dijkstra(int k, int *cost, int n, int d, P* graph) {
	heap_t* h = calloc_g(1);
	
	for(int i = 0; i < n; ++i) cost[i] = INF;
	
	cost[k] = 0;
	
	P t;
	
	t.to = k, t.dist = 0;
	push(h, t.dist, t);
	
	while(h->len) {
		P p = pop(h);
		
		int v = p.to;
		if(cost[v] < p.dist)
			continue;
		
		for(int i = 0; i < d; ++i) {
			P e = graph[v * MAX_D + i];
			
			if(cost[e.to] > cost[v] + e.dist) {
				cost[e.to] = cost[v] + e.dist;
				P m;
				m.to = e.to, m.dist = cost[e.to];
				
				push(h, m.dist, m);
			}
		}
	}
	
	free(h);
}

__device__ int AtreeDim(P* ret, P* graph, int n, int d) {
	int* cost = (int*)malloc(sizeof(int) * MAX_N);
	
	assert(cost != NULL);
	
	dijkstra(0, cost, n, d, graph);
	
	int maxV = -INF, maxI;
	for(int i = 0; i < n; ++i) {
		if(cost[i] > maxV) maxV = cost[i], maxI = i;
	}
	
	dijkstra(maxI, cost, n, d, graph);
	
	ret->to = maxI;
	maxV = -INF;
	
	for(int i = 0; i < n; ++i) {
		if(cost[i] > maxV) maxV = cost[i], maxI = i;
	}
	
	ret->dist = maxI;
	
	free(cost);
	
	return maxV;
}

__device__ P dfs(int v, int d, bool* used, P* graph){
	used[v] = true;
	
	P ret;
	ret.to = v; ret.dist = 0;
	for(int i = 0; i < d; ++i){
		int u = graph[v * MAX_D + i].to;
		int w = graph[v * MAX_D + i].dist;
		if(used[u])continue;
		P tmp = dfs(u, d, used, graph);
		P tmp2;
		tmp2.to = tmp.to; tmp2.dist = w + tmp.dist;
		ret = maxP(ret, tmp2);
	}
	return ret;
}

__device__ int treeDim(int n, int d, P* graph, P* ret){
	bool* used = (bool*)malloc(sizeof(bool) * n);
	
	for(int i = 0; i < n; ++i)used[i] = false;
	int v = dfs(0, d, used, graph).to;
	for(int i = 0; i < n; ++i)used[i] = false;
	P p = dfs(v, d, used, graph);
	ret->to = v, ret->dist = p.to;
	
	free(used);
	return p.dist;
}

__device__ int getI(int p, int c, int *N){
	int sum = 0;
	for(int i = 0; i < c; ++i){
		sum += N[i];
		if(p < sum)return i;
	}
	return -1;
}

int getI_C(int p){
	int sum = 0;
	for(int i = 0; i < c; ++i){
		sum += N[i];
		if(p < sum)return i;
	}
	return -1;
}

bool used_C[MAX_N];
P dfs_C(int v){
	used_C[v] = true;
	
	P ret;
	ret.to = v; ret.dist = 0;
	for(int i = 0; i < d; ++i){
		int u = graph[v][i].to;
		int w = graph[u][i].dist;
		if(used_C[u])continue;
		P tmp = dfs_C(u);
		P tmp2;
		tmp2.to = tmp.to; tmp2.dist = w + tmp.dist;
		ret = maxP_C(ret, tmp2);
	}
	return ret;
}

int treeDim_C(P* ret){
	for(int i = 0; i < n; ++i)used_C[i] = false;
	int v = dfs_C(0).to;
	for(int i = 0; i < n; ++i)used_C[i] = false;
	P p = dfs_C(v);
	ret->to = v, ret->dist = p.to;
	return p.dist;
}

__device__ void Gswap(int p, int q, P *graph, int n, int d, int c, int *W, int *N){
	bool* use = (bool*)malloc(sizeof(bool) * n);
	assert(use != NULL);
	memset(use, 0, sizeof(bool) * n);
	
	int* change = (int*)malloc(sizeof(int) * 250);
	assert(change != NULL);
	int chSize = 0;
	
	change[chSize++] = p;
	change[chSize++] = q;
	use[p] = true;
	use[q] = true;
	
	int tmp[MAX_D];
	for(int i = 0; i < d; ++i)tmp[i] = graph[p * MAX_D + i].to;
	
	for(int i = 0; i < d; ++i){
		graph[p * MAX_D + i].to = graph[q * MAX_D + i].to;
		
		for(int j = 0; j < d; ++j){
			int v = graph[p * MAX_D + j].to;
			if(!use[v])change[chSize++] = v, use[v] = true;
		}
	}
	
	for(int i = 0; i < d; ++i){
		graph[q * MAX_D + i].to = tmp[i];
		
		for(int j = 0; j < d; ++j){
			int v = graph[q * MAX_D + j].to;
			if(!use[v])change[chSize++] = v, use[v] = true;
		}	
	}
	
	for(int i = 0; i < d; ++i)graph[p * MAX_D + i].dist = W[getI(p, c, N) * MAX_C + getI(graph[p * d + i].to, c, N)];
	for(int i = 0; i < d; ++i)graph[q * MAX_D + i].dist = W[getI(q, c, N) * MAX_C + getI(graph[q * d + i].to, c, N)];
	
	for(int i = 0; i < chSize; ++i){
		int v = change[i];
		use[v] = false;
		for(int j = 0; j < d; ++j){
			if(graph[v * MAX_D + j].to == p)graph[v * MAX_D + j].to = q, graph[v * MAX_D + j].dist = W[getI(v, c, N) * MAX_C + getI(q, c, N)];
			else if(graph[v * MAX_D + j].to == q)graph[v * MAX_D + j].to = p, graph[v * MAX_D + j].dist = W[getI(v, c, N) * MAX_C + getI(p, c, N)];
		}
	}
	
	free(use);
	free(change);
}

bool use[MAX_N];
int change[100];
void Gswap_C(int p, int q){
	int chSize = 0;
	
	change[chSize++] = p;
	change[chSize++] = q;
	use[p] = true;
	use[q] = true;
	
	int tmp[MAX_D];
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
	
	for(int i = 0; i < d; ++i)graph[p][i].dist = W[getI_C(p)][getI_C(graph[p][i].to)];
	for(int i = 0; i < d; ++i)graph[q][i].dist = W[getI_C(q)][getI_C(graph[q][i].to)];
	
	for(int i = 0; i < chSize; ++i){
		int v = change[i];
		use[v] = false;
		for(int j = 0; j < d; ++j){
			if(graph[v][j].to == p)graph[v][j].to = q, graph[v][j].dist = W[getI_C(v)][getI_C(q)];
			else if(graph[v][j].to == q)graph[v][j].to = p, graph[v][j].dist = W[getI_C(v)][getI_C(p)];
		}
	}
}

int ans[MAX_N * 16];

void debug(void){
	printf("\n");
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < graphptr[i]; ++j){
			printf("CPU:i: %d to: %d dist: %d\n", i, graph[i][j].to, graph[i][j].dist);
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

__global__ void mm_main(int n, int d, int c, int *W, int* N, P v, P* graph, int* minVarr, P* stub){
	int i;
	i = blockIdx.x * blockDim.x + threadIdx.x;
	
	if(i == v.to || i >= n)return;
	
	stub += i * MAX_N * MAX_D;
	memcpy(stub, graph, sizeof(P) * MAX_N * MAX_D);
	
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < d; ++j){
			//printf("i: %d to: %d c:%d\n", i, graph[i * MAX_D + j].to, graph[i * MAX_D + j].dist);
		}
	}
	
	Gswap(v.to, i, stub, n, d, c, W, N);
	
	P m;
	int ret = AtreeDim(&m, stub, n, d);
	//printf("ret %d\n", ret);
	
	minVarr += i;
	*minVarr = ret;
	for(int i = 0; i < n; ++i){
		for(int j = 0; j < d; ++j){
		//	printf("SWAP: i: %d to: %d c:%d\n", i, stub[i * MAX_D + j].to, stub[i * MAX_D + j].dist);
		}
	}
	
	//printf("ret: %d\n", ret);
	
	Gswap(v.to, i, stub, n, d, c, W, N);
}

__global__ void initMinVArr(unsigned int n, int* minVarr) {
	unsigned int x = threadIdx.x + blockIdx.x * blockDim.x;
	
	if(x >= n) {
		return;
	}
	
	minVarr[x] = INF;
}

__global__ void getV(int n, int d, int* minVarr, P* stub) {
	int minV = INF;
	int minVidx = -1;
	
	for(int i = 0; i < n; ++i) {
		if(minV > minVarr[i]) {
			minVidx = i;
			minV = minVarr[i];
		}
	}
	
	P* rstub = stub;
	stub += minVidx * sizeof(P) * MAX_N * MAX_D;
	for(int i = 0; i < n * d; ++i) {
		rstub[i] = stub[i];
	}
	minVarr[0] = minVarr[minVidx];
}

int main(void) {
	input();
	
	int allMin = INF;
	
	const int BigCnt = 1, smallCnt = 1;
	
	//struct timeval t1, t2, t3, t4;
	//int ms = 0, ms2 = 0;
	
	int *WD, *ND;
	P* graphD;
		
	int *minVarr;
	P *stub;
		
	cudaMalloc((void**)&WD, sizeof(int) * MAX_C * MAX_C);
	cudaMalloc((void**)&ND, sizeof(int) * MAX_C);
	cudaMalloc((void**)&graphD, sizeof(P) * MAX_N * MAX_D);
	cudaMalloc((void**)&minVarr, sizeof(int) * BS);
	cudaMalloc((void**)&stub, sizeof(P) * MAX_N * MAX_N * MAX_D);
	
	cudaDeviceSynchronize();
			
	CUDA_SAFE_CALL( cudaGetLastError() );
	
	for(int z = 0; z < BigCnt; ++z){
		for(int i = 0; i < n; ++i)graphptr[i] = 0;
		
		rnd_init(time(NULL) + z * 117);
		
		if (!generate_random_graph(n, d)) {
			printf("Invalid parameter.\n");
			continue;
		}
		
		for (int i = 0; i < n; ++i) {
			for (int j = i + 1; j < n; ++j) {
				if (G[i][j]){
					graph[i][graphptr[i]].to = j;
					graph[i][graphptr[i]++].dist = W[getI_C(i)][getI_C(j)];
					
					graph[j][graphptr[j]].to = i;
					graph[j][graphptr[j]++].dist = W[getI_C(i)][getI_C(j)];
				}
			}
		}
		
		for(int zz = 0; zz < smallCnt; ++zz){
			P v;
			int dim = treeDim_C(&v);
			
			
			cudaMemcpy(WD, W, sizeof(int) * MAX_C * MAX_C, cudaMemcpyHostToDevice);
			cudaMemcpy(ND, N, sizeof(int) * MAX_C, cudaMemcpyHostToDevice);
			cudaMemcpy(graphD, graph, sizeof(P) * MAX_N * MAX_D, cudaMemcpyHostToDevice);
			
			cudaDeviceSynchronize();
			
			CUDA_SAFE_CALL( cudaGetLastError() );
			
			initMinVArr<<<(n + BS - 1) / BS, BS>>>(n, minVarr);
			
			cudaDeviceSynchronize();
			
			CUDA_SAFE_CALL( cudaGetLastError() );
			
			cudaDeviceSynchronize();
			
			CUDA_SAFE_CALL( cudaGetLastError() );
			
			int ss =1;
			
			mm_main<<<1, n>>>(n, d, c, WD, ND, v, graphD, minVarr, stub);
			
			//mm_main<<<1, 1>>>(n, d, c, WD, ND, v, graphD, minVarr, stub);
			
			cudaDeviceSynchronize();
			
			CUDA_SAFE_CALL( cudaGetLastError() );
			
			getV<<<1,1>>>(n, d, minVarr, stub);
			
			P* stubAns = (P*)malloc(sizeof(P) * MAX_N * MAX_D);
			
			cudaMemcpy(stubAns, stub, sizeof(P) * MAX_N * MAX_D, cudaMemcpyDeviceToHost);
			
			int minVAns;
			
			cudaMemcpy(&minVAns, minVarr, sizeof(int), cudaMemcpyDeviceToHost);
			
			if(minVAns < dim){
				for(int i = 0; i < n; ++i){
					for(int j = 0; j < d; ++j){
						graph[i][j] = stubAns[i * MAX_D + j];
					}
				}
			}
			else{
				if(dim < allMin){
					allMin = dim;
					move();
				}
				free(stubAns);
				break;
			}
			free(stubAns);
		}
		if(allMin == INF)move();
	}
	
	for(int i = 0; i < n * d / 2; ++i){
		printf("%d %d\n", ans[i * 2], ans[i * 2 + 1]);
	}
	
	//printf("%d\n", allMin);
	
	return 0;
}
