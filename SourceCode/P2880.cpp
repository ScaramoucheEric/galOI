#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n, q; cin >> n >> q;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i ++ )
        cin >> arr[i];
    
    vector<vector<int> > st1(n + 1, vector<int>(32, 0)), st2(n + 1, vector<int>(32, 0x3f3f3f3f3f3f3f3f));

    for (int i = 1; i <= n; i ++ )
        st1[i][0] = arr[i], st2[i][0] = arr[i];

    for (int j = 1; 1 << j <= n; j ++ ) {
        for (int i = 1; i + (1 << j) - 1 <= n; i ++ ) {
            st1[i][j] = max(st1[i][j - 1], st1[i + (1 << j - 1)][j - 1]);
            st2[i][j] = min(st2[i][j - 1], st2[i + (1 << j - 1)][j - 1]);
        }
    }

    while(q -- ) {
        int l, r; cin >> l >> r;

        int len = r - l + 1;
        len = log2(len);
        
        int m1, m2;
        m1 = max(st1[l][len], st1[r - (1 << len) + 1][len]);
        m2 = min(st2[l][len], st2[r - (1 << len) + 1][len]);

        cout << m1 - m2 << endl;
    }

    return 0;
}