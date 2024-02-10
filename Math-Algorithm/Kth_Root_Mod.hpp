#pragma once

// 2 乗根・K 乗根 (Z/pZ)
// 計算量 2 乗根：O(log^2(p))、k 乗根：O(g^(1/4)log(g) + log^2(p)) (g = gcd(k, p-1))

// 概要
// x^k = a ⇔ x^g = a^h (h = (k/g)^(-1) mod (p-1)/g) であるから、k = m^e = q (m:素数、q|(p-1)) の場合に解ければこれを繰り返せば良い。
// 原始根 r について x = r^y, a = r^b とする。
// p-1 = s*m^t (s と m は互いに素) とすると、x^q = a ⇔ qy ≡ b (mod s) かつ qy ≡ b (mod m^t) である。
// x = a^((1+s(q-s'))/q) (s' は s の mod m^t における逆元) とすると 1 つ目の条件は満たされるので、 2 つ目の条件が満たされるように調整する。

#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Factor_Ring.hpp"
#include "../Math-Algorithm/Fast_Prime_Factorization.hpp"
#include "../Other/Random.hpp"

// 素数 p について、x^2 ≡ a (mod p) となる x を 1 つ求める (存在しなければ -1)
int sqrt_mod(int a, const int &p) {
    if (a == 0) return 0;
    if (p == 2) return a;
    if (modpow(a, (p - 1) / 2, p) != 1) return -1;
    int s = p - 1, t = 0;
    while (s % 2 == 0) s /= 2, t++;
    long long x = modpow(a, (s + 1) / 2, p);
    long long u = 2;
    while (modpow(u, (p - 1) / 2, p) == 1) u = rng(2, p);
    u = modpow(u, s, p);
    long long y = (1LL * x * x % p) * modinv(a, p) % p;
    while (y != 1) {
        int k = 0;
        long long z = y;
        while (z != 1) k++, z *= z, z %= p;
        for (int i = 0; i < t - k - 1; i++) u *= u, u %= p;
        x *= u, x %= p;
        u *= u, u %= p;
        y *= u, y %= p;
        t = k;
    }
    return x;
}

// x^(m^e) ≡ a (mod p) (m が p-1 の素因数であり、解が存在する場合)
int prime_power_root_mod(int m, int e, int a, const int &p) {
    int s = p - 1, t = 0;
    while (s % m == 0) s /= m, t++;
    vector<int> pw(t + 1, 1);
    for (int i = 0; i < t; i++) pw[i + 1] = pw[i] * m;
    int q = pw[e];
    long long x = modpow(a, (1 + 1LL * s * (q - modinv(s, q))) / q, p);
    long long u = 2;
    while (modpow(u, (p - 1) / m, p) == 1) u = rng(2, p);
    u = modpow(u, s, p);
    long long y = modpow(x, q, p) * modinv(a, p) % p;
    while (y != 1) {
        int k = 0;
        long long z = y;
        while (z != 1) k++, z = modpow(z, m, p);
        long long w = modpow(u, pw[t - k - e], p);
        long long v = modpow(w, pw[e + k - 1], p);
        long long inv = modinv((int)modpow(y, pw[k - 1], p), p);
        int n = modlog(v, inv, p, m);
        w = modpow(w, n, p);
        x *= w, x %= p;
        y *= modpow(w, q, p), y %= p;
    }
    return x;
}

// 素数 p について、x^k ≡ a (mod p) となる x を 1 つ求める (存在しなければ -1)
int kth_root_mod(int k, int a, const int &p) {
    if (a == 0) return k == 0 ? -1 : 0;
    if (p == 2) return a;
    int g = gcd(k, p - 1);
    if (modpow(a, (p - 1) / g, p) != 1) return -1;
    auto ps = prime_factor(g);
    int x = modpow(a, modinv(k / g, (p - 1) / g), p);
    for (auto [m, e] : ps) x = prime_power_root_mod(m, e, x, p);
    return x;
}
