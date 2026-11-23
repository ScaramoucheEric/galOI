#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <queue>
#include <cstdio>
#include <map>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read& operator >> (T & x) {
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
    IO("xorrelay")
    #endif

    int T = 1;
    fin >> T;

    while(T -- ) {
        solve();
    }
}

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve() {
    int n; fin >> n;

    vector<int> arr(n);

    for (int i = 0; i < n; i ++ )
        fin >> arr[i];

    if (n <= 9) {
        int res = 0;
        do {
            int ans = INF;

            for (int i = 1; i < n; i ++ )
                ans = min(ans, arr[i - 1] ^ arr[i]);

            res = max(res, ans);
        } while(next_permutation(all(arr)));

        cout << res << endl;
    } else {
        map<int, int> cnt; int res = 0;

        for (int i = 1; i <= n; i ++ )
            cnt[arr[i - 1]] ++ ;
        
        // for (auto i : cnt) {
        //     cout << i.first << " " << i.second << endl;
        // }

        sort(all(arr));
        arr.erase(unique(all(arr)), arr.end());

        if (arr.size() == 1) {
            cout << 0 << endl;
        } else if (arr.size() == 2) {
            if (abs(cnt[arr[0]] - cnt[arr[1]]) <= 1) {
                cout << (arr[0] ^ arr[1]) << endl;
            } else {
                cout << 0 << endl;
            }
        } else { // arr.size() == 3
            for (int i = 0; i < 3; i ++ )
                for (int j = i + 1; j < 3; j ++ ) {
                    // cout << arr[i] << " ^ " << arr[j] << " = " << (arr[i] ^ arr[j]) << endl;
                }
            for (int i = 0; i < 3; i ++ ) {
                for (int j = i + 1; j < 3; j ++ ) {
                    int k = 3 - i - j;
                    if (cnt[arr[i]] + cnt[arr[j]] < cnt[arr[k]] - 1) {
                        cout << 0 << endl;
                        return ;
                    } else if (abs(cnt[arr[i]] + cnt[arr[j]] - cnt[arr[k]]) <= 1) {
                        // cout << arr[i] << " " << arr[j] << " " << arr[k] << endl;
                        res = max(res, min(arr[i] ^ arr[k], arr[j] ^ arr[k]));
                    } else {
                        res = max(res, min({arr[i] ^ arr[j], arr[j] ^ arr[k], arr[i] ^ arr[k]}));
                    }
                }
            }

            cout << res << endl;

            return;
        }
    }
}