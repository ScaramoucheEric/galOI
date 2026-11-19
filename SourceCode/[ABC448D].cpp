#include <iostream>
#include <vector>
#include <unordered_set>
#include <algorithm>

using namespace std;

#define int long long

vector<vector<int> > G;
vector<int> A;
vector<bool> ans;
unordered_set<int> path;

void dfs(int u, int fa, bool hd) {
    bool cd = hd;
    bool add = false;
    
    if (path.count(A[u])) {
        cd = true;
    } else {
        path.insert(A[u]);
        add = true;
    }
    
    ans[u] = cd;
    
    for (int v : G[u]) {
        if (v != fa) {
            dfs(v, u, cd);
        }
    }
    
    if (add) {
        path.erase(A[u]);
    }
}

signed main() {
    int n; cin >> n;
    
    A.resize(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        cin >> A[i];
    }
    
    G.resize(n + 1);
    for (int i = 0; i < n - 1; i ++ ) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    ans.resize(n + 1);
    path.clear();
    
    dfs(1, -1, false);
    
    for (int i = 1; i <= n; i ++ ) {
        cout << (ans[i] ? "Yes" : "No") << "\n";
    }
    
    return 0;
}