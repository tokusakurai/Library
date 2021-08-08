
//2-SAT(リテラル数が2のクロージャーの乗法標準形の充足可能性を判定する)
//計算量 O(N)

//概要
//(x ∨ y) ⇔ (¬x ⇒ y) ∧ (¬y ⇒ x)
//であるから、各論理変数xについてxと¬xの状態を用意して、x ⇒ yのときにxからyへの有向辺を貼ったグラフを考えると
//各xについてxと¬xが同じ強連結成分に含まれなければ充足可能。
//xと¬xでトポロジカル順序が大きい方を採用すれば解の1つを構築できる。

//verified with
//https://judge.yosupo.jp/problem/two_sat

#pragma once
#include <bits/stdc++.h>
using namespace std;

#include "../Graph/SCC.hpp"

struct Two_SAT{
    Strongly_Connected_Components<true> G;
    const int n;

    Two_SAT(int n) : n(n), G(2*n) {}

    void add_clause(int x, int y){ //¬xは頂点n+xに対応している
        G.add_edge((x+n)%(2*n), y);
        G.add_edge((y+n)%(2*n), x);
    }

    vector<bool> solve(){
        G.decompose();
        vector<bool> ret(n);
        for(int i = 0; i < n; i++){
            if(G.comp[i] == G.comp[n+i]) return {};
            ret[i] = (G.comp[i] > G.comp[n+i]);
        }
        return ret;
    }
};
