
// 平方分割 (雛形)
// 計算量 クエリ O(√n) や O(√(n log(n))) になることが多い

// 概要
// 区間全体にクエリをかける操作が高速にできる場合、バケットサイズ O(√n) で区間を分割することでクエリを高速化出来る。

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

        void eval_all() {}

        void query1(int a, int b, const T &x) {
            a = max(a, l), b = min(b, r);
            if (a >= b) return;
            if (a == l && b == r) {
                query1_all(x);
                return;
            }
            a -= l, b -= l;
        }

        void query1_all(const T &x) {}

        T query2(int a, int b) {
            a = max(a, l), b = min(b, r);
            if (a >= b) return 0;
            if (a == l && b == r) return query2_all();
            a -= l, b -= l;
        }

        T query2_all() {}
    };

    vector<Node> nodes;

    Sqrt_Decomposition(const vector<T> &a, int bucket_size) {
        for (int i = 0; i < (int)a.size(); i += bucket_size) {
            int l = i, r = min(i + bucket_size, (int)a.size());
            nodes.emplace_back(a, l, r);
        }
    }

    void query1(int a, int b, const T &x) {
        for (auto &e : nodes) e.query1(a, b, x);
    }

    T query2(int a, int b) {
        T ret = 0;
        for (auto &e : nodes) ret += e.query2(a, b);
        return ret;
    }
};
