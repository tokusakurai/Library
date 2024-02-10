#pragma once

// 2 べき分割数の数え上げ (重み付き)
// 計算量 O(n log(n)log(k))

// 概要
// [x^k] 1/(1-a_0 x)(1-a_1 x^2)...(1-a_{n-1} x^{2^{n-1}}) を求める。
// a_0 = ... = a_{n-1} = 1 の場合は k を 1,2,..,2^{n-1} の和で表す方法に相当し、その重み付き一般化と言える。
// Bostan Mori のアルゴリズムを用いるが、各ステップで分母の大部分は偶関数なので、分母分子に g(-x) をかける部分を大幅に削減できる。 (奇関数の部分のみでいい)
// i ステップ目を終えた後に分母に加わる新たな奇関数は (1-a_i x) のみであるため、奇関数の部分のみを容易に保持できる。
// n-1 ステップ後には分母・分子ともに n 次以下になっているので、そこからは通常の Bostan Mori のアルゴリズムを適用できる。
// n が小さいときは NTT をするより愚直に畳み込んだ方が速い (verify の提出を参照)。

// verified with
// https://codeforces.com/contest/1864/problem/H

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

// [x^k] f(x)/g(x)(1-x)(1-a_0 x)(1-a_1 x^2)...(1-a_{n-1} x^{2^{n-1}})
template <typename T>
T power_of_two_partition(vector<T> a, long long k, vector<T> f = {1}, vector<T> g = {1}) {
    using NTT_ = Number_Theoretic_Transform<T>;
    int n = 2;
    while (n < max((int)f.size(), (int)g.size()) + (int)a.size()) n <<= 1;
    f.resize(n, 0), g.resize(n, 0);
    vector<T> h(n, 0);
    h[1] = 1;
    NTT_::ntt(h);
    for (int i = 0; k > 0; i++) {
        if (i < (int)a.size()) {
            for (int j = n - 2; j >= 0; j--) g[j + 1] -= a[i] * g[j];
        }
        vector<T> fe(n, 0), fo(n, 0), ge(n, 0), go(n, 0);
        for (int i = 0; i < n; i += 2) {
            fe[i >> 1] = f[i];
            ge[i >> 1] = g[i];
        }
        for (int i = 1; i < n; i += 2) {
            fo[i >> 1] = f[i];
            go[i >> 1] = g[i];
        }
        NTT_::ntt(fe), NTT_::ntt(fo), NTT_::ntt(ge), NTT_::ntt(go);
        if (k & 1) {
            for (int i = 0; i < n; i++) {
                f[i] = fo[i] * ge[i] - fe[i] * go[i];
                g[i] = ge[i] * ge[i] - go[i] * go[i] * h[i];
            }
        } else {
            for (int i = 0; i < n; i++) {
                f[i] = fe[i] * ge[i] - fo[i] * go[i] * h[i];
                g[i] = ge[i] * ge[i] - go[i] * go[i] * h[i];
            }
        }
        NTT_::intt(f), NTT_::intt(g);
        k >>= 1;
    }
    return f[0] / g[0];
}
