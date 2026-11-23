/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC435D].cpp
    @ Time:         12/06/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cstring>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n, m;
    cin >> n >> m;
    
    vector<vector<int> > g(n);
    
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        u--; v--; 
        
        g[v].push_back(u);
    }
    
    vector<bool> st(n, false);
    queue<int> q;

    int Q; cin >> Q;
    
    while (Q -- ) {
        int t, v; cin >> t >> v;
        v -- ; 
        
        if (t == 1) {
            if (!st[v]) {
                st[v] = true;
                q.push(v);
                
                while (!q.empty()) {
                    int cur = q.front();
                    q.pop();
                    
                    for (int to : g[cur]) {
                        if (!st[to]) {
                            st[to] = true;
                            q.push(to);
                        }
                    }
                }
            }
        } else {
            cout << (st[v] ? "Yes" : "No") << "\n";
        }

        // for (int i = 1; i <= n; i ++ )
        //     cout << st[i] << " ";
        // cout << endl;
    }
    
    return 0;
}