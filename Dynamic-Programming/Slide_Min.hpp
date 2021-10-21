
// 配列のスライド最小値
// 計算量 O(n)

// 概要
// dequeに入っているindexは、前のものほどそのindexに対応する配列の値が小さい。
// dequeの先頭に残ったものが区間の最小値のindex。

#pragma once
#include <bits/stdc++.h>
using namespace std;

template <typename T>
vector<T> slide_min(vector<T> v, int k) { // 各iについてmin{v[i],v[i+1],...,v[i+k-1]}を記録した配列を返す
    deque<int> que;
    vector<T> ret;
    for (int i = 0; i < (int)v.size(); i++) {
        while (!que.empty() && v[que.back()] >= v[i]) que.pop_back();
        que.push_back(i);
        if (i - k + 1 >= 0) {
            ret.push_back(v[que.front()]);
            if (que.front() == i - k + 1) que.pop_front();
        }
    }
    return ret;
}
