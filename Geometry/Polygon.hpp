
// 多角形(面積、内外判定)
// 計算量 O(n)

// 概要
// 面積 : 多角形を複数の三角形に分割し、符号付き面積を計算する。
// 内外判定 : 半直線を引いて多角形の辺との交差回数の偶奇を調べる。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A&lang=ja
// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Real area(const vector<Point> &p) { //多角形の面積
    Real ret = 0.0;
    int n = p.size();
    for (int i = 0; i < n; i++) ret += det(p[i], p[(i + 1) % n]);
    return abs(ret * 0.5);
}

int in_polygon(const vector<Point> &p, const Point &q) { // IN:2, ON:1, OUT:0
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