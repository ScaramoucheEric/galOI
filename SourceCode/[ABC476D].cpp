#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()
#define endl '\n'
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)

signed main(){
    #ifndef ONLINE_JUDGE
        IO("abc476d");
    #endif

    int n, m, k, x, y;
    cin >> n >> m >> k >> x >> y;
    
    vector<int> a(n), b(m);
    for (auto &i : a) cin >> i;
    for (auto &i : b) cin >> i;
    
    sort(all(a));
    sort(all(b));
    
    vector<int> sa(n + 1), sb(m + 1);
    for (int i = 0; i < n; i++) sa[i + 1] = sa[i] + a[i];
    for (int i = 0; i < m; i++) sb[i + 1] = sb[i] + b[i];
    
    int ans = 0;
    for (int j = 0; j <= m; j++) {
        if (sb[j] > y) break;

        int ones = x + (y - sb[j]) * k;

        for (int i = 0; i <= n; i ++ ) {
            if (sa[i] > ones) break;
            if (i > 0) ones -= a[i - 1];
        }

        
        int lo = 0, hi = n;
        while (lo < hi) {
            int mid = (lo + hi + 1) / 2;
            if (sa[mid] <= ones) lo = mid;
            else hi = mid - 1;
        }
        ans = max(ans, j + lo);
    }
    
    cout << ans << "\n";
    
    return 0;
}