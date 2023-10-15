
// 木上のスケジューリング問題 (仮)
// 計算量 O(n log(n))

// 問題
// 根付き木があり、i の親 p_i に対して p_i が i より後に出てくる順列 σ の集合を A_n ⊆ S_n とする。
// また、各頂点 i に値 x_i ∈ X が与えられている。
// スコア関数 s : A_n -> R が与えられるとき、s(σ) が最大 (最小)となるような σ ∈ A_n を出力せよ。

// 解法
// 二項演算 ● : X × X → X と、X 上の二項関係 < であって、以下の性質を持つものが存在するならば O(n log(n)) 時間で解ける。
// 　・ ● は反射律・結合律を満たす
// 　・ 任意の x,y ∈ X について、x <= y または y <= x が成立する (< から <= は自然に定義できる)
// 　・ 点列 U = (u_1, ... , u_k), V = (v_1, ... , v_l) について、
// 　　 x_U = x_{u_1} ● x_{u_2} ● ... ● x_{u_k}
// 　　 x_V = x_{v_1} ● x_{v_2} ● ... ● x_{v_l} とすると、
// 　　 s(..., U, V, ...) > s(..., V, U, ...) ⇔ x_U < x_V (つまり x_U < x_V のときに U を V より前に置きたい)

// 以下、根を 1 とする。
// v ∈ argmin_{i ≠ 1} x_i とすると、σ の中で p_v の次には必ず v が来るとしてよい (隣り合うまで v と 1 個前のものをスワップし続けてもスコアが悪くならないから)。
// つまり、グラフ上で辺 {p_v, v} を縮約して、x_{p_v} ← x_{p_v} ● x_v とした問題を解けばよい。これを n - 1 ステップ繰り返すことで解ける。
// priority queue に (x_i, i) を入れて v を取得し、union find で v と p_v をマージしていけばよい。

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <typename T, bool directed = false>
struct Tree_Scheduling {
    using F = function<T(T, T)>;
    using C = function<bool(T, T)>;
    int n;
    const F merge;
    const C comp;
    vector<vector<int>> es;
    vector<int> par;

    // comp(x_i, x_j) == true  <=>  i を j より前に置きたい
    Tree_Scheduling(int n, const F &merge, const C &comp) : n(n), merge(merge), comp(comp), es(n), par(n, -1) {}

    void add_edge(int from, int to) {
        if (directed) {
            par[to] = from;
        } else {
            es[from].emplace_back(to);
            es[to].emplace_back(from);
        }
    }

    void bfs(int root) {
        fill(begin(par), end(par), -2);
        queue<int> que;
        que.push(root);
        par[root] = -1;
        while (!empty(que)) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (par[e] == -2) {
                    par[e] = i;
                    que.push(e);
                }
            }
        }
    }

    vector<int> solve(vector<T> x, int root = 0) {
        using P = pair<T, int>;
        auto comp_P = [&](P a, P b) { return comp(b.first, a.first); };
        if (!directed) bfs(root);
        priority_queue<P, vector<P>, decltype(comp_P)> que(comp_P);
        for (int i = 0; i < n; i++) {
            if (i != root) que.emplace(x[i], i);
        }
        Union_Find_Tree uf(n);
        vector<int> top(n), last(n); // 連結成分内で並べたときの先頭と末尾
        vector<int> next(n, -1);
        for (int i = 0; i < n; i++) top[i] = i, last[i] = i;
        while (!que.empty()) {
            auto [p, i] = que.top();
            que.pop();
            int u = uf[i], v = uf[par[i]];
            if (u == v || comp(p, x[i]) || comp(x[i], p)) continue;
            x[top[v]] = merge(x[top[v]], x[i]);
            next[last[v]] = top[u];
            uf.unite(u, v);
            top[u] = top[v], last[v] = last[u];
            if (top[v] != root) que.emplace(x[top[v]], top[v]);
        }
        vector<int> ret(n);
        for (int i = 0, ptr = root; i < n; i++) {
            ret[i] = ptr;
            ptr = next[ptr];
        }
        return ret;
    }
};
