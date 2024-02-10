#pragma once

// Mo のアルゴリズム (雛形)
// 計算量 αq√n + O(n) (α は区間を伸縮させるのに必要な計算量)

// 概要
// 配列が静的、クエリがオフラインのときに用いることができる。
// 配列をサイズ b ごとのバケットに分割し、クエリを (区間の左端のブロック、区間の右端) のペアでソートする。
// 区間を伸縮させることでクエリに答えていくことを考える。
// 区間の右端の伸縮回数：n^2/2b + O(n)
// 区間の左端の伸縮回数：qb
// トータルでの伸縮回数：qb + n^2/2b + O(n) = q√2n + O(n) (b = n/√2q のとき)
// さらに、バケットを [0,b),[b,2b),... とするものと [0,b/2),[b/2,3b/2),... とするもので小さい方を選ぶことで b = n/√q のとき q√n + O(n) 回に落とせる

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
            for (int i = 0; i < q - 1; i++) ret += abs(qs1[i + 1].l - qs1[i].l) + abs(qs1[i + 1].r - qs1[i].r);
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
