#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
#include <queue>
#include <map>
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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("two")
    #endif

    int T = 1; fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int n; fin >> n;

    vector<int> a(n + 1), b(n + 1);
    
    for (int i = 1; i <= n; i ++ )
        fin >> a[i];
    for (int i = 1; i <= n; i ++ )
        fin >> b[i];

    if ((*max_element(all(a))) <= 2) {
        for (int i = 1; i <= n; i ++ ) {
            if (a[i] == b[i]) continue;
            if (a[i] - b[i] == 2) {
                a[i + 1] ++ ;
                a[i] -- ;
            } else if (b[i] - a[i] == 2) {
                a[i + 1] -- ;
                a[i] ++ ;
            } else {
                puts("-1");
                return ;
            }
            cnt ++ ;
        }

        cout << cnt << endl;
    } else {
        int cnta = 0, cntb = 0;
        for (int i = 1; i <= n; i ++ ) {
            cnta += a[i];
            cntb += b[i];
        }

        if (cnta != cntb) {
            puts("-1");
            return ;
        }

        int res = 0x3f3f3f3f3f3f3f3f;
        int cnt = 0;
        
        function<void()> dfs = [&]() -> void {
            for (int i = 1; i <= n; i ++ ) {
                if (a[i] - a[i + 1] >= 2 and a[i] > b[i]) {
                    a[i] -- ;
                    cnt ++ ;
                    dfs();
                    a[i + 1] ++ ;
                    cnt -- ;
                }
                if (a[i] - a[i - 1] >= 2 and a[i] > b[i]) {
                    a[i] -- ;
                    cnt ++ ;
                    dfs();
                    a[i - 1] ++ ;
                    cnt -- ;
                }

                if (i == n) {
                    if (a == b) {
                        res = min(res, cnt);
                    }
                }
            }
        };

        dfs();

        if (res >= 0x3f3f3f3f3f3f3f3f / 2) cout << -1 << endl;
        else cout << res << endl;
    }
}