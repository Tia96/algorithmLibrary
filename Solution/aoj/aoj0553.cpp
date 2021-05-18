#include <iostream>
#include <queue>

typedef std::pair<int, int> P;

int n, h, max;
long long ans;
std::priority_queue<P> que;

int main(){
	std::cin >> n >> h;
	max = h;
	
	for(int i = 0; i < n - 1; ++i){
		int a, b;
		std::cin >> a >> b;
		
		int cnt = (max - h + b - 1) / b;
		
		h -= a;
		que.push(P(b, cnt));
		
		while(h <= 0){
			P p = que.top();
			que.pop();
			
			while(p.second == 0){
				p = que.top();
				que.pop();
			}
			
			h = std::min(max, h + p.first);
			
			que.push(P(p.first, p.second - 1));
			
			++ans;
		}
	}
	
	std::cout << ans << std::endl;
	
	return 0;
}