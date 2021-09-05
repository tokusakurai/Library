
// 多変数畳み込み(切り捨て)
// 計算量 O(K*N*log(N)+K^2*N)

// 概要
// K変数(x_1,x_2,...,x_K)多項式の積をmod(x_1^(N_1),x_2^(N_2),...,x_K^(N_K))で求める。
// d(i_1,i_2,...,i_K) = i_1+N_1*i_2+N_1*N_2*i_3+...+N_1*N_2*...N_(K-1)*i_Kとして、
// x_1^(i_1)*x_2^(i_2)*...*x_K^(i_K)の項の係数をd(i_1,i_2,...,i_K)番目に並べた一変数(x)多項式を考える。
// χ(N) = floor(N/N_1)+floor(N/(N_1*N_2))+...+floor(N/(N_1*N_2*...N_(K-1)))として、
// x^d(i_1,i_2,..,i_K)をx^d(i_1,i_2,..,i_K)*t(χ(i_1,i_2,..,i_K))に対応させた二変数(x,t)多項式を考える。
// (i_1,i_2,...,i_K)と(j_1,j_2,..,j_K)をdの意味で足してdの逆変換で戻したとき、n箇所で繰り上がりが発生していれば
// そのχはχ(i_1+j_1,i_2+j_2,...,i_K+j_K)よりn大きい値を取る。
// 0<=n<=Kであるから、実際にはχをK+1で割った余りを考えれば十分。

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
