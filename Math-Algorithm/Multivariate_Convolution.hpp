
// 多変数畳み込み (切り捨て)
// 計算量 O(nk(log(n)+k)) (ただし、n = Σ[0<=i<k] n_i)

// 概要
// k 変数 (x_1,x_2,...,x_k) 多項式の積を mod(x_1^(n_1),x_2^(n_2),...,x_k^(n_k)) で求める。
// d(i_1,i_2,...,i_K) = i_1+n_1*i_2+n_1*n_2*i_3+...+n_1*n_2*...n_(k-1)*i_k として、
// x_1^(i_1)*x_2^(i_2)*...*x_k^(i_k) の項の係数を d(i_1,i_2,...,i_k) 番目に並べた一変数 (x) 多項式を考える。
// χ(n) = floor(n/n_1)+floor(n/(n_1*n_2))+...+floor(n/(n_1*n_2*...n_(k-1))) として、
// x^d(i_1,i_2,..,i_k) を x^d(i_1,i_2,..,i_k)*t(χ(i_1,i_2,..,i_k)) に対応させた二変数 (x,t) 多項式を考える。
// (i_1,i_2,...,i_k) と (j_1,j_2,..,j_k) を d の意味で足して d の逆変換で戻したとき、n 箇所で繰り上がりが発生していれば
// その χ は χ(i_1+j_1,i_2+j_2,...,i_k+j_k) より n 大きい値を取る。
// 0 <= n <= k であるから、実際には χ を k+1 で割った余りを考えれば十分。

// verified with
// https://judge.yosupo.jp/problem/multivariate_convolution

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Number_Theoretic_Transform.hpp"

int chi(const vector<int> &base, int n) {
    int k = base.size(), ret = 0;
    for (int e : base) ret += n / e, ret %= k + 1;
    return ret;
}

template <typename T>
vector<T> multivariate_convolve(const vector<T> &a, const vector<T> &b, const vector<int> &base) {
    using NTT_ = Number_Theoretic_Transform<T>;
    int k = base.size(), m = (k > 0 ? base.back() : 1);
    assert((int)a.size() == m && (int)b.size() == m);
    int n = 1;
    while (n < 2 * m - 1) n <<= 1;
    vector<vector<T>> A(k + 1, vector<T>(n, 0));
    vector<vector<T>> B(k + 1, vector<T>(n, 0));
    vector<vector<T>> C(k + 1, vector<T>(n, 0));
    for (int i = 0; i < m; i++) {
        int t = chi(base, i);
        A[t][i] = a[i], B[t][i] = b[i];
    }
    for (int i = 0; i <= k; i++) NTT_::ntt(A[i]), NTT_::ntt(B[i]);
    for (int i = 0; i <= k; i++) {
        for (int j = 0; j <= k; j++) {
            int t = (i + j) % (k + 1);
            for (int l = 0; l < n; l++) C[t][l] += A[i][l] * B[j][l];
        }
    }
    for (int i = 0; i <= k; i++) NTT_::intt(C[i]);
    vector<T> c(m);
    for (int i = 0; i < m; i++) c[i] = C[chi(base, i)][i];
    return c;
}
