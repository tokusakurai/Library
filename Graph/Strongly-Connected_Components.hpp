#pragma once

// 強連結成分分解 (分解後は DAG になる)
// 計算量 O(n+m)

// 概要
// DFS 木を構築し、low link の要領で強連結成分を下から列挙する。(Tarjan のアルゴリズム)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_3_C&lang=ja
// https://judge.yosupo.jp/problem/scc

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Graph_Template.hpp"

template <typename G>
struct Strongly_Connected_Components {
    vector<int> st;
    vector<int> ord, low, comp;
    int components_number;

    Strongly_Connected_Components(const G &g) : ord(g.n, -1), low(g.n), comp(g.n) {
        int cnt_ord = 0, cnt_group = 0;
        for (int i = 0; i < g.n; i++) {
            if (ord[i] == -1) _dfs(i, cnt_ord, cnt_group, g);
        }
        for (int i = 0; i < g.n; i++) comp[i] = cnt_group - 1 - comp[i];
        components_number = cnt_group;
    }

    void _dfs(int now, int &cnt_ord, int &cnt_group, const G &g) {
        ord[now] = low[now] = cnt_ord++;
        st.push_back(now);
        for (auto &e : g[now]) {
            if (ord[e.to] == -1) {
                _dfs(e.to, cnt_ord, cnt_group, g);
                low[now] = min(low[now], low[e.to]);
            } else {
                low[now] = min(low[now], ord[e.to]);
            }
        }
        if (low[now] == ord[now]) {
            while (true) {
                int v = st.back();
                st.pop_back();
                ord[v] = g.n;
                comp[v] = cnt_group;
                if (v == now) break;
            }
            cnt_group++;
        }
    }

    Graph<true> make_graph(const G &g) {
        Graph<true> g2(components_number);
        for (int i = 0; i < g.n; i++) {
            for (auto &e : g[i]) {
                int u = comp[i], v = comp[e.to];
                if (u != v) g2.add_edge(u, v);
            }
        }
        return g2;
    }

    int operator[](int k) const { return comp[k]; }
};
