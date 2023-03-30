
// 永続遅延評価付き Segment Tree
// 計算量 区間更新・区間取得：O(log(n))
// 空間計算量 O(n+q log(n)) (q はクエリの回数)

// 概要
// 永続 Segment Tree に加えて、遅延配列も永続配列として持つことで永続化を実現できる。
// メモリ消費が非常に大きいことに注意。

// verified with
// https://codeforces.com/gym/103438/problem/B

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Acted_Monoid, bool del = false>
struct Persistent_Lazy_Segment_Tree {
    using Monoid = typename Acted_Monoid::Monoid;
    using Operator = typename Acted_Monoid::Operator;
    using M = typename Monoid::V;
    using O = typename Operator::V;

    struct Node {
        Node *lch, *rch;
        M x;
        O lazy;

        Node(Node *lch, Node *rch, const M &x, const O &lazy) : lch(lch), rch(rch), x(x), lazy(lazy) {}
    };

    int n;
    unordered_map<int, Node *> root;
    vector<Node *> used;

    Persistent_Lazy_Segment_Tree(const vector<M> &v, int init_id = 0) { resize(v, init_id); }

    Persistent_Lazy_Segment_Tree(int n, const M &x, int init_id = 0) { resize(n, x, init_id); }

    ~Persistent_Lazy_Segment_Tree() {
        for (int i = 0; i < (int)used.size(); i++) delete used[i];
    }

    Node *make_node(Node *lch, Node *rch, const M &x, const O &lazy) {
        Node *ret = new Node(lch, rch, x, lazy);
        if (del) used.push_back(ret);
        return ret;
    }

    Node *make_node(const M &x, const O &lazy) { return make_node(NULL, NULL, x, lazy); }

    void resize(const vector<M> &v, int init_id) {
        n = v.size();
        root[init_id] = build(v, 0, n);
    }

    void resize(int n, const M &x, int init_id) { resize(vector<M>(n, x), init_id); }

    Node *merge(Node *lch, Node *rch) { return make_node(lch, rch, Monoid::merge(lch->x, rch->x), Operator::id); }

    Node *build(const vector<M> &v, int l, int r) {
        if (r - l == 1) return make_node(v[l], Operator::id);
        int m = (l + r) >> 1;
        return merge(build(v, l, m), build(v, m, r));
    }

    void copy(int ref_id, int new_id) {
        assert(root.count(ref_id));
        root[new_id] = root[ref_id];
    }

    void eval(Node *now) {
        Node *l = now->lch, *r = now->rch;
        now->lch = make_node(l->lch, l->rch, Acted_Monoid::merge(l->x, now->lazy), Operator::merge(l->lazy, now->lazy));
        now->rch = make_node(r->lch, r->rch, Acted_Monoid::merge(r->x, now->lazy), Operator::merge(r->lazy, now->lazy));
        now->lazy = Operator::id;
    }

    Node *update(int a, int b, const O &x, int l, int r, Node *pre) {
        if (a >= b || b <= l || r <= a) return pre;
        if (a <= l && r <= b) return make_node(pre->lch, pre->rch, Acted_Monoid::merge(pre->x, x), Operator::merge(pre->lazy, x));
        int m = (l + r) >> 1;
        eval(pre);
        return merge(update(a, b, x, l, m, pre->lch), update(a, b, x, m, r, pre->rch));
    }

    // ref_id に対応するデータから派生して new_id に対応する新しいデータを作る
    void update(int ref_id, int new_id, int l, int r, const O &x) {
        assert(root.count(ref_id));
        root[new_id] = update(l, r, x, 0, n, root[ref_id]);
    }

    M query(int a, int b, int l, int r, Node *now) {
        if (a >= b || b <= l || r <= a) return Monoid::id;
        if (a <= l && r <= b) return now->x;
        int m = (l + r) >> 1;
        eval(now);
        return Monoid::merge(query(a, b, l, m, now->lch), query(a, b, m, r, now->rch));
    }

    M query(int ref_id, int l, int r) {
        assert(root.count(ref_id));
        return query(l, r, 0, n, root[ref_id]);
    }
};
