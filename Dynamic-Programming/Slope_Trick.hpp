#pragma once

// Slope-Trick
// 計算量 構築：O(1)、定数加算：O(1)、片側一次関数加算：O(log(n))、
// 累積 min：(ならし) O(log(n))、スライド min：O(1)、最小値取得：O(1)、ある1点での値取得：O(n log(n))

// 概要
// 傾きが (存在すれば) 常に整数となる凸関数 (区分線形凸関数と呼ぶ) を考える。 (これを f(x) とする。)
// 傾きが変化する頂点の情報を持つことによって状態を管理する。
// ここで、傾きが 0 の線分を境として、左側と右側に分けて頂点を管理することで最小値や片側一次関数加算を効率的に扱える。

#include <bits/stdc++.h>
using namespace std;

template <typename T>
struct Slope_Trick {
    priority_queue<T> l;
    priority_queue<T, vector<T>, greater<T>> r;
    const T INF_T = numeric_limits<T>::max() / 2;
    T add_l, add_r;
    T min_f = 0;

    // f(x) = 0 で初期化
    Slope_Trick() : add_l(0), add_r(0) {
        l.push(-INF_T);
        r.push(INF_T);
    }

    T get_min() const { return min_f; };

    void add_constant(const T &c) { min_f += c; };

    // f(x) += max(-x+a, 0)
    void add_line_left(const T &a) {
        if (a > r.top() + add_r) {
            min_f += -(r.top() + add_r) + a;
            l.push(r.top() + add_r - add_l);
            r.pop();
            r.push(a - add_r);
        } else {
            l.push(a - add_l);
        }
    }

    // f(x) += max(x-a, 0)
    void add_line_right(const T &a) {
        if (a < l.top() + add_l) {
            min_f += (l.top() + add_l) - a;
            r.push(l.top() + add_l - add_r);
            l.pop();
            l.push(a - add_l);
        } else {
            r.push(a - add_r);
        }
    }

    // f(x) += |x-a|
    void add_abs(const T &a) {
        add_line_left(a);
        add_line_right(a);
    }

    // f(x) <- min{f(y) | y <= x}
    void left_min() {
        while ((int)r.size() > 1) r.pop();
    }

    // f(x) <- min{f(y) | y >= x}
    void right_min() {
        while ((int)l.size() > 1) l.pop();
    }

    // f(x) <- min{f(y) | x-b <= y <= x-a}
    void slide_min(const T &a, const T &b) {
        assert(a <= b);
        add_l += a;
        add_r += b;
    }

    // f(x) <- f(x-a)
    void shift(const T &a) {
        add_l += a;
        add_r += a;
    }

    // f(x) を入手 (ただし、l と r は破壊される)
    T get(const T &x) {
        T ret = min_f;
        while (!l.empty()) {
            ret += max(T(0), -x + (l.top() + add_l));
            l.pop();
        }
        while (!r.empty()) {
            ret += max(T(0), x - (r.top() + add_r));
            r.pop();
        }
        return ret;
    }
};
