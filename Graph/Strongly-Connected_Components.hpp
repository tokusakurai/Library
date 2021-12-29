
// 強連結成分分解（分解後は DAG になる）
// 計算量 O(n+m)

// 概要
// 1 回目の DFS では適当な頂点から始めて帰りがけの順で頂点を並べる。
// 2 回目の DFS では帰りがけの逆順に頂点を見ていき、逆辺を使って到達できる未訪問の頂点があれば、それらは同じ強連結成分となる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=ja
// https://judge.yosupo.jp/problem/scc

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Graph_Template.hpp"

template <bool directed = true>
struct Strongly_Connected_Components {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es, rs;
    vector<int> vs;
    vector<int> comp;
    const int n;
    int m;

    Strongly_Connected_Components(int n) : es(n), rs(n), comp(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m), rs[to].emplace_back(from, m);
        if (!directed) es[to].emplace_back(from, m), rs[from].emplace_back(to, m);
        m++;
    }

    void _dfs(int now) {
        if (comp[now] != -1) return;
        comp[now] = 1;
        for (auto &e : es[now]) _dfs(e.to);
        vs.push_back(now);
    }

    void _rdfs(int now, int col) {
        if (comp[now] != -1) return;
        comp[now] = col;
        for (auto &e : rs[now]) _rdfs(e.to, col);
    }

    Graph<true> decompose() {
        fill(begin(comp), end(comp), -1);
        for (int i = 0; i < n; i++) {
            if (comp[i] == -1) _dfs(i);
        }
        fill(begin(comp), end(comp), -1);
        reverse(begin(vs), end(vs));
        int cnt = 0;
        for (auto &e : vs) {
            if (comp[e] == -1) _rdfs(e, cnt++);
        }
        Graph<true> G(cnt);
        for (int i = 0; i < n; i++) {
            for (auto &e : es[i]) {
                int u = comp[i], v = comp[e.to];
                if (u != v) G.add_edge(u, v);
            }
        }
        return G;
    }

    int operator[](int k) const { return comp[k]; }
};
