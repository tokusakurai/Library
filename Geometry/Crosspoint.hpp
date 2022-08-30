
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
#include "../Geometry/Parallel_Orthogonal.hpp"
#include "../Geometry/Distance.hpp"

vector<Point> crosspoint(const Line &l, const Line &m) {
    if (!intersect(l, m)) return {};
    if (parallel(l, m)) return {l.a, l.b};
    vector<Point> ret;
    Real A = det(l.b - l.a, m.b - m.a);
    Real B = det(l.b - l.a, l.b - m.a);
    if (eq(A, 0.0) && eq(B, 0.0)) {
        ret.push_back(m.a);
    } else {
        ret.push_back(m.a + (m.b - m.a) * B / A);
    }
    return ret;
}

// 平行な場合は共通する区間の端点を返す
vector<Point> crosspoint(const Line &l, const Segment &s) {
    if (!intersect(l, s)) return {};
    if (parallel(l, Line(s))) return {s.a, s.b};
    vector<Point> ret, tmp = crosspoint(Line(l), Line(s));
    for (auto &p : tmp) {
        if (ccw(s.a, s.b, p) == 0) ret.push_back(p);
    }
    return ret;
}

vector<Point> crosspoint(const Segment &s, const Line &l) { return crosspoint(l, s); }

vector<Point> crosspoint(const Segment &s, const Segment &t) {
    if (!intersect(s, t)) return {};
    vector<Point> ret, tmp;
    if (parallel(Line(s), Line(t))) {
        tmp = {s.a, s.b};
        if (sgn(distance(t.a, s.a)) == 1 && sgn(distance(t.a, s.b)) == 1) tmp.push_back(t.a);
        if (sgn(distance(t.b, s.a)) == 1 && sgn(distance(t.b, s.b)) == 1) tmp.push_back(t.b);
    } else {
        tmp = crosspoint(Line(s), Line(t));
    }
    for (auto &p : tmp) {
        if (ccw(s.a, s.b, p) == 0 && ccw(t.a, t.b, p) == 0) ret.push_back(p);
    }
    return ret;
}

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
