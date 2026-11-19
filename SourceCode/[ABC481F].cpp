/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC481F].cpp
    @ Date:         24/10/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

const int MOD = 998244353;
const int MAXN = 200005;

#define all(a) a.begin(), a.end()

struct Edge {
    int u, v, c;
};

vector<Edge> adj[MAXN];
vector<Edge> rev_adj[MAXN];
int len_arr[MAXN];
int dist_val[MAXN];
int rank_arr[MAXN];
int best_pre[MAXN];
int best_c[MAXN];

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    if (!(cin >> N >> M)) return 0;

    for (int i = 0; i < M; ++i) {
        int u, v, c;
        cin >> u >> v >> c;
        adj[u].push_back({u, v, c});
        rev_adj[v].push_back({u, v, c});
    }

    for (int i = 1; i <= N; ++i) {
        len_arr[i] = -1;
        dist_val[i] = 0;
        rank_arr[i] = 0;
    }

    queue<int> q;
    len_arr[1] = 0;
    q.push(1);
    int max_len = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
        max_len = max(max_len, len_arr[u]);
        for (auto& e : adj[u]) {
            int v = e.v;
            if (len_arr[v] == -1) {
                len_arr[v] = len_arr[u] + 1;
                q.push(v);
            }
        }
    }

    vector<vector<int>> buc(max_len + 1);
    for (int i = 1; i <= N; ++i) {
        if (len_arr[i] != -1) {
            buc[len_arr[i]].push_back(i);
        }
    }

    dist_val[1] = 0;
    rank_arr[1] = 0;

    for (int d = 1; d <= max_len; ++d) {
        vector<int>& node = buc[d];
        
        for (int v : node) {
            int best_u = -1;
            int best_c_val = 99;
            for (auto& e : rev_adj[v]) {
                int u = e.u;
                int c = e.c;
                if (len_arr[u] == d - 1) {
                    if (best_u == -1) {
                        best_u = u;
                        best_c_val = c;
                    } else {
                        if (rank_arr[u] < rank_arr[best_u]) {
                            best_u = u;
                            best_c_val = c;
                        } else if (rank_arr[u] == rank_arr[best_u]) {
                            if (c < best_c_val) {
                                best_u = u;
                                best_c_val = c;
                            }
                        }
                    }
                }
            }
            best_pre[v] = best_u;
            best_c[v] = best_c_val;
        }

        sort(all(node), [&](int a, int b) {
            if (rank_arr[best_pre[a]] != rank_arr[best_pre[b]]) {
                return rank_arr[best_pre[a]] < rank_arr[best_pre[b]];
            }
            return best_c[a] < best_c[b];
        });

        int cur_rank = 0;
        for (int i = 0; i < node.size(); ++i) {
            int v = node[i];
            if (i > 0) {
                int prev_v = node[i-1];
                if (rank_arr[best_pre[v]] != rank_arr[best_pre[prev_v]] || best_c[v] != best_c[prev_v]) {
                    cur_rank++;
                }
            }
            rank_arr[v] = cur_rank;
            dist_val[v] = (1LL * dist_val[best_pre[v]] * 10 + best_c[v]) % MOD;
        }
    }

    for (int i = 2; i <= N; ++i) {
        cout << dist_val[i] << "\n";
    }

    return 0;
}