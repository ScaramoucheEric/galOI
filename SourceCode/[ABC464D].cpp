/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC464D].cpp
    @ Date:         27/06/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int T;

    cin >> T;

    while (T -- ) {
        int N; string S;

        cin >> N >> S;
        S = " " + S;

        vector<int> x(N + 1);
        for (int i = 1; i <= N; i++) cin >> x[i];

        vector<int> y(N);
        for (int i = 1; i <= N - 1; i++) cin >> y[i];

        const int INF = -(1LL << 60);
        vector<int> pre(2, INF), cur(2, INF);

        for (int st = 0; st < 2; st++) {
            char tar = (st == 0 ? 'S' : 'R');
            int cost = (S[1] == tar ? 0 : -x[1]);
            pre[st] = cost;
        }

        for (int i = 2; i <= N; i++) {
            fill(cur.begin(), cur.end(), INF);

            for (int pst = 0; pst < 2; pst++) {
                if (pre[pst] == INF) continue;

                for (int ct = 0; ct < 2; ct ++ ) {
                    char tar = (ct == 0 ? 'S' : 'R');
                    int cost = (S[i] == tar ? 0 : -x[i]);

                    int rew = (pst == 1 && ct == 0) ? y[i - 1] : 0;

                    cur[ct] = max(cur[ct], pre[pst] + cost + rew);
                }
            }

            pre.swap(cur);
        }

        int res = 0;

        for (int i = 1; i <= 3; i ++ ) {
            res = max(res, pre[i - 1]);
        }

        int ans = max(pre[0], pre[1]);
        cout << res << " " << ans << endl;
    }

    return 0;
}