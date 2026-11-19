#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>
#include <cmath>
#include <stack>

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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P6510")
    #endif

    int T = 1;
    // fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int n; fin >> n;

    vector<int> a(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> a[i];

    stack<int> stk;

    vector<int> mi(n + 1), ma(n + 1);

    int ans = 0;

    int tn = 0, tx = 0;

    vector<int> sn(n + 1), sx(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        while (tn && a[sn[tn]] >= a[i]) tn -- ;
        while (tx && a[sx[tx]] < a[i]) tx -- ;

        int k = upper_bound(sn.begin() + 1, sn.begin() + 1 + tn, sx[tx]) - sn.begin();

        if (k != (tn + 1)) {
            ans = max(ans, i - sn[k] + 1);
        }

        sn[ ++ tn] = i;
        sx[ ++ tx] = i;
    }

    cout << ans << endl;

    return ;
}