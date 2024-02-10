#pragma once

// Heavy-Light 分解 + データ構造 (パスクエリを効率的に扱える)

// verify 問題集
// https://judge.yosupo.jp/problem/vertex_add_path_sum
// https://judge.yosupo.jp/problem/vertex_set_path_composite
// https://atcoder.jp/contests/joisc2015/tasks/joisc2015_g
// https://atcoder.jp/contests/joisp2023/tasks/joisp2023_a

#include <bits/stdc++.h>
using namespace std;

#include "../Data-Structure/Binary_Indexed_Tree.hpp"
#include "../Data-Structure/Dual_Segment_Tree.hpp"
#include "../Data-Structure/Lazy_Segment_Tree.hpp"
#include "../Data-Structure/Segment_Tree.hpp"
#include "../Tree/Heavy-Light_Decomposition.hpp"

template <typename T, bool use_edge, bool directed = false>
struct HLD_Binary_Indexed_Tree : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    Binary_Indexed_Tree<T> bit;
    vector<T> v;
    const int n;

    HLD_Binary_Indexed_Tree(const vector<T> &v) : HLD((int)v.size()), bit((int)v.size()), v(v), n((int)v.size()) {}

    HLD_Binary_Indexed_Tree(int n, T x = 0) : HLD(n), bit(n), v(n, x), n(n) {}

    void set(int i, const T &x) { v[i] = x; }

    void build() {
        this->decompose();
        if (use_edge) {
            for (int i = 0; i < n - 1; i++) bit.set(this->id_e[i], v[i]);
        } else {
            for (int i = 0; i < n; i++) bit.set(this->id_v[i], v[i]);
        }
        bit.build();
    }

    void add(int i, const T &x) { bit.add((use_edge ? this->id_e : this->id_v)[i], x); }

    void change(int i, const T &x) { bit.change((use_edge ? this->id_e : this->id_v)[i], x); }

    T query(int u, int v) {
        T ret = 0;
        for (auto [l, r] : this->get_path(u, v, use_edge)) ret += bit.query(l, r);
        return ret;
    }

    T operator[](int i) { return bit[(use_edge ? this->id_e : this->id_v)[i]]; }
};

template <typename Monoid, bool use_edge, bool directed = false>
struct HLD_Segment_Tree : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    using M = typename Monoid::V;
    Segment_Tree<Monoid> seg;
    vector<M> v;
    const int n;

    HLD_Segment_Tree(const vector<M> &v) : HLD((int)v.size()), seg((int)v.size()), v(v), n((int)v.size()) {}

    HLD_Segment_Tree(int n, M x = Monoid::id) : HLD(n), seg(n), v(n, x), n(n) {}

    void set(int i, const M &x) { v[i] = x; }

    void build() {
        this->decompose();
        if (use_edge) {
            for (int i = 0; i < n - 1; i++) seg.set(this->id_e[i], v[i]);
        } else {
            for (int i = 0; i < n; i++) seg.set(this->id_v[i], v[i]);
        }
        seg.build();
    }

    void update(int i, const M &x, bool apply = false) { seg.update((use_edge ? this->id_e : this->id_v)[i], x, apply); }

    M query(int u, int v) {
        M ret = Monoid::id;
        for (auto [l, r] : this->get_path(u, v, use_edge)) ret = Monoid::merge(ret, seg.query(l, r));
        return ret;
    }

    M operator[](int i) { return seg[(use_edge ? this->id_e : this->id_v)[i]]; }
};

template <typename Monoid, bool use_edge, bool directed = false>
struct HLD_Segment_Tree_Noncommutative : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    using M = typename Monoid::V;
    Segment_Tree<Monoid> seg1, seg2;
    vector<M> v;
    const int n;

    HLD_Segment_Tree_Noncommutative(const vector<M> &v) : HLD((int)v.size()), seg1((int)v.size()), seg2((int)v.size()), v(v), n((int)v.size()) {}

    HLD_Segment_Tree_Noncommutative(int n, M x = Monoid::id) : HLD(n), seg1(n), seg2(n), v(n, x), n(n) {}

    void set(int i, const M &x) { v[i] = x; }

    void build() {
        this->decompose();
        if (use_edge) {
            for (int i = 0; i < n - 1; i++) {
                seg1.set(this->id_e[i], v[i]);
                seg2.set(n - 1 - this->id_e[i], v[i]);
            }
        } else {
            for (int i = 0; i < n; i++) {
                seg1.set(this->id_v[i], v[i]);
                seg2.set(n - 1 - this->id_v[i], v[i]);
            }
        }
        seg1.build(), seg2.build();
    }

    void update(int i, const M &x, bool apply = false) {
        seg1.update((use_edge ? this->id_e : this->id_v)[i], x, apply);
        seg2.update(n - 1 - (use_edge ? this->id_e : this->id_v)[i], x, apply);
    }

    M query(int u, int v) {
        M ret = Monoid::id;
        for (auto [l, r] : this->get_path_noncommutative(u, v, use_edge)) {
            if (l > r) {
                ret = Monoid::merge(ret, seg2.query(n - l, n - r));
            } else {
                ret = Monoid::merge(ret, seg1.query(l, r));
            }
        }
        return ret;
    }

    M operator[](int i) { return seg1[(use_edge ? this->id_e : this->id_v)[i]]; }
};

template <typename Operator, bool use_edge, bool directed = false>
struct HLD_Dual_Segment_Tree : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    using O = typename Operator::V;
    Dual_Segment_Tree<Operator> seg;
    const int n;

    HLD_Dual_Segment_Tree(int n) : HLD(n), seg(n), n(n) {}

    void update(int u, int v, const O &x) {
        for (auto [l, r] : this->get_path(u, v, use_edge)) seg.update(l, r, x);
    }

    O get(int i) { return seg.get((use_edge ? this->id_e : this->id_v)[i]); }

    O operator[](int i) { return get(i); }
};

template <typename Acted_Monoid, bool use_edge, bool directed = false>
struct HLD_Lazy_Segment_Tree : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    using Monoid = typename Acted_Monoid::Monoid;
    using Operator = typename Acted_Monoid::Operator;
    using M = typename Monoid::V;
    using O = typename Operator::V;
    Lazy_Segment_Tree<Acted_Monoid> seg;
    vector<M> v;
    const int n;

    HLD_Lazy_Segment_Tree(const vector<M> &v) : HLD((int)v.size()), seg((int)v.size()), v(v), n((int)v.size()) {}

    HLD_Lazy_Segment_Tree(int n, M x = Monoid::id) : HLD(n), seg(n), v(n, x), n(n) {}

    void set(int i, const M &x) { v[i] = x; }

    void build() {
        this->decompose();
        if (use_edge) {
            for (int i = 0; i < n - 1; i++) seg.set(this->id_e[i], v[i]);
        } else {
            for (int i = 0; i < n; i++) seg.set(this->id_v[i], v[i]);
        }
        seg.build();
    }

    void update(int u, int v, const O &x) {
        for (auto [l, r] : this->get_path(u, v, use_edge)) seg.update(l, r, x);
    }

    M query(int u, int v) {
        M ret = Monoid::id;
        for (auto [l, r] : this->get_path(u, v, use_edge)) ret = Monoid::merge(ret, seg.query(l, r));
        return ret;
    }

    M operator[](int i) { return seg[(use_edge ? this->id_e : this->id_v)[i]]; }
};

template <typename Acted_Monoid, bool use_edge, bool directed = false>
struct HLD_Lazy_Segment_Tree_Noncommutative : Heavy_Light_Decomposition<directed> {
    using HLD = Heavy_Light_Decomposition<directed>;
    using Monoid = typename Acted_Monoid::Monoid;
    using Operator = typename Acted_Monoid::Operator;
    using M = typename Monoid::V;
    using O = typename Operator::V;
    Lazy_Segment_Tree<Acted_Monoid> seg1, seg2;
    vector<M> v;
    const int n;

    HLD_Lazy_Segment_Tree_Noncommutative(const vector<M> &v) : HLD((int)v.size()), seg1((int)v.size()), seg2((int)v.size()), v(v), n((int)v.size()) {}

    HLD_Lazy_Segment_Tree_Noncommutative(int n, M x = Monoid::id) : HLD(n), seg1(n), seg2(n), v(n, x), n(n) {}

    void set(int i, const M &x) { v[i] = x; }

    void build() {
        this->decompose();
        if (use_edge) {
            for (int i = 0; i < n - 1; i++) {
                seg1.set(this->id_e[i], v[i]);
                seg2.set(n - 1 - this->id_e[i], v[i]);
            }
        } else {
            for (int i = 0; i < n; i++) {
                seg1.set(this->id_v[i], v[i]);
                seg2.set(n - 1 - this->id_v[i], v[i]);
            }
        }
        seg1.build(), seg2.build();
    }

    void update(int u, int v, const O &x) {
        for (auto [l, r] : this->get_path(u, v, use_edge)) {
            seg1.update(l, r, x);
            seg2.update(n - r, n - l, x);
        }
    }

    M query(int u, int v) {
        M ret = Monoid::id;
        for (auto [l, r] : this->get_path_noncommutative(u, v, use_edge)) {
            if (l > r) {
                ret = Monoid::merge(ret, seg2.query(n - l, n - r));
            } else {
                ret = Monoid::merge(ret, seg1.query(l, r));
            }
        }
        return ret;
    }

    M operator[](int i) { return seg1[(use_edge ? this->id_e : this->id_v)[i]]; }
};
