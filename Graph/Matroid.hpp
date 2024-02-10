#pragma once

// マトロイド (分割マトロイド、グラフ的マトロイド、横断マトロイド)
// 計算量

// set(X)：分割マトロイド O(m+n)、グラフ的マトロイド O(m+n)、横断マトロイド O(e√(m+n)+m+n+e)
// C(X,y)：分割マトロイド O(max d_i)、グラフ的マトロイド O(n)、横断マトロイド O(e+m+n)
// C(X,y) は、X ∈ F に y を加えた集合のサーキット (これは一意に定まることが示される)

// 概要
// 分割マトロイド：E(|E| = m) を互いに素な集合 B_1,B_2,...,B_n に分け、B_i からは d_i 個以下しか取ってないものが F に含まれるとしたときのマトロイド (E,F)
// グラフ的マトロイド：グラフ (E,V) (|E| = m,|V| = n) において、F を閉路を持たない E の部分集合全体としたときのマトロイド (E,F)
// 横断マトロイド：二部グラフ (L,R,E) (|L| = m,|R| = n,|E| = e) において、F を完全マッチングが存在する L の部分集合全体としたときのマトロイド (L,F)

// verified with
// https://codeforces.com/gym/103373/problem/I

#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Dulmage-Mendelsohn_Decomposition.hpp"

struct Partition_Matroid {
    const int m; // |E|
    const int n; // 分割の個数
    vector<vector<int>> ids;
    vector<int> belong;
    vector<int> d, cnt;
    vector<vector<int>> used;

    Partition_Matroid(int m, int n, const vector<vector<int>> &ids, const vector<int> &d) : m(m), n(n), ids(ids), d(d), cnt(n), used(n) {
        assert((int)ids.size() == n && (int)d.size() == n);
        belong.assign(m, -1);
        for (int i = 0; i < n; i++) {
            for (auto &e : ids[i]) belong[e] = i;
        }
    }

    int size() { return m; }

    // X∈F 計算量 O(m+n)
    template <typename T>
    void set(const vector<T> &X) {
        fill(begin(cnt), end(cnt), 0);
        for (int i = 0; i < n; i++) used[i].clear();
        for (int i = 0; i < m; i++) {
            if (X[i]) cnt[belong[i]]++;
        }
        for (int i = 0; i < n; i++) {
            assert(cnt[i] <= d[i]);
            if (cnt[i] == d[i]) {
                for (auto &e : ids[i]) {
                    if (X[e]) used[i].push_back(e);
                }
            }
        }
    }

    // C(X,y) 計算量 O(max d_i)
    vector<int> circuit(int y) const {
        int p = belong[y];
        if (cnt[p] == d[p]) {
            vector<int> ret = used[p];
            ret.push_back(y);
            return ret;
        }
        return {};
    }
};

struct Graphic_Matroid {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    const int m; // |E|
    const int n; // |V|
    vector<vector<edge>> list;
    vector<pair<int, int>> es;
    vector<int> pre_v, pre_e;
    vector<int> root;
    vector<int> depth;

    Graphic_Matroid(int m, int n, const vector<pair<int, int>> &es) : m(m), n(n), es(es), pre_v(n), pre_e(n), root(n), depth(n) {
        list.resize(n);
        for (int i = 0; i < m; i++) {
            auto [u, v] = es[i];
            list[u].emplace_back(v, i);
            list[v].emplace_back(u, i);
        }
    }

    int size() { return m; }

    // X∈F 計算量 O(m+n)
    template <typename T>
    void set(const vector<T> &X) {
        fill(begin(pre_v), end(pre_v), -1);
        fill(begin(pre_e), end(pre_e), -1);
        fill(begin(root), end(root), -1);
        fill(begin(depth), end(depth), -1);
        for (int i = 0; i < n; i++) {
            if (root[i] != -1) continue;
            queue<int> que;
            que.push(i);
            depth[i] = 0;
            while (!que.empty()) {
                int j = que.front();
                que.pop();
                root[j] = i;
                for (auto &e : list[j]) {
                    assert(!X[e.id] || root[e.to] == -1 || e.id == pre_e[j]);
                    if (X[e.id] && root[e.to] == -1) {
                        pre_v[e.to] = j;
                        pre_e[e.to] = e.id;
                        depth[e.to] = depth[j] + 1;
                        que.emplace(e.to);
                    }
                }
            }
        }
    }

    // C(X,y) 計算量 O(n)
    vector<int> circuit(int y) const {
        auto [s, t] = es[y];
        if (root[s] != root[t]) return {};
        vector<int> ret;
        while (s != t) {
            if (depth[s] > depth[t]) {
                ret.push_back(pre_e[s]);
                s = pre_v[s];
            } else {
                ret.push_back(pre_e[t]);
                t = pre_v[t];
            }
        }
        ret.push_back(y);
        return ret;
    }
};

struct Transversal_Matroid {
    const int m; // |L|
    const int n; // |R|
    vector<vector<int>> es;
    vector<bool> fixed;
    vector<vector<int>> res;

    Transversal_Matroid(int m, int n, const vector<vector<int>> &es) : m(m), n(n), es(es), fixed(n), res(m + n) {}

    int size() { return m; }

    // X∈F 計算量 O(e√(m+n)+m+n+e)
    template <typename T>
    void set(const vector<T> &X) {
        fill(begin(fixed), end(fixed), true);
        for (int i = 0; i < m + n; i++) res[i].clear();
        Dulmage_Mendelsohn_Decomposition DM(m, n);
        for (int i = 0; i < m; i++) {
            if (X[i]) {
                for (auto &e : es[i]) DM.add_edge(i, e);
            }
        }
        DM.decompose();
        assert(DM.ids_r.back().empty());
        for (auto &e : DM.ids_r[0]) fixed[e] = false;
        for (int i = 0; i < m; i++) {
            for (auto &e : es[i]) res[i].push_back(m + e);
        }
        for (int i = 0; i < (int)DM.ids_l.size() - 1; i++) {
            int k = DM.ids_l[i].size(), l = DM.ids_r[i].size();
            for (int j = 0; j < k; j++) {
                int u = DM.ids_l[i][j], v = DM.ids_r[i][l - k + j];
                res[m + v].push_back(u);
            }
        }
    }

    // C(X,y) 計算量 O(e+m+n)
    vector<int> circuit(int y) const {
        for (auto &e : es[y]) {
            if (!fixed[e]) return {};
        }
        vector<bool> used(m + n, false);
        used[y] = true;
        queue<int> que;
        que.push(y);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : res[i]) {
                if (!used[e]) {
                    used[e] = true;
                    que.emplace(e);
                }
            }
        }
        vector<int> ret;
        for (int i = 0; i < m; i++) {
            if (used[i]) ret.push_back(i);
        }
        return ret;
    }
};
