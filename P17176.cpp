#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
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

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17176");
    #endif
    int n, m; fin >> n >> m;

    vector<vector<PII> > G((n + 2) * (n + 1));

    function<int(int, int)> id = [&](int a, int b) {
        return a * (n + 1) + b;
    };

    struct Node {
        int u, v, w;
    };

    vector<Node> e(m + 1);

    for (int i = 1; i <= m; i ++ ) {
        int u, v, w; fin >> u >> v >> w; e[i] = {u, v, w};
    }

    vector<vector<int> > dp(n + 1, vector<int>(n + 1, INF));

	dp[0][1] = 0;
	for(int i = 1; i <= (n / 2 - 1); i ++ ) {
		for(int j = 1; j <= m;j++){
			int u = e[j].u, v = e[j].v, w = e[j].w;
			dp[i][v] = min(dp[i][v], dp[i - 1][u] + w);
		}
	}
	int ans = INF;

	for(int i = 1; i <= (n / 2 - 1); i ++ )
        ans = min(ans, dp[i][n]);
	if(ans > INF / 2) cout << -1 << endl;
	else cout << ans << endl;
}