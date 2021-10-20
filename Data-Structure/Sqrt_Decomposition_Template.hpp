
// 平方分割 (雛形)
// 計算量 クエリO(√n)やO(√(n log(n)))になることが多い

// 概要
// 区間全体にクエリをかける操作が高速にできる場合、バケットサイズO(√n)で区間を分割することでクエリを高速化出来る。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Sqrt_Decomposition {
    struct Node {
        const int l, r;
        vector<T> v;

        Node(const vector<T> &a, int l, int r) : l(l), r(r) {
            v.resize(r - l);
            copy(begin(a) + l, begin(a) + r, begin(v));
        }

        T eval(const T &x) const { return; }

        void eval_all() {
            for (auto &e : v) e = eval(e);
        }

        void query1(int a, int b, const T &x) {
            a = max(a, l), b = min(b, r);
            if (a >= b) return;
            if (a == l && b == r) {
                query1_all(x);
                return;
            }
        }

        void query1_all(const T &x) {}

        T query2(int a, int b) {
            a = max(a, l), b = min(b, r);
            if (a >= b) return;
            if (a == l && b == r) { return query2_all(); }
        }

        T query2_all() {}
    };

    vector<Node> nodes;

    Sqrt_Decomposition(const vector<T> &a, int bucket_size) {
        for (int i = 0; i < (int)a.size(); i += bucket_size) { nodes.emplace_back(a, i, min(i + bucket_size, (int)a.size())); }
    }

    void query1(int a, int b, const T &x) {
        for (auto &e : nodes) query1(a, b, x);
    }

    T query2(int a, int b) {
        T ret = ;
        for (auto &e : nodes)
            ;
        return ret;
    }
};
