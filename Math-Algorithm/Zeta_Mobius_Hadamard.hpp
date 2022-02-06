
// 高速ゼータ変換、高速メビウス変換、高速アダマール変換
// 計算量 高速ゼータ変換・高速メビウス変換・高速アダマール変換：O(n log(n))

// ゼータ変換：g(T) = Σ[S⊇T]f(S)（上位集合）、g(T) = Σ[S⊆T]f(S)（下位集合）
// メビウス変換：ゼータ変換の逆変換
// アダマール変換：アダマール行列を左から作用させる

// 概要
// 高速ゼータ変換：長さ n の 2 進数表記を n 次元空間での座標のように見なせば、n 次元の累積和であるとみなすことができる。
// 高速メビウス変換：同様に、n 次元の差分であるとみなすことができる。
// 高速アダマール変換：(アダマール行列の (i,j) 成分) = (-1)^(i・j) （i・j は n 次元ベクトルとみたときの i と j の内積）

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
void fast_zeta_transform(vector<T> &a, bool upper) {
    int n = a.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if (!(j & i)) {
                if (upper) {
                    a[j] += a[j | i];
                } else {
                    a[j | i] += a[j];
                }
            }
        }
    }
}

template <typename T>
void fast_mobius_transform(vector<T> &a, bool upper) {
    int n = a.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if (!(j & i)) {
                if (upper) {
                    a[j] -= a[j | i];
                } else {
                    a[j | i] -= a[j];
                }
            }
        }
    }
}

template <typename T>
void fast_hadamard_transform(vector<T> &a, bool inverse = false) {
    int n = a.size();
    assert((n & (n - 1)) == 0);
    for (int i = 1; i < n; i <<= 1) {
        for (int j = 0; j < n; j++) {
            if (!(j & i)) {
                T x = a[j], y = a[j | i];
                a[j] = x + y, a[j | i] = x - y;
            }
        }
    }
    if (inverse) {
        T inv = T(1) / T(n);
        for (auto &e : a) e *= inv;
    }
}
