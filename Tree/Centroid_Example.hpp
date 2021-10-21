
// 木の重心分解 (例)
// 計算量 重心検出 : O(n)、再帰の深さ : O(log(n))、全体の計算量 : O(n log(n))

// 概要
// 一回の分割で新たにできる木のサイズは元の木の半分以下であるから、分割統治したときの再帰の深さは最大でO(log(V))となる。

// verified with
// https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c

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

    vector<int> si, depth;
    vector<bool> used;
    vector<int> cnt;
    vector<int> memo1, memo2;
    vector<vector<pair<int, int>>> query;
    vector<int> ans;

    Graph(int n) : es(n), n(n), m(0), si(n), depth(n), used(n, false), cnt(n, 0), query(n) {}

    void add_edge(int from, int to) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        m++;
    }

    int calc_size(int now, int pre = -1) {
        si[now] = 1;
        for (auto &e : es[now]) {
            if (e.to == pre || used[e.to]) continue;
            depth[e.to] = depth[now] + 1;
            si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    pair<int, int> search_centroid(int now, int sz, int pre = -1) { // (残りの最大部分木の頂点数、重心)
        pair<int, int> ret = make_pair(INT_MAX, -1);
        int M = 0, S = 1;
        for (auto &e : es[now]) {
            if (e.to == pre || used[e.to]) continue;
            ret = min(ret, search_centroid(e.to, sz, now));
            M = max(M, si[e.to]);
            S += si[e.to];
        }
        M = max(M, sz - S);
        ret = min(ret, make_pair(M, now));
        return ret;
    }

    int centroid(int s) { // 頂点sを含む連結成分の重心を返す
        calc_size(s);
        return search_centroid(s, si[s]).second;
    }

    void solve(int i) {
        for (auto &q : query[i]) {
            if (q.first >= depth[i]) ans[q.second] += cnt[q.first - depth[i]];
        }
    }

    void _dfs1(int now, int pre, bool rev) {
        if (!rev) {
            depth[now] = (pre == -1 ? 0 : depth[pre] + 1);
            cnt[depth[now]]++, memo1.push_back(depth[now]);
        } else {
            cnt[depth[now]]--, memo2.push_back(depth[now]);
        }
        for (auto &e : es[now]) {
            if (e.to == pre || used[e.to]) continue;
            _dfs1(e.to, now, rev);
        }
    }

    void _dfs2(int now, int pre) {
        solve(now);
        for (auto &e : es[now]) {
            if (e.to != pre && !used[e.to]) _dfs2(e.to, now);
        }
    }

    void decompose(int root = 0) {
        int c = centroid(root);

        _dfs1(c, -1, false);
        solve(c);
        for (auto &e : es[c]) {
            if (used[e.to]) continue;
            _dfs1(e.to, c, true);
            _dfs2(e.to, c);
            for (auto &e : memo2) cnt[e]++;
            memo2.clear();
        }
        for (auto &e : memo1) cnt[e]--;
        memo1.clear();

        used[c] = true;
        for (auto &e : es[c]) {
            if (!used[e.to]) decompose(e.to);
        }
    }
};
