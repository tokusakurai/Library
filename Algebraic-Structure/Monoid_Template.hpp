#pragma once

// モノイドテンプレート

#include <bits/stdc++.h>
using namespace std;

struct Data_1 {
    constexpr Data_1() {}
};

struct Monoid_1 {
    using V = Data_1;
    static V merge(V a, V b) { return a; }
    static const V id;
};

constexpr Monoid_1::V Monoid_1::id = Data_1();

struct Func_1 {
    constexpr Func_1() {}
};

struct Operator_1 {
    using V = Func_1;
    static V merge(V a, V b) { return a; }
    static const V id;
};

constexpr Operator_1::V Operator_1::id = Func_1();

struct Acted_Monoid_1 {
    using Monoid = Monoid_1;
    using Operator = Operator_1;
    using M = typename Monoid::V;
    using O = typename Operator::V;
    static M merge(M a, O b) { return a; }
};
