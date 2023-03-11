
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

bool Miller_Rabin(long long n, vector<long long> as) {
    using Mint = Montgomery_Mod_Int_64;
    if (Mint::get_mod() != n) Mint::set_mod(n);
    long long d = n - 1;
    while (!(d & 1)) d >>= 1;
    Mint e = 1, rev = n - 1;
    for (long long a : as) {
        if (n <= a) break;
        long long t = d;
        Mint y = Mint(a).pow(t);
        while (t != n - 1 && y != e && y != rev) {
            y *= y;
            t <<= 1;
        }
        if (y != rev && (!(t & 1))) return false;
    }
    return true;
}

bool is_prime(long long n) {
    if (!(n & 1)) return n == 2;
    if (n <= 1) return false;
    if (n < (1LL << 30)) return Miller_Rabin(n, {2, 7, 61});
    return Miller_Rabin(n, {2, 325, 9375, 28178, 450775, 9780504, 1795265022});
}

long long Pollard_rho(long long n) {
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
        long long g = 1;
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

vector<long long> factorize(long long n) {
    if (n <= 1) return {};
    long long p = Pollard_rho(n);
    if (p == n) return {n};
    auto l = factorize(p);
    auto r = factorize(n / p);
    copy(begin(r), end(r), back_inserter(l));
    return l;
}

vector<pair<long long, int>> prime_factor(long long n) {
    auto ps = factorize(n);
    sort(begin(ps), end(ps));
    vector<pair<long long, int>> ret;
    for (auto &e : ps) {
        if (!ret.empty() && ret.back().first == e) {
            ret.back().second++;
        } else {
            ret.emplace_back(e, 1);
        }
    }
    return ret;
}

vector<long long> divisors(long long n) {
    auto ps = prime_factor(n);
    int cnt = 1;
    for (auto &[p, t] : ps) cnt *= t + 1;
    vector<long long> ret(cnt, 1);
    cnt = 1;
    for (auto &[p, t] : ps) {
        long long pw = 1;
        for (int i = 1; i <= t; i++) {
            pw *= p;
            for (int j = 0; j < cnt; j++) ret[cnt * i + j] = ret[j] * pw;
        }
        cnt *= t + 1;
    }
    sort(begin(ret), end(ret));
    return ret;
}
