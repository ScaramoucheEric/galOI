/*
    @ Author:       Eric / Sky__White
    @ Filename:     P5648.cpp
    @ Date:         18/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <stack>
#include <cstdio>
#include <ctime>
#include <vector>

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

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    // freopen("actgame.in", "r", stdin);
    // freopen("actgame.out", "w", stdout);

    int n, m; fin >> n >> m;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) fin >> arr[i];

    stack<int> stk;

    vector<vector<int> > st(n + 2, vector<int>(31));

    for (int i = 1; i <= n; i ++ ) {
        while(stk.size() and arr[stk.top()] < arr[i]) {
            int t = stk.top(); stk.pop();
            st[t][0] = i;
        }
        stk.push(i);
    }
    while(stk.size()) {
        st[stk.top()][0] = n + 1;
        stk.pop();
    }

    for (int i = 0; i <= 30; i ++ )
        st[n + 1][i] = n + 1;

    vector<vector<int> > sum(n + 2, vector<int>(31));

    for (int i = n; i; i -- ) {
        sum[i][0] = (st[i][0] - i) * arr[i];
        for (int j = 1; j <= 30; j ++ ) {
            st[i][j] = st[st[i][j - 1]][j - 1];
            sum[i][j] = sum[i][j - 1] + sum[st[i][j - 1]][j - 1];
        }
    }

    // for (int i = 1; i <= n; i ++ ) {
    //     for (int j = 0; j <= 30; j ++ ) {
    //         cout << i << " " << j << " " << st[i][j] << " " << sum[i][j] << endl;
    //     }
    // }

    int lastans = 0;

    while(m -- ) {
        int u, v; fin >> u >> v;
        int l = 1 + (u ^ lastans) % n,
            q = 1 + (v ^ (lastans + 1)) % (n - l + 1);
        lastans = 0;
        int r = l + q - 1;

        for (int i = 30; ~i; i -- ) {
            if (st[l][i] <= r)
                lastans += sum[l][i], l = st[l][i];
        }
        lastans += arr[l] * (r - l + 1), l = st[l][0];

        cout << lastans << endl;
    }

    return 0;
}