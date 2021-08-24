
//剰余演算(累乗、オイラーのφ関数、離散対数、位数、原始根)
//計算量 K乗 : O(log(K))、離散対数 : (O√M+log(M))、オイラーのφ関数・位数 : O(√M)、原始根 : O(φ(M-1)*log(M))

//概要
//累乗 : ダブリング
//オイラーのφ関数 : Mの素因数を全て列挙し、M以下の自然数のうちMと互いに素なものの割合を考える。
//離散対数 : Baby-step Giant-step
//位数 : φ(M)の約数を全て考える。
//原始根 : 乱数で発生させて、その位数がM-1であるかどうか判定する。原始根は最低でもφ(M-1)個存在する。

//verified with
//https://judge.yosupo.jp/problem/discrete_logarithm_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Other/Random.hpp"

long long modpow(long long x, long long n, const int &m){
    long long ret = 1;
    for(; n > 0; n >>= 1, x *= x, x %= m){
        if(n&1) ret *= x, ret %= m;
    }
    return ret;
}

template<typename T>
T modinv(T a, const T &m){
    T b = m, u = 1, v = 0;
    while(b > 0){
        T t = a/b;
        swap(a -= t*b, b);
        swap(u -= t*v, v);
    }
    return u >= 0 ? u%m : (m-(-u)%m)%m;
}

template<typename T>
T Euler_totient(T m){ //オイラーのφ関数(xとmが互いに素ならば、x^φ(m) ≡ 1(mod m))
    T ret = m;
    for(T i = 2; i*i <= m; i++){
        if(m%i == 0) ret /= i, ret *= i-1;
        while(m%i == 0) m /= i;
    }
    if(m > 1) ret /= m, ret *= m-1;
    return ret;
}

int modlog(int x, int y, int m){ //x^k ≡ y(mod m)となる最小の非負整数k(存在しなければ-1)
    long long g = 1;
    for(int i = m; i > 0; i >>= 1) g *= x, g %= m;
    g = gcd(g, m);
    int c = 0;
    long long t = 1;
    for(; t%g != 0; c++){
        if(t == y) return c;
        t *= x, t %= m;
    }
    if(y%g != 0) return -1;
    t /= g, y /= g, m /= g;
    int n = 0;
    long long gs = 1;
    for(; n*n < m; n++) gs *= x, gs %= m;
    unordered_map<int, int> mp;
    long long e = y;
    for(int i = 0; i < n; mp[e] = ++i) e *= x, e %= m;
    e = t;
    for(int i = 0; i < n; i++){
        e *= gs, e %= m;
        if(mp.count(e)) return c+n*(i+1)-mp[e];
    }
    return -1;
}

template<typename T> T order(T x, const T &m){ //x^k ≡ 1(mod m)となる最小の正整数k(xとmは互いに素)
    T n = Euler_totient(m);
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
    Random_Number_Generator rng;
    while(true){
        T r = rng(1, m);
        for(auto &e: ds){
            if(e == m-1) return r;
            if(modpow(r, e, m) == 1) break;
        }
    }
}
