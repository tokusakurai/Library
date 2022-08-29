
// 根付き木の同型性判定
// 計算量 O(n log(n))

// 概要
// 根付き木の各部分木を同型性に基づいて分類する。
// 部分木にハッシュ値を与え、各頂点の子の部分木のハッシュ値をソートしたものが部分木を特徴づけるものとなっている。

// verified with
// https://judge.yosupo.jp/problem/rooted_tree_isomorphism_classification

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <bool directed = false>
struct Rooted_Tree_Isomorphism {
    struct edge {
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    const int n;
    int m;

    map<vector<int>, int> mp;
    vector<int> res;

    Rooted_Tree_Isomorphism(int n) : es(n), n(n), m(0), res(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int _dfs(int now, int pre = -1) {
        vector<int> chi;
        for (auto &e : es[now]) {
            if (e.to == pre) continue;
            chi.push_back(_dfs(e.to, now));
        }
        sort(begin(chi), end(chi));
        auto it = mp.find(chi);
        if (it == end(mp)) {
            mp[chi] = res[now] = mp.size();
        } else {
            res[now] = it->second;
        }
        return res[now];
    }

    vector<int> build(int root = 0) {
        _dfs(root);
        return res;
    }
};
