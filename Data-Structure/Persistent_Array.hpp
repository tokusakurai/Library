
// 永続配列
// 計算量 1 点更新・1 点取得：O(log(n))、複製：O(1)
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// 配列を Segment Tree のように二分木で表す。この二分木の高さを h (= ceil(log(n))) とする。
// 区間を表す二分木のノードをメモリで管理することによって、更新で新たに作られるノードは h 個とすることができる。
// 取得は、h 回二分木を下ることで得られる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Persistent_Array {
    struct Node {
        Node *lch, *rch;
        T x;

        Node(Node *lch, Node *rch, const T &x) : lch(lch), rch(rch), x(x) {}

        Node(Node *lch, Node *rch) : lch(lch), rch(rch) {}
    };

    Node *root;
    vector<Node *> used;
    int n;

    Persistent_Array(const vector<T> &v) { resize(v); }

    Persistent_Array(int m, const T &x) { resize(m, x); }

    Persistent_Array() : root(NULL) {}

    ~Persistent_Array() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    Node *make_node(Node *lch, Node *rch, const T &x) {
        Node *ret = new Node(lch, rch, x);
        used.push_back(ret);
        return ret;
    }

    Node *make_node(const T &x) { return make_node(NULL, NULL, x); }

    Node *make_node(Node *lch, Node *rch) {
        Node *ret = new Node(lch, rch);
        used.push_back(ret);
        return ret;
    }

    void resize(const vector<T> &v) {
        n = v.size();
        root = build(v, 0, n);
    }

    void resize(int m, const T &x) { resize(vector<T>(m, x)); }

    Node *build(const vector<T> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l]);
        int m = (l + r) >> 1;
        return make_node(build(v, l, m), build(v, m, r));
    }

    void copy(const Persistent_Array<T> &a) {
        root = a.root;
        n = a.n;
    }

    Node *change(int i, const T &x, int l, int r, Node *pre) {
        if (r - l == 1) return make_node(x);
        int m = (l + r) >> 1;
        if (i < m) return make_node(change(i, x, l, m, pre->lch), pre->rch);
        return make_node(pre->lch, change(i, x, m, r, pre->rch));
    }

    void change(int i, const T &x) { root = change(i, x, 0, n, root); }

    T get(int i, int l, int r, Node *now) const {
        if (r - l == 1) return now->x;
        int m = (l + r) >> 1;
        if (i < m) return get(i, l, m, now->lch);
        return get(i, m, r, now->rch);
    }

    T get(int i) const { return get(i, 0, n, root); }

    T operator[](int i) const { return get(i); }
};
