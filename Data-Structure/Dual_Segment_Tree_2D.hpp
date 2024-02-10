#pragma once

// 2 次元双対 Segment Tree
// 計算量 構築：O(n log^2(n)), 矩形更新・1 点取得：O(log^2(n))
// 空間計算量 O(n log(n))

// 概要
// Segment Tree の各ノードに双対 Segment Tree を乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリを O(n log(n)) に削減できる。
// 遅延評価を再伝搬させてないので、作用素が可換モノイドであれば十分。

// verified with
// https://atcoder.jp/contests/tkppc6-1/tasks/tkppc6_1_n

#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Dual_Segment_Tree.hpp"

// C は座標の型
template <typename Commutative_Operator, typename C>
struct Dual_Segment_Tree_2D {
    using O = typename Commutative_Operator::V;
    int n, m;
    vector<C> xs;
    vector<pair<C, C>> all_points;
    vector<vector<pair<C, C>>> points;
    vector<Dual_Segment_Tree<Commutative_Operator>> segs;

    Dual_Segment_Tree_2D() {}

    // 値が欲しい箇所を先に全て挿入しておく
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
            segs.emplace_back((int)points[i].size());
        }
    }

    void update(const C &lx, const C &rx, const C &ly, const C &ry, const O &a) {
        int li = lower_bound(begin(xs), end(xs), lx) - begin(xs);
        int ri = lower_bound(begin(xs), end(xs), rx) - begin(xs);
        li += m, ri += m;
        C mi = (xs.empty() ? 0 : xs.front());
        while (li < ri) {
            if (li & 1) {
                int l = lower_bound(begin(points[li]), end(points[li]), make_pair(ly, mi)) - begin(points[li]);
                int r = lower_bound(begin(points[li]), end(points[li]), make_pair(ry, mi)) - begin(points[li]);
                segs[li].update(l, r, a);
                li++;
            }
            if (ri & 1) {
                ri--;
                int l = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ly, mi)) - begin(points[ri]);
                int r = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ry, mi)) - begin(points[ri]);
                segs[ri].update(l, r, a);
            }
            li >>= 1, ri >>= 1;
        }
    }

    O get(const C &x, const C &y) {
        O ret = Commutative_Operator::id;
        int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
        i += m;
        while (i) {
            int j = lower_bound(begin(points[i]), end(points[i]), make_pair(y, x)) - begin(points[i]);
            ret = Commutative_Operator::merge(ret, segs[i].get(j));
            i >>= 1;
        }
        return ret;
    }
};
