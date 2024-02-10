#pragma once

// スプレー木
// 計算量 挿入・削除・i 番目の値にアクセス・二分探索：(ならし) O(log(n))

// 概要
// 平衡二分探索木で、要素にアクセスするときに splay 操作をしてアクセスした頂点を根に持ってくる。

// verified with
// https://atcoder.jp/contests/arc033/tasks/arc033_3
// https://judge.yosupo.jp/problem/associative_array

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Splay_Tree {
    struct Node {
        Node *lch, *rch, *par;
        T x;
        int size; // 部分木のサイズ

        Node(T x) : lch(NULL), rch(NULL), par(NULL), x(x), size(1) {}

        Node() : Node(0) {}

        int state() {
            if (!this->par) return 0;
            if (this->par->lch == this) return 1;
            if (this->par->rch == this) return -1;
            return 0;
        }

        // 再帰的に子の Node のメモリを解放していく
        void rec_delete() {
            deleter(lch);
            deleter(rch);
        }

        void deleter(Node *child) {
            if (child) {
                child->rec_delete();
                delete child;
            }
        }
    };

    Node *root;

    Splay_Tree() : root(NULL) {}

    Splay_Tree(const Splay_Tree &s) : root(new Node(*s.root)) {}

    Splay_Tree(Splay_Tree &&s) : root(s.root) { s.root = NULL; }

    Splay_Tree &operator=(const Splay_Tree &s) {
        if (&s != this) {
            if (root) {
                root->rec_delete();
                delete root;
            }
            root = new Node(*s.root);
        }
        return *this;
    }

    Splay_Tree &operator=(Splay_Tree &&s) {
        if (&s != this) {
            if (root) {
                root->rec_delete();
                delete root;
            }
            root = s.root;
            s.root = NULL;
        }
        return *this;
    }

    ~Splay_Tree() {
        if (root) {
            root->rec_delete();
            delete root;
        }
    }

    int size() { return (root ? root->size : 0); }

    void update(Node *t) {
        t->size = 1;
        if (t->lch) t->size += t->lch->size;
        if (t->rch) t->size += t->rch->size;
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
        while (t->state() != 0) {
            if (t->par->state() == 0) {
                rotate(t);
            } else if (t->state() == t->par->state()) {
                rotate(t->par), rotate(t);
            } else {
                rotate(t), rotate(t);
            }
        }
        root = t;
    }

    // i 番目 (0-indexed) の値
    Node *get(int i) {
        if (i >= root->size) return NULL;
        Node *now = root;
        while (true) {
            int lsize = (now->lch ? now->lch->size : 0);
            if (i == lsize) break;
            if (i < lsize) {
                now = now->lch;
            } else {
                i -= lsize + 1, now = now->rch;
            }
        }
        splay(now);
        return now;
    }

    T operator[](int i) { return get(i)->x; }

    Node *make_node(const T &x) { return new Node(x); }

    // x 以上で最小のノード
    Node *greater_equal(const T &x) {
        Node *now = root, *ret = NULL;
        while (now) {
            if (now->x < x) {
                now = now->rch;
            } else {
                ret = now;
                now = now->lch;
            }
        }
        if (ret) splay(ret);
        return ret;
    }

    // x より大きい最小のノード
    Node *greater_than(const T &x) {
        Node *now = root, *ret = NULL;
        while (now) {
            if (now->x <= x) {
                now = now->rch;
            } else {
                ret = now;
                now = now->lch;
            }
        }
        if (ret) splay(ret);
        return ret;
    }

    // x 以下で最大のノード
    Node *less_equal(const T &x) {
        Node *now = root, *ret = NULL;
        while (now) {
            if (now->x > x) {
                now = now->lch;
            } else {
                ret = now;
                now = now->rch;
            }
        }
        if (ret) splay(ret);
        return ret;
    }

    // x 未満で最大のノード
    Node *less_than(const T &x) {
        Node *now = root, *ret = NULL;
        while (now) {
            if (now->x >= x) {
                now = now->lch;
            } else {
                ret = now;
                now = now->rch;
            }
        }
        if (ret) splay(ret);
        return ret;
    }

    Node *find(const T &x) {
        Node *ret = greater_equal(x);
        if (!ret || ret->x != x) return NULL;
        return ret;
    }

    // x 以下の要素数
    int count_lower_equal(const T &x) {
        Node *now = root;
        int ret = 0;
        while (now) {
            int lsize = (now->lch ? now->lch->size : 0);
            if (now->x <= x) {
                ret += lsize + 1;
                now = now->rch;
            } else {
                now = now->lch;
            }
        }
        return ret;
    }

    // x 未満の要素数
    int count_lower_than(const T &x) {
        Node *now = root;
        int ret = 0;
        while (now) {
            int lsize = (now->lch ? now->lch->size : 0);
            if (now->x < x) {
                ret += lsize + 1;
                now = now->rch;
            } else {
                now = now->lch;
            }
        }
        return ret;
    }

    void insert(const T &x) {
        Node *c = greater_equal(x);
        if (c && c->x == x) return;
        Node *t = make_node(x);
        if (!c) {
            if (root) root->par = t;
            t->lch = root;
        } else {
            splay(c);
            if (c->lch) c->lch->par = t;
            t->lch = c->lch, t->rch = c;
            c->lch = NULL, c->par = t;
            update(c);
        }
        update(t), root = t;
    }

    void erase(const T &x) {
        Node *t = find(x);
        if (!t) return;
        if (t->rch) {
            t->rch->par = NULL;
            Node *c = greater_than(x);
            c->lch = t->lch;
            if (t->lch) t->lch->par = c;
            update(c);
        } else {
            if (t->lch) t->lch->par = NULL;
            root = t->lch;
        }
        delete t;
    }
};
