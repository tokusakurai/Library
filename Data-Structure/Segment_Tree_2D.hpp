
// 2次元Segment Tree
// 計算量 構築 : O(N*log(N)^2)、1点更新・矩形取得 : O(log(N)^2)
// 空間計算量 O(N*log(N))

// 概要
// Segment Treeの各ノードにSegment Treeを乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリをO(N*log(N))に削減できる。
// y軸方向に計算したあとx軸方向について計算するので、可換モノイドであれば十分。
// ただし、値更新はfを作用する形でないといけない。

// verified with
// https://judge.yosupo.jp/problem/rectangle_sum
// https://judge.yosupo.jp/problem/point_add_rectangle_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Segment_Tree.hpp"

template <typename T>
struct Segment_Tree_2D {
    using F = function<T(T, T)>;
    int n;
    vector<vector<int>> ids;
    vector<Segment_Tree<T>> segs;
    const F f;
    const T e1;

    Segment_Tree_2D(int m, const F &f, const T &e1) : f(f), e1(e1) {
        n = 1;
        while (n < m) n <<= 1;
        ids.resize(2 * n);
    }

    void insert(int x, int y) { // 値を変更する箇所を先に全て挿入しておく
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
            segs.emplace_back((int)ids[i].size(), e1, f, e1);
        }
    }

    void change(int x, int y, const T &a) { // fでaを作用する
        x += n;
        while (x) {
            segs[x].change(lower_bound(begin(ids[x]), end(ids[x]), y) - begin(ids[x]), a, false);
            x >>= 1;
        }
    }

    T query(int lx, int rx, int ly, int ry) const {
        T L = e1, R = e1;
        lx += n, rx += n;
        while (lx < rx) {
            if (lx & 1) {
                int l = lower_bound(begin(ids[lx]), end(ids[lx]), ly) - begin(ids[lx]);
                int r = lower_bound(begin(ids[lx]), end(ids[lx]), ry) - begin(ids[lx]);
                L = f(L, segs[lx].query(l, r));
                lx++;
            }
            if (rx & 1) {
                rx--;
                int l = lower_bound(begin(ids[rx]), end(ids[rx]), ly) - begin(ids[rx]);
                int r = lower_bound(begin(ids[rx]), end(ids[rx]), ry) - begin(ids[rx]);
                R = f(segs[rx].query(l, r), R);
            }
            lx >>= 1, rx >>= 1;
        }
        return f(L, R);
    }
};
