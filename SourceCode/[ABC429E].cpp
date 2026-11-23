/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC429E].cpp
    @ Time:         10/25/2025
    @ Email:        acwing@foxmail.com
*/

#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <algorithm>
using namespace std;

#define int long long

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    cin >> N >> M;

    vector<vector<int>> g(N);
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--;
        g[u].push_back(v);
        g[v].push_back(u);
    }

    string S;
    cin >> S;

    vector<int> dist1(N, INF), dist2(N, INF);
    vector<int> source1(N, -1), source2(N, -1);

    queue<int> q;

    for (int i = 0; i < N; i++) {
        if (S[i] == 'S') {
            dist1[i] = 0;
            source1[i] = i;
            q.push(i);
        }
    }

    while (!q.empty()) {
        int u = q.front(); q.pop();

        for (int v : g[u]) {
            int d = dist1[u] + 1;
            int src = source1[u];

            if (d < dist1[v]) {
                if (source1[v] != src) {
                    dist2[v] = dist1[v];
                    source2[v] = source1[v];
                }
                dist1[v] = d;
                source1[v] = src;
                q.push(v);
            } else if (d < dist2[v] && src != source1[v]) {
                dist2[v] = d;
                source2[v] = src;
                q.push(v);
            }
        }
    }

    for (int i = 0; i < N; i ++ )
        cout << dist1[i] << " " << dist2[i] << endl;

    for (int i = 0; i < N; i++) {
        if (S[i] == 'D') {
            if (dist2[i] == INF) {
                cout << "-1\n";
            } else {
                cout << dist1[i] + dist2[i] << "\n";
            }
        }
    }

    return 0;
}