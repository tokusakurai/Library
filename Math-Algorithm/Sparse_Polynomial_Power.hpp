
// 疎な多項式のべき乗
// 計算量 O(nd + log(k))

// 概要
// A(x) = Σ[0<=i<d]a[i]*x^p[i] として、A(x)^k の先頭 n+1 項を求める。
// B(x) = A(x)^k とすると、形式的微分により B'(x) = kA'(x)A(x)^(k-1) であるから、両辺に A(x) をかけて
// A(x)B'(x) = kA'(x)B(x) となるので、この両辺の x^(i-1) の項の係数を比較して
// i*a[0]b[m] = Σ[1<=j<d]{(k+1)p[j]-i}a[j]b[i-p[j]] となるから、B の係数についての漸化式が立つ。 (ただし、b[i] = [x^i]B(x))
// b[0] = a[0]^k としてこの漸化式を使えばよい。(a[0] ≠ 0 の場合は a[t] ≠ 0 となる最小の t について x^p[t] で割ってからやり直す)

// verified with
// https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse
// https://atcoder.jp/contests/abc222/tasks/abc222_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

// f(x)^k mod x^n (f(x) = Σ[0<=i<d] a[i]*x^p[i])
template <typename T>
vector<T> sparse_polynomial_power(const vector<int> &p, const vector<T> &a, long long k, int n) {
    int d = a.size();
    int t = 0;
    while (t < d && a[t] == 0) t++;
    vector<T> b(n, 0);
    if (t == d) {
        if (k == 0) b[0] = 1;
        return b;
    }
    if (p[t] > 0) {
        if (k > (n - 1) / p[t]) return vector<T>(n, 0);
        vector<int> q(begin(p) + t, end(p));
        for (int i = 0; i < d - t; i++) q[i] -= p[t];
        vector<T> c = sparse_polynomial_power(q, vector<T>(begin(a) + t, end(a)), k, n - k * p[t]);
        for (int i = 0; i < n - k * p[t]; i++) b[k * p[t] + i] = c[i];
        return b;
    }
    vector<T> inv(n + 1, 0);
    inv[1] = 1;
    int mod = T::get_mod();
    for (int i = 2; i <= n; i++) inv[i] = -inv[mod % i] * T(mod / i);
    b[0] = a[0].pow(k);
    T y = a[0].inverse();
    for (int i = 1; i < n; i++) {
        for (int j = 1; j < d; j++) {
            if (i - p[j] < 0) break;
            b[i] += a[j] * b[i - p[j]] * (T(k + 1) * p[j] - i);
        }
        b[i] *= inv[i] * y;
    }
    return b;
}
