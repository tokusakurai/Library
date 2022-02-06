
// Link-Cut Tree
// 計算量 辺の追加・削除・1 点更新・パスクエリ：（ならし）O(log(n))

// 概要
// 木を HL 分解のようにいくつかのパスにして管理する。
// 各パスの成分をスプレー木で持ち、一番左側が根で左から順番に葉方向に進んでいる状態にする。
// スプレー木の結合・分離操作によって、辺の追加・削除を扱うことができる。
// グラフは常に森でなければならない。
// クエリはモノイドを乗せることができる（可換でなくても良い）。

// verified with
// https://judge.yosupo.jp/problem/dynamic_tree_vertex_add_path_sum
// https://judge.yosupo.jp/problem/dynamic_tree_vertex_set_path_composite

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename Monoid>
struct Link_Cut_Tree {
    struct Node {
        Node *lch, *rch, *par;
        int id, size;                  // 部分木のサイズ
        bool rev;                      // 反転の遅延
        Monoid x, left_sum, right_sum; // 左側からの和と右側からの和
        Node(int id, const Monoid &x) : id(id), x(x) {
            lch = NULL, rch = NULL, par = NULL;
            size = 1, rev = false, left_sum = x, right_sum = x;
        }

        int state() {
            if (!par) return 0;
            if (par->lch == this) return 1;
            if (par->rch == this) return -1;
            return 0;
        }
    };

    using F = function<Monoid(Monoid, Monoid)>;
    const F f;
    const Monoid e1;
    vector<Node *> nodes;

    Link_Cut_Tree(const vector<Monoid> &v, const F &f, const Monoid &e1) : f(f), e1(e1) {
        int n = v.size();
        nodes.resize(n);
        for (int i = 0; i < n; i++) { nodes[i] = make_node(i, v[i]); }
    }

    Node *make_node(int id, const Monoid &x) { return new Node(id, x); }

    void toggle(Node *t) {
        swap(t->lch, t->rch);
        swap(t->left_sum, t->right_sum);
        t->rev ^= true;
    }

    void push(Node *t) {
        if (t->rev) {
            if (t->lch) toggle(t->lch);
            if (t->rch) toggle(t->rch);
            t->rev = false;
        }
    }

    void update(Node *t) {
        t->size = 1;
        t->left_sum = t->x, t->right_sum = t->x;
        if (t->lch) {
            t->size += t->lch->size;
            t->left_sum = f(t->lch->left_sum, t->left_sum);
            t->right_sum = f(t->right_sum, t->lch->right_sum);
        }
        if (t->rch) {
            t->size += t->rch->size;
            t->left_sum = f(t->left_sum, t->rch->left_sum);
            t->right_sum = f(t->rch->right_sum, t->right_sum);
        }
    }

    void rotate(Node *t) {
        Node *p = t->par, *q = p->par, *c = t->rch;
        if (p->lch == t) {
            c = t->rch, t->rch = p, p->lch = c;
        } else {
            c = t->lch, t->lch = p, p->rch = c;
        }
        if (q && q->lch == p) q->lch = t;
        if (q && q->rch == p) q->rch = t;
        t->par = q, p->par = t;
        if (c) c->par = p;
        update(p), update(t);
    }

    void splay(Node *t) {
        push(t);
        while (t->state() != 0) {
            if (t->par->state() == 0) {
                push(t->par), push(t);
                rotate(t);
            } else if (t->state() == t->par->state()) {
                push(t->par->par), push(t->par), push(t);
                rotate(t->par), rotate(t);
            } else {
                push(t->par->par), push(t->par), push(t);
                rotate(t), rotate(t);
            }
        }
    }

    Node *expose(Node *t) { // t から根までの辺を全て Heavy-edge にする
        Node *pre = NULL;
        for (Node *now = t; now; now = now->par) {
            splay(now);
            now->rch = pre;
            update(now);
            pre = now;
        }
        splay(t);
        return pre;
    }

    Node expose(int t) { return expose(nodes[t]); };

    void evert(Node *t) { // t を根にする(tを含むスプレー木の向きは反転する)
        expose(t);
        toggle(t);
        push(t);
    }

    void evert(int c) { evert(nodes[c]); };

    void link(Node *c, Node *p) { // c の親を p にするようにしてマージする
        expose(c), expose(p);
        c->par = p, p->rch = c;
    }

    void link(int u, int v) {
        evert(u);
        link(nodes[u], nodes[v]);
    };

    void cut(Node *c) { // c を親から分離する
        expose(c);
        Node *p = c->lch;
        c->lch = NULL, p->par = NULL;
    }

    void cut(int u, int v) {
        evert(u);
        cut(nodes[v]);
    };

    Monoid query(Node *u) {
        expose(u);
        return u->left_sum;
    }

    Monoid query(Node *u, Node *v) {
        evert(u);
        return query(v);
    }

    Monoid query(int u, int v) { return query(nodes[u], nodes[v]); };

    void change(Node *t, const Monoid &x) {
        expose(t);
        t->x = x;
        update(t);
    }

    void change(int t, const Monoid &x) { change(nodes[t], x); };

    void apply(Node *t, const F &op, const Monoid &x) {
        expose(t);
        t->x = op(t->x, x);
        update(t);
    }

    void apply(int t, const F &op, const Monoid &x) { apply(nodes[t], op, x); };
};
