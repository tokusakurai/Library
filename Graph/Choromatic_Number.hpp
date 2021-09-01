
// 彩色数(隣接頂点が異なる色になるように彩色するのに必要な最小の色数)
// 計算量 O(2^V*V)

// 概要
// グラフの独立集合からK個選んで頂点集合全体をちょうど被覆する場合の数を数え上げる。(これが0でなければK彩色可能)
// g(S) := 独立集合K個でSをちょうど被覆する場合の数(同じ頂点が複数個の独立集合に含まれていてもよい)
// f(S) := Σg(T) (T⊆S)
// I(S) := Sの部分集合で独立なものの個数
// 各I(S)はbitDPで求まり、f(S)=I(S)^Kであるから、g(S)は包除原理を用いて求められる。

// verified with
// https://judge.yosupo.jp/problem/chromatic_number

#pragma once
#include <bits/stdc++.h>
using namespace std;

int chromatic_number(vector<vector<int>> G) {
    int n = G.size();
    vector<int> es(n);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (G[i][j] != 0) es[i] |= 1 << j;
        }
    }
    int ret = n;
    for (int d : {7, 11, 21}) { // k色で彩色する場合の数を複数のmodで数え上げる
        int mod = 1000000000 + d;
        vector<int> I(1 << n), f(1 << n, 1);
        for (int S = 0; S < (1 << n); S++) {
            if (S == 0) {
                I[S] = 1;
                continue;
            }
            int u = __builtin_ctz(S);
            I[S] = I[S & ~(1 << u)] + I[S & ~((1 << u) | es[u])];
        }
        for (int i = 1; i < ret; i++) {
            long long all = 0;
            for (int j = 0; j < (1 << n); j++) {
                f[j] = (1LL * f[j] * I[j]) % mod;
                all += (__builtin_parity(j) == (n & 1) ? f[j] : mod - f[j]);
            }
            if (all % mod > 0) ret = min(ret, i);
        }
    }
    return ret;
}
