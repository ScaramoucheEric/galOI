/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     [ABC427C].cpp
    @ Time:         10/11/2025
    @ Email:        acwing@foxmail.com
*/

#include <vector>
#include <cstring>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int N, M;
    cin >> N >> M;
    
    vector<pair<int, int>> edges;
    for (int i = 0; i < M; i++) {
        int u, v;
        cin >> u >> v;
        edges.push_back({u - 1, v - 1});
    }
    
    int max_keep = 0;
    // Try all colorings
    for (int mask = 0; mask < (1 << N); mask++) {
        int valid = 0;
        for (auto& edge : edges) {
            int u = edge.first;
            int v = edge.second;
            // Check if endpoints have different colors
            if (((mask >> u) & 1) != ((mask >> v) & 1)) {
                valid++;
            }
        }
        max_keep = max(max_keep, valid);
    }
    
    cout << M - max_keep << endl;
    
    return 0;
}