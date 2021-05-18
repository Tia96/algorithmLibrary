//構文解析

#include <iostream>
#include <algorithm>
#include <string>
#include <vector>
#include <functional>
#include <queue>
#include <set>
#include <map>
#include <numeric>
#include <cstdio>
#include <cstring>
#include <cmath>
#include <cctype>

#define rep(i, a) REP(i, 0, a)
#define REP(i, a, b) for(int i = a; i < b; ++i)

typedef long long ll;
typedef unsigned long long ull;
typedef std::pair<int, int> P;
typedef std::pair<P, int> PP;
struct edge{ int to, time, cost; };
const double esp = 1e-9;
const int infi = (int)1e+9 + 10;
const ll infll = (ll)1e+17 + 10;

 
std::string str;
std::string::iterator it;
ll mod;
bool flg = false;
 
ll modPow(ll x, ll y){
    if (y == 0)return 1;
    if (y & 1)return x * modPow(x, y - 1) % mod;
    else return modPow(x * x % mod, y / 2) % mod;
}
 
ll number(){
    ll ret = 0;
    while (isdigit(*it)){
        ret *= 10;
        ret += (*it - '0');
        ++it;
    }
    return ret;
}
 
ll expression();
 
ll factor(){
    ll ret;
    if (*it == '('){
        ++it;
        ret = expression();
        ++it;
        return ret;
    }
    else ret = number();
    return ret;
}
 
ll term(){
    ll ret = factor();
    while (true){
        if (*it == '*'){
            ++it;
            ret = (ret * factor()) % mod;
        }
        else if (*it == '/'){
            ++it;
            ll d = factor();
            if (d == 0){
                flg = true; 
                return 0;
            }
            ret = (ret * modPow(d, mod - 2)) % mod;
        }
        else break;
    }
    return ret;
}
 
ll expression(){
    ll ret = term();
    while (true){
        if (*it == '+'){
            ++it;
            ret = (ret + term()) % mod;
        }
        else if (*it == '-'){
            ++it;
            ret = (ret - term()) % mod;
            ret += (ret < 0 ? mod : 0);
        }
        else break;
    }
    return ret;
}
 
int main(){
    while (true){
        std::getline(std::cin, str);
        if (str == "0:")break;
        while (str.find(' ') != std::string::npos)str.erase(str.find(' '), 1);
        mod = 0;
        flg = false;
        while (isdigit(str[0])){
            mod *= 10;
            mod += (str[0]) - '0';
            str.erase(0, 1);
        }
        str.erase(0, 1);
        str += " = ";
        it = str.begin();
        ll ans = expression();
        if (flg)std::cout << "NG" << std::endl;
        else std::cout << str << ans << " (mod " << mod << ")" << std::endl;
    }
    return 0;
}