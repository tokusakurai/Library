
// 多項式べき乗の係数
// 計算量 O(nd)

// 概要
// A(x) = Σ[0<=i<d]a[i]x^i として、[x^n]A(x)^k を求める。
// B(x) = A(x)^k とすると、形式的微分により B'(x) = kA'(x)A(x)^(k-1) であるから、両辺にA(x)をかけて
// A(x)B'(x) = kA'(x)B(x) となるので、この両辺の x^(m-1) の項の係数を比較して
// ma[0]b[m] = Σ[1<=i<d]{(k+1)i-m}a[i]b[m-i] となるから、B の係数についての漸化式が立つ。(ただし、b[m] = [x^m]B(x))

// verified with
// https://atcoder.jp/contests/abc222/tasks/abc222_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
T power_coefficient(const vector<T> &a, long long k, int n) { // [x^n]A(x)^k
    int d = a.size();
    int t = 0;
    while (t < d && a[t] == 0) t++;
    if (t == d) return 0;
    if (t > 0) {
        if (k > n / t) return 0;
        return power_coefficient(vector<T>(begin(a) + t, end(a)), k, n - k * t);
    }
    vector<T> inv(n + 1, 1);
    for (int i = 1; i <= n; i++) inv[i] = inv[i - 1] * i;
    T x = inv[n].inverse();
    for (int i = n; i >= 1; i--) {
        inv[i] = inv[i - 1] * x;
        x *= i;
    }
    vector<T> b(n + 1, 0);
    b[0] = a[0].pow(k);
    T y = a[0].inverse();
    for (int i = 1; i <= n; i++) {
        for (int j = 1; j < d; j++) {
            if (i - j < 0) break;
            b[i] += a[j] * b[i - j] * (T(k + 1) * j - i);
        }
        b[i] *= inv[i] * y;
    }
    return b[n];
}
