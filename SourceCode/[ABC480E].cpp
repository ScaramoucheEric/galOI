/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC480E].cpp
    @ Date:         17/10/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <functional>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <queue>
#include <cmath>

using namespace std;

#define int long long

bool check(int a, int d, int L, int N) {
    __int128 prod = 1;
    for (int i = 0; i < L; i++) {
        prod *= (a + (__int128)i * d);
        if (prod > N) return false; 
    }
    return true;
}

signed main() {
    
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N;
    if (!(cin >> N)) return 0;

    
    int M = pow((long double)N, 1.0 / 3.0);
    while ((__int128)(M + 1) * (M + 1) * (M + 1) <= N) M++;
    while ((__int128)M * M * M > N) M--;
    M += 1; 

    
    int max_L = 0;
    int fact = 1;
    for (int i = 1; i <= 25; i++) {
        fact *= i;
        if (fact > N) break;
        max_L = i;
    }

    int ans = 0;
    
    for (int L = 3; L <= max_L; L++) {
        
        int limit_d = min(M - 1, (int)pow((long double)N, 1.0 / (L - 1)) + 5);
        
        for (int d = 1; d <= limit_d; d++) {
            
            if (!check(1, d, L, N)) break;
            
            int low = 1, high = min((int)pow((long double)N, 1.0 / L) + 5, 1000000000000000000LL);
            int best_a = 0;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (check(mid, L, M, N)) {
                    best_a = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            ans += best_a;
        }
    }

    
    for (int a = 1; a < M; a++) {
        for (int L = 3; L <= max_L; L++) {
            
            if (!check(a, M, L, N)) break;
            
            int low = M, high = min((int)pow((long double)N, 1.0 / (L - 1)) + 5, 1000000000000000000LL);
            int best_d = M - 1;
            while (low <= high) {
                int mid = low + (high - low) / 2;
                if (check(a, mid, L, N)) {
                    best_d = mid;
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
            }
            if (best_d >= M) {
                ans += (best_d - M + 1);
            }
        }
    }

    cout << ans << "\n";

    return 0;
}