/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC431E].cpp
    @ Time:         11/08/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <queue>
#include <cstdio>
#include <functional>

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

const int INF = 0x3f3f3f3f3f3f3f3f;

int next(int d, int tp) {
    if (tp == 0) { 
        return d;
    } else if (tp == 1) { 
        if (d == 0) return 1;
        if (d == 1) return 0;
        if (d == 2) return 3;
        if (d == 3) return 2;
    } else { 
        if (d == 0) return 3;
        if (d == 1) return 2;
        if (d == 2) return 1;
        if (d == 3) return 0;
    }
    return -1; 
}

using TI = tuple<int,int,int,int>;

int solve() {
    int n, m; cin >> n >> m;
    
    vector<string> arr(n);
    for (int i = 0; i < n; i++) {
        cin >> arr[i];
    }
    
    vector<vector<vector<int> > > dist(n, vector<vector<int> >(m, vector<int>(4, INF)));
    
    priority_queue<TI, vector<TI>, greater<TI>> q;
    
    dist[0][0][0] = 0;
    q.push({0, 0, 0, 0});
    
    int dx[] = {0, 1, 0, -1};
    int dy[] = {1, 0, -1, 0};
    
    while (!q.empty()) {
        auto [cost, x, y, d] = q.top();
        q.pop();
    
        if (cost > dist[x][y][d]) continue;
        
        if (x == n - 1 and y == m - 1) {
            int t;
            if (arr[x][y] == 'A') t = 0;
            else if (arr[x][y] == 'B') t = 1;
            else t = 2;
            if (next(d, t) != 0) cost ++ ;
            return cost;
        }
        
        int now_ty;
        if (arr[x][y] == 'A') now_ty = 0;
        else if (arr[x][y] == 'B') now_ty = 1;
        else now_ty = 2;
        
        for (int new_ty = 0; new_ty < 3; new_ty++) {
            int ncost = (new_ty == now_ty) ? 0 : 1;
            int nd = next(d, new_ty);
            
            int nx = x + dx[nd];
            int ny = y + dy[nd];
            
            if (nx >= 0 and nx < n and ny >= 0 and ny < m) {
                if (dist[nx][ny][nd] > cost + ncost) {
                    dist[nx][ny][nd] = cost + ncost;
                    q.push({cost + ncost, nx, ny, nd});
                }
            }
        }
    }
    
    return -1; 
}

signed main() {
    int T;
    cin >> T;
    
    while (T--) {
        cout << solve() << "\n";
    }
    
    return 0;
}