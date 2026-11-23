/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC429C].cpp
    @ Time:         10/25/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <unordered_map>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n; cin >> n;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i ++ )
        cin >> arr[i];

    unordered_map<int, int> cnt;

    for (int i = 1; i <= n; i ++ )
        cnt[arr[i]] ++ ;

    int sum1 = 0, sum2 = 0;

    for (auto [a, b] : cnt)
        sum1 += b * b, sum2 += b * b * b;

    int res = ((n + 1) * sum1 - n * n - sum2) / 2;

    cout << res << endl;
}