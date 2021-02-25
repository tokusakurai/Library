
//01-BFS(辺のコストが0か1のグラフにおける単一始点最短路)
//計算量 O(E+V)

//verified with
//https://atcoder.jp/contests/arc005/tasks/arc005_3

#include <bits/stdc++.h>
using namespace std;

template<typename T, bool directed = false>
struct Weighted_Graph{
    struct edge{
        int to; T cost; int id;
        edge(int to, T cost, int id) : to(to), cost(cost), id(id) {}
    };

    vector<vector<edge>> es;
    vector<T> d;
    const T INF_T;
    const int n;
    int m;

    Weighted_Graph(int n) : es(n), d(n), INF_T(numeric_limits<T>::max()/2), n(n), m(0) {}

    void add_edge(int from, int to, T cost){
        es[from].emplace_back(to, cost, m);
        if(!directed) es[to].emplace_back(from, cost, m);
        m++;
    }

    T bfs(int s, int t = 0){
        fill(begin(d), end(d), INF_T);
        deque<int> que;
        d[s] = 0, que.push_front(s);
        while(!que.empty()){
            int i = que.front(); que.pop_front();
            for(auto &e: es[i]){
                if(d[i]+e.cost < d[e.to]){
                    d[e.to] = d[i]+e.cost;
                    if(e.cost == 0) que.push_front(e.to);
                    else que.push_back(e.to);
                }
            }
        }
        return d[t];
    }
};

int main(){
    int H, W; cin >> H >> W;

    vector<string> S(H);
    for(int i = 0; i < H; i++) cin >> S[i];

    vector<int> dx = {1, 0, -1, 0}, dy = {0, 1, 0, -1};
    Weighted_Graph<int, true> G(H*W);

    int s = 0, t = 0;

    for(int i = 0; i < H; i++){
        for(int j = 0; j < W; j++){
            if(S[i][j] == 's') s = W*i+j;
            if(S[i][j] == 'g') t = W*i+j;
            for(int k = 0; k < 4; k++){
                int ni = i+dx[k], nj = j+dy[k];
                if(ni < 0 || ni >= H || nj < 0 || nj >= W) continue;
                G.add_edge(W*i+j, W*ni+nj, (S[ni][nj] == '#'? 1 : 0));
            }
        }
    }

    cout << (G.bfs(s, t) <= 2? "YES\n" : "NO\n");
}
