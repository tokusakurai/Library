
//グリッド上のBFS
//計算量 O(H*W)

//概要
//BFSをグリッド(上下左右に1マスずつ動ける)上で行う。

//verified with
//https://atcoder.jp/contests/abc007/tasks/abc007_3

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<typename T>
struct Grid{
    const vector<T> S;
    vector<vector<int>> d;
    const int H, W;

    Grid(const vector<T> &S) : S(S), H(S.size()), W(S.front().size()){
        d.resize(H);
        for(int i = 0; i < H; i++) d[i].resize(W);
    }

    bool in(int x, int y){
        return (0 <= x && x < H && 0 <= y && y < W);
    }

    int bfs(int sx, int sy, int tx = 0, int ty = 0){
        for(int i = 0; i < H; i++) fill(begin(d[i]), end(d[i]), INT_MAX/2);
        queue<pair<int, int>> que;
        d[sx][sy] = 0, que.emplace(sx, sy);
        vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
        while(!que.empty()){
            auto [x, y] = que.front(); que.pop();
            for(int k = 0; k < 4; k++){
                int nx = x+dx[k], ny = y+dy[k];
                if(!in(nx, ny) || S[nx][ny] == '#') continue;
                if(d[x][y]+1 < d[nx][ny]){
                    d[nx][ny] = d[x][y]+1, que.emplace(nx, ny);
                }
            }
        }
        return d[tx][ty];
    }
};
