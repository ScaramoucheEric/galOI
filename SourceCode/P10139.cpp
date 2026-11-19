#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <functional>
#include <ctime>
#include <vector>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

void solve() {
    int n; cin >> n;

    vector<int> arr(n + 1);
    
    for (int i = 1; i <= n; i ++ )
        cin >> arr[i];

    sort(1 + all(arr));

    int l = 1, r = n, mid;

    int res = 0x3f3f3f3f3f3f3f3f;

    function<int(int)> judge = [&](int x) -> int {
        int tim = 0, re = 0;

        for (int i = 1; i <= n; i ++ ) {
            if (n - i + 1 == x)
                tim += x, re = tim, x -- /*, printf("1 %lld %lld %lld\n", tim, re, x)*/;
            else if (arr[i] < x + tim or x == 0) {
                re = arr[i]/*, printf("2 %lld %lld %lld\n", tim, re, x)*/;
            } else {
                tim += x;
                re = tim;
                x -- ;
                // printf("3 %lld %lld %lld\n", tim, re, x);
            }
            // printf("%lld %lld %lld\n", i, re, x);
        }

        // printf("\n\n");
        res = min (res, re);
        return re;
    };

    while(l < r) {
        mid = l + r >> 1;

        int t = judge(mid);
        int t1 = 0x3f3f3f3f3f3f3f3f;
        int t2 = 0x3f3f3f3f3f3f3f3f;
        if (mid - 1 > 0) t1 = judge(mid - 1);
        if (mid + 1 <= n) t2 = judge(mid + 1);

        // printf("l = %lld; r = %lld; mid = %lld\njudge(mid) = %lld; judge(mid + 1) = %lld; judge(mid - 1) = %lld\n\n", l, r, mid, t, t1, t2);

        if (t1 < t) r = mid - 1;
        else if (t2 < t) l = mid + 1;
        else if (t1 == t2) l = mid + 1;
        else break;
    }

    cout << res << endl;

    return ;
}

signed main() {
    // freopen("nap.in", "r", stdin);
    // freopen("nap.out", "w", stdout);

    ios::sync_with_stdio(false);
    cin.tie(0);

    int T; cin >> T;
    while(T -- ) {
        solve();
    }

    return 0;
}