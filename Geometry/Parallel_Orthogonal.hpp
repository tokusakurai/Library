
// 2直線の平行・垂直判定
// 計算量 O(1)

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

bool parallel(const Line &a, const Line &b) { return eq(det(a.b - a.a, b.b - b.a), 0.0); }

bool orthogonal(const Line &a, const Line &b) { return eq(dot(a.b - a.a, b.b - b.a), 0.0); }
