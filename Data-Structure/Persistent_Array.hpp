
// 永続配列
// 計算量 1 点更新・1 点取得：O(log(n))、複製：O(1)
// 空間計算量 O(n+q log(n)) (q はクエリの回数)

// 概要
// 配列を Segment Tree のように二分木で表す。この二分木の高さを h (= ceil(log(n))) とする。
// 区間を表す二分木のノードをメモリで管理することによって、更新で新たに作られるノードは h 個とすることができる。
// 取得は、h 回二分木を下ることで得られる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T, bool del = false>
struct Persistent_Array {
    struct Node {
        Node *lch, *rch;
        T x;

        Node(Node *lch, Node *rch, const T &x) : lch(lch), rch(rch), x(x) {}

        Node(Node *lch, Node *rch) : lch(lch), rch(rch) {}
    };

    int n;
    unordered_map<int, Node *> root;
    vector<Node *> used;

    Persistent_Array(const vector<T> &v, int init_id = 0) { resize(v, init_id); }

    Persistent_Array(int n, const T &x, int init_id = 0) { resize(n, x, init_id); }

    ~Persistent_Array() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    Node *make_node(Node *lch, Node *rch, const T &x) {
        Node *ret = new Node(lch, rch, x);
        if (del) used.push_back(ret);
        return ret;
    }

    Node *make_node(const T &x) { return make_node(NULL, NULL, x); }

    Node *make_node(Node *lch, Node *rch) {
        Node *ret = new Node(lch, rch);
        if (del) used.push_back(ret);
        return ret;
    }

    void resize(const vector<T> &v, int init_id = 0) {
        n = v.size();
        root[init_id] = build(v, 0, n);
    }

    void resize(int n, const T &x, int init_id = 0) { resize(vector<T>(n, x), init_id); }

    Node *build(const vector<T> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l]);
        int m = (l + r) >> 1;
        return make_node(build(v, l, m), build(v, m, r));
    }

    void copy(int ref_id, int new_id) {
        assert(root.count(ref_id));
        root[new_id] = root[ref_id];
    }

    Node *update(int i, const T &x, int l, int r, Node *pre) {
        if (r - l == 1) return make_node(x);
        int m = (l + r) >> 1;
        if (i < m) return make_node(update(i, x, l, m, pre->lch), pre->rch);
        return make_node(pre->lch, update(i, x, m, r, pre->rch));
    }

    // ref_id に対応するデータから派生して new_id に対応する新しいデータを作る
    void update(int ref_id, int new_id, int i, const T &x) {
        assert(root.count(ref_id));
        root[new_id] = update(i, x, 0, n, root[ref_id]);
    }

    T get(int i, int l, int r, Node *now) const {
        if (r - l == 1) return now->x;
        int m = (l + r) >> 1;
        if (i < m) return get(i, l, m, now->lch);
        return get(i, m, r, now->rch);
    }

    T get(int ref_id, int i) {
        assert(root.count(ref_id));
        return get(i, 0, n, root[ref_id]);
    }
};
