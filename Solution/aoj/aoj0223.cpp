#include <iostream>
#include <queue>

typedef std::pair<int, int> P; //(x,y)
typedef std::pair<P, P> PP;
typedef std::pair<PP, int> D;

int x, y;
int map[51][51];
bool visit[51][51][51][51];

int dx[] = {0, 1, 0, -1};
int dy[] = {1, 0, -1, 0};

bool back(P p){
	if(map[p.second][p.first])return true;
	else if(p.second < 0 || p.second >= y || p.first < 0 || p.first >= x)return true;
	else return false;
}

int main(){
	while(true){
		for(int i = 0; i < 51; ++i)for(int j = 0; j < 51; ++j)for(int k = 0; k < 51; ++k)for(int l = 0; l < 51; ++l)visit[i][j][k][l] = false;
		
		std::cin >> x >> y;
		if(x == 0 && y == 0)break;
		
		P t, k;
		std::cin >> t.first >> t.second;
		std::cin >> k.first >> k.second;
		--t.first, --t.second;
		--k.first, --k.second;

		for(int i = 0; i < y; ++i){
			for(int j = 0; j < x; ++j){
				std::cin >> map[i][j];
			}
		}

		bool f = false;

		std::queue<D> que;
		que.push(D(PP(t, k), 0));
		
		visit[t.first][t.second][k.first][k.second] = true;

		while(!que.empty()){
			D d = que.front();
			que.pop();
			
			P ct = d.first.first, ck = d.first.second;
			
			if(d.second >= 100){
				break;
			}
			if(ct == ck){
				f = true;
				std::cout << d.second << std::endl;
				break;
			}
			
			for(int i = 0; i < 4; ++i){
				P nt = ct, nk = ck;
				nt.first += dx[i]; nt.second += dy[i];
				nk.first -= dx[i]; nk.second -= dy[i];
				
				if(back(nt))nt = ct;
				if(back(nk))nk = ck;
				
				if(!visit[nt.first][nt.second][nk.first][nk.second]){
					visit[nt.first][nt.second][nk.first][nk.second] = true;	
					que.push(D(PP(nt, nk), d.second + 1));
				}
			}
		}
		
		if(!f)std::cout << "NA" << std::endl;
	}
	return 0;
}