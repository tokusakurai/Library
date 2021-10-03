
// 約数系ゼータ変換、約数系メビウス変換
// 計算量 約数系ゼータ変換、約数系メビウス変換 : O(N*log(log(N)))

// ゼータ変換 : g(T) = Σf(S) (T|S) (上位集合)、 g(T) = Σf(S) (S|T) (下位集合)
// メビウス変換 : ゼータ変換の逆変換

// 概要
// 高速ゼータ変換 : 素因数分解したときに各素因数についての累積和とみなすことができる。
// 高速メビウス変換 : 同様に、各素因数についての差分であるとみなすことができる。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
void divisors_zeta_transform(vector<T> &a, bool upper) {
    int n = a.size();
    vector<bool> is_prime(n, true);
    if (!upper) {
        for (int i = 1; i < n; i++) a[0] += a[i];
    }
    for (int i = 2; i < n; i++) {
        if (!is_prime[i]) continue;
        if (upper) {
            for (int j = (n - 1) / i; j > 0; j--) {
                is_prime[j * i] = false;
                a[j] += a[j * i];
            }
        } else {
            for (int j = 1; j * i < n; j++) {
                is_prime[j * i] = false;
                a[j * i] += a[j];
            }
        }
    }
    if (upper) {
        for (int i = 1; i < n; i++) a[i] += a[0];
    }
}

template <typename T>
void divisors_mobius_transform(vector<T> &a, bool upper) {
    int n = a.size();
    vector<bool> is_prime(n, true);
    if (upper) {
        for (int i = 1; i < n; i++) a[i] -= a[0];
    }
    for (int i = 2; i < n; i++) {
        if (!is_prime[i]) continue;
        if (upper) {
            for (int j = 1; j * i < n; j++) {
                is_prime[j * i] = false;
                a[j] -= a[j * i];
            }
        } else {
            for (int j = (n - 1) / i; j > 0; j--) {
                is_prime[j * i] = false;
                a[j * i] -= a[j];
            }
        }
    }
    if (!upper) {
        for (int i = 1; i < n; i++) a[0] -= a[i];
    }
}
