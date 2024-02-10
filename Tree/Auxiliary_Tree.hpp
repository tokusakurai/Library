#pragma once

// Auxiliary Tree
// 計算量：O(k log(n))

// 概要
// x_1,...,x_k を含む木を、パスを圧縮した形で表現する。
// 元のグラフの DFS の pre-order 順に x_1,...,x_k をソートすると、圧縮された木に含まれる頂点は x_1,...,x_k,lca(x_1,x_2),...,lca(x_{k-1},x_k) のどれか
// x_1,...,x_k をこの順に走査すれば構築できる。

// verified with
// https://atcoder.jp/contests/typical90/tasks/typical90_ai

#include <bits/stdc++.h>
using namespace std;

#include "../Tree/Heavy-Light_Decomposition.hpp"

template <typename T, bool directed = false>
struct Auxiliary_Tree {
    struct edge {
        int to;
        T cost;
        int id;
        edge(int to, int cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> id; // i 番目の頂点が圧縮する前のどの頂点に対応しているか
    const int n;
    int m;

    Auxiliary_Tree(int n) : es(n), id(n), n(n), m(0) {}

    void add_edge(int from, int to, T cost) {
        es[from].emplace_back(to, cost, m);
        if (!directed) es[to].emplace_back(from, cost, m);
        m++;
    }
};

template <bool directed = false>
struct Tree_Compressor : Heavy_Light_Decomposition<directed> {
    using H = Heavy_Light_Decomposition<directed>;
    vector<int> par, id;

    Tree_Compressor(int n) : H(n), par(n, -1), id(n, -1) {}

    void build() { this->decompose(); }

    Auxiliary_Tree<int, directed> compress(vector<int> x) {
        int k = x.size();
        sort(begin(x), end(x), [&](int i, int j) { return this->id_v[i] < this->id_v[j]; });
        x.erase(unique(begin(v), end(v)), end(v));
        vector<int> used, st;
        int cnt = 0;
        used.push_back(x[0]), st.push_back(x[0]);
        id[x[0]] = cnt++;
        for (int i = 1; i < k; i++) {
            int u = this->lca(x[i - 1], x[i]);
            while (!st.empty() && this->depth[st.back()] >= this->depth[u]) {
                int v = st.back();
                st.pop_back();
                if (!st.empty() && this->depth[st.back()] >= this->depth[u]) {
                    par[v] = st.back();
                } else if (u != v) {
                    par[v] = u;
                }
            }
            if (id[u] == -1) id[u] = cnt++, used.push_back(u);
            if (id[x[i]] == -1) id[x[i]] = cnt++, used.push_back(x[i]);
            st.push_back(u), st.push_back(x[i]);
        }
        while (st.size() >= 2) {
            int u = st.back();
            st.pop_back();
            par[u] = st.back();
        }
        Auxiliary_Tree<int, directed> G(cnt);
        for (auto v : used) {
            if (par[v] != -1) G.add_edge(id[par[v]], id[v], this->depth[v] - this->depth[par[v]]);
            G.id[id[v]] = v;
        }
        for (auto v : used) par[v] = -1, id[v] = -1;
        return G;
    }
};
