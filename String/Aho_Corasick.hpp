#pragma once

// Aho-Corasick 法 (複数文字列についてパターンマッチするオートマトンを構築する)
// 計算量 構築 : O(Σ[i]|S_i|)、遷移 : O(1)

// 概要
// 既に構築されているトライ木に情報を加える。
// トライ木では葉が存在したが、葉から出る後退辺を構築することによって遷移を繰り返すことができる。
// 1 文字加えた際の suffix で該当する頂点があり、最も長いものに該当する頂点に移動する。

// verified with
// https://yukicoder.me/problems/no/430
// https://yukicoder.me/problems/no/1269
// https://atcoder.jp/contests/jag2017autumn/tasks/jag2017autumn_h

#include <bits/stdc++.h>
using namespace std;

#include "../String/Trie.hpp"

template <int char_size, char base>
struct Aho_Corasick : Trie<char_size + 1, base> {
    const int FAIL = char_size;
    vector<int> correct; // 接尾辞とマッチする文字列の種類数 (最大でも O(√Σ|S_i|))

    // heavy : 接尾辞とマッチする文字列を全て持つかどうか
    void build(bool heavy = true) {
        correct.resize(this->size());
        for (int i = 0; i < (int)this->size(); i++) { correct[i] = (this->nodes[i].accept).size(); }
        queue<int> que;
        for (int i = 0; i <= char_size; i++) {
            if (this->nodes[0].next[i] != -1) {
                this->nodes[this->nodes[0].next[i]].next[FAIL] = 0;
                que.push(this->nodes[0].next[i]);
            } else {
                this->nodes[0].next[i] = 0;
            }
        }
        while (!que.empty()) {
            auto &now = this->nodes[que.front()];
            int fail = now.next[FAIL];
            correct[que.front()] += correct[fail]; // 全ての頂点についての correct の和は最大でも O(Σ|S_i|)
            que.pop();
            for (int i = 0; i < char_size; i++) {
                if (now.next[i] != -1) {
                    this->nodes[now.next[i]].next[FAIL] = this->nodes[fail].next[i];
                    if (heavy) {
                        auto &u = this->nodes[now.next[i]].accept;
                        auto &v = this->nodes[this->nodes[fail].next[i]].accept;
                        vector<int> accept;
                        set_union(begin(u), end(u), begin(v), end(v), back_inserter(accept));
                        u = accept;
                    }
                    que.push(now.next[i]);
                } else {
                    now.next[i] = this->nodes[fail].next[i];
                }
            }
        }
    }

    // now から s に沿って進めたときのマッチしたパターンの id と回数の組
    map<int, int> match(int now, const string &s) const {
        map<int, int> ret;
        for (auto &c : s) {
            now = this->nodes[now].next[c - base];
            for (auto &u : this->nodes[now].accept) ret[u]++;
        }
        return ret;
    }

    map<int, int> match(const string &s) const { return match(0, s); }

    // now から c の方向に進めたときのマッチしたパターン数と移動先のノードの組
    pair<long long, int> move(int now, const char &c) const {
        now = this->nodes[now].next[c - base];
        return make_pair(correct[now], now);
    }

    pair<long long, int> move(const char &c) const { return move(0, c); }

    pair<long long, int> move(int now, const string &s) const {
        long long sum = 0;
        for (auto &c : s) {
            pair<long long, int> p = move(now, c);
            sum += p.first, now = p.second;
        }
        return make_pair(sum, now);
    }

    pair<long long, int> move(const string &s) const { return move(0, s); }
};
