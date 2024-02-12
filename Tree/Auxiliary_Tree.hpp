#pragma once

// Auxiliary Tree
// 計算量：O(k log(n))

// 概要
// x_1,...,x_k を含む木を、パスを圧縮した形で表現する。
// 元のグラフの DFS の pre-order 順に x_1,...,x_k をソートすると、圧縮された木に含まれる頂点は x_1,...,x_k,lca(x_1,x_2),...,lca(x_{k-1},x_k) のどれか
// x_1,...,x_k をこの順に走査すれば構築できる。

// verified with
// https://atcoder.jp/contests/typical90/tasks/typical90_ai
// https://atcoder.jp/contests/abc340/tasks/abc340_g

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Graph_Template.hpp"
#include "../Tree/Heavy-Light_Decomposition.hpp"

template <typename G>
struct Tree_Compressor : Heavy_Light_Decomposition<G> {
    using H = Heavy_Light_Decomposition<G>;
    using L = typename G::L;

    vector<int> par, id;

    Tree_Compressor(const G &g, int r = 0) : H(g, r), par(g.n, -1), id(g.n, -1) {}

    // 圧縮後のグラフと、圧縮後の i 番目の頂点が元のグラフで何番目だったかを格納する配列を返す
    template <bool directed = false>
    pair<Weighted_Graph<L, directed>, vector<int>> compress(vector<int> x) {
        int k = x.size();
        sort(begin(x), end(x), [&](int i, int j) { return this->id_v[i] < this->id_v[j]; });
        x.erase(unique(begin(x), end(x)), end(x));
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
        Weighted_Graph<L, directed> g(cnt);
        vector<int> vertex_id(cnt);
        for (auto v : used) {
            if (par[v] != -1) g.add_edge(id[par[v]], id[v], this->d[v] - this->d[par[v]]);
            vertex_id[id[v]] = v;
        }
        for (auto v : used) par[v] = -1, id[v] = -1;
        return make_pair(g, vertex_id);
    }
};
