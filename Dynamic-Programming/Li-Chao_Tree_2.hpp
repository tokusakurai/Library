#pragma once

// Li-Chao Tree (オフライン)
// 計算量 構築：O(N)、直線追加：O(log(Q))、線分追加：O(log^2(Q))　最小値 (最大値)クエリ：O(log(Q)) (Q は求値クエリの個数)
// 空間計算量 O(N)

// 概要
// 求値クエリに使う座標があらかじめわかってる場合、その座標で区切ることで Q 個の区間を考えればよくなる。

// verified with
// https://judge.yosupo.jp/problem/line_add_get_min
// https://judge.yosupo.jp/problem/segment_add_get_min

#include <bits/stdc++.h>
using namespace std;

template <typename T, bool is_min = true>
struct Li_Chao_Tree {
    struct Line {
        T a, b;

        Line(const T &a, const T &b) : a(a), b(b) {}

        T get(const T &x) const { return a * x + b; }
    };

    const T INF_T = numeric_limits<T>::max() / 2;
    vector<Line> ls;
    vector<T> xs;
    int n;

    Li_Chao_Tree(const vector<T> &v) {
        xs = v;
        sort(begin(xs), end(xs));
        xs.erase(unique(begin(xs), end(xs)), end(xs));
        n = xs.size();
        int m = 1;
        while (m < n) m <<= 1;
        ls.assign(2 * m, {0, INF_T});
    }

    void add_line(const Line &k, int i, int l, int r) {
        T l1 = ls[i].get(xs[l]), l2 = k.get(xs[l]);
        T r1 = ls[i].get(xs[r]), r2 = k.get(xs[r]);
        if (l1 <= l2 && r1 <= r2) return;
        if (l1 >= l2 && r1 >= r2) {
            ls[i] = k;
            return;
        }
        int m = (l + r - 1) / 2;
        T m1 = ls[i].get(xs[m]), m2 = k.get(xs[m]);
        if (m1 > m2) {
            if (l1 <= l2) {
                add_line(ls[i], 2 * i, l, m);
            } else {
                add_line(ls[i], 2 * i + 1, m + 1, r);
            }
            ls[i] = k;
        } else {
            if (l1 >= l2) {
                add_line(k, 2 * i, l, m);
            } else {
                add_line(k, 2 * i + 1, m + 1, r);
            }
        }
    }

    // 直線 y = ax+b を追加
    void add_line(const T &a, const T &b) {
        if (n == 0) return;
        Line k(is_min ? a : -a, is_min ? b : -b);
        add_line(k, 1, 0, n - 1);
    }

    void add_segment(int s, int t, const Line &k, int i, int l, int r) {
        if (r < s || t < l) return;
        if (s <= l && r <= t) return add_line(k, i, l, r);
        T m = (l + r - 1) / 2;
        add_segment(s, t, k, 2 * i, l, m);
        add_segment(s, t, k, 2 * i + 1, m + 1, r);
    }

    // [l,r) に直線 y = ax+b を追加
    void add_segment(const T &l, const T &r, const T &a, const T &b) {
        if (n == 0) return;
        int s = lower_bound(begin(xs), end(xs), l) - begin(xs);
        int t = lower_bound(begin(xs), end(xs), r) - begin(xs);
        if (t == n || xs[t] >= r) t--;
        Line k(is_min ? a : -a, is_min ? b : -b);
        add_segment(s, t, k, 1, 0, n - 1);
    }

    T query(int p, int i, int l, int r) const {
        if (l == r) return ls[i].get(xs[p]);
        int m = (l + r - 1) / 2;
        if (p <= m) return min(ls[i].get(xs[p]), query(p, 2 * i, l, m));
        return min(ls[i].get(xs[p]), query(p, 2 * i + 1, m + 1, r));
    }

    T query(const T &x) const {
        int p = lower_bound(begin(xs), end(xs), x) - begin(xs);
        T ret = query(p, 1, 0, n - 1);
        return is_min ? ret : -ret;
    }
};
