/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC473D].cpp
    @ Date:         29/08/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
#include <cmath>
#include <vector>
#include <queue>

using namespace std;

int n, k;
int seq[11];

// dp[i][j]: 用第 i 到第 n 个位置（权重 i..n）凑出加权和 j 的方案数
int dp[12][200001];

void enumerate(int pos, int rem) {
    if (pos == n) {
        if (rem % n == 0) {
            seq[n] = rem / n;
        for (int i = 1; i <= n; i++) {
            if (i > 1) printf(" ");
                printf("%d", seq[i]);
            }
            printf("\n");
        }
        return;
    }
    
    int w = pos;
    for (int v = 0; v * w <= rem; v++) {
        int nxt = rem - v * w;
        if (dp[pos + 1][nxt] > 0) {
            seq[pos] = v;
            enumerate(pos + 1, nxt);
        }
    }
}

int main() {
    scanf("%d%d", &n, &k);
    
    for (int j = 0; j <= k; j++) {
        dp[n][j] = (j % n == 0) ? 1 : 0;
    }
    
    for (int i = n - 1; i >= 1; i--) {
        for (int j = 0; j <= k; j++) {
            dp[i][j] = dp[i + 1][j];
        }
        for (int j = i; j <= k; j++) {
            dp[i][j] += dp[i][j - i];
        }
    }
    
    enumerate(1, k);
    return 0;
}