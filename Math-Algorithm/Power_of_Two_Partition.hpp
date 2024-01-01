
// 2 べき分割数の数え上げ (重み付き)
// 計算量 O(n^2 log(n) + n log(n)log(k))

// 概要
// [x^k] 1/(1-a_0 x)(1-a_1 x^2)...(1-a_{n-1} x^{2^{n-1}}) を求める
// a_0 = ... = a_{n-1} = 1 の場合は k を 1,2,..,2^{n-1} の和で表す方法に相当し、その重み付き一般化と言える
// Bostan Mori のアルゴリズムを用いるが、各ステップで分母の大部分は偶関数なので、分母分子に g(-x) をかける部分を大幅に削減できる (奇関数の部分のみでいい)
// i ステップ目を終えた後に分母に加わる新たな奇関数は (1-a_i x) のみであるため、奇関数の部分のみを容易に保持できる
// n-1 ステップ後には分母・分子ともに n 次以下になっているので、そこからは通常の Bostan Mori のアルゴリズムを適用できる。

// verified with
// https://techful-programming.com/techful/event/session/yUZJge8b/question/19348

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"
#include "../Math-Algorithm/Bostan_Mori.hpp"

// [x^k] 1/(1-a_0 x)(1-a_1 x^2)...(1-a_{n-1} x^{2^{n-1}})
template <typename T>
T power_of_two_partition(vector<T> a, long long k) {
    int n = a.size();
    if (n == 0) return k == 0 ? 1 : 0;
    using NTT_ = Number_Theoretic_Transform<T>;

    auto slice_vec = [](vector<T> v, int m, int t) {
        vector<T> ret;
        for (int i = t; i < (int)v.size(); i += m) ret.push_back(v[i]);
        return ret;
    };

    vector<T> f{1}, g{1, -a[0]};
    for (int i = 1; i < n; i++) {
        vector<T> g2 = g;
        for (int j = 1; j < (int)g2.size(); j += 2) g2[j] = -g2[j];
        f = NTT_::convolve(f, g2);
        g = NTT_::convolve(g, g2);
        f = slice_vec(f, 2, k & 1);
        g = slice_vec(g, 2, 0);
        g.push_back(0);
        for (int j = (int)g.size() - 2; j >= 0; j--) g[j + 1] -= a[i] * g[j];
        k >>= 1;
    }
    return Bostan_Mori(f, g, k);
}
