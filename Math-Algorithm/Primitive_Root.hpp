
// 原子根
// 計算量 O(p^(1/4)log(p))

// 概要
// p-1 を素因数分解し、各素因数 e について、r^((p-1)/e) = 1 (mod p) となるような r を見つければよい。
// 原子根は全部で φ(p-1) 個あるので、r を [1,p) からランダムに生成するとき、原子根となる確率は φ(p-1)/(p-1) = O(1/log(log(p)))
// 従って、素因数した後の期待計算量は O((log(p))^2*log(log(p)))

// verified with
// https://judge.yosupo.jp/problem/primitive_root

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Math-Algorithm/Fast_Prime_Factorization.hpp"

unsigned long long primitive_root(unsigned long long p) {
    auto ps = prime_factor(p - 1);

    auto mod_pow = [&](__int128_t x, long long k) {
        __int128_t ret = 1;
        for (; k > 0; k >>= 1, x *= x, x %= p) {
            if (k & 1) ret *= x, ret %= p;
        }
        return (unsigned long long)ret;
    };

    while (true) {
        unsigned long long r = rng(1, p);
        bool flag = true;
        for (auto [e, t] : ps) {
            if (mod_pow(r, (p - 1) / e) == 1) {
                flag = false;
                break;
            }
        }
        if (flag) return r;
    }

    return 0;
}
