
// 最近点対
// 計算量 O(N*log(N))

// 概要
// 平面を分割統治する。

// verified with
// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Geometry/Structure.hpp"

Real closest_pair(vector<Point> p) {
    if (p.size() <= 1) return 1e18;
    sort(begin(p), end(p), compare_x);
    vector<Point> memo(p.size());

    function<Real(int, int)> rec = [&](int l, int r) {
        if (r - l <= 1) return Real(1e18);
        int m = (l + r) >> 1;
        Real x = real(p[m]);
        Real ret = min(rec(l, m), rec(m, r));
        inplace_merge(p.begin() + l, p.begin() + m, p.begin() + r, compare_y);
        int cnt = 0;
        for (int i = l; i < r; i++) {
            if (abs(real(p[i]) - x) >= ret) continue;
            for (int j = 0; j < cnt; j++) {
                Point d = p[i] - memo[cnt - j - 1];
                if (imag(d) >= ret) break;
                ret = min(ret, abs(d));
            }
            memo[cnt++] = p[i];
        }
        return ret;
    };

    return rec(0, p.size());
}
