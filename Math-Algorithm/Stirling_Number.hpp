
//スターリング数のテーブル
//計算量 第1種スターリング数・第2種スターリング数 : O(N*log(N))

//第1種スターリング数 : x(x-1)(x-2)....(x-N+1) の各項の係数のテーブル
//第2種スターリング数 : x^N = Σs(N,K)x(x-1)(x-2)...(x-K+1) を満たすS(N,0),S(N,1),...,S(N,N)のテーブル

//概要
//第1種スターリング数 : x(x-1)...(x-M+1)が求まっているとき、(x-M)(x-M-1)...(x-2*M+1)をNTTで高速に求められる。
//第2種スターリング数 : 包除原理で得られる式を用いてNTTで高速化する。

//verified with
//https://judge.yosupo.jp/problem/stirling_number_of_the_first_kind
//https://judge.yosupo.jp/problem/stirling_number_of_the_second_kind

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/NTT.hpp"

using mint = Mod_Int<998244353>;
Number_Theorem_Transform<998244353, 3> NTT;

vector<mint> first_stirling_number(int n){
    if(n == 0) return {1};
    vector<mint> fac(n+1), ifac(n+1);
    fac[0] = 1;
    for(int i = 1; i <= n; i++) fac[i] = fac[i-1]*i;
    ifac[n] = fac[n].inverse();
    for(int i = n; i >= 1; i--) ifac[i-1] = ifac[i]*i;
    int k = 31-__builtin_clz(n);
    vector<mint> f = {0, 1};
    for(int i = k-1; i >= 0; i--){
        int m = f.size()-1;
        vector<mint> g(m+1);
        mint pw = 1;
        for(int j = 0; j <= m; j++){
            g[m-j] = pw*ifac[j]*(j&1? -1 : 1);
            pw *= m; 
        }
        for(int j = 0; j <= m; j++) f[j] *= fac[j];
        vector<mint> h = NTT.convolve(f, g);
        for(int j = 0; j <= m; j++) f[j] *= ifac[j];
        for(int j = 0; j <= m; j++) h[j] = h[j+m]*ifac[j];
        h.resize(m+1);
        f = NTT.convolve(f, h);
        if((n>>i)&1){
            f.push_back(0);
            for(int j = 2*m; j >= 0; j--){
                f[j+1] += f[j];
                f[j] *= -2*m;
            }
        }
    }
    return f;
}

vector<mint> second_stirling_number(int n){
    vector<mint> ifac(n+1);
    ifac[n] = 1;
    for(int i = 1; i <= n; i++) ifac[n] *= i;
    ifac[n] = ifac[n].inverse();
    for(int i = n; i >= 1; i--) ifac[i-1] = ifac[i]*i;
    vector<mint> f(n+1), g(n+1);
    for(int i = 0; i <= n; i++){
        f[i] = mint(i).pow(n)*ifac[i];
        g[i] = ifac[i]*(i&1? -1 : 1);
    }
    f = NTT.convolve(f, g);
    return vector<mint>(begin(f), begin(f)+n+1);
}
