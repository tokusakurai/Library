
//数論変換(高速剰余変換)(任意mod)
//計算量 O((N+M)*log(N+M))

//概要
//modをPとすると、剰余を取らない場合の畳込みをした結果の各項の最大値はP^2*max(N,M)程度となる。
//P<=2*10^9、N,M<=10^6であったとしても、3種類のNTTmod(10^9程度)での畳み込みの結果から復元することができる。

//verified with
//https://atcoder.jp/contests/practice2/tasks/practice2_f
//https://judge.yosupo.jp/problem/convolution_mod_1000000007

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/NTT.hpp"

//(NTT素数、原始根)
const int m1 = 1045430273, r1 = 3;
const int m2 = 1051721729, r2 = 6;
const int m3 = 1053818881, r3 = 7;

template<int mod>
struct Arbitary_Mod_Number_Theorem_Transform{
    using T = Mod_Int<mod>;
    using mint1 = Mod_Int<m1>;
    using mint2 = Mod_Int<m2>;
    using mint3 = Mod_Int<m3>;
    Number_Theorem_Transform<m1, r1> ntt1;
    Number_Theorem_Transform<m2, r2> ntt2;
    Number_Theorem_Transform<m3, r3> ntt3;

    Arbitary_Mod_Number_Theorem_Transform() {}

    vector<T> convolve(const vector<T> &a, const vector<T> &b){
        int n = a.size(), m = b.size();
        vector<mint1> a1(n), b1(m);
        vector<mint2> a2(n), b2(m);
        vector<mint3> a3(n), b3(m);
        for(int i = 0; i < n; i++) a1[i] = a[i].x, a2[i] = a[i].x, a3[i] = a[i].x;
        for(int i = 0; i < m; i++) b1[i] = b[i].x, b2[i] = b[i].x, b3[i] = b[i].x;
        auto x = ntt1.convolve(a1, b1);
        auto y = ntt2.convolve(a2, b2);
        auto z = ntt3.convolve(a3, b3);
        const auto m1_inv_m2 = mint2(m1).inverse().x;
        const auto m1m2_inv_m3 = (mint3(m1)*m2).inverse().x;
        const auto m1m2_mod = (mint(m1)*m2).x;
        vector<T> ret(n+m-1);
        for(int i = 0; i < n+m-1; i++){
            auto v1 = ((mint2(y[i])+m2-x[i].x)*m1_inv_m2).x;
            auto v2 = ((z[i]+m3-x[i].x-mint3(m1)*v1)*m1m2_inv_m3).x;
            ret[i] = (T(x[i].x))+T(m1)*v1+T(m1m2_mod)*v2;
        }
        return ret;
    }
};
