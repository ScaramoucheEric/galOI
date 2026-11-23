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
    IO("rangewrite")
    #endif

    int T = 1; fin >> T;

    while(T -- ) solve();
}

void solve() {
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i];
    
    if (n == 1) {
        cout << 0 << endl;
        return ;
    }

    int mi = *min_element(1 + all(arr)), ma = *max_element(1 + all(arr));

    int res = 0;

    res = max((ma - mi) * (n - 1) + (ma - (ma - mi)), res);
    int mii = ma - mi;
    res = max(mii + (ma - mii) * (n - 1), res);
    res = max(res, (ma - mi) * (n - 1) + (ma - mi - mi));

    cout << res << endl;
}