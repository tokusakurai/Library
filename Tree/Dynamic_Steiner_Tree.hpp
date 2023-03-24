
// 木上の最小シュタイナー木 (頂点集合の削除・追加ができる)
// 計算量 前計算：O(n log(n))、追加・削除：O(log(n))
// 空間計算量 O(n log(n))

// 概要
// x を頂点集合に追加するとき、DFS 順で x の直前に入っている頂点を l、直後に入っている頂点を r とする。
// このとき、最小シュタイナー木のサイズは (dist(l,x) + dist(x,r) - dist(l,r)) / 2 だけ増える。
// 削除するときは挿入するときの増加分だけ減らせばよい。
// 2 頂点の距離を求めるのに LCA を用いる。

// verified with
// https://codeforces.com/contest/372/problem/D

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Binary_Indexed_Tree.hpp"
#include "../Tree/Heavy-Light_Decomposition.hpp"

template <bool directed = false>
struct Dynamic_Steiner_Tree : Heavy_Light_Decomposition<directed> {
    using H = Heavy_Light_Decomposition<directed>;
    Binary_Indexed_Tree<int> bit;
    vector<int> cnt;
    int si, Steiner_size;

    Dynamic_Steiner_Tree(int n) : H(n), bit(n, 0), cnt(n, 0), si(0), Steiner_size(0) {}

    int insert(int x) {
        if (cnt[x]++ != 0) return Steiner_size;
        int c = bit.sum(this->id_v[x]);
        int l = (c == 0 ? -1 : bit.lower_bound(c));
        int r = bit.lower_bound(c + 1);
        if (l == -1 && r == this->n) {
            bit.add(this->id_v[x], 1);
            si++;
            return ++Steiner_size;
        }
        if (l == -1) l = r, r = bit.lower_bound(si);
        if (r == this->n) r = l, l = bit.lower_bound(1);
        l = this->vs[l], r = this->vs[r];
        bit.add(this->id_v[x], 1);
        si++;
        return Steiner_size += (this->dist(x, l) + this->dist(x, r) - this->dist(l, r)) / 2;
    }

    int erase(int x) {
        if (--cnt[x] != 0) return Steiner_size;
        bit.add(this->id_v[x], -1);
        si--;
        int c = bit.sum(this->id_v[x]);
        int l = (c == 0 ? -1 : bit.lower_bound(c));
        int r = bit.lower_bound(c + 1);
        if (l == -1 && r == this->n) return --Steiner_size;
        if (l == -1) l = r, r = bit.lower_bound(si);
        if (r == this->n) r = l, l = bit.lower_bound(1);
        l = this->vs[l], r = this->vs[r];
        return Steiner_size -= (this->dist(x, l) + this->dist(x, r) - this->dist(l, r)) / 2;
    }
};
