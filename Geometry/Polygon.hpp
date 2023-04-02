
// 多角形 (面積、内外判定)
// 計算量 面積、多角形の内外判定：O(n)、凸多角形の内外判定：O(log(n))

// 概要
// 面積：多角形を複数の三角形に分割し、符号付き面積を計算する。
// 内外判定：半直線を引いて多角形の辺との交差回数の偶奇を調べる。
// 凸多角形の内外判定：多角形を n-2 個の三角形に分割し、そのどれに含まれるかを二分探索する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A&lang=ja
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C&lang=ja
// https://atcoder.jp/contests/abc296/tasks/abc296_g

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Real area(const vector<Point> &p) {
    Real ret = 0.0;
    int n = p.size();
    for (int i = 0; i < n; i++) ret += det(p[i], p[(i + 1) % n]);
    return abs(ret * 0.5);
}

// IN:2, ON:1, OUT:0
// 反時計回り、O(n)
int in_polygon(const vector<Point> &p, const Point &q) {
    int n = p.size();
    int ret = 0;
    for (int i = 0; i < n; i++) {
        Point a = p[i] - q, b = p[(i + 1) % n] - q;
        if (eq(det(a, b), 0.0) && sgn(dot(a, b)) <= 0) return 1;
        if (imag(a) > imag(b)) swap(a, b);
        if (sgn(imag(a)) <= 0 && sgn(imag(b)) == 1 && sgn(det(a, b)) == 1) ret ^= 2;
    }
    return ret;
}

// IN:2, ON:1, OUT:0
// 反時計回り、凸多角形、O(log(n))
int in_convex_polygon(const vector<Point> &p, const Point &q) {
    int n = p.size();
    assert(n >= 3);
    Real b1 = det(p[1] - p[0], q - p[0]);
    Real b2 = det(p[n - 1] - p[0], q - p[0]);
    if (sgn(b1) == -1 || sgn(b2) == 1) return 0;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        (det(p[m] - p[0], q - p[0]) >= 0 ? l : r) = m;
    }
    Real v = det(p[l] - q, p[r] - q);
    return (sgn(v) == 0 ? 1 : sgn(v) == -1 ? 0 : sgn(b1) == 0 || sgn(b2) == 0 ? 1 : 2);
}
