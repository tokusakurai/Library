
// Forldable Queue ( SWAG の deque 版)
// 計算量: push,pop amortized O(1), それ以外 O(1)

// 概要
// 2本の stack で deque をシミュレートできることを利用して deque に入っているモノイドの和を計算する。
// 具体的には2本のstackそれぞれの累積和を保持している。

// verified with
// https://judge.yosupo.jp/problem/deque_operate_all_composite

#pragma once
#include <bits/stdc++.h>
using namespace std;

template<class Monoid>
class Foldable_Deque {
    using M = typename Monoid::V;

    struct Node {
        M value;
        M sum;
        Node() {}
        Node(M v) : value(v), sum(v) {}
        Node(M v, M s) : value(v), sum(s) {}
    };
    
    vector<Node> head, tail;

    public:
    Foldable_Deque() : head(), tail() {}

    // 中に入っている要素の和を計算する。
    // 非可換のモノイドでは右のほうが先頭側であることに注意 (back <-> front)
    M fold() const {
        if(tail.empty() && head.empty()) return Monoid::id;
        else if(tail.empty()) return head.back().sum;
        else if(head.empty()) return tail.back().sum; 
        else return Monoid::merge(tail.back().sum, head.back().sum);
    }

    M front() const {
        assert(!empty());
        if(head.empty()) return tail.at(0).value;
        else return head.back().value;
    }

    M back() const {
        assert(!empty());
        if(tail.empty()) return head.at(0).value;
        else return tail.back().value;
    }

    void push_front(const M &x) {
        if(head.empty()) {
            head.emplace_back(x, x);
        } else {
            head.emplace_back(x, Monoid::merge(head.back().sum, x));
        }
    }

    void push_back(const M &x) {
        if(tail.empty()) {
            tail.emplace_back(x, x);
        } else {
            tail.emplace_back(x, Monoid::merge(x, tail.back().sum));
        }
    }

    template <class... Args>
    decltype(auto) emplace_front(Args&&... args) {
        auto value = typename Monoid::V(std::forward<Args>(args)...);
        if(head.empty()) return head.emplace_back(value);
        else return head.emplace_back(value, Monoid::merge(head.back().sum, value));
    }

    template <class... Args>
    decltype(auto) emplace_back(Args&&... args) {
        auto value = typename Monoid::V(std::forward<Args>(args)...);
        if(tail.empty()) return tail.emplace_back(value);
        else return tail.emplace_back(value, Monoid::merge(value, tail.back().sum));
    }

    void pop_front() {
        assert(!empty());
        if(head.empty()) {
            const size_t tail_sz = size() / 2;
            const size_t head_sz = size() - tail_sz - 1;
            head.resize(head_sz);
            for(size_t i = 0; i < head_sz; i++) {
                head[i].value = move(tail[head_sz -  i].value);
                if(i == 0) {
                    head[i].sum = head[i].value;
                } else {
                    head[i].sum = Monoid::merge(head[i - 1].sum, head[i].value);
                }
            }
            for(size_t i = 0; i < tail_sz; i++) {
                tail[i].value = move(tail[head_sz + i + 1].value);
                if(i == 0) {
                    tail[i].sum = tail[i].value;
                } else {
                    tail[i].sum = Monoid::merge(tail[i].value, tail[i - 1].sum);
                }
            }
            tail.resize(tail_sz);
        } else {
            head.pop_back();
        }
    }

    void pop_back() {
        assert(!empty());
        if(tail.empty()) {
            const size_t head_sz = size() / 2;
            const size_t tail_sz = size() - head_sz - 1;
            tail.resize(tail_sz);
            for(size_t i = 0; i < tail_sz; i++) {
                tail[i].value = move(head[tail_sz -  i].value);
                if(i == 0) {
                    tail[i].sum = tail[i].value;
                } else {
                    tail[i].sum = Monoid::merge(tail[i].value, tail[i - 1].sum);
                }
            }
            for(size_t i = 0; i < head_sz; i++) {
                head[i].value = move(head[tail_sz + i + 1].value);
                if(i == 0) {
                    head[i].sum = head[i].value;
                } else {
                    head[i].sum = Monoid::merge(head[i - 1].sum, head[i].value);
                }
            }
            head.resize(head_sz);
        } else {
            tail.pop_back();
        }
    }

    size_t size() const {
        return head.size() + tail.size();
    }

    bool empty() const {
        return size() == 0;
    }
};