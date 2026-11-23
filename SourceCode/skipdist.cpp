#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

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
    IO("skipdist")
    #endif

    int T = 1; fin >> T;

    while(T -- ) solve();
}

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i];

    if (n == 4) {
        if (arr[1] != arr[3] or arr[2] != arr[4]) {
            puts("-1");
        } else {
            int A, B, C, D;
            int a = arr[2], b = arr[3];
            B = 1;
            A = b - B; C = a - B;
            D = abs(a - b) + B;

            cout << A + B + C + D << endl;

            cout << A << " " << B << " " << C << " " << D << endl;
        }
    } else {
        vector<int> cur(n + 1);

        vector<int> presum(n + 1);

        function<bool()> judge = [&]() -> bool {
            for (int i = 1; i <= n; i ++ ) {
                if (i < n) if (min(cur[i] + cur[i + 1], presum[i - 1] + presum[n] - presum[i + 1]) != arr[i]) return false;
                if (i == n) if (min(cur[n] + cur[1], presum[n - 1] - cur[1]) != arr[n]) return false;
            }
            return true;
        };

        int res = INF;
        vector<int> ans;

        function<void(int)> dfs = [&](int u) {
            if (u == n + 1) {
                if (judge()) {
                    if (res > presum[n]) {
                        ans = cur;
                        res = presum[n];
                    }
                }
                return ;
            }

                        // for (int i = 1; i <= n; i ++ )
                        //     cout << cur[i] << " ";
                        // cout << endl;
                        // for (int i = 1; i <= n; i ++ )
                        //     cout << presum[i] << " ";
                        // cout << endl endl;
            
            for (int i = 1; i <= 6; i ++ ) {
                cur[u] = i;
                presum[u] = presum[u - 1] + cur[u];

                if (u > 1 and presum[u - 2] > arr[u - 1] and cur[u - 1] + cur[u] != arr[u - 1]) continue;
                if (u > 1 and cur[u - 1] + cur[u] < arr[u - 1]) continue;

                dfs(u + 1);
            }
        };

        dfs(1);

        if (res < INF / 2) {
            cout << res << endl;
            for (int i = 1; i <= n; i ++ )
                cout << ans[i] << " ";
            cout << endl;
        } else {
            cout << -1 << endl;
        }
    }
}