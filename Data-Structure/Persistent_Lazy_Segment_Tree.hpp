
// 永続遅延評価付き Segment Tree
// 計算量 区間更新・区間取得：O(log(n))、複製：O(1)
// 空間計算量 O(n+q log(n))（q はクエリの回数）

// 概要
// 永続 Segment Tree に加えて、遅延配列も永続配列として持つことで永続化を実現できる。
// メモリ消費が非常に大きいことに注意。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid, typename Operator_Monoid>
struct Persistent_Lazy_Segment_Tree {
    using F = function<Monoid(Monoid, Monoid)>;
    using G = function<Monoid(Monoid, Operator_Monoid)>;
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;

    struct Node {
        Node *lch, *rch;
        Monoid x;
        Operator_Monoid lazy;

        Node(Node *lch, Node *rch, const Monoid &x, const Operator_Monoid &lazy) : lch(lch), rch(rch), x(x), lazy(lazy) {}
    };

    Node *root;
    vector<Node *> used;
    int n;
    const F f;
    const G g;
    const H h;
    const Monoid e1;
    const Operator_Monoid e2;

    Persistent_Lazy_Segment_Tree(const vector<Monoid> &v, const F &f, const G &g, const H &h, const Monoid &e1, const Operator_Monoid &e2) : f(f), g(g), h(h), e1(e1), e2(e2) { resize(v); }

    Persistent_Lazy_Segment_Tree(int m, const Monoid &x, const F &f, const G &g, const H &h, const Monoid &e1, const Operator_Monoid &e2) : f(f), g(g), h(h), e1(e1), e2(e2) { resize(m, x); }

    Persistent_Lazy_Segment_Tree(const F &f, const G &g, const H &h, const Monoid &e1, const Operator_Monoid &e2) : root(NULL), f(f), g(g), h(h), e1(e1), e2(e2) {}

    ~Persistent_Lazy_Segment_Tree() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    void copy(const Persistent_Lazy_Segment_Tree<Monoid, Operator_Monoid> &seg) {
        root = seg.root;
        n = seg.n;
    }

    Node *make_node(Node *lch, Node *rch, const Monoid &x, const Operator_Monoid &lazy) {
        Node *ret = new Node(lch, rch, x, lazy);
        used.push_back(ret);
        return ret;
    }

    Node *make_node(const Monoid &x, const Operator_Monoid &lazy) { return make_node(NULL, NULL, x, lazy); }

    void resize(const vector<Monoid> &v) {
        n = v.size();
        root = build(v, 0, n);
    }

    void resize(int m, const Monoid &x) { resize(vector<Monoid>(m, x)); }

    Node *merge(Node *lch, Node *rch) { return make_node(lch, rch, f(lch->x, rch->x), e2); }

    Node *build(const vector<Monoid> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l], e2);
        int m = (l + r) >> 1;
        return merge(build(v, l, m), build(v, m, r));
    }

    void eval(Node *now) {
        if (now->lazy == e2) return;
        Node *l = now->lch, *r = now->rch;
        now->lch = make_node(l->lch, l->rch, g(l->x, now->lazy), h(l->lazy, now->lazy));
        now->rch = make_node(r->lch, r->rch, g(r->x, now->lazy), h(r->lazy, now->lazy));
        now->lazy = e2;
    }

    Node *apply(int a, int b, const Operator_Monoid &x, int l, int r, Node *pre) {
        if (a >= b || b <= l || r <= a) return pre;
        if (a <= l && r <= b) return make_node(pre->lch, pre->rch, g(pre->x, x), h(pre->lazy, x));
        int m = (l + r) >> 1;
        eval(pre);
        return merge(apply(a, b, x, l, m, pre->lch), apply(a, b, x, m, r, pre->rch));
    }

    void apply(int l, int r, const Operator_Monoid &x) { root = apply(l, r, x, 0, n, root); }

    Monoid query(int a, int b, int l, int r, Node *now) {
        if (a >= b || b <= l || r <= a) return e1;
        if (a <= l && r <= b) return now->x;
        int m = (l + r) >> 1;
        eval(now);
        return f(query(a, b, l, m, now->lch), query(a, b, m, r, now->rch));
    }

    Monoid query(int l, int r) { return query(l, r, 0, n, root); }

    Monoid operator[](int i) { return query(i, i + 1); }
};
