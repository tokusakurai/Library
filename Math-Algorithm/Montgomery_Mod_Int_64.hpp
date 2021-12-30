
// モンゴメリ乗算 mod-int 構造体（64 ビット）
// 計算量 加減乗算：O(1)、除算：O(log(mod))、k 乗：O(log(k))

// 概要
// モントゴメリ乗算を用いて積の剰余を計算する。
// R = 2^64 として、R がかかった状態での値を保持している。
// また reduction の高速化として、2*mod での余りを保持している。

// verified with
// https://judge.yosupo.jp/problem/factorize

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Montgomery_Mod_Int_64 {
    using u64 = uint64_t;
    using u128 = __uint128_t;

    static u64 mod;
    static u64 r;  // m*r ≡ 1 (mod 2^64)
    static u64 n2; // 2^128 (mod mod)

    u64 x;

    Montgomery_Mod_Int_64() : x(0) {}

    Montgomery_Mod_Int_64(long long b) : x(reduce((u128(b) + mod) * n2)) {}

    static u64 get_r() { // mod 2^64 での逆元
        u64 ret = mod;
        for (int i = 0; i < 5; i++) ret *= 2 - mod * ret;
        return ret;
    }

    static u64 get_mod() { return mod; }

    static void set_mod(u64 m) {
        assert(m < (1LL << 62));
        assert((m & 1) == 1);
        mod = m;
        n2 = -u128(m) % m;
        r = get_r();
        assert(r * mod == 1);
    }

    static u64 reduce(const u128 &b) { return (b + u128(u64(b) * u64(-r)) * mod) >> 64; }

    Montgomery_Mod_Int_64 &operator+=(const Montgomery_Mod_Int_64 &p) {
        if ((x += p.x) >= 2 * mod) x -= 2 * mod;
        return *this;
    }

    Montgomery_Mod_Int_64 &operator-=(const Montgomery_Mod_Int_64 &p) {
        if ((x += 2 * mod - p.x) >= 2 * mod) x -= 2 * mod;
        return *this;
    }

    Montgomery_Mod_Int_64 &operator*=(const Montgomery_Mod_Int_64 &p) {
        x = reduce(u128(x) * p.x);
        return *this;
    }

    Montgomery_Mod_Int_64 &operator/=(const Montgomery_Mod_Int_64 &p) {
        *this *= p.inverse();
        return *this;
    }

    Montgomery_Mod_Int_64 &operator++() { return *this += Montgomery_Mod_Int_64(1); }

    Montgomery_Mod_Int_64 operator++(int) {
        Montgomery_Mod_Int_64 tmp = *this;
        ++*this;
        return tmp;
    }

    Montgomery_Mod_Int_64 &operator--() { return *this -= Montgomery_Mod_Int_64(1); }

    Montgomery_Mod_Int_64 operator--(int) {
        Montgomery_Mod_Int_64 tmp = *this;
        --*this;
        return tmp;
    }

    Montgomery_Mod_Int_64 operator+(const Montgomery_Mod_Int_64 &p) const { return Montgomery_Mod_Int_64(*this) += p; };

    Montgomery_Mod_Int_64 operator-(const Montgomery_Mod_Int_64 &p) const { return Montgomery_Mod_Int_64(*this) -= p; };

    Montgomery_Mod_Int_64 operator*(const Montgomery_Mod_Int_64 &p) const { return Montgomery_Mod_Int_64(*this) *= p; };

    Montgomery_Mod_Int_64 operator/(const Montgomery_Mod_Int_64 &p) const { return Montgomery_Mod_Int_64(*this) /= p; };

    bool operator==(const Montgomery_Mod_Int_64 &p) const { return (x >= mod ? x - mod : x) == (p.x >= mod ? p.x - mod : p.x); };

    bool operator!=(const Montgomery_Mod_Int_64 &p) const { return (x >= mod ? x - mod : x) != (p.x >= mod ? p.x - mod : p.x); };

    Montgomery_Mod_Int_64 inverse() const {
        assert(*this != Montgomery_Mod_Int_64(0));
        return pow(mod - 2);
    }

    Montgomery_Mod_Int_64 pow(long long k) const {
        Montgomery_Mod_Int_64 now = *this, ret = 1;
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    u64 get() const {
        u64 ret = reduce(x);
        return ret >= mod ? ret - mod : ret;
    }

    friend ostream &operator<<(ostream &os, const Montgomery_Mod_Int_64 &p) { return os << p.get(); }

    friend istream &operator>>(istream &is, Montgomery_Mod_Int_64 &p) {
        long long a;
        is >> a;
        p = Montgomery_Mod_Int_64(a);
        return is;
    }
};

typename Montgomery_Mod_Int_64::u64 Montgomery_Mod_Int_64::mod, Montgomery_Mod_Int_64::r, Montgomery_Mod_Int_64::n2;
