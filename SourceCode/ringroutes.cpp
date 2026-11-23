#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <set>

namespace std{
    class Read {
        public:
        template<typename T>
        inline Read & operator >> (T & x) {
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

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("ringroutes")
    #endif

    int T = 1; fin >> T;

    while(T -- )
        solve();
}

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m; fin >> n >> m;

    string str; cin >> str;
    str = " " + str;

    vector<short> st(n + 1);

    for (int i = 1; i <= n; i ++ )
        st[i] = str[i] - '0';

    int ans = 0;
    vector<int> s(m + 1), t(m + 1);

    for (int i = 1; i <= m; i ++ )
        fin >> s[i] >> t[i];

    set<vector<short> > Set;

    for (int S = 0; S < 1 << n; S ++ ) {
        vector<short> s = st;
        for (int i = 2; i <= n; i ++ )
            if ((S >> i - 1) & 1)
                s[i] ^= 1, s[i - 1] ^= 1;
        if (S & 1)
            s[1] ^= 1, s[n] ^= 1;
        vector<int> pre(n + 1);

        for (int i = 1; i <= n; i ++ )
            pre[i] = pre[i - 1] + s[i];

        int cnt = 0;

        for (int i = 1; i <= m; i ++ ) {
            int S = s[i], T = t[i];
            if (pre[T - 1] - pre[S - 1] == 0 or pre[T - 1] - pre[S - 1] == T - S) cnt ++ ;
            else if (pre[n] - pre[T - 1] + pre[S - 1] == 0 or pre[n] - pre[T - 1] + pre[S - 1] == n - (T - S)) cnt ++ ;
        }

        if (cnt == m) {
            Set.insert(s);
            // for (int i = 0; i < S; i ++ )
            //     if (S >> i & 1)
            //         cout << i + 1 << " ";
            // cout << endl;
        }
    }

    cout << Set.size() << endl;

    return ;
}