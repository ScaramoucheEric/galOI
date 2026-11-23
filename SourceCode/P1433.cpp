/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     P1433.cpp
    @ Time:         09/06/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <cmath>
#include <bitset>

using namespace std;

double dist(double a, double b, double x, double y) {
    double ta = a - x, tb = b - y;
    return sqrt(ta * ta + tb * tb);
}

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;

    vector<pair<double,double> > arr(n);

    for (int i = 0; i < n; i ++ )
        cin >> arr[i].first >> arr[i].second;
    
    vector<vector<double> > dp(n, vector<double>(1 << n, 1e18));

    for (int i = 0; i < n; i ++ )
        dp[i][1 << i] = dist(0, 0, arr[i].first, arr[i].second);

    for (int S = 1; S < 1 << n; S ++ ) {
        for (int j = 0; j < n; j ++ )
            if (S >> j & 1) {
                int s = S - (1 << j);
                if (s == 0) {
                    continue;
                } else {
                    for (int k = 0; k < n; k ++ )
                        if (s >> k & 1)
                            dp[j][S] = min(dp[j][S], dp[k][s] + dist(arr[k].first, arr[k].second, arr[j].first, arr[j].second));
                }
            }
    }

    double res = 1e18;

    for (int i = 0; i < n; i ++ )
        res = min(res, dp[i][(1 << n) - 1]);
    
    // for (int j = 0; j < 1 << n; j ++ ) {
    //     for (int i = 0; i < n; i ++ )
    //         cerr << i << " " << bitset<4>(j).to_string() << " " << dp[i][j] << endl;
    //     }

    printf("%.2lf\n", res);

    return 0;
}