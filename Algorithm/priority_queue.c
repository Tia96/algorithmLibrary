#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define Data int

typedef struct{
	Data data;
	int prior;
}node;

typedef struct{
	node* nodes;
	int arr_sz;  //配列のサイズを示す
	int que_sz;  //次に格納する場所を示す
}priority_queue;

node* my_realloc(node* old_ptr, int old_sz, int new_sz){
	node* new_ptr = (node*)malloc(sizeof(node) * new_sz);
	if(old_sz){
		memcpy(new_ptr, old_ptr, sizeof(node) * old_sz);
		free(old_ptr);
	}
	return new_ptr;
}

void push(priority_queue *q, Data d, int prior){
	if(q->que_sz >= q->arr_sz){
		int new_sz = (q->arr_sz ? q->arr_sz * 2 : 8);
		q->nodes = my_realloc(q->nodes, q->arr_sz, new_sz);
		q->arr_sz = new_sz;
	}
	
	int k = q->que_sz;
	
	while(true){
		if(k == 0)break;
		
		int next = (k - 1) / 2;
		if(q->nodes[next].prior < prior){
			q->nodes[k] = q->nodes[next];
			k = next;
		}
		else break;
	}
	
	q->nodes[k].data = d;
	q->nodes[k].prior = prior;
	
	++q->que_sz;
}

Data pop(priority_queue *q){
	Data ret = q->nodes[0].data;
	
	q->nodes[0] = q->nodes[--q->que_sz];
	
	int k = 0;
	while(true){
		int l = k * 2 + 1, r = k * 2 + 2;
		int next = -1;
		
		if(l < q->que_sz)next = l;
		if(r < q->que_sz)next = (q->nodes[r].prior > q->nodes[l].prior ? r : l);
		
		if(next == -1)break;
		
		if(q->nodes[next].prior > q->nodes[k].prior){
			q->nodes[k] = q->nodes[next];
			k = next;
		}
		else break;
	}
	
	q->nodes[k] = q->nodes[q->que_sz];
	
	return ret;
}

int main(void){
	priority_queue que = {0};

	push(&que, 100, 3);
	push(&que, 10, 2);
	push(&que, 1, 1);
	
	for(int i = 0; i < que.que_sz; ++i){
		//printf("%d\n", que.nodes[i].data);
	}
	
	while(que.que_sz){
		printf("%d\n", pop(&que));
	}

	return 0;
}