//Dice

class Dice{
public:
	//(front,back,up,down,right,left) = (1,3,5,0,2,4)
	int dat[6];

	void front(){
		int tmp = dat[0];
		dat[0] = dat[1];
		dat[1] = dat[5];
		dat[5] = dat[3];
		dat[3] = tmp;
	}
	void back(){
		int tmp = dat[0];
		dat[0] = dat[3];
		dat[3] = dat[5];
		dat[5] = dat[1];
		dat[1] = tmp;
	}
	void right(){
		int tmp = dat[0];
		dat[0] = dat[2];
		dat[2] = dat[5];
		dat[5] = dat[4];
		dat[4] = tmp;
	}
	void left(){
		int tmp = dat[0];
		dat[0] = dat[4];
		dat[4] = dat[5];
		dat[5] = dat[2];
		dat[2] = tmp;
	}
};

int n;
Dice d[101];

void init(int p, int q){
	rep(i, 7){
		if (d[p].dat[1] == d[q].dat[1])return;
		d[q].front();
	}
	d[q].right();
	rep(i, 7){
		if (d[p].dat[1] == d[q].dat[1])return;
		d[q].front();
	}
}

void init2(int p, int q){
	rep(i, 7){
		if (d[p].dat[0] == d[q].dat[0])return;
		d[q].right();
	}
}

int main(){
	std::cin >> n;
	rep(i, n)std::cin >> d[i].dat[5] >> d[i].dat[1] >> d[i].dat[2] >> d[i].dat[4] >> d[i].dat[3] >> d[i].dat[0];
	bool ans = true;
	rep(i, n - 1){
		REP(j, i + 1, n)init(i, j), init2(i, j);
		REP(j, i + 1, n){
			bool f = true;
			REP(k, 3, 6)if (d[i].dat[k] != d[j].dat[k])f = false;
			if (f)ans = false;
		}
		std::cout << 7 << std::endl;
	}

	if (ans)std::cout << "Yes" << std::endl;
	else std::cout << "No" << std::endl;
	return 0;
}