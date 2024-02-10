#pragma once

// 階段状のグリッドにおける最短経路数え上げ
// 計算量 O((n+m)log(n+m)log n) (m = max h_i)

// 概要
// 階段状のマス目がある。下の辺の各マスに値が書き込まれている。これを初期値として経路数え上げの dp をしたとき、右の辺の各マスには何が書き込まれるか？
// この問題は分割統治を用いることで解くことができる。
// 参考：https://twitter.com/noshi91/status/1640315787528519680

// verified with
// https://codeforces.com/gym/102220

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Combination.hpp"
#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

// 左側から i 列目は h_i 個のマスからなる階段状のグリッドを考える。また、i 列目の一番下には a_i が書かれている。
// この状態からグリッド上で右または上のみに移動する経路数え上げ dp を行ったときに、一番右の列に書かれる数字を (下から順に) 求める。
template <typename T>
vector<T> step_grid_path_count(vector<int> h, const vector<T> &a) {
    using NTT_ = Number_Theoretic_Transform<T>;
    using comb_ = Combination<T>;
    int n = h.size();
    assert((int)a.size() == n);
    if (n == 0) return {};
    if (n == 1) return vector<T>(h[0], a[0]);
    for (int i = n - 2; i >= 0; i--) h[i] = min(h[i], h[i + 1]);
    assert(h[0] >= 0);
    if (h[0] == 0) {
        int l = 0;
        while (l < n && h[l] == 0) l++;
        return step_grid_path_count(vector<int>(begin(h) + l, end(h)), vector<T>(begin(a) + l, end(a)));
    }
    int m = n / 2;
    auto b = step_grid_path_count(vector<int>(begin(h), begin(h) + m), vector<T>(begin(a), begin(a) + m));
    int x = n - m, y = h[m - 1], z = 1;
    while (z < x + y - 1) z <<= 1;
    vector<T> c(x, 0), d(y, 0);
    vector<T> gg(z, 0);
    for (int i = 0; i < x + y - 1; i++) gg[i] = comb::fac(i);
    NTT_::ntt(gg);
    //  a->c
    {
        vector<T> f(x, 0), g(x, 0);
        for (int i = 0; i < x; i++) f[i] = a[m + i];
        for (int i = 0; i < x; i++) g[i] = comb_::C(y - 1 + i, i);
        f = NTT_::convolve(f, g);
        for (int i = 0; i < x; i++) c[i] += f[i];
    }
    // b->d
    {
        vector<T> f(y, 0), g(y, 0);
        for (int i = 0; i < y; i++) f[i] = b[i];
        for (int i = 0; i < y; i++) g[i] = comb_::C(x - 1 + i, i);
        f = NTT_::convolve(f, g);
        for (int i = 0; i < y; i++) d[i] += f[i];
    }
    // a->d
    {
        vector<T> f(z, 0), g(z, 0);
        for (int i = 0; i < x; i++) f[i] = a[m + i] * comb_::ifac(x - 1 - i);
        NTT_::ntt(f);
        for (int i = 0; i < z; i++) f[i] *= gg[i];
        NTT_::intt(f);
        for (int i = 0; i < y; i++) d[i] += f[x - 1 + i] * comb_::ifac(i);
    }
    // b->c
    {
        vector<T> f(z, 0), g(z, 0);
        for (int i = 0; i < y; i++) f[i] = b[i] * comb_::ifac(y - 1 - i);
        NTT_::ntt(f);
        for (int i = 0; i < z; i++) f[i] *= gg[i];
        NTT_::intt(f);
        for (int i = 0; i < x; i++) c[i] += f[y - 1 + i] * comb_::ifac(i);
    }
    vector<T> ret(h[n - 1]);
    for (int i = 0; i < y; i++) ret[i] = d[i];
    vector<int> h_up(x);
    for (int i = 0; i < x; i++) h_up[i] = h[m + i] - y;
    auto d_up = step_grid_path_count(h_up, c);
    for (int i = 0; i < (int)d_up.size(); i++) ret[y + i] = d_up[i];
    return ret;
};
