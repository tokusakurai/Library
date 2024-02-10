#pragma once

// 長方形の和集合の面積
// 計算量 O(n log(n))

// 概要
// 座標圧縮してから平面走査。range add range min count の遅延セグメント木を用いる。

// verified with
// judge.yosupo.jp/problem/area_of_union_of_rectangles

#include <bits/stdc++.h>
using namespace std;

#include "../Algebraic-Structure/Monoid_Example.hpp"
#include "../Data-Structure/Lazy_Segment_Tree.hpp"

template <typename T>
T rectangle_union_area(const vector<T> &lx, const vector<T> &rx, const vector<T> &ly, const vector<T> &ry) {
    int n = lx.size();
    vector<T> ys(2 * n);
    for (int i = 0; i < n; i++) {
        ys[2 * i] = ly[i];
        ys[2 * i + 1] = ry[i];
    }
    sort(begin(ys), end(ys));
    ys.erase(unique(begin(ys), end(ys)), end(ys));
    int m = ys.size();
    T d = ys[m - 1] - ys[0];
    vector<int> comp_ly(n), comp_ry(n);
    for (int i = 0; i < n; i++) {
        comp_ly[i] = lower_bound(begin(ys), end(ys), ly[i]) - begin(ys);
        comp_ry[i] = lower_bound(begin(ys), end(ys), ry[i]) - begin(ys);
    }
    using P = pair<T, T>;
    vector<P> v(m - 1);
    for (int i = 0; i < m - 1; i++) v[i] = P(0, ys[i + 1] - ys[i]);
    Lazy_Segment_Tree<Min_Count_Add_Acted_Monoid<T, T>> seg(v);
    vector<P> eve(2 * n);
    for (int i = 0; i < n; i++) {
        eve[2 * i] = P(lx[i], i + 1);
        eve[2 * i + 1] = P(rx[i], -i - 1);
    }
    sort(begin(eve), end(eve));
    T ret = 0;
    for (int i = 0; i < 2 * n - 1; i++) {
        if (eve[i].second > 0) {
            int id = eve[i].second - 1;
            seg.update(comp_ly[id], comp_ry[id], 1);
        } else {
            int id = -eve[i].second - 1;
            seg.update(comp_ly[id], comp_ry[id], -1);
        }
        auto [mi, len] = seg.query(0, m - 1);
        ret += T(eve[i + 1].first - eve[i].first) * T(d - (mi == 0 ? len : 0));
    }
    return ret;
}