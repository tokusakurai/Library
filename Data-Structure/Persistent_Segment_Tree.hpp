
// 永続 Segment Tree
// 計算量 1 点更新・区間取得：O(log(n))
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// 永続配列とほぼ同様にして実装できる。

// verified with
// https://atcoder.jp/contests/abc253/tasks/abc253_f

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid, bool del = false>
struct Persistent_Segment_Tree {
    using M = typename Monoid::V;

    struct Node {
        Node *lch, *rch;
        M x;

        Node(Node *lch, Node *rch, const M &x) : lch(lch), rch(rch), x(x) {}
    };

    int n;
    unordered_map<int, Node *> root;
    vector<Node *> used;

    Persistent_Segment_Tree(const vector<M> &v, int init_id = 0) { resize(v, init_id); }

    Persistent_Segment_Tree(int n, const M &x, int init_id = 0) { resize(n, x, init_id); }

    ~Persistent_Segment_Tree() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    Node *make_node(Node *lch, Node *rch, const M &x) {
        Node *ret = new Node(lch, rch, x);
        if (del) used.push_back(ret);
        return ret;
    }

    Node *make_node(const M &x) { return make_node(NULL, NULL, x); }

    void resize(const vector<M> &v, int init_id = 0) {
        n = v.size();
        root[init_id] = build(v, 0, n);
    }

    void resize(int n, const M &x, int init_id = 0) { resize(vector<M>(n, x), init_id); }

    Node *merge(Node *lch, Node *rch) { return make_node(lch, rch, Monoid::merge(lch->x, rch->x)); }

    Node *build(const vector<M> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(v, l, m), build(v, m, r));
    }

    void copy(int ref_id, int new_id) {
        assert(root.count(ref_id));
        root[new_id] = root[ref_id];
    }

    Node *update(int i, const M &x, int l, int r, Node *pre) {
        if (r - l == 1) return make_node(x);
        int m = (l + r) >> 1;
        if (i < m) return merge(update(i, x, l, m, pre->lch), pre->rch);
        return merge(pre->lch, update(i, x, m, r, pre->rch));
    }

    // ref_id に対応するデータから派生して new_id に対応する新しいデータを作る
    void update(int ref_id, int new_id, int i, const M &x, bool apply = false) {
        assert(root.count(ref_id));
        root[new_id] = update(i, apply ? Monoid::merge(query(ref_id, i, i + 1), x) : x, 0, n, root[ref_id]);
    }

    M query(int a, int b, int l, int r, Node *now) const {
        if (a >= b || b <= l || r <= a) return Monoid::id;
        if (a <= l && r <= b) return now->x;
        int m = (l + r) >> 1;
        return Monoid::merge(query(a, b, l, m, now->lch), query(a, b, m, r, now->rch));
    }

    M query(int ref_id, int l, int r) {
        assert(root.count(ref_id));
        return query(l, r, 0, n, root[ref_id]);
    }
};
