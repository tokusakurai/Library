#pragma once

// Static Top Tree
// 計算量 構築：O(n log(n))、頂点・辺更新 O(log^2(n))
// 空間計算量 O(n)

// 概要
// 木 DP の過程を、path cluster と point cluster に分類する。
// path cluster 同士のマージを heavy path 上の二分木、point cluster 同士のマージを二分木上にする。
// これによって、マージ過程の深さを O(log^2(n)) にすることができ、実用上も高速である。

// verified with
// https://judge.yosupo.jp/problem/point_set_tree_path_composite_sum_fixed_root
// https://atcoder.jp/contests/abc351/tasks/abc351_g

#include <bits/stdc++.h>
using namespace std;

template <typename Tree_DP, bool directed = false>
struct Static_Top_Tree {
    using Path = typename Tree_DP::Path_Cluster;
    using Point = typename Tree_DP::Point_Cluster;
    using V = typename Tree_DP::Vertex;
    using E = typename Tree_DP::Edge;

    enum Types { merge_path, merge_point, attach_edge, attach_root, singleton };

    struct Node {
        int par, left, right;
        Types type;
        int relation; // vertex[i] を持つ場合 i, edge[i] を持つ場合 n+i, その他 -1
        Path data_path;
        Point data_point;
        Node(Types type, int relation) : par(-1), left(-1), right(-1), type(type), relation(relation) {}
    };

    struct Edge {
        int to, id;
        Edge(int to, int id) : to(to), id(id) {}
    };

    vector<V> vertex; // 頂点 i のデータ
    vector<E> edge;   // 辺 i のデータ
    vector<Node> nodes;
    vector<vector<Edge>> es;
    vector<int> vertex_nodes_idx; // vertex[i] を持つ node の index
    vector<int> edge_nodes_idx;   // edge[i] を持つ node の index
    vector<int> si;
    const int n;
    int m;

    Static_Top_Tree(int n, const vector<V> &vertex) : vertex(vertex), edge(n - 1), es(n), vertex_nodes_idx(n, -1), edge_nodes_idx(n - 1, -1), si(n, 1), n(n), m(0) { nodes.reserve(4 * n); }

    Static_Top_Tree(int n) : Static_Top_Tree(n, vector<V>(n)) {}

    void add_edge(int from, int to, const E &e) {
        es[from].emplace_back(to, m);
        if (!directed) es[to].emplace_back(from, m);
        edge[m] = e;
        m++;
    }

    int dfs_sz(int now, int pre = -1) {
        for (auto e : es[now]) {
            if (e.to == pre) continue;
            si[now] += dfs_sz(e.to, now);
        }
        return si[now];
    }

    void add_node(int p, Node node) {
        int k = nodes.size();
        if (p != -1) {
            if (nodes[p].left == -1) {
                nodes[p].left = k;
            } else {
                nodes[p].right = k;
            }
        }
        nodes.push_back(node);
        nodes[k].par = p;
    }

    void struct_paths(int now, int pre = -1, int pre_node = -1) {
        int memo_pre = pre;
        vector<int> heavy_path, heavy_path_id;
        while (now != -1) {
            heavy_path.push_back(now);
            int ma = -1;
            Edge heavy{-1, -1};
            for (auto &e : es[now]) {
                if (e.to == pre) continue;
                if (ma < si[e.to]) {
                    ma = si[e.to];
                    heavy = e;
                }
            }
            if (heavy.id != -1) heavy_path_id.push_back(heavy.id);
            pre = now;
            now = heavy.to;
        }
        int d = heavy_path.size();
        vector<int> idx(d);

        auto rec = [&](auto &&rec, int l, int r, int p) -> void {
            int k = nodes.size();
            if (r - l == 1) {
                idx[l] = k;
                vertex_nodes_idx[heavy_path[l]] = k;
                add_node(p, Node(Types::singleton, heavy_path[l]));
                return;
            }
            int m = (l + r) / 2;
            edge_nodes_idx[heavy_path_id[m - 1]] = k;
            add_node(p, Node(Types::merge_path, n + heavy_path_id[m - 1]));
            rec(rec, l, m, k);
            rec(rec, m, r, k);
        };

        rec(rec, 0, d, pre_node);
        for (int i = 0; i < d - 1; i++) {
            int npre = (i == 0 ? memo_pre : heavy_path[i - 1]);
            struct_points(heavy_path[i], heavy_path[i + 1], npre, idx[i]);
        }
    }

    void struct_points(int now, int heavy, int pre = -1, int pre_node = -1) {
        vector<int> light, light_id;
        for (auto &e : es[now]) {
            if (e.to == pre || e.to == heavy) continue;
            light.push_back(e.to);
            light_id.push_back(e.id);
        }
        if (light.empty()) return;
        nodes[pre_node].type = Types::attach_root;
        int c = light.size();
        vector<int> idx(c);

        auto rec = [&](auto &&rec, int l, int r, int p) -> void {
            int k = nodes.size();
            if (r - l == 1) {
                idx[l] = k;
                edge_nodes_idx[light_id[l]] = k;
                add_node(p, Node(Types::attach_edge, n + light_id[l]));
                return;
            }
            int m = (l + r) / 2;
            add_node(p, Node(Types::merge_point, -1));
            rec(rec, l, m, k);
            rec(rec, m, r, k);
        };

        rec(rec, 0, c, pre_node);
        for (int i = 0; i < c; i++) struct_paths(light[i], now, idx[i]);
    }

    void recalc(int i) {
        int l = nodes[i].left, r = nodes[i].right;
        if (nodes[i].type == Types::merge_path) {
            nodes[i].data_path = Tree_DP::merge_path(nodes[l].data_path, nodes[r].data_path, edge[nodes[i].relation - n]);
        } else if (nodes[i].type == Types::merge_point) {
            nodes[i].data_point = Tree_DP::merge_point(nodes[l].data_point, nodes[r].data_point);
        } else if (nodes[i].type == Types::attach_edge) {
            nodes[i].data_point = Tree_DP::attach_edge(nodes[l].data_path, edge[nodes[i].relation - n]);
        } else if (nodes[i].type == Types::attach_root) {
            nodes[i].data_path = Tree_DP::attach_root(nodes[l].data_point, vertex[nodes[i].relation]);
        } else if (nodes[i].type == Types::singleton) {
            nodes[i].data_path = Tree_DP::singleton(vertex[nodes[i].relation]);
        }
    }

    Path build(int root = 0) {
        dfs_sz(root);
        struct_paths(root);
        for (int i = (int)nodes.size() - 1; i >= 0; i--) recalc(i);
        return nodes[0].data_path;
    }

    void thrust(int i) {
        while (i != -1) {
            recalc(i);
            i = nodes[i].par;
        }
    }

    Path update_vertex(int i, const V &x) {
        vertex[i] = x;
        thrust(vertex_nodes_idx[i]);
        return nodes[0].data_path;
    }

    Path update_edge(int i, const E &x) {
        edge[i] = x;
        thrust(edge_nodes_idx[i]);
        return nodes[0].data_path;
    }
};
