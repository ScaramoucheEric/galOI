/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC438D].cpp
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
    int n; cin >> n;
    
    vector<int> A(n + 1), B(n + 1), C(n + 1);
    for (int i = 1; i <= n; i++) cin >> A[i];
    for (int i = 1; i <= n; i++) cin >> B[i];
    for (int i = 1; i <= n; i++) cin >> C[i];
    
    vector<int> preA(n+1, 0), preB(n+1, 0);
    for (int i = 1; i <= n; i++) {
        preA[i] = preA[i - 1] + A[i];
        preB[i] = preB[i - 1] + B[i];
    }
    
    vector<int> suf(n+2, 0);
    for (int i = n; i >= 1; i--) {
        suf[i] = suf[i+1] + C[i];
    }
    
    int mm = LLONG_MIN;
    int res = LLONG_MIN;
    
    for (int y = 2; y < n; y++) {
        mm = max(mm, preA[y - 1] - preB[y - 1]);
        
        int cur = mm + preB[y] + suf[y + 1];
        res = max(res, cur);
    }
    
    cout << res << endl;
    
    return 0;
}