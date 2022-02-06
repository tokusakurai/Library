
// Mo のアルゴリズム（例）
// 計算量 O((n+q)√n)

// 概要
// 区間の伸縮を O(1) で行えるため、計算量は O((n+q)√n)

// verified with
// https://atcoder.jp/contests/abc174/tasks/abc174_f

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct query {
    int l, r, id;
    query(int l, int r, int id) : l(l), r(r), id(id) {}
};

template <typename T, typename Q>
struct Mo {
    vector<T> a;
    const int n;
    int l, r;
    Q ans;
    vector<int> cnt;

    Mo(vector<T> a) : a(a), n(a.size()), l(0), r(0), ans(0), cnt(a.size(), 0) {}

    void insert(int x) {
        if (cnt[a[x]]++ == 0) ans++;
    }

    void insert_left(int x) { insert(x); }

    void insert_right(int x) { insert(x); }

    void erase(int x) {
        if (--cnt[a[x]] == 0) ans--;
    }

    void erase_left(int x) { erase(x); }

    void erase_right(int x) { erase(x); }

    vector<Q> solve(int bucket_size, vector<query> qs) {
        vector<Q> ret(qs.size());
        sort(begin(qs), end(qs), [&](query p, query q) {
            int A = (p.l) / bucket_size, B = (q.l) / bucket_size;
            if (A != B) return A < B;
            if (A % 2 == 0) return p.r < q.r;
            return p.r > q.r;
        });
        for (auto &e : qs) {
            while (e.l < l) insert(--l);
            while (r < e.r) insert(r++);
            while (l < e.l) erase(l++);
            while (e.r < r) erase(--r);
            ret[e.id] = ans;
        }
        return ret;
    }
};
