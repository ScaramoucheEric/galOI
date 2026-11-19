/*
    @ Author:       Eric / Sky__White
    @ Filename:     复仇之魂.cpp
    @ Date:         30/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>
#include <unordered_map>
#include <list>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

signed main(){
    int n; fin >> n;
    
    vector<int> p(n + 1), pos(n + 1);
    for(int i = 1; i <= n; i++){
        fin >> p[i];
        pos[p[i]] = i;
    }
    
    vector<int> sufMax(n + 2, 0);
    for(int x = n - 1; x >= 0; x--){
        sufMax[x] = max(sufMax[x + 1], pos[x + 1]);
    }
    
    vector<int> preMin(n + 2, n + 1);
    for(int x = 1; x <= n; x++){
        preMin[x] = min(preMin[x - 1], pos[x]);
    }
    
    vector<int> R0(n + 1, 0), L0(n + 1, 0);
    
    for(int k = 0; k < n; k++){
        R0[k] = k;
        bool chain_ok = true;
        for(int kp = k + 1; kp <= n; kp++){
            if(kp > k + 1 && pos[kp] < pos[kp - 1]) {
                chain_ok = false; 
                break;
            }
            if(sufMax[kp] >= pos[k + 1]) {
                
                
                continue;
            }
            if(chain_ok) R0[k] = kp;
        }

        vector<int> L(n + 1, 0), R(n + 1, 0);
        
        for (int i = 1; i < n; i ++ ) {
            L[i] = i;
            R[i] = i;
        }

        L0[k] = k;
        chain_ok = true;
        for(int kp = k + 1; kp <= n; kp++){
            if(kp > k + 1 && pos[kp] > pos[kp - 1]) {
                chain_ok = false;
                break;
            }
            if(preMin[kp] <= pos[k + 1]) {
                continue;
            }
            if(chain_ok) L0[k] = kp;
        }
    }
    
    const int INF = 1e9;
    vector<vector<int>> dp(n + 1, vector<int>(n + 2, INF));
    dp[0][0] = 0;
    
    int ans = INF;
    
    for(int k = 0; k < n; k++){
        for(int s = 0; s <= n; s++){
            if(dp[k][s] == INF) continue;
            int cost = dp[k][s];
            
            if(s + 1 <= n){
                dp[k + 1][s + 1] = min(dp[k + 1][s + 1], cost + 1);
            }
            if(s > 0){
                if(R0[k] > k){
                    dp[R0[k]][s - 1] = min(dp[R0[k]][s - 1], cost + 1);
                }
                if(L0[k] > k){
                    dp[L0[k]][s - 1] = min(dp[L0[k]][s - 1], cost + 1);
                }
            }
        }
    }
    
    for(int s = 0; s <= n; s++){
        ans = min(ans, dp[n][s]);
    }
    
    cout << ans << endl;
    return 0;
}