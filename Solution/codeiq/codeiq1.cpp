#include <iostream>
#include <algorithm>
#include <queue>

struct data{
	int x, y;
	int cnt;
	int dir;
	
	data(int a, int b, int c, int d):x(a),y(b),cnt(c),dir(d){}
};

bool operator < (const data& a, const data& b){
	return a.cnt > b.cnt;
}

int h, w;
char map[65][65];
int visit[65][65];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

int main(){
	std::cin >> h >> w;
	for(int i = 0; i < h; ++i){
		for(int j = 0; j < w; ++j){
			std::cin >> map[i][j];
		}
	}
	
	for(int i = 0; i < 65; ++i){
		for(int j = 0; j < 65; ++j){
			visit[i][j] = 100000;
		}
	}
	
	std::priority_queue<data> que;
	que.push(data(0, 0, 0, 0));
	que.push(data(0, 0, 0, 1));
	que.push(data(0, 0, 0, 2));
	que.push(data(0, 0, 0, 3));
	
	visit[0][0] = 0;
	
	int ans;
	
	while(!que.empty()){
		data d = que.top();
		que.pop(); 
		
		if(d.x == w - 1 && d.y == h - 1){
			ans = d.cnt;
			break;
		}
		
		for(int i = 0; i < 4; ++i){
			int nx = d.x + dx[i], ny = d.y + dy[i];
			int ndir = i, ncnt = d.cnt + (i != d.dir);
			
			if(nx >= 0 && nx < w && ny >= 0 && ny < h && ncnt <= visit[ny][nx] && map[ny][nx] != '#'){
				visit[ny][nx] = ncnt;
				que.push(data(nx, ny, ncnt, ndir));
			}
		}
	}
	
	std::cout << ans << std::endl;
	
	return 0;
}