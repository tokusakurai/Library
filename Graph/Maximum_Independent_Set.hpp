#pragma once

// 最大安定集合 (どの 2 点も隣接しない点集合で最大のもの)
// 計算量 O((1.381^n)n)

// 概要
// 次数が 1 以下の頂点があれば必ず採用し、なければ残っている頂点で次数が最大のものについて採用するかしないかで分岐する。

// verified with
// https://atcoder.jp/contests/code-thanks-festival-2017-open/tasks/code_thanks_festival_2017_g
// https://judge.yosupo.jp/problem/maximum_independent_set

#include <bits/stdc++.h>
using namespace std;

long long maximum_independent_set(vector<long long> G, long long rem = -1) {
    int n = G.size();
    if (rem == -1) rem = (1LL << n) - 1;
    long long ret = 0;
    int k = -1, m = -1;
    while (true) {
        bool update = false;
        for (int i = 0; i < n; i++) {
            if (!((rem >> i) & 1)) continue;
            int s = __builtin_popcountll(rem & G[i]);
            if (s > m) k = i, m = s;
            if (s <= 1) {
                rem &= ~(G[i] | (1LL << i));
                ret |= (1LL << i), update = true;
            }
        }
        if (!update) break;
        k = -1, m = -1;
    }
    if (rem > 0) {
        rem &= ~(1LL << k);
        long long p = maximum_independent_set(G, rem);
        long long q = maximum_independent_set(G, rem & ~G[k]);
        if (__builtin_popcountll(p) > __builtin_popcountll(q)) {
            ret |= p;
        } else {
            ret |= ((1LL << k) | q);
        }
    }
    return ret;
}
