
// 2 次元双対 Segment Tree
// 計算量 構築：O(n log^2(n)), 矩形更新・1 点取得：O(log^2(n))
// 空間計算量 O(n log(n))

// 概要
// Segment Tree の各ノードに双対 Segment Tree を乗せている。
// あらかじめ座標圧縮しておき、必要な部分だけ残すことでメモリを O(n log(n)) に削減できる。
// 遅延評価を再伝搬させてないので、作用素が可換モノイドであれば十分。

// verified with
// https://atcoder.jp/contests/tkppc6-1/tasks/tkppc6_1_n

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Dual_Segment_Tree.hpp"

// S は座標の型
template <typename T, typename S>
struct Dual_Segment_Tree_2D {
    using H = function<T(T, T)>;
    int n;
    vector<S> xs;
    vector<pair<S, S>> all_points;
    vector<vector<pair<S, S>>> points;
    vector<Dual_Segment_Tree<T>> segs;
    const H h;
    const T e2;

    Dual_Segment_Tree_2D(const H &h, const T &e2) : h(h), e2(e2) {}

    // 値が欲しい箇所を先に全て挿入しておく
    void insert(const S &x, const S &y) {
        xs.push_back(x);
        all_points.emplace_back(x, y);
    }

    void build() {
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
        int m = xs.size();
        n = 1;
        while (n < m) n <<= 1;
        points.resize(2 * n);
        for (auto &p : all_points) {
            auto [x, y] = p;
            int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
            i += n;
            while (i) {
                points[i].emplace_back(y, x);
                i >>= 1;
            }
        }
        for (int i = 0; i < 2 * n; i++) {
            sort(begin(points[i]), end(points[i]));
            points[i].erase(unique(begin(points[i]), end(points[i])), end(points[i]));
            segs.emplace_back((int)points[i].size(), h, e2);
        }
    }

    void apply(const S &lx, const S &rx, const S &ly, const S &ry, const T &a) {
        int li = lower_bound(begin(xs), end(xs), lx) - begin(xs);
        int ri = lower_bound(begin(xs), end(xs), rx) - begin(xs);
        li += n, ri += n;
        S mi = (xs.empty() ? 0 : xs.front());
        while (li < ri) {
            if (li & 1) {
                int l = lower_bound(begin(points[li]), end(points[li]), make_pair(ly, mi)) - begin(points[li]);
                int r = lower_bound(begin(points[li]), end(points[li]), make_pair(ry, mi)) - begin(points[li]);
                segs[li].apply(l, r, a);
                li++;
            }
            if (ri & 1) {
                ri--;
                int l = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ly, mi)) - begin(points[ri]);
                int r = lower_bound(begin(points[ri]), end(points[ri]), make_pair(ry, mi)) - begin(points[ri]);
                segs[ri].apply(l, r, a);
            }
            li >>= 1, ri >>= 1;
        }
    }

    T get(const S &x, const S &y) {
        T ret = e2;
        int i = lower_bound(begin(xs), end(xs), x) - begin(xs);
        i += n;
        while (i) {
            int j = lower_bound(begin(points[i]), end(points[i]), make_pair(y, x)) - begin(points[i]);
            ret = h(ret, segs[i].get(j));
            i >>= 1;
        }
        return ret;
    }
};
