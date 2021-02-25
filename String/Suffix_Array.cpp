
//接尾辞配列、高さ配列
//計算量 接尾辞配列構築:O(|S|*log(|S|)), 二分探索:O(|T|*log(|S|))、 高さ配列構築:O(|S|)

//接尾辞配列(suffix array) : 文字列の全ての接尾辞を辞書順にソートしたものを記録する(実際には何字目からの接尾辞かを記録する)
//高さ配列(longest common prefix array) : 接尾辞配列の隣同士で接頭辞が何文字一致しているかを記録する

//verified with
//http://judge.u-aizu.ac.jp/onlinejudge/description.jsp?id=ALDS1_14_D&lang=ja
//https://atcoder.jp/contests/practice2/tasks/practice2_i
//https://judge.yosupo.jp/problem/suffixarray
//https://judge.yosupo.jp/problem/number_of_substrings

#include <bits/stdc++.h>
using namespace std;

struct Suffix_Array{
    vector<int> sa;
    const string s;
    const int n;

    Suffix_Array(const string &s) : s(s), n(s.size()){
        sa.resize(n);
        iota(begin(sa), end(sa), 0);
        sort(begin(sa), end(sa), [&](int a, int b){
            return s[a] == s[b] ? a > b : s[a] < s[b]; 
        });
        vector<int> rank(n), c(begin(s), end(s)), cnt(n);
        for(int len = 1; len < n; len <<= 1){
            for(int i = 0; i < n; i++){
                if(i == 0 || c[sa[i-1]] != c[sa[i]]) rank[sa[i]] = i;
                else{
                    if(sa[i-1]+len >= n || c[sa[i-1]+len/2] != c[sa[i]+len/2]) rank[sa[i]] = i;
                    else rank[sa[i]] = rank[sa[i-1]];
                }
            }
            iota(begin(cnt), end(cnt), 0);
            copy(begin(sa), end(sa), c.begin());
            for(int i = 0; i < n; i++){
                int j = c[i]-len;
                if(j >= 0) sa[cnt[rank[j]]++] = j;
            }
            swap(rank, c);
        }
    }

    int operator [] (int i) const {return sa[i];}

    int size() const {return n;}

    bool compare_substr(const string &t, int si = 0, int ti = 0) const{ //sのsi文字目以降とtのti文字目以降を比較
        int m = t.size();
        while(si < n && ti < m){
            if(s[si] != t[ti]) return s[si] < t[ti];
            si++, ti++;
        }
        return si == n && ti < m;
    }

    int lower_bound(const string &t) const{ //辞書順でt以降となるもので最初の接尾辞
        int l = -1, r = n;
        while(r-l > 1){
            int m = (l+r)/2;
            (compare_substr(t, sa[m]) ? l : r) = m;
        }
        return r;
    }

    int upper_bound(string t) const{
        t.back()++;
        return lower_bound(t);
    }
};

struct Longest_Common_Prefix_Array{
    vector<int> rank, lcp;
    const Suffix_Array sa;
    const int n;

    Longest_Common_Prefix_Array(const Suffix_Array &sa) : sa(sa), n(sa.size()){
        rank.resize(n), lcp.resize(n-1);
        for(int i = 0; i < n; i++) rank[sa[i]] = i;
        int h = 0;
        for(int i = 0; i < n; i++){
            if(rank[i]+1 < n){
                int j = sa[rank[i]+1];
                while(max(i, j)+h < n && sa.s[i+h] == sa.s[j+h]) h++;
                lcp[rank[i]] = h;
                if(h > 0) h--;
            }
        }
    }

    int operator [] (int i) const {return lcp[i];}
};

int main(){
    string S; cin >> S;

    Suffix_Array sa(S);
    Longest_Common_Prefix_Array lcp(sa);

    long long N = S.size(), ans = N*(N+1)/2;

    for(int i = 0; i < N-1; i++) ans -= lcp[i];
    cout << ans << '\n';
}
