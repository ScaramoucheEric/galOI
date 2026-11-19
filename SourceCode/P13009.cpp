/*
    @ Author:       Eric / Sky__White
    @ Filename:     solution.cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

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

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n, m; fin >> n >> m;

    int sum = 0;
    vector<int> f({0, INF, INF});

    for (int i = 0; i < n; i ++ ) {
        int a; fin >> a;
        int v0 = a, v1 = m / a, v2 = m / v1, M = max({v0, v1, v2});

        sum += M;
        
        bool ok[3] = {v0 == M, v1 == M, v2 == M};
        
        vector<int> nf({INF, INF, INF});
        
        for (int j = 0; j < 3; j ++ ) {
            if (!ok[j]) continue;

            for (int j0 = 0; j0 < 3; j0 ++ ) {
                if (f[j0] >= INF) continue;

                int val = f[j0] + (j > j0 ? j - j0 : 0);
                if (val < nf[j]) nf[j] = val;
            }
        }
        f = nf;
    }

    int ans = *min_element(all(f));
    cout << sum << " " << ans << endl;
}

signed main() {
    int T; fin >> T;

    while (T -- ) solve();
    return 0;
}