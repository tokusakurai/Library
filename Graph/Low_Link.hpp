#pragma once

// Low-Link
// 計算量 O(n+m)

// 定義
// 橋：取り除くとグラフが非連結になるような辺
// 関節点：除くと誘導部分グラフが非連結になるような頂点

// 概要
// ord[i] := 頂点 i を DFS で何番目に探索したか
// low[i] := 頂点 i から後退辺を 1 回まで通ることで到達できる頂点の ord の最小値
// 辺 (u,v) (ord[u] < ord[v]) が橋 <-> ord[u] < low[v]
// 根が関節点 <-> 子が 2 つ以上
// 根でない頂点 u が関節点 <-> u の子 v で ord[u] <= low[v] を満たすものが存在する

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja

#include <bits/stdc++.h>
using namespace std;

template <typename G>
struct Low_Link {
    vector<int> ord, low;
    vector<bool> used;
    vector<int> articulation, bridge;

    Low_Link(const G &g) : ord(g.n), low(g.n), used(g.n, false) {
        int k = 0;
        for (int i = 0; i < g.n; i++) {
            if (!used[i]) k = _dfs(i, -1, k, g);
        }
    }

    int _dfs(int now, int pre, int k, const G &g) {
        used[now] = true;
        ord[now] = low[now] = k++;
        bool is_articulation = false;
        int cnt = 0;
        for (auto &e : g[now]) {
            if (e.id == pre) continue;
            if (!used[e.to]) {
                cnt++;
                k = _dfs(e.to, e.id, k, g);
                low[now] = min(low[now], low[e.to]);
                if (pre != -1 && low[e.to] >= ord[now]) is_articulation = true;
                if (ord[now] < low[e.to]) bridge.push_back(e.id);
            } else {
                low[now] = min(low[now], ord[e.to]);
            }
        }
        if (pre == -1 && cnt >= 2) is_articulation = true;
        if (is_articulation) articulation.push_back(now);
        return k;
    }
};
