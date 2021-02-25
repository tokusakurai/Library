
//剰余演算(累乗、オイラーのφ関数、離散対数、位数、原始根)
//計算量 K乗:O(log(K))、オイラーのφ関数・離散対数・位数:O(√M)、原始根:O(log(M))

#include <bits/stdc++.h>
using namespace std;

struct Random_Number_Generator{
    mt19937_64 mt;

    Random_Number_Generator() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}

    int64_t operator () (int64_t l, int64_t r){ //[l,r)で乱数発生
        uniform_int_distribution<int64_t> dist(l, r-1);
        return dist(mt);
    }

    int64_t operator () (int64_t r){  //[0,r)で乱数発生
        return (*this)(0, r);
    }
};

long long modpow(long long x, long long n, const int &m){
    long long ret = 1;
    for(; n > 0; n >>= 1, x *= x, x %= m){
        if(n&1) ret *= x, ret %= m;
    }
    return ret;
}

template<typename T>
T Euler_Totient(T m){ //オイラーのφ関数(xとmが互いに素ならば、x^φ(m)≡1(mod m))
    T ret = m;
    for(T i = 2; i*i <= m; i++){
        if(m%i == 0) ret /= i, ret *= i-1;
        while(m%i == 0) m /= i;
    }
    if(m > 1) ret /= m, ret *= m-1;
    return ret;
}

int modlog(const int &x, long long y, const int &m){ //x^k=y(mod m)となる最小の非負整数k(xとmは互いに素)
    unordered_map<int, int> mp;
    int n = 0; long long now = 1;
    for(; n*n < m; n++){
        if(!mp.count(now)) mp[now] = n;
        now *= x, now %= m;
    }
    now = modpow(now, Euler_Totient(m)-1, m);
    for(int i = 0; i < n; i++){
        if(mp.count(y)) return n*i+mp[y];
        y *= now, y %= m;
    }
    return -1;
}

template<typename T> T order(T x, const T &m){ //x^k=1(mod m)となる最小の正整数k(xとmは互いに素)
    T n = Euler_Totient(m);
    vector<T> ds;
    for(T i = 1; i*i <= n; i++){
        if(n%i == 0) ds.push_back(i), ds.push_back(n/i);
    }
    sort(begin(ds), end(ds));
    for(auto &e: ds){
        if(modpow(x, e, m) == 1) return e;
    }
    return -1;
}

template<typename T> T primitive_root(const T &m){ //素数mの原始根
    vector<T> ds;
    for(T i = 1; i*i <= m-1; i++){
        if((m-1)%i == 0) ds.push_back(i), ds.push_back((m-1)/i);
    }
    sort(begin(ds), end(ds));
    Random_Number_Generator rnd;
    while(true){
        T r = rnd(1, m);
        for(auto &e: ds){
            if(e == m-1) return r;
            if(modpow(r, e, m) == 1) break;
        }
    }
}

int main(){
    int m; cin >> m;

    int k = primitive_root(m);
    cout << k << ' ' << order(k, m) << '\n';
}
