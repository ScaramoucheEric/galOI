/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     [ABC427D].cpp
    @ Time:         10/11/2025
    @ Email:        acwing@foxmail.com
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int T;
    cin >> T;
    
    while (T--) {
        int N, M, K;
        cin >> N >> M >> K;
        string S;
        cin >> S;
        
        vector<vector<int>> adj(N+1);
        for (int i = 0; i < M; i++) {
            int u, v;
            cin >> u >> v;
            adj[u].push_back(v);
        }
        
        int totalMoves = 2 * K;
        vector<vector<char>> dp(N+1, vector<char>(totalMoves + 1));
        
        // Base case: m = 0
        for (int i = 1; i <= N; i++) {
            dp[i][0] = S[i-1];
        }
        
        // DP
        for (int m = 1; m <= totalMoves; m++) {
            for (int i = 1; i <= N; i++) {
                if (m % 2 == 0) { // Alice's turn
                    bool found = false;
                    for (int v : adj[i]) {
                        if (dp[v][m-1] == 'A') {
                            found = true;
                            break;
                        }
                    }
                    dp[i][m] = found ? 'A' : 'B';
                } else { // Bob's turn
                    bool found = false;
                    for (int v : adj[i]) {
                        if (dp[v][m-1] == 'B') {
                            found = true;
                            break;
                        }
                    }
                    dp[i][m] = found ? 'B' : 'A';
                }
            }
        }
        
        if (dp[1][totalMoves] == 'A') {
            cout << "Alice\n";
        } else {
            cout << "Bob\n";
        }
    }
    
    return 0;
}