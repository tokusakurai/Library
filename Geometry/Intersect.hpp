
// 各図形の交差判定
// 計算量 O(1)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B&lang=ja
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

bool intersect(const Line &l, const Point &p) { return abs(ccw(l.a, l.b, p)) != 1; }

bool intersect(const Segment &s, const Point &p) { return ccw(s.a, s.b, p) == 0; }

bool intersect(const Line &l, const Line &m) {
    if (!eq(det(l.b - l.a, m.b - m.a), 0.0)) return true;
    return eq(det(l.b - l.a, m.b - l.a), 0.0);
}

bool intersect(const Line &l, const Segment &s) { return sgn(det(l.b - l.a, s.a - l.a) * det(l.b - l.a, s.b - l.a)) <= 0; }

bool intersect(const Segment &s, const Line &l) { return intersect(l, s); }

bool intersect(const Segment &s, const Segment &t) {
    if (ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) > 0) return false;
    return ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

Real distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) { return sgn(c.r - distance(l, c.p)) >= 0; }

bool intersect(const Circle &c, const Point &p) { return eq(abs(p - c.p), c.r); }

int intersect(Circle c1, Circle c2) { // 共通接線の本数
    if (c1.r < c2.r) swap(c1, c2);
    Real d = abs(c1.p - c2.p);
    int a = sgn(d - c1.r - c2.r);
    if (a >= 0) return 3 + a;
    return 1 + sgn(d - c1.r + c2.r);
}
