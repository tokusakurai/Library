
// オイラー閉路・オイラー路の検出
// 計算量 O(E+V)

// オイラー路 : 全ての辺をちょうど一度通るパス
// オイラー閉路 : 閉路になるオイラー路

// 連結グラフがオイラー閉路をもつ必要十分条件
// 有向グラフ : すべての頂点について(入次数)=(出次数)、無向グラフ：全ての頂点の次数が偶数
// 連結グラフがオイラー路をもつ(かつオイラー閉路はもたない)必要十分条件
// 有向グラフ : (入次数)-(出次数)が1,-1である頂点がちょうど1つずつあり、それ以外は全て0、無向グラフ：次数が奇数である頂点がちょうど2つある

// verified with
// https://codeforces.com/contest/1361/problem/C
// https://yukicoder.me/submissions/591125

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Union_Find_Tree.hpp"

template <bool directed = false>
struct Eulerian_Trail {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<pair<int, int>> list;
    vector<bool> used_e, used_v;
    vector<int> deg;
    const int n;
    int m;

    Eulerian_Trail(int n) : es(n), used_v(n), deg(n), n(n), m(0) {}

    void add_edge(int from, int to) {
        list.emplace_back(from, to), es[from].emplace_back(to, m);
        if (directed)
            deg[from]++, deg[to]--;
        else
            es[to].emplace_back(from, m), deg[from]++, deg[to]++;
        m++;
    }

    pair<int, int> get_edge(int id) { return list[id]; }

    vector<int> trace(int s) {
        stack<edge> st;
        vector<int> ret;
        st.emplace(s, -1);
        while (!st.empty()) {
            int now = st.top().to;
            used_v[now] = true;
            if (es[now].empty()) {
                ret.push_back(st.top().id);
                st.pop();
            } else {
                auto e = es[now].back();
                es[now].pop_back();
                if (used_e[e.id]) continue;
                used_e[e.id] = true, st.push(e);
            }
        }
        ret.pop_back();
        reverse(begin(ret), end(ret));
        return ret;
    }

    vector<vector<int>> eulerian_trail() { // 各連結成分に対してオイラー路を列挙
        vector<vector<int>> ret;
        fill(begin(used_v), end(used_v), false);
        if (directed) {
            for (auto &e : deg)
                if (e != 0) return {};
        } else {
            for (auto &e : deg)
                if (e & 1) return {};
        }
        used_e.assign(m, false);
        for (int i = 0; i < n; i++) {
            if (es[i].empty() || used_v[i]) continue;
            ret.push_back(trace(i));
        }
        return ret;
    }

    vector<vector<int>> semi_eulerian_trail() { // 各連結成分に対して準オイラー路を列挙
        Union_Find_Tree uf(n);
        for (auto &e : list) uf.unite(e.first, e.second);
        vector<vector<int>> group(n);
        for (int i = 0; i < n; i++) { group[uf[i]].emplace_back(i); }
        vector<vector<int>> ret;
        used_e.assign(m, false);
        for (auto &vs : group) {
            if (vs.empty()) continue;
            int s = -1, t = -1;
            if (directed) {
                for (auto &u : vs) {
                    if (abs(deg[u]) > 1)
                        return {};
                    else if (deg[u] == 1) {
                        if (s != -1) return {};
                        s = u;
                    }
                }
            } else {
                for (auto &u : vs) {
                    if (deg[u] & 1) {
                        if (s == -1)
                            s = u;
                        else if (t == -1)
                            t = u;
                        else
                            return {};
                    }
                }
            }
            ret.push_back(trace(s == -1 ? vs.front() : s));
            if (ret.back().empty()) ret.pop_back();
        }
        return ret;
    }
};
