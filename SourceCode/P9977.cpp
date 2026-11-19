#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <ctime>
#include <deque>
#include <unordered_map>
#include <set>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

const int INF = 0x3f3f3f3f3f3f3f3f;

using PII = pair<int,int> ;

unordered_map<int,int> st;
multiset<int> q;

signed main() {
    int n, m, k; cin >> n >> m >> k;

    vector<PII> arr;

    for (int i = 1; i <= n; i ++ ) {
        int a, b; cin >> a >> b;
        arr.push_back({a, b});
    }
    sort(all(arr), greater<PII>());

    int cnt = 0;

    q.insert(INF);
    st[INF] = m;

    for (auto i : arr) {
        int b = i.first, a = i.second;
        // cout << ": " << b << " " << a << endl;

        while (a > 0 && !q.empty()) {
            auto it = q.lower_bound(b + k);
            if (it == q.end()) {
                break;
            }
            
            int t = *it;
            int av = st[t];
            
            if (a >= av) {
                cnt += av;
                a -= av;
                
                st[b] += av;
                if (st[b] == av) {
                    q.insert(b);
                }
                
                st[t] = 0;
                q.erase(it);
            } else {
                cnt += a;
                st[t] -= a;
                st[b] += a;
                if (st[b] == a) {
                    q.insert(b);
                }
                a = 0;
            }
        }
    }

    cout << cnt << endl;

    return 0;
}