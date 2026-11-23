/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC456tE].cpp
    @ Date:         05/02/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <iostream>
#include <vector>
#include <string>
#include <stack>
#include <cstring>
using namespace std;

int N, M, W;
vector<vector<int>> G;
vector<string> S;
vector<vector<int>> ok;

int id(int city, int day) {
    return city * W + day;
}

bool Cyc(int start, vector<vector<int>>& graph, vector<int>& vis, vector<int>& rec) {
    if (rec[start]) return true;
    if (vis[start]) return false;

    vis[start] = 1;
    rec[start] = 1;

    for (int nxt : graph[start]) {
        if (Cyc(nxt, graph, vis, rec)) return true;
    }

    rec[start] = 0;
    return false;
}

bool solve() {
    int totalNodes = N * W;
    vector<vector<int>> graph(totalNodes);

    for (int city = 0; city < N; city++) {
        for (int day = 0; day < W; day++) {
            if (!ok[city][day]) continue;

            int nextDay = (day + 1) % W;

            if (ok[city][nextDay]) {
                graph[id(city, day)].push_back(id(city, nextDay));
            }

            for (int nbr : G[city]) {
                if (ok[nbr][nextDay]) {
                    graph[id(city, day)].push_back(id(nbr, nextDay));
                }
            }
        }
    }

    vector<int> startn;
    for (int city = 0; city < N; city++) {
        if (ok[city][0]) {
            startn.push_back(id(city, 0));
        }
    }

    vector<int> vis(totalNodes, 0);
    vector<int> rec(totalNodes, 0);

    if (startn.empty()) return false;

    for (int s : startn) {
        if (!vis[s]) {
            if (Cyc(s, graph, vis, rec)) {
                return true;
            }
        }
    }

    return false;
}

int main() {
    int T;
    cin >> T;
    while (T--) {
        cin >> N >> M;
        G.assign(N, vector<int>());
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            u--; v--;
            G[u].push_back(v);
            G[v].push_back(u);
        }
        S.resize(N);
        int k; cin >> k;
        for (int i = 0; i < N; i++) {
            cin >> S[i];
        }
        W = S[0].size();

        ok.assign(N, vector<int>(W, 0));
        for (int i = 0; i < N; i++) {
            for (int j = 0; j < W; j++) {
                if (S[i][j] == 'o') ok[i][j] = 1;
            }
        }

        bool ans = solve();
        cout << (ans ? "Yes" : "No") << endl;
    }
    return 0;
}