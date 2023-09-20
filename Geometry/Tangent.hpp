
// 円と点・円の接線
// 計算量 O(1)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Crosspoint.hpp"

// 点 p を通る円 c の接線と c の接点
vector<Point> tangent(const Circle &c, const Point &p) { return crosspoint(c, Circle(p, sqrt(norm(p - c.p) - c.r * c.r))); }

// 共通接線
vector<Line> tangent(Circle c1, Circle c2) {
    vector<Line> ret;
    if (c1.r < c2.r) swap(c1, c2);
    Real r = abs(c2.p - c1.p);
    if (eq(r, 0.0)) return ret;
    Point u = (c2.p - c1.p) / r;
    Point v = rotate(u, pi * 0.5);
    for (Real s : {1.0, -1.0}) {
        Real h = (c1.r + c2.r * s) / r;
        if (eq(abs(h), 1.0)) {
            ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
        } else if (abs(h) < 1.0) {
            Point uu = u * h, vv = v * sqrt(1.0 - h * h);
            ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
            ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
        }
    }
    return ret;
}

// 共通接線の本数
int tangent_num(Circle c1, Circle c2) {
    if (c1.r < c2.r) swap(c1, c2);
    Real d = abs(c1.p - c2.p);
    int a = sgn(d - c1.r - c2.r);
    if (a >= 0) return 3 + a;
    return 1 + sgn(d - c1.r + c2.r);
}
