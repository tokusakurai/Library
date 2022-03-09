
// 永続配列
// 計算量 更新・取得：O(log(n))
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// 更新：時刻 s での配列の i 番目の要素を x に変えたものを時刻 t での配列とする
// 取得：時刻 t での配列の i 番目の要素を取得
// 配列を Segment Tree のように二分木で表す。この二分木の高さを h (= ceil(log(n))) とする。
// 区間を表す二分木のノードをメモリで管理することによって、更新で新たに作られるノードは h 個とすることができる。
// 取得は、h 回二分木を下ることで得られる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, typename S = int> // 配列の要素の型、時刻の型
struct Persistent_Array {
    struct Node {
        Node *lch, *rch;
        T x;

        Node(const T &x) : lch(NULL), rch(NULL), x(x) {}

        Node() : Node(0) {}
    };

    vector<Node *> roots, used;
    vector<S> ts;
    int n;

    Persistent_Array(const vector<T> &v, S t = -1) {
        int m = v.size();
        n = 1;
        while (n < m) n <<= 1;
        ts.push_back(t);
        roots.push_back(make_node());
        init(v, 0, n, roots[0]);
    }

    Persistent_Array(int m, const T &x, S t = -1) : Persistent_Array(vector<T>(m, x), t) {}

    ~Persistent_Array() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    Node *make_node(const T &x) {
        Node *ret = new Node(x);
        used.push_back(ret);
        return ret;
    }

    Node *make_node() {
        Node *ret = new Node();
        used.push_back(ret);
        return ret;
    }

    void init(const vector<T> &v, int l, int r, Node *now) {
        if (r - l == 1) {
            if (l < (int)v.size()) now->x = v[l];
            return;
        }
        int m = (l + r) >> 1;
        now->lch = make_node(), now->rch = make_node();
        init(v, l, m, now->lch), init(v, m, r, now->rch);
    }

    void change(const S &s, const S &t, int i, const T &x) { // 時刻 s での配列の i 番目の要素を x に変えたものを時刻 t での配列とする
        int k = lower_bound(begin(ts), end(ts), s) - begin(ts);
        ts.push_back(t);
        if (i == -1) {
            roots.push_back(roots[k]);
            return;
        }
        roots.push_back(make_node());
        Node *now = roots.back(), *pre = roots[k];
        int l = 0, r = n;
        while (true) {
            if (r - l == 1) {
                now->x = x;
                break;
            }
            now->lch = pre->lch, now->rch = pre->rch;
            int m = (l + r) >> 1;
            if (i < m) {
                now->lch = make_node();
                now = now->lch, pre = pre->lch;
                r = m;
            } else {
                now->rch = make_node();
                now = now->rch, pre = pre->rch;
                l = m;
            }
        }
    }

    T query(const S &t, int i) const { // 時刻 t での配列の i 番目の要素を取得
        int k = lower_bound(begin(ts), end(ts), t) - begin(ts);
        int l = 0, r = n;
        Node *now = roots[k];
        while (r - l > 1) {
            int m = (l + r) >> 1;
            if (i < m) {
                now = now->lch;
                r = m;
            } else {
                now = now->rch;
                l = m;
            }
        }
        return now->x;
    }
};
