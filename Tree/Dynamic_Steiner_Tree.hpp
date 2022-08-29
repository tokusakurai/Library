
// 木上の最小シュタイナー木 (頂点集合の削除・追加ができる)
// 計算量 前計算：O(n log(n))、追加・削除：O(log(n))
// 空間計算量 O(n log(n))

// 概要
// x を頂点集合に追加するとき、DFS 順で x の直前に入っている頂点を l、直後に入っている頂点を r とする。
// このとき、最小シュタイナー木のサイズは (dist(l,x) + dist(x,r) - dist(l,r)) / 2 だけ増える。
// 削除するときは挿入するときの増加分だけ減らせばよい。
// 2 頂点の距離を求めるのに LCA を用いる。

// verified with
// https://codeforces.com/contest/372/problem/D

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Graph {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    // par[i][j] := 頂点 j の 2^i 個前の祖先
    vector<vector<int>> par;
    vector<int> depth;
    int height;

    vector<int> vs, ids;
    set<int> s;
    int Steiner_size;

    Graph(int n) : es(n), n(n), m(0), depth(n), ids(n), Steiner_size(0) {
        height = 1;
        while ((1 << height) < n) height++;
        par.assign(height, vector<int>(n));
    }

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void prepare(int now, int pre = -1) {
        if (pre == -1) depth[now] = 0;
        par[0][now] = pre;
        ids[now] = vs.size();
        vs.push_back(now);
        for (auto &e : es[now]) {
            if (e.to != pre) {
                depth[e.to] = depth[now] + 1;
                prepare(e.to, now);
            }
        }
    }

    // root を根として前準備する
    void build(int root = 0) {
        prepare(root);
        for (int j = 0; j < height - 1; j++) {
            for (int i = 0; i < n; i++) {
                if (par[j][i] == -1) {
                    par[j + 1][i] = -1;
                } else {
                    par[j + 1][i] = par[j][par[j][i]];
                }
            }
        }
    }

    int lca(int u, int v) {
        if (depth[u] < depth[v]) swap(u, v);
        int D = depth[u] - depth[v];
        for (int i = 0; i < height; i++) {
            if ((D >> i) & 1) u = par[i][u];
        }
        if (u == v) return u;
        for (int i = height - 1; i >= 0; i--) {
            if (par[i][u] != par[i][v]) u = par[i][u], v = par[i][v];
        }
        return par[0][u];
    }

    int dist(int u, int v) { return depth[u] + depth[v] - 2 * depth[lca(u, v)]; }

    int insert(int x) {
        if (s.count(ids[x])) return Steiner_size;
        if (s.empty()) {
            Steiner_size++;
        } else {
            auto l = s.upper_bound(ids[x]);
            auto r = l--;
            if (r == begin(s) || r == end(s)) l = begin(s), r = end(s), r--;
            Steiner_size += (dist(vs[*l], x) + dist(x, vs[*r]) - dist(vs[*l], vs[*r])) / 2;
        }
        s.insert(ids[x]);
        return Steiner_size;
    }

    int erase(int x) {
        if (!s.count(ids[x])) return Steiner_size;
        s.erase(ids[x]);
        if (s.empty()) {
            Steiner_size--;
        } else {
            auto l = s.upper_bound(ids[x]);
            auto r = l--;
            if (r == begin(s) || r == end(s)) l = begin(s), r = end(s), r--;
            Steiner_size -= (dist(vs[*l], x) + dist(x, vs[*r]) - dist(vs[*l], vs[*r])) / 2;
        }
        return Steiner_size;
    }
};
