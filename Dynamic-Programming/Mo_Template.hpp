
// Moのアルゴリズム(雛形)
// 計算量 O(α*(N+Q)*√N) (αは区間を伸縮させるのに必要な計算量)

// 概要
// 配列が静的、クエリがオフラインのときに用いることができる。
// 配列をサイズO(√N)ごとのバケットに分割し、クエリを(区間の左端のブロック、区間の右端)のペアでソートする。
// 区間を伸縮させることでクエリに答えていくことを考える。
// 区間の右端の伸縮回数 : O(N*√N)
// 区間の左端の伸縮回数 : O(Q*√N)
// トータルでの伸縮回数 : O((N+Q)*√N)

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct query {
    int l, r, id;
    query(int l, int r, int id) : l(l), r(r), id(id) {}
};

template <typename T, typename Q> // Tは配列の要素の型、Qはクエリに対する答えの型
struct Mo {
    vector<T> a;
    const int n;
    int l, r;
    Q ans;

    Mo(vector<T> a) : a(a), n(a.size()), l(0), r(0), ans(0) {}

    void insert(int x) {}

    void insert_left(int x) {}

    void insert_right(int x) {}

    void erase(int x) {}

    void erase_left(int x) {}

    void erase_right(int x) {}

    vector<Q> solve(int bucket_size, vector<query> qs) {
        vector<Q> ret(qs.size());
        sort(begin(qs), end(qs), [&](query a, query b) {
            int A = (a.l) / bucket_size, B = (b.l) / bucket_size;
            if (A != B) return A < B;
            if (A % 2 == 0) return a.r < b.r;
            return a.r > b.r;
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
