#pragma once

// 数論変換 (高速剰余変換) (任意 mod)
// 計算量 O((n+m)log(n+m))

// 概要
// mod を p とすると、剰余を取らない場合の畳込みをした結果の各項の最大値は p^2*max(n,m) 程度となる。
// p = 2*10^9、n,m = 10^6 であったとしても、3 種類の NTT-mod (10^9 程度)での畳み込みの結果から復元することができる。
// 具体的な手順は以下の通り。
// x = m1*s1+c1 = m2*s2+c2 = m3*s3+c3 であるとすると、s1 ≡ (c2-c1)/m1 (mod m2) である。この右辺を t1 とする。
// x = m1m2*s+m1*t1+c1 と表されるので、t ≡ (c3-m1*t1-c1)/m1m2 (mod m3) となる。この右辺を t とする。
// 従って、x ≡ m1m2*t+m1*t1+c1 (mod m1m2m3) が得られる。

// verified with
// https://atcoder.jp/contests/practice2/tasks/practice2_f
// https://judge.yosupo.jp/problem/convolution_mod_1000000007

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

const int m1 = 880803841; // 105*2^23 + 1
const int m2 = 897581057; // 107*2^23 + 1
const int m3 = 998244353; // 119*2^23 + 1

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
        if (a.empty() || b.empty()) return {};
        int n = a.size(), m = b.size();
        vector<mint_1> a1(n), b1(m);
        vector<mint_2> a2(n), b2(m);
        vector<mint_3> a3(n), b3(m);
        for (int i = 0; i < n; i++) a1[i] = a[i].x, a2[i] = a[i].x, a3[i] = a[i].x;
        for (int i = 0; i < m; i++) b1[i] = b[i].x, b2[i] = b[i].x, b3[i] = b[i].x;
        vector<mint_1> c1 = NTT_1::convolve(a1, b1);
        vector<mint_2> c2 = NTT_2::convolve(a2, b2);
        vector<mint_3> c3 = NTT_3::convolve(a3, b3);
        const mint_2 m1_inv_m2 = mint_2(m1).inverse();
        const mint_3 m1m2_inv_m3 = (mint_3(m1) * m2).inverse();
        vector<T> c(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            long long t1 = (m1_inv_m2 * (c2[i].x - c1[i].x)).x;
            long long t = (m1m2_inv_m3 * (c3[i].x - t1 * m1 - c1[i].x)).x;
            c[i] = T(t) * m1 * m2 + T(t1) * m1 + c1[i].x;
        }
        return c;
    }
};
