
// DM 分解
// 計算量 O((e√(n+m)+n+m) (e は辺の総数)

// 概要
// 2 部グラフの隣接行列の行と列を並び替えて、できるだけ細かくなるようにブロック三角化する。
// 左側、右側の頂点集合をそれぞれ L,R とする。R の部分集合 S について、
// Γ(S) := {i∈L|i と S の頂点を結ぶ辺がある}
// p(S) := |Γ(S)|-|S|
// とすると、p の最小値を与える R の部分集合全体は部分束をなすので、半順序を構成することができる。
// まず、グラフの最大マッチングを 1 つ求め、これを M とする。
// 以下、M に含まれる辺は両方向に、M に含まれない辺は左から右に貼ってできる有向グラフを考える。
// V_0 を C\∂M に到達可能な頂点集合、V_∞ を R\∂M から到達可能な頂点集合とする。
// V_1,V_2,... は V_0 と V_∞ を除いた集合を強連結成分分解したときの成分のトポロジカルソート順となる。
// 各 V_k が DM 分解の各ブロックに含まれる頂点集合となる。

// verified with
// https://atcoder.jp/contests/abc223/tasks/abc223_g
// https://domjudge.qoj.ac/team/problems/230/text

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Graph/Hopcroft-Karp.hpp"

struct Dulmage_Mendelsohn_Decomposition : Hopcroft_Karp {
    using BM = Hopcroft_Karp;
    vector<vector<int>> rs;
    vector<vector<int>> ids_l, ids_r; // 左側と右側のブロック
    vector<int> comp_l, comp_r;       // 属するブロックの番号
    vector<int> vs;

    Dulmage_Mendelsohn_Decomposition(int n, int m) : BM(n, m), rs(n), comp_l(n), comp_r(m) {}

    void _dfs(int now, int col) {
        if (comp_l[now] != n + 1) return;
        comp_l[now] = col;
        for (auto &e : this->es[now]) {
            int to = this->match[e];
            if (to != -1) _dfs(to, col);
        }
        if (col > 0) vs.push_back(now);
    }

    void _rdfs(int now, int col) {
        if (comp_l[now] != n + 1) return;
        comp_l[now] = col;
        for (auto &e : rs[now]) _rdfs(e, col);
    }

    void decompose() {
        this->max_matching();
        for (int i = 0; i < n; i++) {
            for (auto &e : this->es[i]) {
                int to = this->match[e];
                if (to != -1) rs[to].push_back(i);
            }
        }
        fill(begin(comp_l), end(comp_l), n + 1);
        for (int i = 0; i < n; i++) {
            bool flag = true;
            for (auto &e : es[i]) {
                if (this->match[e] == -1) {
                    _rdfs(i, 0);
                    flag = false;
                } else if (this->match[e] == i) {
                    flag = false;
                }
            }
            if (flag) _dfs(i, -1);
        }
        for (int i = 0; i < n; i++) _dfs(i, 1);
        for (int i = 0; i < n; i++) {
            if (comp_l[i] > 0) comp_l[i] = n + 1;
        }
        reverse(begin(vs), end(vs));
        int cnt = 1;
        for (auto &e : vs) {
            if (comp_l[e] == n + 1) _rdfs(e, cnt++);
        }
        for (int i = 0; i < n; i++) {
            if (comp_l[i] == -1) comp_l[i] = cnt;
        }
        for (int i = 0; i < m; i++) {
            if (this->match[i] == -1) {
                comp_r[i] = 0;
            } else {
                comp_r[i] = comp_l[this->match[i]];
            }
        }
        ids_l.resize(cnt + 1), ids_r.resize(cnt + 1);
        for (int i = 0; i < m; i++) {
            if (this->match[i] == -1) ids_r[0].push_back(i);
        }
        vector<bool> used(n, false);
        for (int i = 0; i < m; i++) {
            int e = this->match[i];
            if (e != -1) {
                ids_l[comp_l[e]].push_back(e);
                ids_r[comp_r[i]].push_back(i);
                used[e] = true;
            }
        }
        for (int i = 0; i < n; i++) {
            if (!used[i]) ids_l[cnt].push_back(i);
        }
    }
};
