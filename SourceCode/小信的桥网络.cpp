/*
    @ Author:       Eric / Sky__White
    @ Filename:     小信的桥网络.cpp
    @ Date:         12/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <queue>
#include <deque>
#include <vector>
#include <cstdio>
#include <functional>
#include <set>

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
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int Mod = 1e9 + 7;

using PII = pair<int, int>;

void solve() {
    int n, m; fin >> n >> m;

    vector<int> arr(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i]; arr[i] %= m;
    }

    set<pair<int, int> > st;

    for (int i = 2; i <= n; i ++ )
        st.insert({arr[i], i});

    int res = 0, a = 0;

    if (n == 1) {
        cout << 0 << endl;
        return ;
    }

    vector<bool> vis(n + 1);

    priority_queue<pair<int, PII>, vector<pair<int, PII> >, greater<pair<int, PII> > > q;

    auto t1 = st.begin(), t2 = st.lower_bound({m - arr[1], 0});

    if (t2 == st.end() or (t1->first + arr[1]) % m < (t2->first + arr[1]) % m) {
        q.push({(t1->first + arr[1]) % m, {1, t1->second}});
    } else {
        q.push({(t2->first + arr[1]) % m, {1, t2->second}});
    }
    st.erase({arr[1], 1});
    
    while(q.size()) {
        // auto prin = q;
        // cout << endl;
        // while(prin.size()) {
        //     cout << prin.top().first << " " << prin.top().second.first << " " << prin.top().second.second << endl; prin.pop();
        // }
        auto t = q.top(); q.pop();
        if (vis[t.second.second]) continue;
        vis[t.second.second] = true;

        st.erase({arr[t.second.second], t.second.second});
        
        res += t.first;
        // cout << t.first << " " << t.second.first << " " << t.second.second << endl;
        
        t1 = st.begin(), t2 = st.lower_bound({m - arr[t.second.first], 0});
        
        if (st.size() == 0) continue;
        if (t2 == st.end() or (t1->first + arr[t.second.first]) % m < (t2->first + arr[t.second.first]) % m) {
            q.push({(t1->first + arr[t.second.first]) % m, {t.second.first, t1->second}});
        } else {
            q.push({(t2->first + arr[t.second.first]) % m, {t.second.first, t2->second}});
        }
            
        t1 = st.begin(), t2 = st.lower_bound({m - arr[t.second.second], 0});
        if (st.size() == 0) continue;
        if (t2 == st.end() or (t1->first + arr[t.second.second]) % m < (t2->first + arr[t.second.second]) % m) {
            q.push({(t1->first + arr[t.second.second]) % m, {t.second.second, t1->second}});
        } else {
            q.push({(t2->first + arr[t.second.second]) % m, {t.second.second, t2->second}});
        }
        // cout << res << endl << endl;
    }

    cout << res << endl;
}

signed main() {
    // freopen("net.in", "r", stdin);
    // freopen("net.out", "w", stdout);

    int T; fin >> T;

    while(T -- ) solve();

    return 0;
}