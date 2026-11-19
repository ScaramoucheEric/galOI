#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

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

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17830");
    #endif

    int n, m; fin >> n >> m;
    vector<int> last(m + 1), arr(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
        last[arr[i]] = max(last[arr[i]], i);
    }
    vector<vector<int> > G(n + 2);

    for (int i = 1; i <= n; i ++ ) {
        G[last[arr[i]] == i ? i + 1 : last[arr[i]] + 1].push_back(i);
    }

    vector<int> siz(n + 2);

    function<void(int)> dfs = [&](int u) -> void {
        siz[u] = 1;

        for (auto v : G[u]) {
            dfs(v);
            siz[u] += siz[v];
        }
    };

    dfs(n + 1);

    vector<int> cnt(m + 1);
    for (int i = 1; i <= n; i ++ ) {
        cnt[arr[i]] += siz[i];
    }

    for (int i = 1; i <= m; i ++ )
        cout << cnt[i] << " ";
    cout << endl;
}