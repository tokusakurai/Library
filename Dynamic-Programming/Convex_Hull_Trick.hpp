
//Convex-Hull-Trick(追加する直線の傾きが、最小値クエリなら単調非増加、最大値クエリなら単調非減少のときのみ)
//計算量 直線追加 : O(1)、最小値(最大値)クエリ : O(log(N))、単調な最小値(最大値)クエリ : O(1)(ならし)

//概要
//直線を追加していく際、直線群の中で最も下になることがありえないようなものを除去していく。
//クエリが単調な場合、尺取りの要領で採用する直線を決めることができる。
//クエリが単調でない場合は二分探索を用いる。

//verified with
//https://atcoder.jp/contests/colopl2018-final/tasks/colopl2018_final_c

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T, bool ismin = true> //ismin : 最小値クエリかどうか
struct Convex_Hull_Trick{
    vector<T> a, b; //y = ax+b
    deque<int> que;

    Convex_Hull_Trick() {};

    bool empty() const {return que.empty();}

    T f(int i, const T &x) const {return a[i]*x+b[i];}

    bool judge(int i, int j, int k) const{
        return (b[k]-b[j])*(a[j]-a[i]) >= (b[j]-b[i])*(a[k]-a[j]);
    }

    void add_line(T p, T q){ //y = px+qを追加
        if(!ismin) p *= -1, q *= -1;
        assert(empty() || a.back() >= p);
        int k = a.size();
        a.push_back(p), b.push_back(q);
        if(!empty() && a[que.back()] == p){
            if(b[que.back()] <= q) return;
            que.pop_back();
        }
        while(que.size() >= 2 && judge(que[que.size()-2], que[que.size()-1], k)) que.pop_back();
        que.push_back(k);
    }

    T query(T x){
        assert(!empty());
        int l = 0, r = que.size();
        while(r-l > 1){
            int m = (l+r)/2;
            (f(que[m-1], x) >= f(que[m], x)? l : r) = m;
        }
        return ismin? f(que[l], x) : -f(que[l], x);
    }

    T query_monotone_inc(T x){
        assert(!empty());
        while(que.size() >= 2 && f(que[0], x) >= f(que[1], x)) que.pop_front();
        return ismin? f(que[0], x) : -f(que[0], x);
    }

    T query_monotone_dec(T x){
        assert(!empty());
        while(que.size() >= 2 && f(que[que.size()-1], x) >= f(que[que.size()-2], x)) que.pop_back();
        return ismin? f(que[que.size()-1], x) : -f(que[que.size()-1], x);
    }
};
