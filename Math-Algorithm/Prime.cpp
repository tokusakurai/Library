
//素数・約数に関する計算
//計算量 約数列挙・素因数分解・素数判定:O(√N)、エラトステネスの篩:O(N*log(log(N)))

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=jp
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C&lang=jp
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C


#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> divisors(const T &n){
    vector<T> ret;
    for(T i = 1; i*i <= n; i++){
        if(n%i == 0){
            ret.pb(i);
            if(i*i != n) ret.pb(n/i);
        }
    }
    sort(all(ret));
    return ret;
}

template<typename T>
vector<pair<T, int>> prime_factor(T n){
    vector<pair<T, int>> ret;
    for(T i = 2; i*i <= n; i++){
        int cnt = 0;
        while(n%i == 0) cnt++, n /= i;
        if(cnt > 0) ret.emplace_back(i, cnt);
    }
    if(n > 1) ret.emplace_back(n, 1);
    return ret;
}

template<typename T>
bool is_prime(const T &n){
    if(n == 1) return false;
    for(T i = 2; i*i <= n; i++){
        if(n%i == 0) return false;
    }
    return true;
}

vector<bool> Eratosthenes(const int &n){
    vector<bool> ret(n+1, true);
    if(n >= 0) ret[0] = false;
    if(n >= 1) ret[1] = false;
    for(int i = 2; i*i <= n; i++){
        if(!ret[i]) continue;
        for(int j = i+i; j <= n; j += i) ret[j] = false;
    }
    return ret;
}

vector<int> Eratosthenes2(const int &n){ //自身を割り切る最小の素数が記録された配列を返す
    vector<int> ret(n+1);
    iota(begin(ret), end(ret), 0);
    if(n >= 0) ret[0] = -1;
    if(n >= 1) ret[1] = -1;
    for(int i = 2; i*i <= n; i++){
        if(ret[i] < i) continue;
        for(int j = i+i; j <= n; j += i) ret[j] = min(ret[j], i);
    }
    return ret;
}

int main(){
    int T; cin >> T;

    vector<bool> p = Eratosthenes(100000000);

    int ans = 0;
    while(T--){
        int N; cin >> N;
        ans += p[N];
    }
    cout << ans << '\n';
}
