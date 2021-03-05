
//トライ木
//計算量 文字列追加・検索：O(|S|)

//概要
//トライ木の各頂点は、次に各文字を使った際の行き先の情報を記録する。
//追加：文字列を前から見て、トライ木を根から降りていく。該当する頂点がなくなったら新しい頂点を作る。
//検索：文字列を前から見て、トライ木を根から降りていく。

//verified with
//https://atcoder.jp/contests/tenka1-2016-final/tasks/tenka1_2016_final_c

#include <bits/stdc++.h>
using namespace std;

template<int char_size, char base>
struct Trie{
    struct Node{
        vector<int> next, accept;
        int count; //子以下に追加された文字列の数

        Node() : next(char_size, -1), count(0) {}
    };

    vector<Node> nodes;

    Trie() {nodes.emplace_back();}

    int count() const {return nodes.front().count;}

    int size() const {return nodes.size();}

    void insert(const string &s, int id){ //sを追加
        int now = 0;
        for(int i = 0; i < (int)s.size(); i++){
            int &next = nodes[now].next[s[i]-base];
            if(next == -1){
                next = size(), nodes.emplace_back();
            }
            nodes[now].count++, now = next;
        }
        nodes[now].count++, nodes[now].accept.push_back(id);
    }

    void insert(const string &s) {insert(s, count());}

    bool search(const string &s, bool prefix = false) const{ //s(のprefix)を検索
        int now = 0;
        for(int i = 0; i < s.size(); i++){
            now = nodes[now].next[s[i]-base];
            if(now == -1) return false;
        }
        return (prefix)? true : !nodes[now].accept.empty();
    }
};

int main(){
    string S; int M; cin >> S >> M;
    int N = S.size();

    Trie<26, 'a'> trie;

    for(int i = 0; i < M; i++){
        string P; cin >> P;
        trie.insert(P);
    }

    vector<int> W(M);
    for(int i = 0; i < M; i++) cin >> W[i];

    vector<int> dp(N+1, 0);
    
    for(int i = 0; i < N; i++){
        int now = 0;
        for(int j = 0; j <= 200; j++){
            if(now == -1) break;
            for(auto &e: trie.nodes[now].accept){
                dp[i+j] = max(dp[i+j], dp[i]+W[e]);
            }
            if(i+j == N) break;
            now = trie.nodes[now].next[S[i+j]-'a'];
        }
        dp[i+1] = max(dp[i+1], dp[i]);
    }

    cout << dp[N] << '\n';
}
