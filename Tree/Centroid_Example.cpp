
//木の重心分解(例)
//計算量 1回の重心分解:O(V)、再帰の深さ:O(log(V))、全体の計算量:O(V*log(V))

//verified with
//https://atcoder.jp/contests/yahoo-procon2018-final-open/tasks/yahoo_procon2018_final_c

#include <bits/stdc++.h>
using namespace std;

template<bool directed = false>
struct Graph{
    struct edge{
        int to, id;
        edge(int to, int id) : to(to), id(id) {}
    };

    vector<vector<edge>> es;
    vector<int> si, depth;
    vector<bool> used;
    const int n;
    int m;

    vector<int> cnt;
    vector<int> memo1, memo2;
    vector<vector<pair<int, int>>> query;
    vector<int> ans;

    Graph(int n) : es(n), si(n), depth(n), used(n, false), n(n), m(0), cnt(n, 0), query(n) {}

    void add_edge(int from, int to){
        es[from].emplace_back(to, m);
        if(!directed) es[to].emplace_back(from, m);
        m++;
    }

    int calc_size(int now, int pre = -1){
        si[now] = 1;
        for(auto &e: es[now]){
            if(e.to == pre || used[e.to]) continue;
            depth[e.to] = depth[now]+1;
            si[now] += calc_size(e.to, now);
        }
        return si[now];
    }

    pair<int, int> search_centroid(int now, int sz, int pre = -1){ //(残りの最大部分木の頂点数、重心)
        pair<int, int> ret = make_pair(INT_MAX, -1);
        int M = 0, S = 1;
        for(auto &e: es[now]){
            if(e.to == pre || used[e.to]) continue;
            ret = min(ret, search_centroid(e.to, sz, now));
            M = max(M, si[e.to]);
            S += si[e.to];
        }
        M = max(M, sz-S);
        ret = min(ret, make_pair(M, now));
        return ret;
    }

    void solve(int i){
        for(auto &q: query[i]){
            if(q.first >= depth[i]) ans[q.second] += cnt[q.first-depth[i]];
        }
    }

    void dfs1(int now, int pre, bool rev){
        if(!rev){
            depth[now] = (pre == -1? 0 : depth[pre]+1);
            cnt[depth[now]]++, memo1.push_back(depth[now]);
        }
        else cnt[depth[now]]--, memo2.push_back(depth[now]);
        for(auto &e: es[now]){
            if(e.to == pre || used[e.to]) continue;
            dfs1(e.to, now, rev);
        }
    }

    void dfs2(int now, int pre){
        solve(now);
        for(auto &e: es[now]){
            if(e.to != pre && !used[e.to]) dfs2(e.to, now);
        }
    }

    void decompose(int root = 0){
        calc_size(root);
        int c = search_centroid(root, si[root]).second;

        dfs1(c, -1, false);
        solve(c);
        for(auto &e: es[c]){
            if(used[e.to]) continue;
            dfs1(e.to, c, true);
            dfs2(e.to, c);
            for(auto &e: memo2) cnt[e]++;
            memo2.clear();
        }
        for(auto &e: memo1) cnt[e]--;
        memo1.clear();

        used[c] = true;
        for(auto &e: es[c]){
            if(!used[e.to]) decompose(e.to);
        }
    }
};

int main(){
    int V, Q; cin >> V >> Q;

    Graph G(V);
    for(int i = 0; i < V-1; i++){
        int u, v; cin >> u >> v; u--, v--;
        G.add_edge(u, v);
    }

    G.ans.resize(Q);
    for(int i = 0; i < Q; i++){
        int x, k; cin >> x >> k; x--;
        G.query[x].emplace_back(k, i);
    }

    G.decompose();

    for(int i = 0; i < Q; i++) cout << G.ans[i] << '\n';
}
