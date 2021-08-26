
//スプレー木
//計算量 挿入・削除・i番目の値にアクセス・二分探索 : (ならし)O(log(N))

//概要
//平衡二分探索木で、要素にアクセスするときにsplay操作をしてアクセスした頂点を根に持ってくる。

//verified with
//https://atcoder.jp/contests/arc033/tasks/arc033_3
//https://judge.yosupo.jp/problem/associative_array

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Splay_Tree{
    struct Node{
        Node *lch, *rch, *par;
        T x;
        int size; //部分木のサイズ

        Node(T x) : lch(NULL), rch(NULL), par(NULL), x(x), size(1) {}

        Node() : Node(0) {}

        int state(){
            if(!this->par) return 0;
            if(this->par->lch == this) return 1;
            if(this->par->rch == this) return -1;
            return 0;
        }
    };

    Node *root;

    Splay_Tree() : root(NULL) {}

    int size(){
        return (root? root->size : 0);
    }

    void update(Node *t){
        t->size = 1;
        if(t->lch) t->size += t->lch->size;
        if(t->rch) t->size += t->rch->size;
    }

    void rotate(Node *t){
        Node *p = t->par, *q = p->par, *c = t->rch;
        if(p->lch == t) c = t->rch, t->rch = p, p->lch = c;
        else c = t->lch, t->lch = p, p->rch = c;
        if(q && q->lch == p) q->lch = t;
        if(q && q->rch == p) q->rch = t;
        t->par = q, p->par = t;
        if(c) c->par = p;
        update(p), update(t);
    }

    void splay(Node *t){
        while(t->state() != 0){
            if(t->par->state() == 0) rotate(t);
            else if(t->state() == t->par->state()) rotate(t->par), rotate(t);
            else rotate(t), rotate(t);
        }
        root = t;
    }

    Node *get(int i){ //i番目(0-indexed)の値
        if(i >= root->size) return NULL;
        Node *now = root;
        while(true){
            int lsize = (now->lch? now->lch->size : 0);
            if(i == lsize) break;
            if(i < lsize) now = now->lch;
            else i -= lsize+1, now = now->rch;
        }
        splay(now);
        return now;
    }

    T operator [] (int i) {return get(i)->x;}

    Node *make_node(const T &x){
        return new Node(x);
    }

    Node *lower_bound(T x){ //x以上で最小のノード
        Node *now = root, *ret = NULL;
        while(now){
            if(now->x < x) now = now->rch;
            else{
                ret = now;
                now = now->lch;
            }
        }
        if(ret) splay(ret);
        return ret;
    }

    Node *upper_bound(T x){ //x以上の最小のノード
        Node *now = root, *ret = NULL;
        while(now){
            if(now->x <= x) now = now->rch;
            else{
                ret = now;
                now = now->lch;
            }
        }
        if(ret) splay(ret);
        return ret;
    }

    Node *find(T x){ //xより大きい最小のノード
        Node *ret = lower_bound(x);
        if(!ret || ret->x != x) return NULL;
        return ret;
    }

    void insert(T x){
        Node *c = lower_bound(x);
        if(c && c->x == x) return;
        Node *t = make_node(x);
        if(!c){
            if(root) root->par = t;
            t->lch = root;
        }
        else{
            splay(c);
            if(c->lch) c->lch->par = t;
            t->lch = c->lch, t->rch = c;
            c->lch = NULL, c->par = t;
            update(c);
        }
        update(t), root = t;
    }

    void erase(T x){
        Node *t = find(x);
        if(!t) return;
        if(t->rch){
            t->rch->par = NULL;
            Node *c = upper_bound(x);
            c->lch = t->lch;
            if(t->lch) t->lch->par = c;
            update(c);
        }
        else{
            if(t->lch) t->lch->par = NULL;
            root = t->lch;
        }
        delete t;
    }
};
