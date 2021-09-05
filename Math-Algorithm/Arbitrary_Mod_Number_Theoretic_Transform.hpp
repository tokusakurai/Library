
// 数論変換(高速剰余変換)(任意mod)
// 計算量 O((N+M)*log(N+M))

// 概要
// modをPとすると、剰余を取らない場合の畳込みをした結果の各項の最大値はP^2*max(N,M)程度となる。
// P<=2*10^9、N,M<=10^6であったとしても、3種類のNTTmod(10^9程度)での畳み込みの結果から復元することができる。

// verified with
// https://atcoder.jp/contests/practice2/tasks/practice2_f
// https://judge.yosupo.jp/problem/convolution_mod_1000000007

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

// NTT素数たち
const int m1 = 1045430273;
const int m2 = 1051721729;
const int m3 = 1053818881;

template <typename T>
struct Arbitrary_Mod_Number_Theoretic_Transform {
    using mint_1 = Mod_Int<m1>;
    using mint_2 = Mod_Int<m2>;
    using mint_3 = Mod_Int<m3>;
    using NTT_1 = Number_Theoretic_Transform<mint_1>;
    using NTT_2 = Number_Theoretic_Transform<mint_2>;
    using NTT_3 = Number_Theoretic_Transform<mint_3>;

    Arbitrary_Mod_Number_Theoretic_Transform() {}

    static vector<T> convolve(const vector<T> &a, const vector<T> &b) {
        int n = a.size(), m = b.size();
        vector<mint_1> a1(n), b1(m);
        vector<mint_2> a2(n), b2(m);
        vector<mint_3> a3(n), b3(m);
        for (int i = 0; i < n; i++) a1[i] = a[i].x, a2[i] = a[i].x, a3[i] = a[i].x;
        for (int i = 0; i < m; i++) b1[i] = b[i].x, b2[i] = b[i].x, b3[i] = b[i].x;
        auto x = NTT_1::convolve(a1, b1);
        auto y = NTT_2::convolve(a2, b2);
        auto z = NTT_3::convolve(a3, b3);
        const auto m1_inv_m2 = mint_2(m1).inverse().x;
        const auto m1m2_inv_m3 = (mint_3(m1) * m2).inverse().x;
        const auto m1m2_mod = (mint(m1) * m2).x;
        vector<T> ret(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            auto v1 = ((mint_2(y[i]) + m2 - x[i].x) * m1_inv_m2).x;
            auto v2 = ((z[i] + m3 - x[i].x - mint_3(m1) * v1) * m1m2_inv_m3).x;
            ret[i] = (T(x[i].x)) + T(m1) * v1 + T(m1m2_mod) * v2;
        }
        return ret;
    }
};
