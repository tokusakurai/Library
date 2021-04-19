
//多角形の面積
//計算量 O(1)

//概要
//多角形を複数の三角形に分割し、符号付き面積を計算する。

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Real area(const vector<Point> &p){ //多角形の面積
    Real ret = 0.0;
    int n = p.size();
    for(int i = 0; i < n; i++) ret += det(p[i], p[(i+1)%n]);
    return abs(ret * 0.5);
}
