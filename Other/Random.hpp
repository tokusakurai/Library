
// 乱数発生
// 計算量 O(1)

#pragma once
#include <bits/stdc++.h>
using namespace std;

struct Random_Number_Generator {
    mt19937_64 mt;

    Random_Number_Generator() : mt(chrono::steady_clock::now().time_since_epoch().count()) {}

    int64_t operator()(int64_t l, int64_t r) { // 区間 [l,r) の整数で乱数発生
        uniform_int_distribution<int64_t> dist(l, r - 1);
        return dist(mt);
    }

    int64_t operator()(int64_t r) { // 区間 [0,r) の整数で乱数発生
        return (*this)(0, r);
    }
} rng;
