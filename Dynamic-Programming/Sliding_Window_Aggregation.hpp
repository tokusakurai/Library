
// SWAG(Sliding Window Aggregation)
// 計算量：各クエリならし O(1)

// 概要
// Monoid の列を持って、左を削除、右に追加、全体の積の計算が行える。
// 適当な位置で区切ってそれより左側の累積積と右側の総積を持つ。
// pop_front は左側の累積積を pop_back すればよい。右に追加は右側の総積に右から作用させればよい。

// verified with
// https://judge.yosupo.jp/problem/queue_operate_all_composite
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_3_D

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
struct Sliding_Window_Aggregation {
    using M = typename Monoid::V;
    vector<M> left_prod, right;
    M right_prod;

    Sliding_Window_Aggregation(int n) {
        left_prod.reserve(n + 1), right.reserve(n + 1);
        left_prod.push_back(Monoid::id);
        right_prod = Monoid::id;
    }

    Sliding_Window_Aggregation() : Sliding_Window_Aggregation(0) {}

    void push_back(const M &x) {
        right.push_back(x);
        right_prod = Monoid::merge(right_prod, x);
    }

    void pop_front() {
        if ((int)left_prod.size() == 1) {
            assert(!right.empty());
            reverse(begin(right), end(right));
            right.pop_back();
            for (auto &e : right) left_prod.push_back(Monoid::merge(e, left_prod.back()));
            right.clear();
            right_prod = Monoid::id;
        } else {
            left_prod.pop_back();
        }
    }

    M query() const { return Monoid::merge(left_prod.back(), right_prod); }
};

template <typename Monoid>
struct Two_Pointer_Query {
    using M = typename Monoid::V;
    const int n;
    int left, right;
    const vector<M> a;
    Sliding_Window_Aggregation<Monoid> swag;

    Two_Pointer_Query(const vector<M> &a) : n(a.size()), left(0), right(0), a(a), swag(n) {}

    M query(int l, int r) {
        assert(left <= l && right <= r && r <= n);
        while (right < r) swag.push_back(a[right++]);
        while (left < l) swag.pop_front(), left++;
        return swag.query();
    }
};
