//Suffix Array
//O(m log n)
const int max = 1000005;

std::string text;
int textSize, k = 1;
int rank[max + 1], tmp[max + 1], sa[max + 1];

bool compare_sa(int i, int j){
	if (rank[i] != rank[j])return rank[i] < rank[j];
	else {
		int ri = (i + k <= textSize ? rank[i + k] : -1);
		int rj = (j + k <= textSize ? rank[j + k] : -1);
		return ri < rj;
	}
}

void construct_sa(){
	textSize = text.size();
	rep(i, textSize + 1){
		sa[i] = i;
		rank[i] = (i < textSize ? text[i] : -1);
	}

	for (; k <= textSize; k *= 2){
		std::sort(sa, sa + textSize + 1, compare_sa);

		tmp[sa[0]] = 0;
		REP(j, 1, textSize + 1)tmp[sa[j]] = tmp[sa[j - 1]] + (compare_sa(sa[j - 1], sa[j]) ? 1 : 0);
		rep(j, textSize + 1)rank[j] = tmp[j];
	}
}

bool find(std::string t){
	int l = 0, r = text.size();
	while (l <= r){
		int m = (l + r) / 2;
		if (text.compare(sa[m], t.size(), t) < 0)l = m + 1;
		else r = m - 1;
	}
	return (text.compare(sa[r + 1], t.size(), t) == 0);
}

int n;

int main(){
	std::cin >> text >> n;
	construct_sa();
	rep(i, n){
		char str[1005];
		scanf("%s", &str);
		printf("%d\n", (find(str) ? 1 : 0));
	}

	return 0;
}

//RollingHash
//O(n + m)
class RollingHash{
private:
	static const ull B = (ull)1e+8 + 7;

	std::string text;
	int texSize;
	std::vector<ull> pow, phash;

	inline ull TextHash(int s, int e){
		return phash[e] - phash[s] * pow[e - s];
	}

public:
	RollingHash(std::string tex) :text(tex), texSize(text.size()), pow(texSize + 1), phash(texSize + 1){
		pow[0] = 1;
		phash[0] = 0;
		rep(i, texSize){
			phash[i + 1] = phash[i] * B + text[i];
			pow[i + 1] = pow[i] * B;
		}
	}

	void find(std::string pat){
		int patSize = pat.size();
		if (patSize > texSize)return;

		ull patHash = 0;
		rep(i, patSize)patHash = patHash * B + pat[i];

		rep(i, texSize - patSize + 1){
			if (TextHash(i, i + patSize) == patHash)printf("%d\n", i);
		}

	}
};

//BM–@
//Åˆ«O(nm) •½‹ÏO(n / m)
class BM{
public:
	//pattern‚ªtext‚ÉŠÜ‚Ü‚ê‚Ä‚¢‚é‚©
	std::string text, pattern;
	BM(std::string tex, std::string pat) : text(tex), pattern(pat){}

	int skip[256];

	void find(){
		int patSize = pattern.size();

		rep(i, 256)skip[i] = patSize;
		rep(i, patSize)skip[pattern[i]] = (patSize - i - 1);

		int i = patSize - 1;
		while (i < text.size()){
			int check = 0;
			while (check < patSize && text[i - check] == pattern[patSize - check - 1])++check;
			if (check == patSize){
				printf("%d\n", i - patSize + 1);
				++i;
			}
			else i = std::max(i + 1, i - check + skip[text[i - check]]);
		}
	}
};