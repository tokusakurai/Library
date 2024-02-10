#pragma once

// ハミルトンサイクルの検出
// ハミルトンサイクルを持つ部分集合の列挙：O(n*2^n)、部分集合 S におけるハミルトンサイクルの復元：O(|S|*2^|S|)

// 概要
// 始点 s から出発して頂点集合 S を通った時に、最終的にいる位置としてありえるものを管理する。

// verified with
// https://codeforces.com/contest/1804/problem/E

#include <bits/stdc++.h>
using namespace std;

// ハミルトンサイクルを持つ部分集合を全て列挙
vector<bool> enumerate_Hamilton_cycle(const vector<int> &es) {
    int n = es.size();
    vector<bool> ret(1 << n, false);
    for (int s = n - 1; s >= 0; s--) {
        vector<int> dp(1 << (s + 1), 0);
        dp[1 << s] |= 1 << s;
        for (int S = 0; S < (1 << (s + 1)); S++) {
            if (dp[S] == 0) continue;
            int ok = 0;
            for (int i = 0; i <= s; i++) {
                if ((dp[S] >> i) & 1) ok |= es[i];
            }
            if ((ok >> s) & 1) ret[S] = true;
            for (int i = 0; i <= s; i++) {
                if ((S >> i) & 1 || !((ok >> i) & 1)) continue;
                dp[S | (1 << i)] |= 1 << i;
            }
        }
    }
    return ret;
}

// 部分集合 S におけるハミルトンサイクルを 1 つ復元 (存在しなければ空)
vector<int> recover_Hamilton_cycle(const vector<int> &es, int S) {
    int n = es.size();
    vector<int> nodes;
    for (int i = 0; i < n; i++) {
        if ((S >> i) & 1) nodes.push_back(i);
    }
    int m = nodes.size();
    if (m == 0) return {};
    vector<int> es_comp(m), rs_comp(m);
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < m; j++) {
            int f = (es[nodes[i]] >> nodes[j]) & 1;
            es_comp[i] |= f << j;
            rs_comp[j] |= f << i;
        }
    }
    vector<int> dp(1 << m, 0);
    dp[1] |= 1;
    for (int T = 0; T < (1 << m); T++) {
        if (dp[T] == 0) continue;
        int ok = 0;
        for (int i = 0; i < m; i++) {
            if ((dp[T] >> i) & 1) ok |= es_comp[i];
        }
        for (int i = 0; i < m; i++) {
            if ((T >> i) & 1 || !((ok >> i) & 1)) continue;
            dp[T | (1 << i)] |= 1 << i;
        }
    }
    vector<int> ret;
    int now = 0, used = (1 << m) - 1;
    while (used > 0) {
        int ok = rs_comp[now] & dp[used];
        if (ok == 0) return {};
        int pre = __builtin_ctz(ok);
        ret.push_back(nodes[pre]);
        used &= ~(1 << pre);
        now = pre;
    }
    reverse(begin(ret), end(ret));
    return ret;
}
