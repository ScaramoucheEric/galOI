#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <map>
#include <functional>
#include <queue>

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

using PII = pair<int, int>;
const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m; fin >> n >> m;

    vector<int> fa(n + 1), arr(n + 1);

    for (int i = 1; i <= n; i ++ ) fa[i] = i;

    function<int(int)> find = [&](int x) {
        if (fa[x] == x) return x;
        
        int fafa = find(fa[x]);
        arr[x] += arr[fa[x]];
        return fa[x] = fafa;
    };

    bool flag = true;

    for (int i = 1; i <= m; i ++ ) {
        int l, r, w; fin >> l >> r >> w;
        l -- ;
        if (flag) {
            if (find(l) != find(r)) {
                arr[find(r)] = arr[l] - arr[r] - w;
                fa[fa[r]] = fa[l];
            } else if (w != arr[l] - arr[r]) {
                puts("false"); flag = false;
            }
        }
    }
    if (flag)
        puts("true");

    return ;
}

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P2294");
    #endif

    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}