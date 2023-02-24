
// 2 次元 Segment Tree
// 計算量 構築：O(n log^2(n))、1 点更新・矩形取得：O(log^2(n))
// 空間計算量 O(n log(n))

// 概要
// Segment Tree の各ノードに Segment Tree を乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリを O(n log(n)) に削減できる。
// y 軸方向に計算したあと x 軸方向について計算するので、可換モノイドであれば十分。

// verified with
// https://judge.yosupo.jp/problem/rectangle_sum
// https://judge.yosupo.jp/problem/point_add_rectangle_sum
// https://codeforces.com/gym/103443/problem/C

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Segment_Tree.hpp"

// C は座標の型
template <typename Commutative_Monoid, typename C>
struct Segment_Tree_2D {
    using M = typename Commutative_Monoid::V;
    int n, m;
    vector<C> xs;
    vector<pair<C, C>> all_points;
    vector<vector<pair<C, C>>> points;
    vector<Segment_Tree<Commutative_Monoid>> segs;

    Segment_Tree_2D() {}

    // 値を変更する箇所を先に全て挿入しておく
    void insert(const C &x, const C &y) {
        xs.push_back(x);
        all_points.emplace_back(x, y);
    }

    void build() {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
        n = xs.size(), m = 1;
        while (m < n) m <<= 1;
        points.resize(2 * m);
        for (auto &p : all_points) {
            auto [x, y] = p;
            int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
            i += m;
            while (i) {
                points[i].emplace_back(y, x);
                i >>= 1;
            }
        }
        for (int i = 0; i < 2 * m; i++) {
            sort(begin(points[i]), end(points[i]));
            points[i].erase(unique(begin(points[i]), end(points[i])), end(points[i]));
            segs.emplace_back((int)points[i].size(), Commutative_Monoid::id);
        }
    }

    void update(const C &x, const C &y, const M &a, bool apply = false) {
        int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
        i += m;
        while (i) {
            int j = lower_bound(begin(points[i]), end(points[i]), make_pair(y, x)) - begin(points[i]);
            segs[i].update(j, a, apply);
            i >>= 1;
        }
    }

    M query(const C &lx, const C &rx, const C &ly, const C &ry) const {
        M L = Commutative_Monoid::id, R = Commutative_Monoid::id;
        int li = lower_bound(begin(xs), end(xs), lx) - begin(xs);
        int ri = lower_bound(begin(xs), end(xs), rx) - begin(xs);
        li += m, ri += m;
        C mi = (xs.empty() ? 0 : xs.front());
        while (li < ri) {
            if (li & 1) {
                int l = lower_bound(begin(points[li]), end(points[li]), make_pair(ly, mi)) - begin(points[li]);
                int r = lower_bound(begin(points[li]), end(points[li]), make_pair(ry, mi)) - begin(points[li]);
                L = Commutative_Monoid::merge(L, segs[li].query(l, r));
                li++;
            }
            if (ri & 1) {
                ri--;
                int l = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ly, mi)) - begin(points[ri]);
                int r = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ry, mi)) - begin(points[ri]);
                R = Commutative_Monoid::merge(segs[ri].query(l, r), R);
            }
            li >>= 1, ri >>= 1;
        }
        return Commutative_Monoid::merge(L, R);
    }
};
