#include <stdlib.h>
#include <stdbool.h>
#include "sc1.h"

#define REP(i, a, b) for(int i = a; i < b; ++i)
#define rep(i, a) REP(i, 0, a)

typedef unsigned long long ll;

ll map[N][N];
ll exist[N * 2 + 2];
ll poss[N * 2 + 2][200];
int possSize[N * 2 + 2];
int lineSum;
ll useNum;
int target, ind;

typedef struct{
	int type, line, ind;
	ll add;
} Diff;

int bitToNum(ll x){
	int k = 1;
	while(x){
		if(x & 1ull)return k;
		x >>= 1;
		++k;
	}
	return 0;
}

bool nextPermutation(ll *array, int size){
	if(!size)return false;
	
	int i = size - 1, j = size - 1;
	ll tmp;
	
	while (i > 0 && array[i - 1] >= array[i])--i;
	if (!i)return false;
	
	while (array[j] <= array[i - 1])--j;
	tmp = array[i - 1];
	array[i - 1] = array[j];
	array[j] = tmp;
	
	j = size - 1;
	while (i < j) {
		tmp = array[i];
		array[i] = array[j];
		array[j] = tmp;
		++i, --j;
	}
	return true;
}

void makeComb(int n, int sum, int prev, ll element){
	if(n == N){
		if(sum == target)poss[ind][possSize[ind]++] = element;
	}
	else {
		REP(i, prev + 1, N * N + 1)if(!((1ull << (i - 1)) & useNum) && sum + i <= target)makeComb(n + 1, sum + i, i, (element | (1ull << (i - 1))));
	}
}

void diffReg(Diff *diff, int *size, int type, int line, int ind, ll add){
	diff[*size].type = type;
	diff[*size].line = line;
	diff[*size].ind = ind;
	diff[*size].add = add;
	++(*size);
}

void simulate(int k){
	if(k == 15){
		int tmp[N][N];
		rep(i, N){
			rep(j, N)tmp[i][j] = bitToNum(map[i][j]);
		}
		
		output(tmp);
		exit(0);
	}
	
	int blankPos[N * 2 + 2][N];
	int blankSize[N * 2 + 2];
	rep(i, N * 2 + 2)blankSize[i] = 0;
	
	rep(i, N){
		rep(j, N){
			if(map[i][j])continue;
			
			blankPos[i][blankSize[i]++] = j;
			blankPos[N + j][blankSize[N + j]++] = i;
			if(i == j)blankPos[N * 2][blankSize[N * 2]++] = j;
			if(i + j == N - 1)blankPos[N * 2 + 1][blankSize[N * 2 + 1]++] = j;
		}
	}
	
	int minI = 0, minP = 100000, minB = 100000;
	rep(i, N * 2 + 2){
		if(!possSize[i])continue;
		if(possSize[i] < minP || (possSize[i] == minP && blankSize[i] < minB))minI = i, minP = possSize[i], minB = blankSize[i];
	}

	for(int i = 0, ii = 0; i < possSize[minI]; ++i, ++ii){
		while(!poss[minI][ii])++ii;
		
		ll element[N];
		int eleSize = 0;
		
		int x, y;
		
		ll tmp = poss[minI][ii];
		while(tmp){
			element[eleSize] = (tmp & -tmp);
			tmp = (tmp & ~element[eleSize]);
			++eleSize;
		}
		
		Diff diff[1000];
		int diffSize = 0;	
		
		do{
			diffSize = 0;
			
			diffReg(diff, &diffSize, 2, minI, 0, possSize[minI]);
			possSize[minI] = 0;
			
			rep(j, blankSize[minI]){
				if(minI < N)x = blankPos[minI][j], y = minI;
				else if(N <= minI && minI < N * 2)x = minI - N, y = blankPos[minI][j];
				else if(minI == N * 2)x = y = blankPos[minI][j];
				else if(minI == N * 2 + 1)x = blankPos[minI][j], y = N - blankPos[minI][j] - 1;
				
				diffReg(diff, &diffSize, 0, y, x, map[y][x]);
				map[y][x] = element[j];
				
				ll isDo = 0;
				isDo |= (1ull << y);
				isDo |= (1ull << (N + x));
				if(x == y)isDo |= (1ull << (N * 2));
				if(x + y == N - 1)isDo |= (1ull << (N * 2 + 1));
				
				rep(p, N * 2 + 2){
					if(!possSize[p])continue;

					int cnt = 0;
					bool f1 = ((isDo >> p) & 1ull), f2;
					
					for(int q = 0, qi = 0; q < possSize[p]; ++q, ++qi){
						while(!poss[p][qi])++qi;
						
						f2 = (poss[p][qi] & element[j]);
						
						if((f1 && !f2) || (!f1 && f2)){
							diffReg(diff, &diffSize, 1, p, qi, poss[p][qi]);
							++cnt;
							poss[p][qi] = 0;
						}
						else if(f1 && f2){
							diffReg(diff, &diffSize, 1, p, qi, poss[p][qi]);
							poss[p][qi] = (poss[p][qi] & ~element[j]);
						}
					}
					diffReg(diff, &diffSize, 2, p, 0, possSize[p]);
					possSize[p] -= cnt;
					if(!possSize[p])goto nextPerm;
				}
			}
			simulate(k + blankSize[minI]);
nextPerm:;
			for(int j = diffSize - 1; j >= 0; --j){
				if(diff[j].type == 0)map[diff[j].line][diff[j].ind] = diff[j].add;
				else if(diff[j].type == 1)poss[diff[j].line][diff[j].ind] = diff[j].add;
				else if(diff[j].type == 2)possSize[diff[j].line] = diff[j].add;
			}
			
		}while(nextPermutation(element, blankSize[minI]));
	}
}

int main(){
	input(s);
	
	lineSum = (1 + N * N) * N / 2;
	
	rep(i, N){
		rep(j, N){
			if(!s[i][j])continue;
			
			ll x = (1ull << (s[i][j] - 1));
			map[i][j] = x;
			useNum |= x;
			exist[i] |= x;
			exist[N + j] |= x;
			if(i == j)exist[N * 2] |= x;
			if(i + j == N - 1)exist[N * 2 + 1] |= x;
		}
	}
	
	rep(i, N * 2 + 2){
		int cnt = 0, sum = 0;
		
		rep(j, N * N)if((exist[i] >> j) & 1ull)++cnt, sum += (j + 1);
		target = lineSum - sum, ind = i;
		makeComb(cnt, 0, 0, 0);
	}
	
	simulate(0);

	return 0;
}
