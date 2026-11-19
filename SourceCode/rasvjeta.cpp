#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    // freopen("rasvjeta.in", "r", stdin);
    // freopen("rasvjeta.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;

    vector<int> pre(n + 2, 0);

    for (int i = 1; i <= m; i ++ ) {
        int a; cin >> a;
        pre[max(a - k, 0ll)] += 1;
        pre[min(a + k + 1, n + 1)] -= 1;
    }

    for (int i = 1; i <= n + 1; i ++ )
        pre[i] += pre[i - 1];

    vector<int> node;
    
    // for (int i = 1; i <= n; i ++ )
    //     cout << pre[i] << " ";
    // cout << endl;

    int cnt = 0;

    for (int i = 1; i <= n; i ++ ) {
        if (pre[i] == 0) {
            // cout << i << endl;
            for (int j = 0; i + j <= min(n, 2 * k + i); j ++ )
                pre[j + i] ++ ;
            i += 2 *;
            
            // for (int i = 1; i <= n; i ++ )
            //     cout << pre[i] << " ";
            // cout << endl;
            cnt ++ ;
        }
    }

    cout << cnt << endl;

    // for (int i = 1; i <= n; i ++ )
    //     cout << pre[i] << " ";
    // cout << endl;

    return 0;
}