
// 高速素因数分解
// 計算量 O(n^(1/4)log(n))

// 概要
// ミラーラビンの素数判定法で素数判定をし、素数なら終了する。
// 素数でないならばポラードのロー法で非自明な約数を発見し、再帰的に素因数分解する。

// verified with
// https://judge.yosupo.jp/problem/factorize

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Montgomery_Mod_Int_64.hpp"
#include "../Other/Random.hpp"

bool Miller_Rabin(unsigned long long n, vector<unsigned long long> as) {
    using Mint = Montgomery_Mod_Int_64;
    if (Mint::get_mod() != n) Mint::set_mod(n);
    unsigned long long d = n - 1;
    while (!(d & 1)) d >>= 1;
    Mint e = 1, rev = n - 1;
    for (unsigned long long a : as) {
        if (n <= a) break;
        unsigned long long t = d;
        Mint y = Mint(a).pow(t);
        while (t != n - 1 && y != e && y != rev) {
            y *= y;
            t <<= 1;
        }
        if (y != rev && (!(t & 1))) return false;
    }
    return true;
}

bool is_prime(unsigned long long n) {
    if (!(n & 1)) return n == 2;
    if (n <= 1) return false;
    if (n < (1LL << 30)) return Miller_Rabin(n, {2, 7, 61});
    return Miller_Rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

unsigned long long Pollard_rho(unsigned long long n) {
    using Mint = Montgomery_Mod_Int_64;
    if (!(n & 1)) return 2;
    if (is_prime(n)) return n;
    if (Mint::get_mod() != n) Mint::set_mod(n);
    Mint R, one = 1;
    auto f = [&](Mint x) { return x * x + R; };
    auto rnd = [&]() { return rng(n - 2) + 2; };
    while (true) {
        Mint x, y, ys, q = one;
        R = rnd(), y = rnd();
        unsigned long long g = 1;
        int m = 128;
        for (int r = 1; g == 1; r <<= 1) {
            x = y;
            for (int i = 0; i < r; i++) y = f(y);
            for (int k = 0; g == 1 && k < r; k += m) {
                ys = y;
                for (int i = 0; i < m && i < r - k; i++) q *= x - (y = f(y));
                g = gcd(q.get(), n);
            }
        }
        if (g == n) {
            do { g = gcd((x - (ys = f(ys))).get(), n); } while (g == 1);
        }
        if (g != n) return g;
    }
    return 0;
}

vector<unsigned long long> factorize(unsigned long long n) {
    if (n <= 1) return {};
    unsigned long long p = Pollard_rho(n);
    if (p == n) return {n};
    auto l = factorize(p);
    auto r = factorize(n / p);
    copy(begin(r), end(r), back_inserter(l));
    return l;
}

vector<pair<unsigned long long, int>> prime_factor(unsigned long long n) {
    auto ps = factorize(n);
    sort(begin(ps), end(ps));
    vector<pair<unsigned long long, int>> ret;
    for (auto &e : ps) {
        if (!ret.empty() && ret.back().first == e) {
            ret.back().second++;
        } else {
            ret.emplace_back(e, 1);
        }
    }
    return ret;
}
