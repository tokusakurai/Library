#pragma once

// 各図形の距離
// 計算量 O(1)

// verified with
// https://atcoder.jp/contests/arc042/tasks/arc042_b
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D&lang=ja

#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Intersect.hpp"
#include "../Geometry/Projection_Reflection.hpp"

Real distance(const Point &p, const Point &q) { return abs(q - p); }

Real distance(const Line &l, const Point &p) { return abs(p - Point(projection(l, p))); }

Real distance(const Segment &s, const Point &p) {
    Point h = projection(s, p);
    if (intersect(s, h)) return abs(h - p);
    return min(abs(s.a - p), abs(s.b - p));
}

Real distance(const Line &l, const Line &m) { return intersect(l, m) ? 0.0 : distance(l, m.a); }

Real distance(const Line &l, const Segment &s) {
    if (intersect(l, s)) return 0.0;
    return min(distance(l, s.a), distance(l, s.b));
}

Real distance(const Segment &s, const Line &l) { return distance(l, s); }

Real distance(const Segment &s, const Segment &t) {
    if (intersect(s, t)) return 0.0;
    return min({distance(s, t.a), distance(s, t.b), distance(t, s.a), distance(t, s.b)});
}
