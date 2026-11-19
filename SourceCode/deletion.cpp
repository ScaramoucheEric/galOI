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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

void solve();

signed main() {
    #ifndef ONLINE_JUDGE
    IO("deletion")
    #endif

    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}

void solve() {
    int n, m; fin >> n >> m;

    vector<int> arr, a(n + 1), b(m + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> a[i];

    for (int i = 1; i <= m; i ++ )
        fin >> b[i];

    if (m == 0) {
        puts("YES");
        return ;
    }

    int t = *min_element(1 + all(b));

    for (int i = 1; i <= n; i ++ )
        if (a[i] >= t)
            arr.push_back(a[i]);

    int pos = arr.size() - 1;

    for (int i = m; i; i -- , pos -- ) {
        if (pos < 0) {
            puts("NO");
            return ;
        }
        if (b[i] != arr[pos]) {
            if (arr[pos] == t) {
                i ++ ;
                continue;
            }

            puts("NO");
            return ;
        }
    }
    a.clear();
    for (int i = 0; i <= pos; i ++ )
        if (arr[i] > t)
            a.push_back(arr[i]);

    // cout << a.size() << endl;

    // cout << "arr: ";
    // for (int i = 0; i < arr.size(); i ++ )
    //     cout << arr[i] << " ";
    // cout << endl;
    // cout << "a: ";   
    // for (int i = 0; i < a.size(); i ++ )
    //     cout << a[i] << " ";

    // cout << endl << t << endl;
    
    if (a.size() & 1) {
        puts("NO");
        return ;
    }

    for (int i = 0; i < a.size(); i ++ )
        if (a[i] != a[i + 1]) {
            puts("NO");
            return ;
        }

    puts("YES");

    return ;
}