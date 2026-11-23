#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>
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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)

using namespace std; Read fin;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P17746");
    #endif

    int n, k; fin >> n >> k;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    for (int i = 1; i <= n; i ++ ) {
        int x; fin >> x;
        arr[i] = x - arr[i];
        if (arr[i] < 0) {
            puts("-1");
            return 0;
        }
    }

    queue<int> q;

    int cnt = 0, cur = 0;

    vector<int> opt(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        while(q.size() and i - q.front() + 1 > k)
            cur -= opt[q.front()], opt[q.front()] = 0, q.pop();
        if (cur < arr[i]) {
            opt[i] = arr[i] - cur;
            cnt += arr[i] - cur;
            cur = arr[i];
            q.push(i);
        }
        if (cur > arr[i]) {
            int tt = cur - arr[i];
            while(q.size() and tt) {
                tt -= opt[q.front()];
                opt[q.front()] = 0;
                if (tt < 0) {
                    opt[q.front()] -= tt;
                    tt = 0;
                    break;
                }
                q.pop();
            }
            cur = arr[i];
        }
    }

    cout << cnt << endl;
}