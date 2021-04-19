
//点・直線(線分)・円に関する基本的な計算
//計算量 構築 : O(1)、内積・行列式・CCW : O(1)

//概要
//点 : 複素数平面としてcomplexで管理する。
//直線(線分) : 2点で管理する。
//円 : 中心と半径で管理する。
//CCW : 線分abに対するcの位置関係を求める。(詳しくはverify URL)

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=CGL_1_C&lang=ja

#pragma once
#include <bits/stdc++.h>
using namespace std;

int sgn(Real a) {return (a < -EPS)? -1 : (a > EPS)? 1 : 0;} //符号関数

bool eq(Real a, Real b) {return sgn(b - a) == 0;}

using Real = double;
using Point = complex<Real>;

const Real EPS = 1e-10; //ここは適宜調節する
const Real pi = acos(-1.0);

Point operator * (const Point &p, const Real &d){
    return Point(real(p) * d, imag(p) * d);
}

Point operator / (const Point &p, const Real &d){
    return p * (1 / d);
}

istream &operator >> (istream &is, Point &p){
    Real a, b;
    is >> a >> b;
    p = Point(a, b);
    return is;
}

ostream &operator << (ostream &os, Point &p){
    return os << real(p) << ' ' << imag(p);
}

bool compare_x(const Point &p, const Point &q){
    if(!eq(real(p), real(q))) return real(p) < real(q);
    return imag(p) < imag(q);
}

bool compare_y(const Point &p, const Point &q){
    if(!eq(imag(p), imag(q))) return imag(p) < imag(q);
    return real(p) < real(q);
}

Point rotate(const Point &p, const Real &t){
    return p * Point(cos(t), sin(t));
}

Real dot(const Point &p, const Point &q){
    return real(p) * real(q) + imag(p) * imag(q);
}

Real det(const Point &p, const Point &q){
    return real(p) * imag(q) - imag(p) * real(q);
}

int ccw(const Point &a, Point b, Point c){
    b = b - a, c = c - a;
    if(sgn(det(b, c)) == 1) return +1; //COUNTER_CLOCKWISE
    if(sgn(det(b, c)) == -1) return -1; //CLOCKWISE
    if(dot(b, c) < 0.0) return +2; //ONLINE_BACK
    if(norm(b) < norm(c)) return -2; //ONLINE_FRONT
    return 0; //ON_SEGMENT
}

struct Line{
    Point a, b;
    Line() {}
    Line (Point a, Point b) : a(a), b(b) {}

    friend ostream &operator << (ostream &os, Line &l){
        return os << l.a << ' ' << l.b;
    }

    friend istream &operator >> (istream &is, Line &l){
        return is >> l.a >> l.b;
    }
};

struct Segment : Line{
    Segment() {}
    Segment(Point a, Point b) : Line(a, b) {}
};

struct Circle{
    Point p;
    Real r;
    Circle() {}
    Circle(Point p, Real r) : p(p), r(r) {}
};
