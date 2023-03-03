
// run 列挙
// 計算量 O(|S|log(|S|))

// 概要
// 文字列 S の run とは、2 以上の周期を持つ S の極大な連続部分文字列
// 分割統治と z-algorithm で列挙することができる。
// run の個数は O(|S|) 個になることが保証される。

// verified with
// https://judge.yosupo.jp/problem/runenumerate

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../String/Z_Algorithm.hpp"

template <typename T>
vector<tuple<int, int, int>> run_enumerate(const T &s) {
    int n = s.size();
    vector<tuple<int, int, int>> runs;

    auto enumerate = [&](int l, int m, int r, bool rev) {
        int len = r - l, mid = m - l;
        T t(begin(s) + l, begin(s) + r);
        if (rev) {
            reverse(begin(t), end(t));
            mid = len - mid;
            m = l + mid;
        }
        T tl(begin(t), begin(t) + mid);
        reverse(begin(tl), end(tl));
        T tr(begin(t) + mid, end(t));
        copy(begin(t), end(t), back_inserter(tr));
        vector<int> zl = z_algorithm(tl), zr = z_algorithm(tr);
        zl.push_back(0);
        for (int k = 1; k <= mid; k++) {
            int left = m - k - zl[k];
            int right = min(m + zr[len - k], r);
            if (rev) {
                swap(left, right);
                left = l + r - left;
                right = l + r - right;
            }
            if (right - left < 2 * k) continue;
            if (left > 0 && s[left - 1] == s[left + k - 1]) continue;
            if (right < n && s[right] == s[right - k]) continue;
            runs.emplace_back(left, right, k);
        }
    };

    auto rec = [&](int l, int r, auto &&rec) -> void {
        if (r - l <= 1) return;
        int m = (l + r) / 2;
        rec(l, m, rec), rec(m, r, rec);
        enumerate(l, m, r, false);
        enumerate(l, m, r, true);
    };

    rec(0, n, rec);
    sort(begin(runs), end(runs));
    vector<tuple<int, int, int>> ret;
    for (auto [l, r, t] : runs) {
        if (!ret.empty() && get<1>(ret.back()) == l && get<2>(ret.back()) == r) continue;
        ret.emplace_back(t, l, r);
    }
    sort(begin(ret), end(ret));
    return ret;
}
