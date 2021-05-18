#include <stdio.h>
#include <stdlib.h>

#define MAX_N 100000
#define INF 1000000000

typedef struct {
	int to, dist;
}P;

P graph[MAX_N][16];
int graphptr[MAX_N];

int n;

//ƒq[ƒv
typedef struct {
	int prior;
	P data;
} node_t;

typedef struct {
	node_t *nodes;
	int len;
	int size;
} heap_t;

void push(heap_t *h, int prior, P data) {
	if (h->len + 1 >= h->size) {
		h->size = h->size ? h->size * 2 : 4;
		h->nodes = (node_t*)realloc(h->nodes, h->size * sizeof(node_t));
	}
	int i = h->len + 1;
	int j = i / 2;
	while (i > 1 && h->nodes[j].prior > prior) {
		h->nodes[i] = h->nodes[j];
		i = j;
		j /= 2;
	}
	h->nodes[i].prior = prior;
	h->nodes[i].data = data;
	h->len++;
}

P pop(heap_t *h) {
	int i, j, k;
	if (!h->len) {
		P p;
		p.to = -1; p.dist = -1;
		return p;
	}
	P data = h->nodes[1].data;
	h->nodes[1] = h->nodes[h->len];
	h->len--;
	i = 1;
	while (true) {
		k = i;
		j = 2 * i;
		if (j <= h->len && h->nodes[j].prior < h->nodes[k].prior) k = j;
		if (j + 1 <= h->len && h->nodes[j + 1].prior < h->nodes[k].prior)k = j + 1;
		if (k == i)break;
		h->nodes[i] = h->nodes[k];
		i = k;
	}
	h->nodes[i] = h->nodes[h->len + 1];
	return data;
}

int cost[MAX_N];

void dijkstra(int k) {
	heap_t *h = (heap_t*)calloc(1, sizeof(heap_t));
	for (int i = 0; i < n; ++i)cost[i] = INF;
	cost[k] = 0;
	P t;
	t.to = k, t.dist = 0;
	push(h, t.dist, t);
	while (h->len) {
		P p = pop(h);
		int v = p.to;
		if (cost[v] < p.dist)continue;
		for (int i = 0; i < graphptr[v]; ++i) {
			P e = graph[v][i];
			if (cost[e.to] > cost[v] + e.dist) {
				cost[e.to] = cost[v] + e.dist;
				P m;
				m.to = e.to; m.dist = cost[e.to];
				push(h, m.dist, m);
			}
		}
	}
}

//ƒOƒ‰ƒt‚Ì’¼Œa
int treeDim(P *ret) {
	dijkstra(0);

	int maxV = -INF, maxI;
	for (int i = 0; i < n; ++i) {
		if (cost[i] > maxV)maxV = cost[i], maxI = i;
	}

	dijkstra(maxI);

	ret->to = maxI;

	maxV = -INF, maxI;
	for (int i = 0; i < n; ++i) {
		if (cost[i] > maxV)maxV = cost[i], maxI = i;
	}

	ret->dist = maxI;
	return maxV;
}

int main(void) {
	scanf("%d", &n);
	for (int i = 0; i < n - 1; ++i) {
		int a, b, c;
		scanf("%d%d%d", &a, &b, &c);

		graph[a][graphptr[a]].to = b;
		graph[a][graphptr[a]++].dist = c;

		graph[b][graphptr[b]].to = a;
		graph[b][graphptr[b]++].dist = c;
	}

	P p;
	printf("%d\n", treeDim_C(&p));

	return 0;
}
