#pragma once

// 幾何ライブラリ全体

#include <bits/stdc++.h>
using namespace std;

using Real = long double;
using Point = complex<Real>;

const Real EPS = 1e-10; // ここは適宜調節する
const Real pi = acos(-1.0);

int sgn(Real a) { return (a < -EPS) ? -1 : (a > EPS) ? 1 : 0; }

bool eq(Real a, Real b) { return sgn(b - a) == 0; }

Point operator*(const Point &p, const Real &d) { return Point(real(p) * d, imag(p) * d); }

Point operator/(const Point &p, const Real &d) { return p * (1 / d); }

istream &operator>>(istream &is, Point &p) {
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

ostream &operator<<(ostream &os, const Point &p) { return os << real(p) << ' ' << imag(p); }

bool compare_x(const Point &p, const Point &q) {
    if (!eq(real(p), real(q))) return real(p) < real(q);
    return imag(p) < imag(q);
}

bool compare_y(const Point &p, const Point &q) {
    if (!eq(imag(p), imag(q))) return imag(p) < imag(q);
    return real(p) < real(q);
}

struct Line {
    Point a, b;
    Line() {}
    Line(Point a, Point b) : a(a), b(b) {}

    friend ostream &operator<<(ostream &os, Line &l) { return os << l.a << ' ' << l.b; }

    friend istream &operator>>(istream &is, Line &l) { return is >> l.a >> l.b; }
};

struct Segment : Line {
    Segment() {}
    Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle {
    Point p;
    Real r;
    Circle() {}
    Circle(Point p, Real r) : p(p), r(r) {}
};

Point rotate(const Point &p, const Real &t) { return p * Point(cos(t), sin(t)); }

Real dot(const Point &p, const Point &q) { return real(p) * real(q) + imag(p) * imag(q); }

Real det(const Point &p, const Point &q) { return real(p) * imag(q) - imag(p) * real(q); }

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=ja
// 線分 ab に対する c の位置関係
int ccw(const Point &a, Point b, Point c) {
    b = b - a, c = c - a;
    if (sgn(det(b, c)) == 1) return +1;         // COUNTER_CLOCKWISE
    if (sgn(det(b, c)) == -1) return -1;        // CLOCKWISE
    if (sgn(dot(b, c)) == -1) return +2;        // ONLINE_BACK
    if (sgn(norm(c) - norm(b)) == 1) return -2; // ONLINE_FRONT
    return 0;                                   // ON_SEGMENT
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_A&lang=ja
// 平行判定
bool parallel(const Line &a, const Line &b) { return eq(det(a.b - a.a, b.b - b.a), 0.0); }

// 垂直判定
bool orthogonal(const Line &a, const Line &b) { return eq(dot(a.b - a.a, b.b - b.a), 0.0); }

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_A&lang=ja
// 垂線の足
Point projection(const Line &l, const Point &p) {
    Real t = dot(p - l.a, l.b - l.a) / norm(l.b - l.a);
    return l.a + (l.b - l.a) * t;
}

Point projection(const Segment &s, const Point &p) {
    Real t = dot(p - s.a, s.b - s.a) / norm(s.b - s.a);
    return s.a + (s.b - s.a) * t;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_B&lang=ja
// 線対称の位置にある点
Point reflection(const Line &l, const Point &p) { return p + (projection(l, p) - p) * 2.0; }

bool intersect(const Line &l, const Point &p) { return abs(ccw(l.a, l.b, p)) != 1; }

bool intersect(const Segment &s, const Point &p) { return ccw(s.a, s.b, p) == 0; }

bool intersect(const Line &l, const Line &m) {
    if (!eq(det(l.b - l.a, m.b - m.a), 0.0)) return true;
    return eq(det(l.b - l.a, m.b - l.a), 0.0);
}

bool intersect(const Line &l, const Segment &s) { return sgn(det(l.b - l.a, s.a - l.a) * det(l.b - l.a, s.b - l.a)) <= 0; }

bool intersect(const Segment &s, const Line &l) { return intersect(l, s); }

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_B&lang=ja
bool intersect(const Segment &s, const Segment &t) {
    if (ccw(s.a, s.b, t.a) * ccw(s.a, s.b, t.b) > 0) return false;
    return ccw(t.a, t.b, s.a) * ccw(t.a, t.b, s.b) <= 0;
}

Real distance(const Line &l, const Point &p);

bool intersect(const Circle &c, const Line &l) { return sgn(c.r - distance(l, c.p)) >= 0; }

bool intersect(const Circle &c, const Point &p) { return eq(abs(p - c.p), c.r); }

bool intersect(const Circle &c1, const Circle &c2) {
    Real d = abs(c1.p - c2.p);
    if (sgn(d - c1.r - c2.r) == 1) return false;
    if (sgn(d - abs(c1.r - c2.r)) == -1) return false;
    return true;
}

Real distance(const Point &p, const Point &q) { return abs(q - p); }

Real distance(const Line &l, const Point &p) { return abs(p - Point(projection(l, p))); }

// https://atcoder.jp/contests/arc042/tasks/arc042_b
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

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_D&lang=ja
Real distance(const Segment &s, const Segment &t) {
    if (intersect(s, t)) return 0.0;
    return min({distance(s, t.a), distance(s, t.b), distance(t, s.a), distance(t, s.b)});
}

vector<Point> crosspoint(const Line &l, const Line &m) {
    if (!intersect(l, m)) return {};
    if (parallel(l, m)) return {l.a, l.b};
    vector<Point> ret;
    Real A = det(l.b - l.a, m.b - m.a);
    Real B = det(l.b - l.a, l.b - m.a);
    if (eq(A, 0.0) && eq(B, 0.0)) {
        ret.push_back(m.a);
    } else {
        ret.push_back(m.a + (m.b - m.a) * B / A);
    }
    return ret;
}

// 平行な場合は共通する区間の端点を返す
vector<Point> crosspoint(const Line &l, const Segment &s) {
    if (!intersect(l, s)) return {};
    if (parallel(l, Line(s))) return {s.a, s.b};
    vector<Point> ret, tmp = crosspoint(Line(l), Line(s));
    for (auto &p : tmp) {
        if (ccw(s.a, s.b, p) == 0) ret.push_back(p);
    }
    return ret;
}

vector<Point> crosspoint(const Segment &s, const Line &l) { return crosspoint(l, s); }

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_2_C&lang=ja
vector<Point> crosspoint(const Segment &s, const Segment &t) {
    if (!intersect(s, t)) return {};
    vector<Point> ret, tmp;
    if (parallel(Line(s), Line(t))) {
        tmp = {s.a, s.b};
        if (sgn(distance(t.a, s.a)) == 1 && sgn(distance(t.a, s.b)) == 1) tmp.push_back(t.a);
        if (sgn(distance(t.b, s.a)) == 1 && sgn(distance(t.b, s.b)) == 1) tmp.push_back(t.b);
    } else {
        tmp = crosspoint(Line(s), Line(t));
    }
    for (auto &p : tmp) {
        if (ccw(s.a, s.b, p) == 0 && ccw(t.a, t.b, p) == 0) ret.push_back(p);
    }
    return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_D&lang=ja
vector<Point> crosspoint(const Circle &c, const Line &l) {
    Point h = projection(l, c.p);
    Point e = (l.b - l.a) / abs(l.b - l.a);
    vector<Point> ret;
    if (!intersect(c, l)) return ret;
    if (eq(distance(l, c.p), c.r)) {
        ret.push_back(h);
    } else {
        Real base = sqrt(c.r * c.r - norm(h - c.p));
        ret.push_back(h + e * base), ret.push_back(h - e * base);
    }
    return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_E&lang=ja
vector<Point> crosspoint(const Circle &c1, const Circle &c2) {
    Real d = abs(c1.p - c2.p);
    Real a = acos((c1.r * c1.r + d * d - c2.r * c2.r) / (2 * c1.r * d));
    Real t = atan2(c2.p.imag() - c1.p.imag(), c2.p.real() - c1.p.real());
    vector<Point> ret;
    if (!intersect(c1, c2)) return ret;
    if (eq(a, 0.0)) {
        ret.push_back(Point(c1.p + rotate(Point(c1.r, 0.0), t)));
    } else {
        Point p1 = c1.p + rotate(Point(c1.r, 0.0), t + a);
        Point p2 = c1.p + rotate(Point(c1.r, 0.0), t - a);
        ret.push_back(p1), ret.push_back(p2);
    }
    return ret;
}

// 垂直二等分線
Line vertical_bisector(const Point &p, const Point &q) {
    Line l;
    l.a = (p + q) * 0.5;
    l.b = l.a + rotate(q - p, pi * 0.5);
    return l;
}

// アポロニウスの円
Circle Apollonius(const Point &p, const Point &q, const Real &a, const Real &b) {
    Point p1 = (p * b + q * a) / (a + b), p2 = (-p * b + q * a) / (a - b);
    Circle c;
    c.p = (p1 + p2) * 0.5;
    c.r = abs(p1 - p2) * 0.5;
    return c;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_A&lang=ja
Real area(const vector<Point> &p) {
    Real ret = 0.0;
    int n = p.size();
    for (int i = 0; i < n; i++) ret += det(p[i], p[(i + 1) % n]);
    return abs(ret * 0.5);
}

// https://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_3_C&lang=ja
// IN:2, ON:1, OUT:0
// 反時計回り、O(n)
int in_polygon(const vector<Point> &p, const Point &q) {
    int n = p.size();
    int ret = 0;
    for (int i = 0; i < n; i++) {
        Point a = p[i] - q, b = p[(i + 1) % n] - q;
        if (eq(det(a, b), 0.0) && sgn(dot(a, b)) <= 0) return 1;
        if (imag(a) > imag(b)) swap(a, b);
        if (sgn(imag(a)) <= 0 && sgn(imag(b)) == 1 && sgn(det(a, b)) == 1) ret ^= 2;
    }
    return ret;
}

// https://atcoder.jp/contests/abc296/tasks/abc296_g
// 反時計回り、凸多角形、O(log(n))
int in_convex_polygon(const vector<Point> &p, const Point &q) {
    int n = p.size();
    assert(n >= 3);
    Real b1 = det(p[1] - p[0], q - p[0]);
    Real b2 = det(p[n - 1] - p[0], q - p[0]);
    if (sgn(b1) == -1 || sgn(b2) == 1) return 0;
    int l = 1, r = n - 1;
    while (r - l > 1) {
        int m = (l + r) / 2;
        (det(p[m] - p[0], q - p[0]) >= 0 ? l : r) = m;
    }
    Real v = det(p[l] - q, p[r] - q);
    return (sgn(v) == 0 ? 1 : sgn(v) == -1 ? 0 : sgn(b1) == 0 || sgn(b2) == 0 ? 1 : 2);
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_F&lang=ja
// 点 p を通る円 c の接線と c の接点
vector<Point> tangent(const Circle &c, const Point &p) { return crosspoint(c, Circle(p, sqrt(norm(p - c.p) - c.r * c.r))); }

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_G&lang=ja
// 共通接線
vector<Line> tangent(Circle c1, Circle c2) {
    vector<Line> ret;
    if (c1.r < c2.r) swap(c1, c2);
    Real r = abs(c2.p - c1.p);
    if (eq(r, 0.0)) return ret;
    Point u = (c2.p - c1.p) / r;
    Point v = rotate(u, pi * 0.5);
    for (Real s : {1.0, -1.0}) {
        Real h = (c1.r + c2.r * s) / r;
        if (eq(abs(h), 1.0)) {
            ret.emplace_back(c1.p + u * c1.r, c1.p + (u + v) * c1.r);
        } else if (abs(h) < 1.0) {
            Point uu = u * h, vv = v * sqrt(1.0 - h * h);
            ret.emplace_back(c1.p + (uu + vv) * c1.r, c2.p - (uu + vv) * c2.r * s);
            ret.emplace_back(c1.p + (uu - vv) * c1.r, c2.p - (uu - vv) * c2.r * s);
        }
    }
    return ret;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_7_A&lang=ja
// 共通接線の本数
int tangent_num(Circle c1, Circle c2) {
    if (c1.r < c2.r) swap(c1, c2);
    Real d = abs(c1.p - c2.p);
    int a = sgn(d - c1.r - c2.r);
    if (a >= 0) return 3 + a;
    return 1 + sgn(d - c1.r + c2.r);
}

// 下側凸包
vector<Point> lower_convex_hull(vector<Point> p) {
    sort(begin(p), end(p), compare_x);
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n == 1) return p;
    vector<Point> ch(n);
    for (int i = 0; i < n; i++) {
        if (k == 1 && eq(real(ch[0]), real(p[i]))) {
            if (imag(ch[0]) > imag(p[i])) ch[0] = p[i];
            continue;
        }
        while (k >= 2 && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= 0) k--;
        ch[k++] = p[i];
    }
    if (k >= 2 && eq(real(ch[k - 1]), real(ch[k - 2]))) k--;
    ch.resize(k);
    return ch;
}

// 上側凸包
vector<Point> upper_convex_hull(vector<Point> p) {
    sort(begin(p), end(p), compare_x);
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n == 1) return p;
    vector<Point> ch(n);
    for (int i = 0; i < n; i++) {
        if (k == 1 && eq(real(ch[0]), real(p[i]))) {
            if (imag(ch[0]) < imag(p[i])) ch[0] = p[i];
            continue;
        }
        while (k >= 2 && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) >= 0) k--;
        ch[k++] = p[i];
    }
    if (k >= 2 && eq(real(ch[k - 1]), real(ch[k - 2]))) k--;
    ch.resize(k);
    return ch;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_4_A&lang=ja
vector<Point> convex_hull(vector<Point> p) {
    sort(begin(p), end(p), compare_x);
    p.erase(unique(begin(p), end(p)), end(p));
    int n = p.size(), k = 0;
    if (n == 1) return p;
    vector<Point> ch(2 * n);
    for (int i = 0; i < n; ch[k++] = p[i++]) {
        while (k >= 2 && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= 0) k--;
    }
    for (int i = n - 2, t = k + 1; i >= 0; ch[k++] = p[i--]) {
        while (k >= t && sgn(det(ch[k - 1] - ch[k - 2], p[i] - ch[k - 1])) <= 0) k--;
    }
    ch.resize(k - 1);
    return ch;
}

// http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_5_A&lang=ja
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
