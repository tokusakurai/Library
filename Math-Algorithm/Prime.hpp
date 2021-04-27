
//素数・約数に関する計算
//計算量 約数列挙・素因数分解・素数判定 : O(√N)、1,2,...,nのうちkと互いに素な自然数の数え上げ : O(2^|(kの素因数)|) エラトステネスの篩 : O(N*log(log(N)))

//概要
//約数列挙・素因数分解・素数判定 : 自然数Nの素因数で√Nより大きいものは高々1つなので、√N以下の数全てについて割り切れるか調べる。
//1,2,...,nのうちkと互いに素な自然数の数え上げ : 約数包除
//エラトステネスの篩 : 前から順番に見て、注目している数が素数ならその数の倍数(その数は含めない)は全て素数ではないことになるので、テーブルをfalseに切り替える。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=NTL_1_A&lang=jp
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C&lang=jp
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_1_C

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
vector<T> divisors(const T &n){
    vector<T> ret;
    for(T i = 1; i*i <= n; i++){
        if(n%i == 0){
            ret.push_back(i);
            if(i*i != n) ret.push_back(n/i);
        }
    }
    sort(begin(ret), end(ret));
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

//1,2,...,nのうちkと互いに素である自然数の個数
template<typename T>
T coprime(T n, T k){
    vector<pair<T, int>> ps = prime_factor(k);
    int m = ps.size();
    T ret = 0;
    for(int i = 0; i < (1<<m); i++){
        T prd = 1;
        for(int j = 0; j < m; j++){
            if((i>>j)&1) prd *= ps[j].first;
        }
        ret += (__builtin_parity(i)? -1 : 1)*(n/prd);
    }
    return ret;
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

vector<int> Eratosthenes2(const int &n){
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
