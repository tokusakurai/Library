
// 2次元双対Segment Tree
// 計算量 構築 : O(N*log(N)^2)、矩形更新・1点取得 : O(log(N)^2)
// 空間計算量 O(N*log(N))

// 概要
// Segment Treeの各ノードに双対Segment Treeを乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリをO(N*log(N))に削減できる。
// 遅延評価を再伝搬させてないので、作用素が可換モノイドであれば十分。

// verified with
// https://atcoder.jp/contests/tkppc6-1/tasks/tkppc6_1_n

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Dual_Segment_Tree.hpp"

template <typename T>
struct Dual_Segment_Tree_2D {
    using H = function<T(T, T)>;
    int n;
    vector<vector<int>> ids;
    vector<Dual_Segment_Tree<T>> segs;
    const H h;
    const T e2;

    Dual_Segment_Tree_2D(int m, const H &h, const T &e2) : h(h), e2(e2) {
        n = 1;
        while (n < m) n <<= 1;
        ids.resize(2 * n);
    }

    void insert(int x, int y) { // 値が欲しい箇所を先に全て挿入しておく
        x += n;
        while (x) {
            ids[x].push_back(y);
            x >>= 1;
        }
    }

    void build() {
        for (int i = 0; i < 2 * n; i++) {
            sort(begin(ids[i]), end(ids[i]));
            ids[i].erase(unique(begin(ids[i]), end(ids[i])), end(ids[i]));
            segs.emplace_back((int)ids[i].size(), h, e2);
        }
    }

    void apply(int lx, int rx, int ly, int ry, const T &x) {
        lx += n, rx += n;
        while (lx < rx) {
            if (lx & 1) {
                int l = lower_bound(begin(ids[lx]), end(ids[lx]), ly) - begin(ids[lx]);
                int r = lower_bound(begin(ids[lx]), end(ids[lx]), ry) - begin(ids[lx]);
                segs[lx].apply(l, r, x);
                lx++;
            }
            if (rx & 1) {
                rx--;
                int l = lower_bound(begin(ids[rx]), end(ids[rx]), ly) - begin(ids[rx]);
                int r = lower_bound(begin(ids[rx]), end(ids[rx]), ry) - begin(ids[rx]);
                segs[rx].apply(l, r, x);
            }
            lx >>= 1, rx >>= 1;
        }
    }

    T get(int x, int y) {
        x += n;
        T ret = e2;
        while (x) {
            ret = h(ret, segs[x].get(lower_bound(begin(ids[x]), end(ids[x]), y) - begin(ids[x])));
            x >>= 1;
        }
        return ret;
    }
};