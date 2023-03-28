
// 強連結成分分解（分解後は DAG になる）
// 計算量 O(n+m)

// 概要
// DFS 木を構築し、low link の要領で強連結成分を下から列挙する。(Tarjan のアルゴリズム)

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

    vector<vector<edge>> es;
    vector<int> st;
    vector<int> ord, low, comp;
    const int n;
    int m;

    Strongly_Connected_Components(int n) : es(n), ord(n), low(n), comp(n), n(n), m(0) { st.reserve(n); }

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    void _dfs(int now, int &cnt_ord, int &cnt_group) {
        ord[now] = low[now] = cnt_ord++;
        st.push_back(now);
        for (auto &e : es[now]) {
            if (ord[e.to] == -1) {
                _dfs(e.to, cnt_ord, cnt_group);
                low[now] = min(low[now], low[e.to]);
            } else {
                low[now] = min(low[now], ord[e.to]);
            }
        }
        if (low[now] == ord[now]) {
            while (true) {
                int v = st.back();
                st.pop_back();
                ord[v] = n;
                comp[v] = cnt_group;
                if (v == now) break;
            }
            cnt_group++;
        }
    }

    int decompose() {
        fill(begin(ord), end(ord), -1);
        int cnt_ord = 0, cnt_group = 0;
        for (int i = 0; i < n; i++) {
            if (ord[i] == -1) _dfs(i, cnt_ord, cnt_group);
        }
        for (int i = 0; i < n; i++) comp[i] = cnt_group - 1 - comp[i];
        return cnt_group;
    }

    Graph<true> make_graph() {
        Graph<true> G(decompose());
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
