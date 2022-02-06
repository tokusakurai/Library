
// 2 点からの距離の距離の比が等しくなるような点集合を表す図形
// 計算量 O(1)

// 概要
// 2 点から等距離の場合は垂直二等分線
// そうでないときはアポロニウスの円

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Line vertical_bisector(const Point &p, const Point &q) {
    Line l;
    l.a = (p + q) * 0.5;
    l.b = l.a + rotate(q - p, pi * 0.5);
    return l;
}

Circle Apollonius(const Point &p, const Point &q, const Real &a, const Real &b) {
    Point p1 = (p * b + q * a) / (a + b), p2 = (-p * b + q * a) / (a - b);
    Circle c;
    c.p = (p1 + p2) * 0.5;
    c.r = abs(p1 - p2) * 0.5;
    return c;
}
