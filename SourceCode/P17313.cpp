#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
#include <map>
#include <vector>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

using namespace std; Read fin;

using PII = pair<int, int> ;

const int INF = 0x3f3f3f3f3f3f3f3f;
#undef int

using LL = long long;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17313");
    #endif

    int n, m, p, q; LL t; fin >> n >> m >> p >> q >> t;

    vector<int> c(n + 1); vector<vector<int> > w(n + 1);

    vector<int> to_i(m + 1), to_j(m + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> c[i];
        w[i].reserve(c[i] + 1);
        w[i].push_back(0);

        for (int j = 1, x; j <= c[i]; j ++ )
            fin >> x, w[i].push_back(x), to_i[x] = i, to_j[x] = j;
    }

    int L; fin >> L;

    vector<int> str(L + 1);

    for (int i = 1; i <= L; i ++ )
        fin >> str[i];

    vector<vector<LL> > dp(L + 1, vector<LL>(60, INF));

    dp[0][0] = 0;
    
    for (int i = 1; i <= L; i ++ ) {
        int ii = to_i[str[i]], jj = to_j[str[i]];
        for (int j = 0; j < 60; j ++ ) {
            for (int from = 0; from < 60; from ++ ) {
                int dist = (j >= from) ? (j - from) : (60 + j - from);
                int cur = j % c[ii] + 1;

                if (jj == cur) dp[i][j] = min(dp[i][j], dp[i - 1][from] + dist * t + p);
                else dp[i][j] = min(dp[i][j], dp[i - 1][from] + dist * t + abs(jj - cur) + q);
            }
        }
    }

    LL res = INF;

    for (int i = 0; i < 60; i ++ )
        res = min(res, dp[L][i]);

    cout << res << endl;
}