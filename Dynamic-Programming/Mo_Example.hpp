#pragma once

// Mo のアルゴリズム (例)
// 計算量 O((n+q)√n)

// 概要
// 区間の伸縮を O(1) で行えるため、計算量は O((n+q)√n)

// verified with
// https://atcoder.jp/contests/abc174/tasks/abc174_f

#include <bits/stdc++.h>
using namespace std;

struct query {
    int l, r, id;
    query(int l, int r, int id) : l(l), r(r), id(id) {}
};

// T は配列の要素の型、A はクエリに対する答えの型
template <typename T, typename A>
struct Mo {
    vector<T> a;
    const int n;
    int l, r;
    A ans;
    vector<int> cnt;

    Mo(vector<T> a) : a(a), n(a.size()), l(0), r(0), ans(0), cnt(a.size(), 0) {}

    void insert(int x) {
        if (cnt[a[x]]++ == 0) ans++;
    }

    void insert_left(int x) {}

    void insert_right(int x) {}

    void erase(int x) {
        if (--cnt[a[x]] == 0) ans--;
    }

    void erase_left(int x) {}

    void erase_right(int x) {}

    vector<A> solve(const vector<query> &qs) {
        int q = qs.size();
        if (q == 0) return {};
        int b = ceil(n / sqrt(q));
        if (b <= 0) b = 1;

        auto comp1 = [&](const query &q1, const query &q2) {
            int x = q1.l / b, y = q2.l / b;
            if (x != y) return x < y;
            if (x % 2 == 0) return q1.r < q2.r;
            return q1.r > q2.r;
        };
        auto comp2 = [&](const query &q1, const query &q2) {
            int x = (q1.l + b / 2) / b, y = (q2.l + b / 2) / b;
            if (x != y) return x < y;
            if (x % 2 == 0) return q1.r < q2.r;
            return q1.r > q2.r;
        };
        auto step_num = [&](const vector<query> &qs1) {
            long long ret = 0;
            for (int i = 0; i < q; i++) ret += abs(qs1[i + 1].l - qs1[i].l) + abs(qs1[i + 1].r - qs1[i].r);
            return ret;
        };

        auto qs1 = qs, qs2 = qs;
        sort(begin(qs1), end(qs1), comp1);
        sort(begin(qs2), end(qs2), comp2);
        if (step_num(qs1) > step_num(qs2)) swap(qs1, qs2);

        vector<A> ret(q);
        for (auto &e : qs1) {
            while (e.l < l) insert(--l);
            while (r < e.r) insert(r++);
            while (l < e.l) erase(l++);
            while (e.r < r) erase(--r);
            ret[e.id] = ans;
        }
        return ret;
    }
};
