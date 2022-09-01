
// 有理整数環の剰余環 Z/mZ における演算 (累乗、逆元、オイラーの φ 関数、離散対数、位数、原始根)
// 計算量 k 乗：O(log(k))、逆元：O(log(m))、離散対数：(O√m+log(m))、オイラーの φ 関数・位数：O(√m)、原始根：O(φ(m-1)log(m))

// 概要
// 累乗：ダブリング
// 逆元：ユークリッドの互除法で、左から行列を作用させているとみる。
// オイラーの φ 関数：m の素因数を全て列挙し、m 以下の自然数のうち m と互いに素なものの割合を考える。
// 離散対数：Baby-step Giant-step
// 位数：φ(m) の約数を全て考える。
// 原始根：乱数で発生させて、その位数が m-1 であるかどうか判定する。原始根は最低でも φ(m-1) 個存在する。

// verified with
// https://judge.yosupo.jp/problem/discrete_logarithm_mod

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Other/Random.hpp"

struct Random_Number_Generator {
    mt19937_64 mt;

    Random_Number_Generator() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}

    // [l,r) での一様乱数
    int64_t operator()(int64_t l, int64_t r) {
        uniform_int_distribution<int64_t> dist(l, r - 1);
        return dist(mt);
    }

    // [0,r) での一様乱数
    int64_t operator()(int64_t r) { return (*this)(0, r); }
} rng;

long long modpow(long long x, long long n, const int &m) {
    x %= m;
    long long ret = 1;
    for (; n > 0; n >>= 1, x *= x, x %= m) {
        if (n & 1) ret *= x, ret %= m;
    }
    return ret;
}

template <typename T>
T modinv(T a, const T &m) {
    T b = m, u = 1, v = 0;
    while (b > 0) {
        T t = a / b;
        swap(a -= t * b, b);
        swap(u -= t * v, v);
    }
    return u >= 0 ? u % m : (m - (-u) % m) % m;
}

// オイラーの φ 関数 (x と m が互いに素ならば、x^φ(m) ≡ 1 (mod m))
template <typename T>
T Euler_totient(T m) {
    T ret = m;
    for (T i = 2; i * i <= m; i++) {
        if (m % i == 0) ret /= i, ret *= i - 1;
        while (m % i == 0) m /= i;
    }
    if (m > 1) ret /= m, ret *= m - 1;
    return ret;
}

// x^k ≡ y (mod m) となる最小の非負整数 k (存在しなければ -1)
int modlog(int x, int y, int m, int max_ans = -1) {
    if (max_ans == -1) max_ans = m;
    long long g = 1;
    for (int i = m; i > 0; i >>= 1) g *= x, g %= m;
    g = gcd(g, m);
    int c = 0;
    long long t = 1;
    for (; t % g != 0; c++) {
        if (t == y) return c;
        t *= x, t %= m;
    }
    if (y % g != 0) return -1;
    t /= g, y /= g, m /= g;
    int n = 0;
    long long gs = 1;
    for (; n * n < max_ans; n++) gs *= x, gs %= m;
    unordered_map<int, int> mp;
    long long e = y;
    for (int i = 0; i < n; mp[e] = ++i) e *= x, e %= m;
    e = t;
    for (int i = 0; i < n; i++) {
        e *= gs, e %= m;
        if (mp.count(e)) return c + n * (i + 1) - mp[e];
    }
    return -1;
}

// x^k ≡ 1 (mod m) となる最小の正整数 k (x と m は互いに素)
template <typename T>
T order(T x, const T &m) {
    T n = Euler_totient(m);
    vector<T> ds;
    for (T i = 1; i * i <= n; i++) {
        if (n % i == 0) ds.push_back(i), ds.push_back(n / i);
    }
    sort(begin(ds), end(ds));
    for (auto &e : ds) {
        if (modpow(x, e, m) == 1) return e;
    }
    return -1;
}

// 素数 p の原始根
template <typename T>
T primitive_root(const T &p) {
    vector<T> ds;
    for (T i = 1; i * i <= p - 1; i++) {
        if ((p - 1) % i == 0) ds.push_back(i), ds.push_back((p - 1) / i);
    }
    sort(begin(ds), end(ds));
    while (true) {
        T r = rng(1, p);
        for (auto &e : ds) {
            if (e == p - 1) return r;
            if (modpow(r, e, p) == 1) break;
        }
    }
}
