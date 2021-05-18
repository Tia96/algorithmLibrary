#include <stdio.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

#define MAX_NM 300005
#define MAX(a, b) ((a) > (b) ? (a) : (b))
#define MIN(a, b) ((a) < (b) ? (a) : (b))

int L, n, m;

typedef struct{
	int Pos, Pow, ind;
}P;

int comp(const void *rhs, const void *lhs)
{
	P l = *(P*)rhs;
	P r = *(P*)lhs;

	return (l.Pow - r.Pow == 0 ? l.Pos - r.Pos : l.Pow - r.Pow);
}

P relayB[MAX_NM + 5], relayA[MAX_NM + 5];
P robo[MAX_NM + 5];
P nextRelay[MAX_NM + 5][2], nextRelayS[MAX_NM + 5][2];

int lower_bound(int t){
	int ans = 0;
	int lowid = 0, midid, highid = n;
	while (lowid <= highid) {
		midid = (lowid + highid) / 2;
		if (relayA[midid].Pow == t)ans = midid, highid = midid - 1;

		else if (relayA[midid].Pow < t) {
			lowid = midid + 1;
		}
		else {
			highid = midid - 1;
		}
	}
	return ans;
}

int ptr = 0, ptr2 = 0;
P stack[MAX_NM + 5], stack2[MAX_NM + 5];

void stack_push(P num){
	stack[ptr] = num;
	++ptr;
}

void stack_pop(){
	if (ptr > 0) --ptr;
}

P stack_top(){
	return stack[ptr - 1];
}

int stack_size(){
	return ptr;
}

void stack2_push(P num){
	stack2[ptr2] = num;
	++ptr2;
}

void stack2_pop(){
	if (ptr2 > 0) --ptr2;
}

P stack2_top(){
	return stack2[ptr2 - 1];
}

int stack2_size(){
	return ptr2;
}

int main(){
	scanf("%d %d", &L, &n);

	for (int i = 0; i < n; ++i){
		scanf("%d %d", &relayB[i].Pos, &relayB[i].Pow);
		relayB[i].ind = i;
	}

	scanf("%d", &m);

	for (int i = 0; i < m; ++i){
		scanf("%d %d", &robo[i].Pos, &robo[i].Pow);
	}

	memcpy(relayA, relayB, sizeof(relayA));

	P max = { INT_MAX, -1, -1 }, min = { INT_MIN, -1, -1 };

	for (int i = 0; i < n; ++i){
		while (stack_size() != 0 && stack_top().Pow < relayB[i].Pow) stack_pop();
		while (stack2_size() != 0 && stack2_top().Pow <= relayB[i].Pow)stack2_pop();

		nextRelay[i][0] = (stack_size() != 0 ? stack_top() : min);
		nextRelayS[i][0] = (stack2_size() != 0 ? stack2_top() : min);

		stack_push(relayB[i]);
		stack2_push(relayB[i]);
	}

	while (stack_size() != 0)stack_pop();
	while (stack2_size() != 0)stack2_pop();

	for (int i = n - 1; i >= 0; --i){
		while (stack_size() != 0 && stack_top().Pow < relayB[i].Pow) stack_pop();
		while (stack2_size() != 0 && stack2_top().Pow <= relayB[i].Pow)stack2_pop();

		nextRelay[i][1] = (stack_size() != 0 ? stack_top() : max);
		nextRelayS[i][1] = (stack2_size() != 0 ? stack2_top() : max);

		stack_push(relayB[i]);
		stack2_push(relayB[i]);
	}

	qsort(relayA, n, sizeof(P), comp);

	for (int i = 0; i < m; ++i){
		P *ptr = &relayA[lower_bound(robo[i].Pow)];

		int sum = 0, start = 0, end = 0;
		while (ptr->Pow == robo[i].Pow){
			start = MAX(MAX(0, ptr->Pos - robo[i].Pos), nextRelay[ptr->ind][0].Pos + robo[i].Pos);
			if(nextRelay[i][0].Pow == ptr->Pow)start = MAX(start, end);

			end = MIN(MIN(L, ptr->Pos + robo[i].Pos), nextRelay[ptr->ind][1].Pos - robo[i].Pos);
			if (nextRelay[ptr->ind][1].Pow == ptr->Pow){
				end = MIN(MIN(L, ptr->Pos + robo[i].Pos), nextRelayS[ptr->ind][1].Pos - robo[i].Pos);
			}

			if (end > start) sum += end - start;

			++ptr;
		}

		printf("%d\n", sum);
	}

	return 0;
}
