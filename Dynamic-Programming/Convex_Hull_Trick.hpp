#pragma once

// Convex-Hull-Trick (追加する直線の傾きが、両方向について単調のときのみ)
// 計算量 直線追加：O(1)、最小値 (最大値) クエリ：O(log(n))、単調な最小値(最大値)クエリ：(ならし) O(1)

// 概要
// 直線を追加していく際、直線群の中で最も下になることがありえないようなものを除去していく。
// クエリが単調な場合、尺取りの要領で採用する直線を決めることができる。
// クエリが単調でない場合は二分探索を用いる。

// verified with
// https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c

#include <bits/stdc++.h>
using namespace std;

template <typename T, bool is_min = true>
struct Convex_Hull_Trick {
    struct Line {
        T a, b;

        Line(const T &a, const T &b) : a(a), b(b) {}

        T get(const T &x) { return a * x + b; }
    };

    deque<Line> ls;

    Convex_Hull_Trick(){};

    bool empty() const { return ls.empty(); }

    // (l1,l2,l3) の中で l2 を消してもいいか
    bool judge(const Line &l1, const Line &l2, const Line &l3) const {
        T a1 = l2.a - l1.a, b1 = l2.b - l1.b;
        T a2 = l3.a - l2.a, b2 = l3.b - l2.b;
        // return a2 * b1 <= a1 * b2;
        return __int128_t(a2) * b1 <= __int128_t(a1) * b2;
    }

    // 最小値クエリなら傾き単調増加、最大値クエリなら傾き単調減少
    void add_line_left(const Line &l) {
        assert(empty() || l.a >= ls.front().a);
        if (!empty() && l.a == ls.front().a) {
            if (l.b >= ls.front().b) return;
            ls.pop_front();
        }
        while (ls.size() >= 2) {
            Line l2 = ls.front(), l3 = ls[1];
            if (!judge(l, l2, l3)) break;
            ls.pop_front();
        }
        ls.push_front(l);
    }

    void add_line_left(const T &a, const T &b) { add_line_left(Line(is_min ? a : -a, is_min ? b : -b)); }

    // 最小値クエリなら傾き単調減少、最大値クエリなら傾き単調増加
    void add_line_right(const Line &l) {
        assert(empty() || ls.back().a >= l.a);
        if (!empty() && ls.back().a == l.a) {
            if (ls.back().b <= l.b) return;
            ls.pop_back();
        }
        while (ls.size() >= 2) {
            Line l1 = ls[ls.size() - 2], l2 = ls.back();
            if (!judge(l1, l2, l)) break;
            ls.pop_back();
        }
        ls.push_back(l);
    }

    void add_line_right(const T &a, const T &b) { add_line_right(Line(is_min ? a : -a, is_min ? b : -b)); }

    T query(const T &x) {
        assert(!empty());
        int l = 0, r = ls.size();
        while (r - l > 1) {
            int m = (l + r) / 2;
            (ls[m - 1].get(x) >= ls[m].get(x) ? l : r) = m;
        }
        T ret = ls[l].get(x);
        return is_min ? ret : -ret;
    }

    T query_monotone_inc(const T &x) {
        assert(!empty());
        while (ls.size() >= 2 && ls.front().get(x) >= ls[1].get(x)) ls.pop_front();
        T ret = ls.front().get(x);
        return is_min ? ret : -ret;
    }

    T query_monotone_dec(const T &x) {
        assert(!empty());
        while (ls.size() >= 2 && ls[ls.size() - 2].get(x) <= ls.back().get(x)) ls.pop_back();
        T ret = ls.back().get(x);
        return is_min ? ret : -ret;
    }
};
