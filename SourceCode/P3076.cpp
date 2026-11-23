#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

signed main() {
    int n, m; cin >> n >> m;

    int ans = 0;
    vector<int> s(n + 1), t = s;
    s[0] = m, t[0] = 0;

    for (int i = 1; i <= n; i ++ ) {
        cin >> s[i] >> t[i];
        ans += abs(s[i] - t[i]);
    }

    sort(all(s));
    sort(all(t));

    for (int i = 0; i <= n; i ++ ) {
        ans += abs(s[i] - t[i]);
    }

    cout << ans << endl;

    return 0;
}