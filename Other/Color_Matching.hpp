#pragma once

// color matching (各頂点に色が与えられたときに、異色になる組数が最大になるようなマッチング)
// 計算量 O(n log(n))

// 概要
// 色でソートして、 i 番目と i+n/2 番目をマッチングさせていく。

#include <bits/stdc++.h>
using namespace std;

// c_i != c_j となるようなものをできるだけ多くマッチングさせる。
// 奇数のときは 1 つ余る。c_i = -1 のときは使わない。
vector<int> color_matching(const vector<int> &c) {
    int n = c.size();
    vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        if (c[i] != -1) v.emplace_back(i);
    }
    sort(begin(v), end(v), [&](int i, int j) {
        if (c[i] != c[j]) return c[i] < c[j];
        return i < j;
    });
    int k = v.size(), d = (k + 1) / 2;
    vector<int> match(n, -1);
    for (int i = 0; i < k / 2; i++) {
        match[v[i]] = v[i + d];
        match[v[i + d]] = v[i];
    }
    if (k % 2 == 1) match[v[d - 1]] = v[d - 1];
    return match;
};

// c_{p_i} と c_i が異なるような i の個数が最大になるような順列 p を構成
// c_i = -1 のときは使わない。
vector<int> color_bijection(const vector<int> &c) {
    int n = c.size();
    vector<int> v;
    v.reserve(n);
    for (int i = 0; i < n; i++) {
        if (c[i] != -1) v.emplace_back(i);
    }
    sort(begin(v), end(v), [&](int i, int j) {
        if (c[i] != c[j]) return c[i] < c[j];
        return i < j;
    });
    int k = v.size(), d = k / 2;
    vector<int> p(n, -1);
    for (int i = 0, j = d; i < k; i++, j++) {
        if (j == k) j = 0;
        p[v[i]] = v[j];
    }
    return p;
};
