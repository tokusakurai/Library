#pragma once

// ローリングハッシュ、固定長ハッシュ (mod：(2^61)-1、基数：mod の原始根からランダムに取る)
// 計算量 構築：O(n)、ハッシュクエリ：O(1)

// 概要
// 文字列や配列にハッシュ値をつける。
// mod をできるだけ大きい素数、基数をその原始根に取ることで衝突が起こる確率が小さくなる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_B&lang=ja
// https://atcoder.jp/contests/arc024/tasks/arc024_3

#include <bits/stdc++.h>
using namespace std;

#include "../Other/Random.hpp"

struct Hash_Int {
    using ull = unsigned long long;
    static const ull mod = (1ULL << 61) - 1;
    ull x;

    Hash_Int() : x(0) {}

    Hash_Int(ull y) : x(y) { normalize(); }

    static ull get_mod() { return mod; }

    void normalize() {
        ull y = (x >> 61) + (x & mod);
        if (y >= mod) y -= mod;
        x = y;
    }

    // m 以上の base を乱択で生成する
    static Hash_Int generate_base(Hash_Int m = (1ULL << 50)) {
        while (true) {
            ull k = rng(mod);
            if (gcd(mod - 1, k) != 1) continue;
            Hash_Int base = Hash_Int(3).pow(k);
            if (base >= m) return base;
        }
        return 0;
    }

    Hash_Int &operator+=(const Hash_Int &p) {
        x += p.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    Hash_Int &operator-=(const Hash_Int &p) {
        x += mod - p.x;
        if (x >= mod) x -= mod;
        return *this;
    }

    Hash_Int &operator*=(const Hash_Int &p) {
        ull y = p.x;
        ull x1 = x >> 31, x2 = x & ((1ULL << 31) - 1);
        ull y1 = y >> 31, y2 = y & ((1ULL << 31) - 1);
        ull z = x1 * y2 + x2 * y1;
        ull z1 = z >> 30, z2 = z & ((1ULL << 30) - 1);
        x = x1 * y1 * 2 + x2 * y2 + z1 + (z2 << 31);
        normalize();
        return *this;
    }

    Hash_Int &operator/=(const Hash_Int &p) {
        *this *= p.inverse();
        return *this;
    }

    Hash_Int &operator++() { return *this += Hash_Int(1); }

    Hash_Int operator++(int) {
        Hash_Int tmp = *this;
        ++*this;
        return tmp;
    }

    Hash_Int &operator--() { return *this -= Hash_Int(1); }

    Hash_Int operator--(int) {
        Hash_Int tmp = *this;
        --*this;
        return tmp;
    }

    Hash_Int operator-() const { return Hash_Int(mod - x); }

    Hash_Int operator+(const Hash_Int &p) const { return Hash_Int(*this) += p; }

    Hash_Int operator-(const Hash_Int &p) const { return Hash_Int(*this) -= p; }

    Hash_Int operator*(const Hash_Int &p) const { return Hash_Int(*this) *= p; }

    Hash_Int operator/(const Hash_Int &p) const { return Hash_Int(*this) /= p; }

    bool operator==(const Hash_Int &p) const { return x == p.x; }

    bool operator!=(const Hash_Int &p) const { return x != p.x; }

    bool operator<(const Hash_Int &p) const { return x < p.x; }

    bool operator>(const Hash_Int &p) const { return x > p.x; }

    bool operator<=(const Hash_Int &p) const { return x <= p.x; }

    bool operator>=(const Hash_Int &p) const { return x >= p.x; }

    Hash_Int inverse() const {
        assert(*this != Hash_Int(0));
        return pow(mod - 2);
    }

    Hash_Int pow(long long k) const {
        Hash_Int now = *this, ret = 1;
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const Hash_Int &p) { return os << p.x; }

    friend istream &operator>>(istream &is, Hash_Int &p) {
        ull a;
        is >> a;
        p = Hash_Int(a);
        return is;
    }
};

// 0 が含まれないように
template <typename T = string>
struct Rolling_Hash {
    const int n;
    const Hash_Int base; // 基数
    vector<Hash_Int> hashed, pw;

    Rolling_Hash(const T &s, Hash_Int base) : n(s.size()), base(base) {
        hashed.assign(n + 1, 0), pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * base;
            hashed[i + 1] = hashed[i] * base + s[i];
        }
    }

    // 文字列の [l,r) の部分のハッシュ値
    Hash_Int get_hash(int l, int r) const { return hashed[r] - hashed[l] * pw[r - l]; }

    Hash_Int get_all_hash() const { return hashed[n]; }

    // s[l1:r1] と s[l2:r2] の最長共通接頭辞
    int lcp(int l1, int r1, int l2, int r2) {
        int ok = 0, ng = min(r1 - l1, r2 - l2) + 1;
        while (ng - ok > 1) {
            int mid = (ok + ng) / 2;
            (get_hash(l1, l1 + mid) == get_hash(l2, l2 + mid) ? ok : ng) = mid;
        }
        return ok;
    }

    // s[l1:r1] と s[l2:r2] の辞書順大小比較 (-1 : <, 0 : =, 1 : >)
    int comp(int l1, int r1, int l2, int r2) {
        int d = lcp(l1, r1, l2, r2);
        if (r1 == l1 + d && r2 == l2 + d) return 0;
        if (r1 == l1 + d) return -1;
        if (r2 == l2 + d) return 1;
        return get_hash(l1 + d, l1 + d + 1) < get_hash(l2 + d, l2 + d + 1) ? -1 : 1;
    }
};

template <typename T>
struct Fixed_Size_Hash {
    const int n;
    const Hash_Int base;
    vector<T> v;
    Hash_Int hashed;
    vector<Hash_Int> pw;

    Fixed_Size_Hash(const vector<T> &v, Hash_Int base) : n(v.size()), base(base), v(v) {
        hashed = 0;
        pw.assign(n + 1, 1);
        for (int i = 0; i < n; i++) {
            pw[i + 1] = pw[i] * base;
            hashed = hashed * base + v[i];
        }
    }

    Fixed_Size_Hash(int m, const T &x, Hash_Int base) : Fixed_Size_Hash(vector<T>(m, x), base) {}

    Hash_Int add(int i, const T &x) {
        hashed += pw[n - 1 - i] * (Hash_Int::get_mod() + x);
        v[i] += x;
        return hashed;
    }

    Hash_Int change(int i, const T &x) { return add(i, x - v[i]); }

    Hash_Int get_hash() const { return hashed; }
};
