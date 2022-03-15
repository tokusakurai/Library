
// Li-Chao Tree
// 計算量 構築：O(1)、直線追加：O(log(D))、線分追加：O(log^2(D))　最小値（最大値）クエリ：O(log(D)) （D はクエリの取りうる x 座標の幅）
// 空間計算量 O(Q_1 log(D)+Q_2 log(D))（Q_1, Q_2 はそれぞれ直線追加、線分追加クエリの個数）

// 概要
// Segment Tree の要領で、各区間に 1 つの直線を対応させる。
// このとき、対応させる直線は区間の中央で最小の値を取るものにする。
// 更新する際に遅延操作を組み合わせることで、直線追加を O(log(D)) 個のノードの更新で実現することができる。
// 線分追加クエリは O(log(D)) 個のノードに直線を追加する。

// verified with
// https://judge.yosupo.jp/problem/line_add_get_min
// https://judge.yosupo.jp/problem/segment_add_get_min

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, T min_x, T max_x, bool is_min = true>
struct Li_Chao_Tree {
    struct Line {
        T a, b;

        Line(const T &a, const T &b) : a(a), b(b) {}

        T get(const T &x) const { return a * x + b; }
    };

    struct Node {
        Node *lch, *rch;
        Line l;

        Node(const Line &l) : lch(NULL), rch(NULL), l(l) {}

        Node(const T &a, const T &b) : lch(NULL), rch(NULL), l(a, b) {}
    };

    Node *root;
    const T INF_T = numeric_limits<T>::max() / 2;

    Li_Chao_Tree() : root(NULL) {}

    ~Li_Chao_Tree() { rec_delete(root); }

    void rec_delete(Node *now) {
        if (!now) return;
        rec_delete(now->lch), rec_delete(now->rch);
        delete now;
    }

    Node *add_line(const Line &k, Node *now, const T &l, const T &r) {
        if (!now) return new Node(k);
        T l1 = now->l.get(l), l2 = k.get(l);
        T r1 = now->l.get(r), r2 = k.get(r);
        if (l1 <= l2 && r1 <= r2) return now;
        if (l1 >= l2 && r1 >= r2) {
            now->l = k;
            return now;
        }
        T m = (l + r - 1) / 2;
        T m1 = now->l.get(m), m2 = k.get(m);
        if (m1 > m2) {
            if (l1 <= l2) {
                now->lch = add_line(now->l, now->lch, l, m);
            } else {
                now->rch = add_line(now->l, now->rch, m + 1, r);
            }
            now->l = k;
        } else {
            if (l1 >= l2) {
                now->lch = add_line(k, now->lch, l, m);
            } else {
                now->rch = add_line(k, now->rch, m + 1, r);
            }
        }
        return now;
    }

    void add_line(const T &a, const T &b) { // 直線 y = ax+b を追加
        Line k(is_min ? a : -a, is_min ? b : -b);
        root = add_line(k, root, min_x, max_x);
    }

    Node *add_segment(const T &s, const T &t, const Line &k, Node *now, const T &l, const T &r) {
        if (r < s || t < l) return now;
        if (s <= l && r <= t) return add_line(k, now, l, r);
        T m = (l + r - 1) / 2;
        if (!now) now = new Node(0, INF_T);
        now->lch = add_segment(s, t, k, now->lch, l, m);
        now->rch = add_segment(s, t, k, now->rch, m + 1, r);
        return now;
    }

    void add_segment(const T &l, const T &r, const T &a, const T &b) { // [l,r) に直線 y = ax+b を追加
        Line k(is_min ? a : -a, is_min ? b : -b);
        root = add_segment(l, r - 1, k, root, min_x, max_x);
    }

    T query(const T &x, Node *now, const T &l, const T &r) const {
        if (!now) return INF_T;
        if (l == r) return now->l.get(x);
        T m = (l + r - 1) / 2;
        if (x <= m) return min(now->l.get(x), query(x, now->lch, l, m));
        return min(now->l.get(x), query(x, now->rch, m + 1, r));
    }

    T query(const T &x) const {
        T ret = query(x, root, min_x, max_x);
        return is_min ? ret : -ret;
    }
};
