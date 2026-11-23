#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>

#pragma GCC optimize("Ofast")
#pragma GCC optimize("O2")
#pragma GCC optimize("O3")

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
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

signed main() {
    // freopen("glove.in", "r", stdin);
    // freopen("glove.out", "w", stdout);
    int n; fin >> n;

    vector<int> a(n + 1), v(n + 1);

    for (int i = 1; i <= n; i ++ ) fin >> a[i];
    for (int i = 1; i <= n; i ++ ) fin >> v[i];

    int m; fin >> m;

    struct Query {
        int b, k, id, res;
    }; vector<Query> q(m + 1);

    int maxn = *max_element(1 + all(a)), minn = *min_element(1 + all(a));

    for (int i = 1; i <= m; i ++ ) fin >> q[i].b >> q[i].k, q[i].id = i, q[i].res = 0, maxn = max(maxn, q[i].b), minn = min(minn, q[i].b);

    // sort(1 + all(q), [&](Query a, Query b) {
    //     return a.b < b.b;
    // });

    // for (int i = 0; i <= m; i ++ )
    //     cout << q[i].b << " " << q[i].k << " " << q[i].id << " " << q[i].res << endl; 

    vector<int> pre_a(n + 1), pre_v(n + 1);

    for (int i = 1; i <= n; i ++ )
        pre_a[i] = pre_a[i - 1] + a[i],
        pre_v[i] = pre_v[i - 1] + v[i];

    for (int i = 1; i <= m; i ++ ) {
        int l = 0, r = maxn - minn, dis = -1; int L, R;

        while(l <= r) {
            int mid = l + r >> 1;
            L = lower_bound(1 + all(a), q[i].b - mid) - a.begin();
            R = upper_bound(1 + all(a), q[i].b + mid) - a.begin() - 1;

            // cout << l << " " << r << " " << L << " " << R << endl;
            if (L > R or L == n + 1) l = mid + 1;
            else if (R - L + 1 < q[i].k) {
                l = mid + 1;
            } else if (R - L + 1 == q[i].k) {
                dis = mid;
                break;
            } else if (R - L + 1 == q[i].k + 1 and abs(a[L] - q[i].b) == abs(a[R] - q[i].b)) {
                dis = mid;
                R -- ;
                break;
            } else if (R - L + 1 > q[i].k) {
                r = mid - 1;
                // cout << "Turn left: " << R - L + 1 << " " << q[i].k << endl;
            }
        }

        // for (int j = L; j <= R; j ++ ) {
        //     q[i].res += v[j] - abs(a[j] - q[i].b);
        // }

        int mid = lower_bound(1 + all(a), q[i].b) - a.begin();

        if (mid > R or mid == R and a[mid] == q[i].b)
            q[i].res = pre_v[R] - pre_v[L - 1] - (q[i].b * (R - L + 1) - (pre_a[R] - pre_a[L - 1]));
        else if (mid <= L)
            q[i].res = pre_v[R] - pre_v[L - 1] - ((pre_a[R] - pre_a[L - 1]) - q[i].b * (R - L + 1));
        else
            q[i].res = pre_v[R] - pre_v[L - 1] - ((pre_a[R] - pre_a[mid - 1]) - (q[i].b * (R - mid + 1)) + (q[i].b * (mid - 1 - L + 1)) - (pre_a[mid - 1] - pre_a[L - 1]));

        // cout << L << " " << R << " " << dis << " " << endl;
    }

    // sort(1 + all(q), [&](Query a, Query b) {
    //     return a.id < b.id;
    // });

    for (int i = 1; i <= m; i ++ )
        printf("%lld\n", q[i].res);
}