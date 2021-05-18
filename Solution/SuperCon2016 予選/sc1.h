#include<stdio.h>
#include<time.h>
#define N 6

int s[N][N];
clock_t starttime,endtime;
void input(int s[][N]){
	int i,j;	
	for(i=0;i<N;++i){for(j=0;j<N;++j){scanf("%d",&s[i][j]);}}
	starttime=clock();
}
void output(int s[][N]){
	int i,j;
	endtime=clock();
	for(i=0;i<N;++i){for(j=0;j<N;++j){printf(" %3d",s[i][j]);}}
	printf(" %d\n",(int)(endtime-starttime));
}
