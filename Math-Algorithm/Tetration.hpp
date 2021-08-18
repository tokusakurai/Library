//テトレーション(mod)
//計算量 O(√M)

//概要
//x^^n := 1(n = 0), x^(x^^(n-1))(n>=1)として再帰的に定義される。
//n>=φ(M)であるとき、x^n ≡ x^(φ(M)+n%φ(M))が成立する。
//演算の結果でM以上になったかのフラグを持っておけばx^nのループに入っているかどうかを確認できる。
//φ(M)>=ceil(log_2(M))であることから、一度フラグが立ったら常に立っているとしていい。
//ただし、x = 0,1は場合分けする必要がある。
//M←φ(M)を2回行うとMは半分以下になることから計算量はO(√M)と評価できる。

//verified with
//https://judge.yosupo.jp/problem/tetration_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Modulo.hpp"

long long modpow(long long x, long long n, const int &m, int &flag){ //答えがm以上になるならflagを立てる
    long long ret = 1;
    for(; n > 0; n >>= 1, x *= x, x %= m){
        if(n&1){
            ret *= x;
            if(ret >= m) flag = 1, ret %= m;
        }
    }
    return ret;
}

long long modtetration(const long long &x, const long long &n, const int &m, int &flag){ //flagが立っていればx^nは周期に入っている(n>=φ(m))
    if(m == 1) return flag = 1;
    if(x == 0) return (n&1? 0 : 1);
    if(x == 1 || n == 0) return 1;
    if(n == 1){
        if(x >= m) flag = 1;
        return x%m+flag*m;
    }
    long long tmp = modtetration(x, n-1, Euler_Totient(m), flag);
    long long ret = modpow(x, tmp, m, flag);
    return ret+flag*m;
}

long long modtetration(const long long &x, const long long &n, const int &m){
    int flag = 0;
    return modtetration(x, n, m, flag)%m;
}
