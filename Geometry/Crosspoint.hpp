
// 各図形の交点
// 計算量 O(1)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Intersect.hpp"
#include "../Geometry/Projection_Reflection.hpp"

vector<Point> crosspoint(const Line &l, const Line &m) {
    vector<Point> ret;
    if (!intersect(l, m)) return ret;
    Real A = det(l.b - l.a, m.b - m.a);
    Real B = det(l.b - l.a, l.b - m.a);
    if (eq(A, 0.0) && eq(B, 0.0)) {
        ret.push_back(m.a);
    } else {
        ret.push_back(m.a + (m.b - m.a) * B / A);
    }
    return ret;
}

vector<Point> crosspoint(const Segment &s, const Segment &t) { return crosspoint(Line(s), Line(t)); }

vector<Point> crosspoint(const Circle &c, const Line &l) {
    Point h = projection(l, c.p);
    Point e = (l.b - l.a) / abs(l.b - l.a);
    vector<Point> ret;
    if (!intersect(c, l)) return ret;
    if (eq(distance(l, c.p), c.r)) {
        ret.push_back(h);
    } else {
        Real base = sqrt(c.r * c.r - norm(h - c.p));
        ret.push_back(h + e * base), ret.push_back(h - e * base);
    }
    return ret;
}

vector<Point> crosspoint(const Circle &c1, const Circle &c2) {
    Real d = abs(c1.p - c2.p);
    Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
    vector<Point> ret;
    if (!intersect(c1, c2)) return ret;
    if (eq(a, 0.0)) {
        ret.push_back(Point(c1.p + rotate(Point(c1.r, 0.0), t)));
    } else {
        Point p1 = c1.p + rotate(Point(c1.r, 0.0), t + a);
        Point p2 = c1.p + rotate(Point(c1.r, 0.0), t - a);
        ret.push_back(p1), ret.push_back(p2);
    }
    return ret;
}
