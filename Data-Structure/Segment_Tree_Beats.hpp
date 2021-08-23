
//Segment Tree Beats
//計算量 : 区間chmin・chmax : (ならし)O(log(N)^2)、区間add・update・min・max・sum : O(log(N))

//概要
//セグメント木の各ノードについて
//区間の最小値、厳密な2番目の最小値、最小値の個数、最大値、厳密な2番目の最大値、最大値の個数、和の情報を持っておく。
//add・update・min・max・sumクエリは遅延セグメント木と同様にしてできる。
//chmin・chmaxは1番目と2番目の間のときだけ更新(1番目だけ全て置き換える)し、そうでなければ下に流す。
//1回の操作で最悪O(N)個のノードを探索することになるが、計算量はならしでO(log(N)^2)となる。

//verified with
//https://judge.yosupo.jp/problem/range_chmin_chmax_add_range_sum

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Segment_Tree_Beats{
    vector<T> max_1, max_2, min_1, min_2;
    vector<int> max_cnt, min_cnt;
    vector<T> sum, add, upd; //addとupdはそれぞれ加算・更新の遅延配列
    vector<int> L, R;
    const T INF_T;
    int n;

    Segment_Tree_Beats(const vector<T> &v) : INF_T(numeric_limits<T>::max()/2) {
        int m = v.size();
        n = 1;
        while(n < m) n <<= 1;
        max_1.assign(2*n, -INF_T), max_2.assign(2*n, -INF_T), max_cnt.assign(2*n, 0);
        min_1.assign(2*n, INF_T), min_2.assign(2*n, INF_T), min_cnt.assign(2*n, 0);
        sum.assign(2*n, 0), add.assign(2*n, 0), upd.assign(2*n, INF_T);
        L.assign(2*n, 0), R.assign(2*n, n);
        for(int i = 1; i < n; i++){
            L[2*i] = L[i], R[2*i] = (L[i]+R[i])/2;
            L[2*i+1] = (L[i]+R[i])/2, R[2*i+1] = R[i];
        }
        for(int i = 0; i < m; i++) init_node(i, v[i]);
        for(int i = n-1; i > 0; i--) pull(i);
    }

    void init_node(int i, T x){
        i += n;
        max_1[i] = x, max_cnt[i] = 1;
        min_1[i] = x, min_cnt[i] = 1;
        sum[i] = x;
    }

    void node_chmin(int i, const T &x){ //max_1[i] > x > max_2[i]のときのchmin
        sum[i] += (x-max_1[i])*max_cnt[i];
        if(min_1[i] == max_1[i]) min_1[i] = x;
        if(min_2[i] == max_1[i]) min_2[i] = x;
        max_1[i] = x;
        if(upd[i] != INF_T && x < upd[i]) upd[i] = x;
    }

    void node_chmax(int i, const T &x){ //min_1[i] < x < min_2[i]のときのchmax
        sum[i] += (x-min_1[i])*min_cnt[i];
        if(max_1[i] == min_1[i]) max_1[i] = x;
        if(max_2[i] == min_1[i]) max_2[i] = x;
        min_1[i] = x;
        if(upd[i] != INF_T && x > upd[i]) upd[i] = x;
    }

    void node_add(int i, const T &x){ //全体にadd
        if(max_1[i] != -INF_T) max_1[i] += x;
        if(max_2[i] != -INF_T) max_2[i] += x;
        if(min_1[i] != INF_T) min_1[i] += x;
        if(min_2[i] != INF_T) min_2[i] += x;
        sum[i] += x*(R[i]-L[i]);
        if(upd[i] != INF_T) upd[i] += x;
        add[i] += x;
    }

    void node_update(int i, const T &x){ //全体にupdate
        max_1[i] = x, max_2[i] = -INF_T, max_cnt[i] = R[i]-L[i];
        min_1[i] = x, min_2[i] = INF_T, min_cnt[i] = R[i]-L[i];
        upd[i] = x, add[i] = 0;
    }

    void push(int i){ //iから遅延評価を子に流す
        if(upd[i] != INF_T){
            node_update(2*i, upd[i]);
            node_update(2*i+1, upd[i]);
            upd[i] = INF_T;
            return;
        }
        if(add[i] != 0){
            node_add(2*i, add[i]);
            node_add(2*i+1, add[i]);
            add[i] = 0;
        }
        if(max_1[i] < max_1[2*i]) node_chmin(2*i, max_1[i]);
        if(min_1[i] > min_1[2*i]) node_chmax(2*i, min_1[i]);
        if(max_1[i] < max_1[2*i+1]) node_chmin(2*i+1, max_1[i]);
        if(min_1[i] > min_1[2*i+1]) node_chmax(2*i+1, min_1[i]);
    }

    void pull(int i){ //子の状態からiの状態を復元する
        int l = 2*i, r = 2*i+1;
        sum[i] = sum[l]+sum[r];
        if(max_1[l] > max_1[r]){
            max_1[i] = max_1[l], max_2[i] = max(max_2[l], max_1[r]);
            max_cnt[i] = max_cnt[l];
        }
        else if(max_1[l] < max_1[r]){
            max_1[i] = max_1[r], max_2[i] = max(max_1[l], max_2[r]);
            max_cnt[i] = max_cnt[r];
        }
        else{
            max_1[i] = max_1[l], max_2[i] = max(max_2[l], max_2[r]);
            max_cnt[i] = max_cnt[l]+max_cnt[r];
        }
        if(min_1[l] < min_1[r]){
            min_1[i] = min_1[l], min_2[i] = min(min_2[l], min_1[r]);
            min_cnt[i] = min_cnt[l];
        }
        else if(min_1[l] > min_1[r]){
            min_1[i] = min_1[r], min_2[i] = min(min_1[l], min_2[r]);
            min_cnt[i] = min_cnt[r];
        }
        else{
            min_1[i] = min_1[l], min_2[i] = min(min_2[l], min_2[r]);
            min_cnt[i] = min_cnt[l]+min_cnt[r];
        }
    }

    void range_chmin(int l, int r, const T &x, int i = 1){
        if(r <= L[i] || R[i] <= l || max_1[i] <= x) return;
        if(l <= L[i] && R[i] <= r && max_2[i] < x) node_chmin(i, x);
        else{
            push(i);
            range_chmin(l, r, x, 2*i);
            range_chmin(l, r, x, 2*i+1);
            pull(i);
        }
    }

    void range_chmax(int l, int r, const T &x, int i = 1){
        if(r <= L[i] || R[i] <= l || min_1[i] >= x) return;
        if(l <= L[i] && R[i] <= r && min_2[i] > x) node_chmax(i, x);
        else{
            push(i);
            range_chmax(l, r, x, 2*i);
            range_chmax(l, r, x, 2*i+1);
            pull(i);
        }
    }

    void range_add(int l, int r, const T &x, int i = 1){
        if(r <= L[i] || R[i] <= l) return;
        if(l <= L[i] && R[i] <= r) node_add(i, x);
        else{
            push(i);
            range_add(l, r, x, 2*i);
            range_add(l, r, x, 2*i+1);
            pull(i);
        }
    }

    void range_update(int l, int r, const T &x, int i = 1){
        if(r <= L[i] || R[i] <= l) return;
        if(l <= L[i] && R[i] <= r) node_update(i, x);
        else{
            push(i);
            range_update(l, r, x, 2*i);
            range_update(l, r, x, 2*i+1);
            pull(i);
        }
    }

    T range_min(int l, int r, int i = 1){
        if(r <= L[i] || R[i] <= l) return INF_T;
        if(l <= L[i] && R[i] <= r) return min_1[i];
        push(i);
        return min(range_min(l, r, 2*i), range_min(l, r, 2*i+1));
    }

    T range_max(int l, int r, int i = 1){
        if(r <= L[i] || R[i] <= l) return -INF_T;
        if(l <= L[i] && R[i] <= r) return max_1[i];
        push(i);
        return max(range_max(l, r, 2*i), range_max(l, r, 2*i+1));
    }

    T range_sum(int l, int r, int i = 1){
        if(r <= L[i] || R[i] <= l) return 0;
        if(l <= L[i] && R[i] <= r) return sum[i];
        push(i);
        return range_sum(l, r, 2*i)+range_sum(l, r, 2*i+1);
    }
};
