
// ローリングハッシュ、固定長ハッシュ (mod：(2^61)-1、基数：mod の原始根からランダムに取る)
// 計算量 構築：O(n)、ハッシュクエリ：O(1)

// 概要
// 文字列や配列にハッシュ値をつける。
// mod をできるだけ大きい素数、基数をその原始根に取ることで衝突が起こる確率が小さくなる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
// https://atcoder.jp/contests/arc024/tasks/arc024_3

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Other/Random.hpp"

using ull = unsigned long long;
const ull mod = (1ULL << 61) - 1;

ull hash_mod(ull x) {
    ull ret = (x >> 61) + (x & mod);
    return ret - (ret >= mod ? mod : 0);
}

ull hash_mul(ull x, ull y) {
    x = hash_mod(x), y = hash_mod(y);
    ull x1 = x >> 31, x2 = x & ((1ULL << 31) - 1), y1 = y >> 31, y2 = y & ((1ULL << 31) - 1);
    ull z = x1 * y2 + x2 * y1, z1 = z >> 30, z2 = z & ((1ULL << 30) - 1);
    return hash_mod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
}

ull hash_pow(ull x, ull n) {
    ull ret = 1;
    for (; n > 0; n >>= 1, x = hash_mul(x, x)) {
        if (n & 1) ret = hash_mul(ret, x);
    }
    return ret;
}

// m 以上の base を乱択で生成する
ull generate_base(ull m = (1ULL << 50)) {
    while (true) {
        ull k = rng(mod);
        if (gcd(mod - 1, k) != 1) continue;
        ull base = hash_pow(3, k);
        if (base >= m) return base;
    }
    return 0;
}

// 0 が含まれないように
template <typename T = string>
struct Rolling_Hash {
    const int n;
    const ull base; // 基数
    vector<ull> hashed, pw;

    Rolling_Hash(const T &s, ull base) : n(s.size()), base(base) {
        hashed.assign(n + 1, 0), pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = hash_mul(pw[i], base);
            hashed[i + 1] = hash_mul(hashed[i], base) + s[i];
            if (hashed[i + 1] >= mod) hashed[i + 1] -= mod;
        }
    }

    // 文字列の [l,r) の部分のハッシュ値
    ull get_hash(int l, int r) const {
        ull ret = hashed[r] + mod - hash_mul(hashed[l], pw[r - l]);
        return ret - (ret >= mod ? mod : 0);
    }

    ull get_all_hash() const { return hashed[n]; }
};

template <typename T>
struct Fixed_Size_Hash {
    const int n;
    const ull base;
    vector<T> v;
    ull hashed;
    vector<ull> pw;

    Fixed_Size_Hash(const vector<T> &v, ull base) : n(v.size()), base(base), v(v) {
        hashed = 0;
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = hash_mul(pw[i], base);
            hashed = hash_mul(hashed, base) + v[i];
            if (hashed >= mod) hashed -= mod;
        }
    }

    Fixed_Size_Hash(int m, const T &x, ull base) : Fixed_Size_Hash(vector<T>(m, x), base) {}

    ull add(int i, const T &x) {
        hashed += hash_mul(pw[n - 1 - i], mod + x);
        if (hashed >= mod) hashed -= mod;
        v[i] += x;
        return hashed;
    }

    ull change(int i, const T &x) { return add(i, x - v[i]); }

    ull get_hash() const { return hashed; }
};
