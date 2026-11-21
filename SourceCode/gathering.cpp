#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <ctime>

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
    IO("gathering")
    #endif

    int T = 1; fin >> T;

    while(T -- ) solve();

    // cout << clock() * 1.0 / CLOCKS_PER_SEC << endl;
}

void solve() {
    int n, r; fin >> n >> r;

    vector<vector<int> > G(n + 1);

    vector<int> L(n + 1), U(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> L[i] >> U[i];

    for (int i = 1; i < n; i ++ ) {
        int u, v; fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
        // cout << u << " " << v << endl;
    }
    // cout << endl;

    if (n <= 5) {
        vector<int> arr(n + 1);
        vector<int> ans(n + 1), temp(n + 1);

        int res = -1, res_cnt;
        int cnt = 0;

        function<bool(int, int)> check = [&](int u, int fa) -> bool {
            vector<int> opt;
            for (auto v : G[u]) {
                if (v == fa) continue;
                if (!check(v, u)) { return false; }
                opt.push_back(arr[v]);
            }

            sort(all(opt));

            for (int i : opt) {
                if (i > arr[u]) return false;
                arr[u] += i;
                if (i)
                    cnt ++ ;
            }

            return true;
        };

        for (int S = 0; S < 1 << n; S ++ ) {
            int sum = 0; cnt = 0;
            for (int i = 1; i <= n; i ++ ) {
                arr[i] = (S >> i - 1) & 1 ? L[i] : U[i];
                temp[i] = arr[i];
                sum += arr[i];
            }

            if (check(r, r)) {
                if (sum > res) {
                    sum = res;
                    ans = temp;
                    res_cnt = cnt;
                }
            }
        }

        function<void(int, int)> print = [&](int u, int fa) -> void {
            vector<int> opt;
            for (auto v : G[u]) {
                if (v == fa) continue;
                print(v, u);
                opt.push_back(v);
            }

            sort(all(opt), [&](int a, int b) {
                return ans[a] < ans[b];
            });

            for (int i : opt) {
                if (ans[i])
                    cout << i << " " << u << endl, ans[u] += ans[i];
            }
        };

        if (~res) {
            cout << "YES" << endl;
            cout << res << endl;

            for (auto i : ans)
                cout << i << " ";
            cout << endl;

            print(r, r);

            cout << res_cnt << endl;
        } else {
            puts("NO");
        }
    } else if ([&]() -> bool {
        for (int i = 1; i <= n; i ++ )
            if (L[i] != U[i]) {
                cout << i << endl;
                return false;
            }
        return true;
    }()){
        vector<int> arr(n + 1), temp(n + 1);

        int cnt = 0, sum = 0;

        function<bool(int, int)> check = [&](int u, int fa) -> bool {
            vector<int> opt;
            // cout << u << " " << fa << endl;
            for (auto v : G[u]) {
                if (v == fa) continue;
                if (!check(v, u)) { return false; }
                opt.push_back(arr[v]);
            }

            sort(all(opt));

            for (int i : opt) {
                if (i > arr[u]) return false;
                arr[u] += i;
                if (i)
                    cnt ++ ;
            }

            return true;
        };

        for (int i = 1; i <= n; i ++ )
            arr[i] = temp[i] = L[i], sum += arr[i];

        function<void(int, int)> print = [&](int u, int fa) -> void {
            vector<int> opt;
            for (auto v : G[u]) {
                if (v == fa) continue;
                print(v, u);
                opt.push_back(v);
            }

            sort(all(opt), [&](int a, int b) {
                return arr[a] < arr[b];
            });

            for (int i : opt) {
                if (arr[i])
                    cout << i << " " << u << endl, arr[u] += arr[i];
            }
        };

        if (check(r, r)) {
            puts("YES");
            cout << sum << endl;

            for (int i = 1; i <= n; i ++ )
                cout << temp[i] << " ";
            cout << endl;

            print(r, r);

            cout << cnt << endl;
        } else {
            puts("NO");
        }
    } else {
        puts("NO");
    }
}