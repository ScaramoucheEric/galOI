/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF10D.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
    @ Problem:      CF10D LCIS 最长公共上升子序列 + 完整方案输出
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <cctype>
using namespace std;

namespace std {
    class Read {
    public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while (!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while (isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; 
Read fin;

const int N = 505;

// dp[i][j] : a前i个, b前j个, 以b[j]结尾的LCIS长度
int dp[N][N];
// pre[i][j] : 记录路径前驱，用于输出方案
pair<int,int> pre[N][N];

signed main() {
    int n; fin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i ++ ) fin >> a[i];

    int m; fin >> m;
    vector<int> b(m + 1);
    for (int j = 1; j <= m; j ++ ) fin >> b[j];

    for (int i = 1; i <= n; i ++ ) {
        int maxv = 0;
        pair<int,int> last = {0,0};
        for (int j = 1; j <= m; j ++ ) {
            dp[i][j] = dp[i-1][j];
            pre[i][j] = {i-1, j};

            if (a[i] == b[j]) {
                dp[i][j] = maxv + 1;
                pre[i][j] = last;
            }
            if (b[j] < a[i]) {
                if (dp[i-1][j] > maxv) {
                    maxv = dp[i-1][j];
                    last = {i-1, j};
                }
            }
        }
    }

    int ans = 0;
    int pi = n, pj = 0;
    for (int j = 1; j <= m; j ++ ) {
        if (dp[n][j] > ans) {
            ans = dp[n][j];
            pj = j;
        }
    }

    vector<int> res;
    while (pi && pj) {
        auto [ni, nj] = pre[pi][pj];
        if (dp[pi][pj] != dp[ni][nj]) {
            res.push_back(b[pj]);
        }
        pi = ni, pj = nj;
    }
    reverse(all(res));

    cout << ans << endl;
    for (auto x : res) cout << x << " ";
    cout << endl;

    return 0;
}
