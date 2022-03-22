
// Dinic 法（最大流）
// 計算量 O(mn^2)

// 概要
// BFS で残余グラフにおける始点から各点の最短距離を確定 -> 始点から終点まで最短路で結ぶ増加パスを DFS で探索。
// このステップを始点から終点までの増加パスが存在しなくなるまで行う。
// 各ステップで最短距離は増加するので、ステップ回数は n-1 回以下。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=GRL_6_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename F> // 流量の型
struct Dinic {
    struct edge {
        int to;
        F cap;
        int rev;
        edge(int to, F cap, int rev) : to(to), cap(cap), rev(rev) {}
    };

    vector<vector<edge>> es;
    vector<int> d, pos;
    const F INF_F = numeric_limits<F>::max() / 2;
    const int n;

    Dinic(int n) : es(n), d(n), pos(n), n(n) {}

    void add_edge(int from, int to, F cap, bool directed = true) {
        es[from].emplace_back(to, cap, (int)es[to].size());
        es[to].emplace_back(from, directed ? 0 : cap, (int)es[from].size() - 1);
    }

    bool _bfs(int s, int t) {
        fill(begin(d), end(d), -1);
        queue<int> que;
        d[s] = 0;
        que.push(s);
        while (!que.empty()) {
            int i = que.front();
            que.pop();
            for (auto &e : es[i]) {
                if (e.cap > 0 && d[e.to] == -1) {
                    d[e.to] = d[i] + 1;
                    que.push(e.to);
                }
            }
        }
        return d[t] != -1;
    }

    F _dfs(int now, int t, F flow) {
        if (now == t) return flow;
        for (int &i = pos[now]; i < (int)es[now].size(); i++) {
            edge &e = es[now][i];
            if (e.cap > 0 && d[e.to] > d[now]) {
                F f = _dfs(e.to, t, min(flow, e.cap));
                if (f > 0) {
                    e.cap -= f;
                    es[e.to][e.rev].cap += f;
                    return f;
                }
            }
        }
        return 0;
    }

    F max_flow(int s, int t) { // 操作後の d 配列は最小カットの 1 つを表す（0 以上なら s 側、-1 なら t 側）
        F flow = 0;
        while (_bfs(s, t)) {
            fill(begin(pos), end(pos), 0);
            F f = 0;
            while ((f = _dfs(s, t, INF_F)) > 0) flow += f;
        }
        return flow;
    }
};
