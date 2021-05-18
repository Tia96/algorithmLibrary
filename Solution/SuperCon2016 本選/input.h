#include <cstdio>

#define MAX_N 2048
#define MAX_D 16
#define MAX_C 3
#define INF 1000000

int n, d, c;
int N[MAX_C];
int W[MAX_C][MAX_C];

void input(){
	scanf("%d%d%d", &n, &d, &c);
	for(int i = 0; i < c; ++i)scanf("%d", &N[i]);
	for(int i = 0; i < c; ++i){
		for(int j = 0; j < c; ++j)scanf("%d", &W[i][j]);
	}
}