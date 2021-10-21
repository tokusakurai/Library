
// 凸包
// 計算量 O(n log(n))

// 概要
// 上側凸包と下側凸包を求めてつなげる。
// 座標の幅がmであり、格子点のみであるとすると、凸包の個数はO(m^(2/3))個。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

vector<Point> convex_hull(vector<Point> p) {
    int n = p.size(), k = 0;
    sort(begin(p), end(p), compare_x);
    vector<Point> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS) k--;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1]) < EPS) k--;
    }
    ch.resize(k - 1);
    return ch;
}
