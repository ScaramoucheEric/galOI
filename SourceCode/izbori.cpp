#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

struct Node {
    int cnt, id;

    bool operator <(const Node & W) {
        if (cnt != W.cnt)
            return cnt > W.cnt;
        return id < W.id;
    }
};

signed main() {
    freopen("izbori.in", "r", stdin);
    freopen("izbori.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n, m, k; cin >> n >> m >> k;

    vector<vector<int> > arr(n + 1, vector<int>(m + 1));

    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            cin >> arr[i][j];

    vector<int> st(m + 1, 0);
    vector<Node> man(m + 1);

    int res = 0x3f3f3f3f3f3f3f3f;

    for (int i = 0; i <= m; i ++ )
        man[i].id = i, man[i].cnt = 0;
    
    for (int S = 0; S < 1 << m; S ++ ) {
        for (int i = 0; i <= m; i ++ )
            man[i].cnt = 0, man[i].id = i;

        int cnt = 0;

        for (int i = 0; i < m; i ++ )
            st[i + 1] = S >> i & 1;
        for (int i = 1; i <= m; i ++ )
            if (st[i])
                cnt ++ ;
        
        for (int i = 1; i <= n; i ++ ) {
            for (int j = 1; j <= m; j ++ )
                if (!st[arr[i][j]]) {
                    man[arr[i][j]].cnt += 1;
                    break;
                }
        }

        sort(all(man));

        if (man[0].id == k) {
            res = min(res, cnt);
        }
    }

    for (int i = 0; i <= m; i ++ )
        man[i].cnt = 0, man[i].id = i;

    for (int i = 1; i <= n; i ++ )
        man[arr[i][1]].cnt ++ ;
    sort(all(man));
    
    cout << man[0].id << endl << res << endl;

    return 0;
}