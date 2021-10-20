
// mod-int構造体(modは素数)
// 計算量 加減乗算 : O(1), 除算 : O(log(mod)), k乗 : O(log(k))

// 累乗 : ダブリング
// 逆元 : aとmが互いに素なとき、フェルマーの小定理よりa^(m-1)≡1(mod m)なので、aの逆元はa^(m-2)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=DPL_5_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <int mod>
struct Mod_Int {
    int x;

    Mod_Int() : x(0) {}

    Mod_Int(long long y) : x(y >= 0 ? y % mod : (mod - (-y) % mod) % mod) {}

    static int get_mod() { return mod; }

    Mod_Int &operator+=(const Mod_Int &p) {
        if ((x += p.x) >= mod) x -= mod;
        return *this;
    }

    Mod_Int &operator-=(const Mod_Int &p) {
        if ((x += mod - p.x) >= mod) x -= mod;
        return *this;
    }

    Mod_Int &operator*=(const Mod_Int &p) {
        x = (int)(1LL * x * p.x % mod);
        return *this;
    }

    Mod_Int &operator/=(const Mod_Int &p) {
        *this *= p.inverse();
        return *this;
    }

    Mod_Int &operator++() { return *this += Mod_Int(1); }

    Mod_Int operator++(int) {
        Mod_Int tmp = *this;
        ++*this;
        return tmp;
    }

    Mod_Int &operator--() { return *this -= Mod_Int(1); }

    Mod_Int operator--(int) {
        Mod_Int tmp = *this;
        --*this;
        return tmp;
    }

    Mod_Int operator-() const { return Mod_Int(-x); }

    Mod_Int operator+(const Mod_Int &p) const { return Mod_Int(*this) += p; }

    Mod_Int operator-(const Mod_Int &p) const { return Mod_Int(*this) -= p; }

    Mod_Int operator*(const Mod_Int &p) const { return Mod_Int(*this) *= p; }

    Mod_Int operator/(const Mod_Int &p) const { return Mod_Int(*this) /= p; }

    bool operator==(const Mod_Int &p) const { return x == p.x; }

    bool operator!=(const Mod_Int &p) const { return x != p.x; }

    Mod_Int inverse() const {
        assert(*this != Mod_Int(0));
        return pow(mod - 2);
    }

    Mod_Int pow(long long k) const {
        Mod_Int now = *this, ret = 1;
        for (; k > 0; k >>= 1, now *= now) {
            if (k & 1) ret *= now;
        }
        return ret;
    }

    friend ostream &operator<<(ostream &os, const Mod_Int &p) { return os << p.x; }

    friend istream &operator>>(istream &is, Mod_Int &p) {
        long long a;
        is >> a;
        p = Mod_Int<mod>(a);
        return is;
    }
};
