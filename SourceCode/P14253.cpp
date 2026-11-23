#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <unordered_map>

#define int long long
#define all(a) a.begin(), a.end()

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
    } fin;
}

using namespace std;

void solve() {
    int n; fin >> n; vector<int> arr(n + 1), presum(n + 1, 0);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i];
    
    for (int i = 1; i <= n; i ++ )
        presum[i] = presum[i - 1] + arr[i];

    unordered_map<int, int> cnt;

    for (int i = 0; i <= n; i ++ )
        cnt[presum[i]] ++ ;

    int res = 0;

    for (auto [a, b] : cnt) {
        res = max(res, b - 1);
    }

    cout << res << endl;

    for (int i = 1; i <= n; i ++ )
        cout << res << endl;
    for (auto [a, b] : cnt)
        cout << a << " " << b << endl;

    return ;
}

#undef int
#define Find

#ifdef Find
#endif

signed main() {
    int T; fin >> T;
    while(T -- ) {
        solve();
    }

    return 0;
}