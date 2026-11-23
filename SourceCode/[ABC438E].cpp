/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC438E].cpp
    @ Time:         12/27/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int N, Q;
    cin >> N >> Q;
    vector<int> A(N + 1);
    for (int i = 1; i <= N; i++) {
        cin >> A[i];
    }

    
    vector<int> dist(N + 1, -1), psum(N + 1, 0), en(N + 1, -1), len(N + 1, 0), cyc(N + 1, 0);
    vector<vector<int>> cpre(N + 1);
    vector<vector<int>> pvals(N + 1); 

    vector<int> vis(N + 1, 0); 

    vector<int> node;

    function<void(int)> dfs = [&](int u) {
        if (vis[u] == 2) return;

        if (vis[u] == 1) {
            int idx = -1;
            for (int i = 0; i < (int)node.size(); i++) {
                if (node[i] == u) {
                    idx = i;
                    break;
                }
            }
            int Len = node.size() - idx;
            vector<int> cnode(Len);
            vector<int> pref(Len + 1, 0);
            for (int i = 0; i < Len; i++) {
                cnode[i] = node[idx + i];
            }
            for (int i = 0; i < Len; i++) {
                pref[i + 1] = pref[i] + cnode[i];
            }
            int sum_cycle = pref[Len];
            for (int i = 0; i < Len; i++) {
                int v = cnode[i];
                len[v] = Len;
                cyc[v] = sum_cycle;
                cpre[v] = pref; 
                en[v] = v;
                dist[v] = 0;
                psum[v] = 0;
                pvals[v].clear();
            }
            
            for (int i = 0; i < idx; i++) {
                int v = node[i];
                en[v] = u;
                dist[v] = idx - i;
                
                int s = 0;
                vector<int> vals;
                for (int j = i; j < idx; j++) {
                    s += node[j];
                    vals.push_back(node[j]);
                }
                psum[v] = s;
                pvals[v] = vals;
            }
            return;
        }
        vis[u] = 1;
        node.push_back(u);
        dfs(A[u]);
        vis[u] = 2;
        node.pop_back();
    };

    for (int i = 1; i <= N; i++) {
        if (!vis[i]) {
            node.clear();
            dfs(i);
        }
    }

    
    while (Q--) {
        int T;
        int B;
        cin >> T >> B;
        if (T <= dist[B]) {
            int ans = 0;
            for (int i = 0; i < T; i++) {
                ans += pvals[B][i];
            }
            cout << ans << endl;
        } else {
            int rem = T - dist[B];
            int r = en[B];
            int L = len[r];
            int full = rem / L;
            int re = rem % L;
            int ans = psum[B] + full * cyc[r] + cpre[r][re];
            cout << ans << endl;
        }
    }

    return 0;
}