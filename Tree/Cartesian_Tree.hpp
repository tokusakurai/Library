
// Cartesian tree
// 計算量 O(n)

// 概要
// Cartesian tree：数列を最小値の index (最小値が複数あるときは最も小さいもの) で分割して再帰的に構築される二分木
// 頂点 i の親 p[i] は、l[i] := max{j | j < i かつ a[j] <= a[i]}, r[i] := min{j | j > i かつ a[j] < a[i]} とすると、
// a[l[i]] > a[r[i]] ならば p[i] = l[i]
// a[l[i]] <= a[r[i]] ならば p[i] = r[i]
// となるので、stack を用いて数列 p を求めることができる。

// verified with
// https://judge.yosupo.jp/problem/cartesian_tree

#pragma once
#include <bits/stdc++.h>
using namespace std;

// is_min : 最小値で分割するか最大値で分割するか
// left_prior : 同じ値が複数場合左を優先するか右を優先するか
template <typename T>
vector<int> cartesian_tree(vector<T> a, bool is_min, bool left_prior = true) {
    int n = a.size();
    if (!is_min) {
        for (int i = 0; i < n; i++) a[i] = -a[i];
    }
    if (!left_prior) reverse(begin(a), end(a));
    stack<int> st;
    vector<int> p(n, -1);
    for (int i = 0; i < n; i++) {
        int pre = -1;
        while (!st.empty() && a[i] < a[st.top()]) {
            pre = st.top();
            st.pop();
        }
        if (pre != -1) p[pre] = i;
        if (!st.empty()) p[i] = st.top();
        st.push(i);
    }
    if (!left_prior) {
        reverse(begin(p), end(p));
        for (int i = 0; i < n; i++) {
            if (p[i] != -1) p[i] = n - 1 - p[i];
        }
    }
    return p;
}
