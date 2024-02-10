#pragma once

// 疎な形式的冪級数演算
// 計算量 inv・log・exp：O(nd)、pow：O(nd + log(k))

// 概要
// f(x) = Σ[0<=i<d] a[i]*x^p[i]
// g(x)/f(x)：前から求まる
// log(f(x))：∫f'(x)/f(x)dx
// exp(f(x))：g(x) = exp(f(x)) とすると、g'(x) = f'(x)g(x) -> 前から求まる
// f(x)^k：g(x) = f(x)^k とすると、f(x)g'(x) = kf'(x)g(x) -> 前から求まる

// verified with
// https://judge.yosupo.jp/problem/inv_of_formal_power_series_sparse
// https://judge.yosupo.jp/problem/exp_of_formal_power_series_sparse
// https://judge.yosupo.jp/problem/log_of_formal_power_series_sparse
// https://judge.yosupo.jp/problem/pow_of_formal_power_series_sparse
// https://atcoder.jp/contests/abc222/tasks/abc222_h

#include <bits/stdc++.h>
using namespace std;

// g(x)/f(x) mod x^n (f(x) = Σ[0<=i<d] a[i]*x^p[i], f[0] != 0, g(x) = Σ b[i]*x^i)
template <typename T>
vector<T> sparse_polynomial_inv(const vector<int> &p, const vector<T> &a, vector<T> b, int n) {
    int d = p.size();
    T inv = a[0].inverse();
    b.resize(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 1; j < d; j++) {
            if (i - p[j] < 0) break;
            b[i] -= a[j] * b[i - p[j]];
        }
        b[i] *= inv;
    }
    return b;
}

// log(f(x)) mod x^n (f(x) = Σ[0<=i<d] a[i]*x^p[i], f[0] = 1)
template <typename T>
vector<T> sparse_polynomial_log(const vector<int> &p, const vector<T> &a, int n) {
    int d = p.size();
    vector<T> b(n, 0);
    for (int i = 1; i < d; i++) b[p[i] - 1] += a[i] * T(p[i]);
    b = sparse_polynomial_inv(p, a, b, n);
    vector<T> inv(n + 1, 0);
    inv[1] = 1;
    int mod = T::get_mod();
    for (int i = 2; i <= n; i++) inv[i] = -inv[mod % i] * T(mod / i);
    for (int i = n - 1; i >= 1; i--) b[i] = b[i - 1] * inv[i];
    b[0] = 0;
    return b;
}

// exp(f(x)) mod x^n (f(x) = Σ[0<=i<d] a[i]*x^p[i], f[0] = 0)
template <typename T>
vector<T> sparse_polynomial_exp(const vector<int> &p, const vector<T> &a, int n) {
    int d = p.size();
    vector<T> inv(n + 1, 0);
    inv[1] = 1;
    int mod = T::get_mod();
    for (int i = 2; i <= n; i++) inv[i] = -inv[mod % i] * T(mod / i);
    vector<T> b(n, 0);
    b[0] = 1;
    for (int i = 1; i < n; i++) {
        for (int j = 0; j < d; j++) {
            if (i - p[j] < 0) break;
            b[i] += b[i - p[j]] * a[j] * T(p[j]);
        }
        b[i] *= inv[i];
    }
    return b;
}

// f(x)^k mod x^n (f(x) = Σ[0<=i<d] a[i]*x^p[i])
template <typename T>
vector<T> sparse_polynomial_pow(const vector<int> &p, const vector<T> &a, long long k, int n) {
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
        vector<T> c = sparse_polynomial_pow(q, vector<T>(begin(a) + t, end(a)), k, n - k * p[t]);
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
