/**
 * https://github.com/networkx/networkx/blob/master/networkx/generators/random_graphs.py
 * random_regular_graph をC言語に直したもの
 *
 * n: 頂点数, d: 次数
 * generate_random_graph(n, d) を呼ぶとグローバルに宣言されている配列G[][]が
 * 隣接行列となる
 *
 * a-b に辺があるとき G[a][b] = 1
 * a-b に辺がないとき G[a][b] = 0
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

#define MAX_N 2048
int G[MAX_N][MAX_N];

unsigned long xor128(void) {
    // x, y, z, w が乱数のシード
    static unsigned long x=123456789,y=362436069,z=521288629,w=88675123;
    unsigned long t;
    t=(x^(x<<11));x=y;y=z;z=w; return( w=(w^(w>>19))^(t^(t>>8)) );
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

/******************ここより上をコピーして使用*******************/

int main() {
    int n, d;
    scanf("%d%d", &n, &d);
    if (!generate_random_graph(n, d)) {
        printf("Invalid parameter.\n");
        return 1;
    }

    int i, j;
    for (i = 0; i < n; i++) {
        for (j = i+1; j < n; j++) {
            if (G[i][j])
                printf("%d %d\n", i, j);
        }
    }
    return 0;
}
