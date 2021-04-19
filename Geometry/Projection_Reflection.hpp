
//直線に対する垂線の足と線対称な点
//計算量 O(1)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A&lang=ja
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Point projection(const Line &l, const Point &p){
    Real t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
    return l.a + (l.b - l.a) * t;
}

Point projection(const Segment &s, const Point &p){
    Real t = dot(p - s.a, s.b - s.a) / norm(s.b - s.a);
    return s.a + (s.b - s.a) * t;
}

Point reflection(const Line &l, const Point &p){
    return p + (projection(l, p) - p) * 2.0;
}

Point reflection(const Segment &s, const Point &p){
    return p + (projection(s, p) - p) * 2.0;
}
