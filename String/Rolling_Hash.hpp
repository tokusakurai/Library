
// ローリングハッシュ、配列ハッシュ (mod : (2^61)-1、基数 : modの原始根からランダムに取る)
// 計算量 構築 : O(n), ハッシュクエリ : O(1)

// 概要
// 文字列や配列にハッシュ値をつける。
// modをできるだけ大きい素数、基数をその原始根に取ることで衝突が起こる確率が小さくなる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
// https://atcoder.jp/contests/arc024/tasks/arc024_3

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Other/Random.hpp"

using ull = unsigned long long;

struct Rolling_Hash {
    const ull mod = (1ULL << 61) - 1;

    ull calc_mod(ull x) const {
        ull ret = (x >> 61) + (x & mod);
        return ret - (ret >= mod ? mod : 0);
    }

    ull mul(ull x, ull y) const {
        x = calc_mod(x), y = calc_mod(y);
        ull x1 = x >> 31, x2 = x & ((1ULL << 31) - 1), y1 = y >> 31, y2 = y & ((1ULL << 31) - 1);
        ull z = x1 * y2 + x2 * y1, z1 = z >> 30, z2 = z & ((1ULL << 30) - 1);
        return calc_mod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
    }

    ull pow(ull x, ull n) const {
        ull ret = 1;
        for (; n > 0; n >>= 1, x = mul(x, x)) {
            if (n & 1) ret = mul(ret, x);
        }
        return ret;
    }

    ull base; // 基数
    vector<ull> hashed, pw;

    void set_base() { // 基数は乱数を用いて生成する
        while (true) {
            ull k = rng(mod);
            if (gcd(mod - 1, k) != 1) continue;
            base = pow(3, k);
            if (base < 256) continue;
            break;
        }
    }

    Rolling_Hash(const string &s) {
        set_base();
        int n = s.size();
        hashed.resize(n + 1), pw.resize(n + 1);
        hashed[0] = 0, pw[0] = 1;
        for (int i = 0; i < n; i++) {
            pw[i + 1] = mul(pw[i], base);
            hashed[i + 1] = mul(hashed[i], base) + s[i];
            if (hashed[i + 1] >= mod) hashed[i + 1] -= mod;
        }
    }

    ull query(int l, int r) const { // 文字列の[l,r)の部分のハッシュ値
        ull ret = hashed[r] + mod - mul(hashed[l], pw[r - l]);
        return ret - (ret >= mod ? mod : 0);
    }

    ull get_hash(const string &s) const {
        ull ret = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            ret = mul(ret, base) + s[i];
            if (ret >= mod) ret -= mod;
        }
        return ret;
    }
};

template <typename T>
struct Array_Hash {
    const ull mod = (1ULL << 61) - 1;

    ull calc_mod(ull x) const {
        ull ret = (x >> 61) + (x & mod);
        return ret - (ret >= mod ? mod : 0);
    }

    ull mul(ull x, ull y) const {
        x = calc_mod(x), y = calc_mod(y);
        ull x1 = x >> 31, x2 = x & ((1ULL << 31) - 1), y1 = y >> 31, y2 = y & ((1ULL << 31) - 1);
        ull z = x1 * y2 + x2 * y1, z1 = z >> 30, z2 = z & ((1ULL << 30) - 1);
        return calc_mod(x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31));
    }

    ull pow(ull x, ull n) const {
        ull ret = 1;
        for (; n > 0; n >>= 1, x = mul(x, x)) {
            if (n & 1) ret = mul(ret, x);
        }
        return ret;
    }

    ull base;
    vector<ull> pw;

    void set_base(T m) {
        Random_Number_Generator rng;
        while (true) {
            ull k = rng(mod);
            if (gcd(mod - 1, k) != 1) continue;
            base = pow(3, k);
            if (base <= ull(m)) continue;
            break;
        }
    }

    Array_Hash(int n, T m) { // 配列の長さ、要素の最大値
        set_base(m);
        pw.resize(n + 1);
        pw[0] = 1;
        for (int i = 0; i < n; i++) { pw[i + 1] = mul(pw[i], base); }
    }

    ull get_hash(const vector<T> &v) const {
        ull ret = 0;
        for (int i = 0; i < (int)v.size(); i++) {
            ret += mul(v[i], pw[i]);
            if (ret >= mod) ret -= mod;
        }
        return ret;
    }
};
