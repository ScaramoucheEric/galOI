#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <queue>
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

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, m; fin >> n >> m;

    vector<int> W(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> W[i];
    }

    vector<vector<int> > G(n + 1);

    for (int i = 1; i <= m; i ++ ) {
        int a, b; fin >> a >> b;
        G[a].push_back(b); G[b].push_back(a);
    }

    vector<vector<int> > dp(n + 1, vector<int>(n + 1, INF));

    for (int i = 0; i <= n; i ++ ) dp[1][i] = i * W[1];

    for (int i = n; i ; i -- ) for (int u = 1; u <= n; u ++ ) for (auto v : G[u]) {
        dp[v][i - 1] = min(dp[v][i - 1], dp[u][i] + W[v] * (i - 1));
    }

    for (int i = 1; i <= n; i ++ )
        cout << dp[i][0] << endl;
}