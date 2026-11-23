#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <queue>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using PII = pair<int, int>;

signed main() {
    int k; cin >> k;

    vector<priority_queue<PII> > q(k + 1);

    for (int i = 1; i <= k; i ++ ) {
        int n; cin >> n;
        for (int j = 1; j <= n; j ++ ) {
            int x; cin >> x;
            q[i].push({x, i});
        }
    }

    // for (int i = 1; i <= k; i ++ )
    //     cout << q[i].size() << " ";

    vector<bool> st(k + 1, false);

    while(true) {
        for (int i = 1; i <= k; i ++ ) {
            if (st[i]) continue;
            if (q[i].empty()) continue;
            q[0].push(q[i].top());
            q[i].pop();
            st[i] = true;
        }
        // cout << q[0].size() << endl;
        if (q[0].size() <= 2) break;
        if(q[0].size() >= 3) {
            vector<PII> vec;
            vec.push_back(q[0].top()); q[0].pop();
            vec.push_back(q[0].top()); q[0].pop();
            vec.push_back(q[0].top()); q[0].pop();

            sort(all(vec));

            if (vec[0].first + vec[1].first > vec[2].first) {
                for (int i = 0; i < 3; i ++ )
                    cout << vec[i].second << " " << vec[i].first << " ";
                cout << endl;
                return 0;
            }

            for (int i = 0; i < 2; i ++ )
                q[0].push(vec[i]);
            st[vec[2].second] = false;
            // for (int i = 0; i <= 2; i ++ )
            //     cout << vec[i].first << " " << vec[i].second << endl;
            // cout << endl;
        }
    }

    cout << "NIE" << endl;

    return 0;
}