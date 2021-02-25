
//Aho-Corasick法(複数文字列についてパターンマッチするオートマトンを構築する)
//計算量 構築:O(Σ|S_i|)、遷移:O(1)

//verified with
//https://yukicoder.me/problems/no/430
//https://yukicoder.me/problems/no/1269
//https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_h

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

    void insert(const string &s, int id){
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

    bool search(const string &s, bool prefix = false) const{
        int now = 0;
        for(int i = 0; i < s.size(); i++){
            now = nodes[now].next[s[i]-base];
            if(now == -1) return false;
        }
        return (prefix)? true : !nodes[now].accept.empty();
    }
};

template<int char_size, char base>
struct Aho_Corasick : Trie<char_size+1, base>{
    const int FAIL = char_size;
    vector<int> correct; //接尾辞とマッチする文字列の種類数(最大でもO(√Σ|S_i|))

    void build(bool heavy = true){ //heavy := 接尾辞とマッチする文字列を全て持つかどうか
        correct.resize(this->size());
        for(int i = 0; i < (int)this->size(); i++){
            correct[i] = (this->nodes[i].accept).size();
        }
        queue<int> que;
        for(int i = 0; i <= char_size; i++){
            if(this->nodes[0].next[i] != -1){
                this->nodes[this->nodes[0].next[i]].next[FAIL] = 0;
                que.push(this->nodes[0].next[i]);
            }
            else{
                this->nodes[0].next[i] = 0;
            }
        }
        while(!que.empty()){
            auto &now = this->nodes[que.front()];
            int fail = now.next[FAIL];
            correct[que.front()] += correct[fail]; //全ての頂点についてのcorrectの和は最大でもO(Σ|S_i|)
            que.pop();
            for(int i = 0; i < char_size; i++){
                if(now.next[i] != -1){
                    this->nodes[now.next[i]].next[FAIL] = this->nodes[fail].next[i];
                    if(heavy){
                        auto &u = this->nodes[now.next[i]].accept;
                        auto &v = this->nodes[this->nodes[fail].next[i]].accept;
                        vector<int> accept;
                        set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
                        u = accept;
                    }
                    que.push(now.next[i]);
                }
                else{
                    now.next[i] = this->nodes[fail].next[i];
                }
            }
        }
    }

    map<int, int> match(int now, const string &s) const{ //nowからsに沿って進めたときのマッチしたパターンのidと回数の組
        map<int, int> ret;
        for(auto &c: s){
            now = this->nodes[now].next[c-base];
            for(auto &u: this->nodes[now].accept) ret[u]++;
        }
        return ret;
    }

    map<int, int> match(const string &s) const {return match(0, s);}

    pair<long long, int> move(int now, const char &c) const{ //nowからcの方向に進めたときのマッチしたパターン数と移動先のノードの組
        now = this->nodes[now].next[c-base];
        return make_pair(correct[now], now);
    }

    pair<long long, int> move(const char &c) const {return move(0, c);}

    pair<long long, int> move(int now, const string &s) const{
        long long sum = 0;
        for(auto &c: s){
            pair<long long, int> p = move(now, c);
            sum += p.first, now = p.second;
        }
        return make_pair(sum, now);
    }

    pair<long long, int> move(const string &s) const {return move(0, s);}
};

int main(){
    int N; cin >> N;

    Aho_Corasick<26, 'a'> trie;

    vector<string> S(N);

    for(int i = 0; i < N; i++){
        cin >> S[i];
        trie.insert(S[i]);
    }

    trie.build();

    string T; cin >> T;

    int ptr = 0, M = T.size();
    vector<int> dp(M+1, 0);
    dp[0] = 1;

    int MOD = 1000000007;

    for(int i = 0; i < M; i++){
        ptr = trie.move(ptr, T[i]).second;
        for(auto &e: trie.nodes[ptr].accept){
            dp[i+1] += dp[i+1-S[e].size()], dp[i+1] %= MOD;
        }
    }

    cout << dp[M] << '\n';
}
