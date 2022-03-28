
// 高速フーリエ変換（64 ビット符号付き整数）
// 計算量 O((n+m)log(n+m))

// 概要
// 畳み込んだ結果が 64 ビット符号付き整数に収まるならば、10^9 程度の 3 種類の NTT-mod（10^9 程度）での畳み込みの結果から一意に復元することができる。

// verified with
// https://atcoder.jp/contests/atc001/tasks/fft_c
// https://atcoder.jp/contests/utpc2021/tasks/utpc2021_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

const int m1 = 880803841; // 105*2^23 + 1
const int m2 = 897581057; // 107*2^23 + 1
const int m3 = 998244353; // 119*2^23 + 1

struct Fast_Fourier_Transform_Integer {
    using mint_1 = Mod_Int<m1>;
    using mint_2 = Mod_Int<m2>;
    using mint_3 = Mod_Int<m3>;
    using NTT_1 = Number_Theoretic_Transform<mint_1>;
    using NTT_2 = Number_Theoretic_Transform<mint_2>;
    using NTT_3 = Number_Theoretic_Transform<mint_3>;

    Fast_Fourier_Transform_Integer() {}

    static vector<long long> convolve(const vector<long long> &a, const vector<long long> &b) {
        if (a.empty() || b.empty()) return {};
        int n = a.size(), m = b.size();
        vector<mint_1> a1(n), b1(m);
        vector<mint_2> a2(n), b2(m);
        vector<mint_3> a3(n), b3(m);
        for (int i = 0; i < n; i++) a1[i] = a[i], a2[i] = a[i], a3[i] = a[i];
        for (int i = 0; i < m; i++) b1[i] = b[i], b2[i] = b[i], b3[i] = b[i];
        vector<mint_1> c1 = NTT_1::convolve(a1, b1);
        vector<mint_2> c2 = NTT_2::convolve(a2, b2);
        vector<mint_3> c3 = NTT_3::convolve(a3, b3);
        mint_2 m1_inv_m2 = mint_2(m1).inverse();
        mint_3 m1m2_inv_m3 = (mint_3(m1) * m2).inverse();
        vector<long long> c(n + m - 1);
        for (int i = 0; i < n + m - 1; i++) {
            long long t1 = (m1_inv_m2 * (c2[i].x - c1[i].x)).x;
            long long t = (m1m2_inv_m3 * (c3[i].x - t1 * m1 - c1[i].x)).x;
            if (t > m3 - t) t -= m3;
            c[i] = t * m1 * m2 + t1 * m1 + c1[i].x;
        }
        return c;
    }
};
