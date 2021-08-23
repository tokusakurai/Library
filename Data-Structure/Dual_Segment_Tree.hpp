
//双対Segment Tree
//計算量 構築 : O(N)、区間更新・1点取得 : O(log(N))
//空間計算量 O(N)

//概要
//区間更新 : まず更新される各ノードについて遅延評価を解消してから、遅延配列を更新する。
//1点取得 : 取得する点の遅延評価を解消する。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_D&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DSL_2_E&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T, typename Operator_Monoid>
struct Dual_Segment_Tree{
    using G = function<T(T, Operator_Monoid)>;
    using H = function<Operator_Monoid(Operator_Monoid, Operator_Monoid)>;
    int n, height;
    vector<T> seg;
    vector<Operator_Monoid> lazy;
    const G g;
    const H h;
    const Operator_Monoid e2;
    
    //h(h(p,q),r) = h(p,h(q,r)), h(e2,p) = h(p,e2) = p
    //g(g(a,p),q) = g(a,h(p,q))

    Dual_Segment_Tree(const vector<T> &v, const G &g, const H &h, const Operator_Monoid &e2) : g(g), h(h), e2(e2){
        int m = v.size();
        n = 1, height = 0;
        while(n < m) n <<= 1, height++;
        lazy.assign(2*n, e2);
        seg = v;
    }

    Dual_Segment_Tree(int m, const T &x, const G &g, const H &h, const Operator_Monoid &e2) : g(g), h(h), e2(e2){
        n = 1, height = 0;
        while(n < m) n <<= 1, height++;
        lazy.assign(2*n, e2);
        seg.assign(m, x);
    }

    inline void eval(int i){
        if(i < n && lazy[i] != e2){
            lazy[2*i] = h(lazy[2*i], lazy[i]);
            lazy[2*i+1] = h(lazy[2*i+1], lazy[i]);
            lazy[i] = e2;
        }
    }

    inline void thrust(int i){
        for(int j = height; j > 0; j--) eval(i>>j);
    }

    void apply(int l, int r, const Operator_Monoid &x){
        l = max(l, 0), r = min(r, n);
        if(l >= r) return;
        l += n, r += n;
        thrust(l), thrust(r-1);
        while(l < r){
            if(l&1) lazy[l] = h(lazy[l], x), l++;
            if(r&1) r--, lazy[r] = h(lazy[r], x);
            l >>= 1, r >>= 1;
        }
    }

    T get(int i){
        thrust(i+n);
        return g(seg[i], lazy[i+n]);
    }

    T operator [] (int i) {return get(i);}
};
