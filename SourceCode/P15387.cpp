#include <cstring>
#include <iostream>
#include <algorithm>
#include <queue>
#include <functional>
#include <cstdio>
#include <vector>
#include <utility>

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
const int Mod = 998244353;

void solve() {
    int n, m; fin >> n >> m;

    vector<int> val(n + 1);
    vector<int> fa(n + 1);
    vector<int> sz(n + 1);
    vector<int> wi(n + 1);
    vector<int> rt(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> val[i];
        fa[i] = i; sz[i] = 1; wi[i] = rt[i] = val[i];
    }

    function<void(int&, int)> add = [&](int &x, int y) {
        (x += y) %= Mod;
        if (x < 0) x += Mod;
    };

    function<void(int&, int)> mul = [&](int &x, int y) {
        x = x * y % Mod;
    };

    function<int(int, int)> qpow = [&](int base, int exp) -> int {
        int res = 1;
        while (exp > 0) {
            if (exp & 1) res = res * base % Mod;
            base = base * base % Mod;
            exp >>= 1;
        }
        return res;
    };

    function<PII(int)> find = [&](int x) -> PII {
        if (x == fa[x]) return {x, 0};
        PII tmp = find(fa[x]);
        fa[x] = tmp.first;
        add(wi[x], tmp.second);
        return {fa[x], wi[x]};
    };

    function<void(int, int, int)> merge = [&](int x, int y, int p) {
        if (x == y) return;

        if (sz[x] > sz[y]) {
            swap(x, y);
            p = (1 - p + Mod) % Mod;
        }

        sz[y] += sz[x];
        sz[x] = 0;

        int tmp1 = rt[x];
        int tmp2 = rt[y];
        int nP = (1 - p + Mod) % Mod;

        add(wi[x], p * tmp2 % Mod);
        add(wi[y], nP * tmp1 % Mod);

        fa[x] = y;
        add(wi[x], -wi[y]);

        rt[y] = (p * tmp2 % Mod + nP * tmp1 % Mod) % Mod;
        rt[x] = 0;
    };

    int ans = 0;

    for (int i = 1; i <= m; i ++ ) {
        int x, y, p; fin >> x >> y >> p;

        PII res_x = find(x);
        add(ans, res_x.second);
        add(ans, wi[res_x.first]);
        x = res_x.first;

        PII res_y = find(y);
        add(ans, res_y.second);
        add(ans, wi[res_y.first]);
        y = res_y.first;

        merge(x, y, p);
    }

    cout << ans << endl;
}

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P15387");
    #endif
    
    solve();

    return 0;
}