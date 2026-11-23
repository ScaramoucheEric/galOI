/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     P5686.cpp
    @ Time:         09/27/2025
    @ Email:        acwing@foxmail.com
*/

#include <iostream>
#include <vector>
#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

const int MOD = 1e9 + 7;

signed main() {
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1);
    for (int i = 1; i <= n; i++) {
        cin >> a[i];
    }
    for (int i = 1; i <= n; i++) {
        cin >> b[i];
    }
    vector<int> A(n + 1), B(n + 1);
    vector<int> sumA(n + 1), sumB(n + 1), sumAB(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        A[i] = (A[i - 1] + a[i]) % MOD;
        B[i] = (B[i - 1] + b[i]) % MOD;
        sumA[i] = (sumA[i - 1] + A[i]) % MOD;
        sumB[i] = (sumB[i - 1] + B[i]) % MOD;
        sumAB[i] = (sumAB[i - 1] + A[i] * B[i] % MOD) % MOD;
    }
    int ans = 0;
    for (int r = 1; r <= n; r ++ ) {
        ans += (r * A[r] % MOD * B[r] % MOD - B[r] * sumA[r - 1] % MOD - A[r] * sumB[r - 1] % MOD + sumAB[r - 1]) % MOD;
        ans = (ans + MOD) % MOD;
    }
    cout << ans << endl;
    return 0;
}