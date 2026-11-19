/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     [ABC427E].cpp
    @ Time:         10/11/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n, m; cin >> n >> m;

    vector<string> arr(n + 2);

    for (int i = 1; i <= n; i ++ ) {
        cin >> arr[i];
        arr[i] = '.' + arr[i] + '.';
    }
    for (int i = 0; i <= m + 1; i ++ )
        arr[0].push_back('.'), arr[n + 1].push_back('.');

    int x, y;

    [&]() {
        for (int i = 1; i <= n; i ++ )
            for (int j = 1; j <= m; j ++ )
                if (arr[i][j] == 'T') {
                    arr[i][j] = '.';
                    x = i, y = j;
                    return ;
                }
        return ;
    }();

    queue<vector<string> > q;

    q.push(arr);

    while(q -- ) {
        auto t = q.front(); q.pop();
    }

    return 0;
}