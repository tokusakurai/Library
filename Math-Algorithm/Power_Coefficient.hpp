
// 多項式べき乗の係数
// 計算量 O(nd)

// 概要
// A(x) = Σ[0<=i<d]a[i]x^i として、A(x)^k の先頭 n+1 項を求める。
// B(x) = A(x)^k とすると、形式的微分により B'(x) = kA'(x)A(x)^(k-1) であるから、両辺に A(x) をかけて
// A(x)B'(x) = kA'(x)B(x) となるので、この両辺の x^(i-1) の項の係数を比較して
// i*a[0]b[m] = Σ[1<=j<=d-1]{(k+1)j-i}a[j]b[i-j] となるから、B の係数についての漸化式が立つ。（ただし、b[i] = [x^i]B(x)）
// b[0] = a[0]^k としてこの漸化式を使えばよい。（a[0] ≠ 0 の場合は a[t] ≠ 0 となる最小の t について x^t で割ってからやり直す）

// verified with
// https://atcoder.jp/contests/abc222/tasks/abc222_h

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> power_coefficient(const vector<T> &a, long long k, int n) { // A(x)^k の先頭 n+1 項
    int d = a.size();
    int t = 0;
    while (t < d && a[t] == 0) t++;
    if (t == d) return vector<T>(n + 1, 0);
    if (t > 0) {
        if (k > n / t) return vector<T>(n + 1, 0);
        vector<T> b(n + 1, 0);
        vector<T> c = power_coefficient(vector<T>(begin(a) + t, end(a)), k, n - k * t);
        for (int i = 0; i <= n - k * t; i++) b[k * t + i] = c[i];
        return b;
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
    return b;
}
