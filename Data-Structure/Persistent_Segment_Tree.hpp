
// 永続 Segment Tree
// 計算量 1 点更新・区間取得：O(log(n))、複製：O(1)
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// 永続配列とほぼ同様にして実装できる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
struct Persistent_Segment_Tree {
    using F = function<Monoid(Monoid, Monoid)>;

    struct Node {
        Node *lch, *rch;
        Monoid x;

        Node(Node *lch, Node *rch, const Monoid &x) : lch(lch), rch(rch), x(x) {}
    };

    Node *root;
    vector<Node *> used;
    int n;
    const F f;
    const Monoid e1;

    Persistent_Segment_Tree(const vector<Monoid> &v, const F &f, const Monoid &e1) : f(f), e1(e1) { resize(v); }

    Persistent_Segment_Tree(int m, const Monoid &x, const F &f, const Monoid &e1) : f(f), e1(e1) { resize(m, x); }

    Persistent_Segment_Tree(const F &f, const Monoid &e1) : root(NULL), f(f), e1(e1) {}

    ~Persistent_Segment_Tree() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    void copy(const Persistent_Segment_Tree<Monoid> &seg) {
        root = seg.root;
        n = seg.n;
    }

    Node *make_node(Node *lch, Node *rch, const Monoid &x) {
        Node *ret = new Node(lch, rch, x);
        used.push_back(ret);
        return ret;
    }

    Node *make_node(const Monoid &x) { return make_node(NULL, NULL, x); }

    void resize(const vector<Monoid> &v) {
        n = v.size();
        root = build(v, 0, n);
    }

    void resize(int m, const Monoid &x) { resize(vector<Monoid>(m, x)); }

    Node *merge(Node *lch, Node *rch) { return make_node(lch, rch, f(lch->x, rch->x)); }

    Node *build(const vector<Monoid> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l]);
        int m = (l + r) >> 1;
        return merge(build(v, l, m), build(v, m, r));
    }

    Node *change(int i, const Monoid &x, int l, int r, Node *pre) {
        if (r - l == 1) return make_node(x);
        int m = (l + r) >> 1;
        if (i < m) return merge(change(i, x, l, m, pre->lch), pre->rch);
        return merge(pre->lch, change(i, x, m, r, pre->rch));
    }

    void change(int i, const Monoid &x) { root = change(i, x, 0, n, root); }

    Monoid query(int a, int b, int l, int r, Node *now) const {
        if (a >= b || b <= l || r <= a) return e1;
        if (a <= l && r <= b) return now->x;
        int m = (l + r) >> 1;
        return f(query(a, b, l, m, now->lch), query(a, b, m, r, now->rch));
    }

    Monoid query(int l, int r) const { return query(l, r, 0, n, root); }

    Monoid operator[](int i) const { return query(i, i + 1); }
};
