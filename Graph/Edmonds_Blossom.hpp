#pragma once

// Edmonds の花アルゴリズム
// 計算量 O(N^3)

// 概要
// 交互増加道をみつける反復アルゴリズム。
// 交互増加道が見つからなくても花を見つければ、縮約することによってより小さいサイズの問題に帰着できる。

// verirfied with
// https://judge.yosupo.jp/problem/general_matching

#include <bits/stdc++.h>
using namespace std;

void Edmonds_blossom(vector<vector<bool>> es, vector<int> &match) {
    int n = es.size();

    auto contract = [&](vector<int> c) {
        int l = c.size();
        vector<int> mp(n, 0); // 縮約前と縮約後の頂点の対応付け
        vector<int> vs;
        for (auto &e : c) mp[e] = -1;
        int p = 0;
        for (int i = 0; i < n; i++) {
            if (mp[i] != -1) {
                mp[i] = p++;
                vs.push_back(i);
            }
        }
        for (auto &e : c) mp[e] = p;
        vector<vector<bool>> ces(p + 1, vector<bool>(p + 1, false));
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) ces[mp[i]][mp[j]] = (ces[mp[i]][mp[j]] | es[i][j]);
        }
        vector<int> cmatch(p + 1, -1);
        for (int i = 0; i < n; i++) {
            if (match[i] == -1 || (mp[i] == p && mp[match[i]] == p)) continue;
            cmatch[mp[i]] = mp[match[i]];
        }
        Edmonds_blossom(ces, cmatch);
        fill(begin(match), end(match), -1);
        for (int i = 0; i < p; i++) {
            if (cmatch[i] != -1 && cmatch[i] != p) match[vs[i]] = vs[cmatch[i]];
        }
        if (cmatch[p] != -1) {
            int q = cmatch[p];
            for (int i = 0; i < l; i++) {
                if (es[c[i]][vs[q]]) {
                    match[c[i]] = vs[q];
                    match[vs[q]] = c[i];
                    for (int j = 0; j < l - 1; j++) match[c[(i + 1 + j) % l]] = c[(i + 1 + (j ^ 1)) % l];
                    break;
                }
            }
        } else {
            for (int j = 0; j < l - 1; j++) match[c[j]] = c[j ^ 1];
        }
    };

    auto get_path = [&](int v, const vector<int> &pre) {
        vector<int> ret;
        while (pre[v] != -1) {
            ret.push_back(v);
            v = pre[v];
        }
        ret.push_back(v);
        reverse(begin(ret), end(ret));
        return ret;
    };

    auto bfs = [&](auto &&bfs) -> void {
        queue<int> que;
        vector<int> d(n, -1), pre(n, -1), r(n, -1);
        for (int i = 0; i < n; i++) {
            if (match[i] == -1) {
                que.push(i);
                d[i] = 0;
                r[i] = i;
            }
        }
        while (!empty(que)) {
            int i = que.front();
            que.pop();
            for (int j = 0; j < n; j++) {
                if (i == j || !es[i][j] || match[i] == j) continue;
                if (d[j] == -1) {
                    d[j] = d[i] + 1;
                    pre[j] = i;
                    r[j] = r[i];
                    int k = match[j];
                    d[k] = d[j] + 1;
                    pre[k] = j;
                    r[k] = r[j];
                    que.push(k);
                } else if (d[j] % 2 == 0) {
                    vector<int> p = get_path(i, pre), q = get_path(j, pre);
                    if (r[i] != r[j]) {
                        for (int k = 0; k < (int)p.size() - 1; k++) match[p[k]] = p[k ^ 1];
                        for (int k = 0; k < (int)q.size() - 1; k++) match[q[k]] = q[k ^ 1];
                        match[i] = j;
                        match[j] = i;
                        bfs(bfs);
                        return;
                    } else {
                        int t = 0;
                        while (t + 1 < (int)p.size() && t + 1 < (int)q.size() && p[t + 1] == q[t + 1]) t++;
                        vector<int> c;
                        for (int k = t; k < (int)p.size(); k++) c.push_back(p[k]);
                        for (int k = (int)q.size() - 1; k > t; k--) c.push_back(q[k]);
                        contract(c);
                        return;
                    }
                }
            }
        }
    };

    bfs(bfs);
}
