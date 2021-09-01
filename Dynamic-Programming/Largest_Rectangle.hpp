
// ヒストグラム中の最大長方形
// 計算量 O(N)

// 概要
// left[i] := j<=iかつmin(h[j],h[j+1],...,h[i])=h[i]を満たす最小のj
// stackに入っているindexは、前のものほどそのindexに対応するヒストグラムが高い。
// stackから取り除かれるときが右端に相当する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_3_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T largest_rectangle(vector<T> h) {
    stack<int> st;
    h.push_back(0);
    vector<int> left(h.size(), 0);
    T ret = 0;
    for (int i = 0; i < h.size(); i++) {
        while (!st.empty() && h[st.top()] >= h[i]) {
            int j = st.top();
            st.pop();
            ret = max(ret, h[j] * (i - left[j]));
        }
        if (!st.empty()) left[i] = st.top() + 1;
        st.push(i);
    }
    return ret;
}
