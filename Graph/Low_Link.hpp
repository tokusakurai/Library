
// Low-Link
// 計算量 O(n+m)

// 橋：取り除くとグラフが非連結になるような辺
// 関節点：除くと誘導部分グラフが非連結になるような頂点

// 概要
// ord[i] := 頂点iをDFSで何番目に探索したか
// low[i] := 頂点iから後退辺を1回まで通ることで到達できる頂点のordの最小値
// 辺(u,v)(ord[u]<ord[v])が橋⇔ord[u]<low[v]
// 根が関節点⇔子が2つ以上
// 根でない頂点uが関節点⇔uの子vでord[u]<=low[v]を満たすものが存在する

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_A&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_B&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Low_Link {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> ord, low;
    vector<bool> used;
    vector<int> articulation, bridge;
    const int n;
    int m;

    Low_Link(int n) : es(n), ord(n), low(n), used(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int _dfs(int now, int pre, int k) {
        used[now] = true;
        ord[now] = low[now] = k++;
        bool is_articulation = false;
        int cnt = 0;
        for (auto &e : es[now]) {
            if (e.id == pre) continue;
            if (!used[e.to]) {
                cnt++;
                k = _dfs(e.to, e.id, k);
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

    void build() {
        fill(begin(used), end(used), false);
        int k = 0;
        for (int i = 0; i < n; i++) {
            if (!used[i]) k = _dfs(i, -1, k);
        }
    }
};
