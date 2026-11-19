
/*
    @ Author:       Eric / Sky__White
    @ Filename:     冰场折返.cpp
    @ Date:         14/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <unordered_map>
#include <queue>
#include <map>
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

const int INF = 0x3f3f3f3f3f3f3f3f;

using PII = pair<int, int>;

void solve() {
    int H, W, n; fin >> H >> W >> n;

    PII s, t; fin >> s.first >> s.second >> t.first >> t.second;

    vector<PII> pos(n + 1);
    for (int i = 1; i <= n; i ++ ) {
        fin >> pos[i].first >> pos[i].second;
    }

    // vector<int> lsh;
    // unordered_map<int, int> lss_R, lss_C;

    // lsh.push_back(s.first - 1); lsh.push_back(s.first); lsh.push_back(s.first + 1);
    // lsh.push_back(t.first - 1); lsh.push_back(t.first); lsh.push_back(t.first + 1);
    // for (int i = 1; i <= n; i ++ ) lsh.push_back(pos[i].first), lsh.push_back(pos[i].first + 1), lsh.push_back(pos[i].first - 1);
    // sort(all(lsh));
    // lsh.erase(unique(all(lsh)), lsh.end());

    // for (int i = 0; i < lsh.size(); i ++ )
    //     lss_R[lsh[i]] = i + 1;

    // t.first = lss_R[t.first], s.first = lss_R[s.first];

    // for (int i = 1; i <= n; i ++ )
    //     pos[i].first = lss_R[pos[i].first];

    // lsh.clear();

    // lsh.push_back(s.second - 1); lsh.push_back(s.second); lsh.push_back(s.second + 1);
    // lsh.push_back(t.second - 1); lsh.push_back(t.second); lsh.push_back(t.second + 1);
    // for (int i = 1; i <= n; i ++ ) lsh.push_back(pos[i].second), lsh.push_back(pos[i].second + 1), lsh.push_back(pos[i].second - 1);
    // sort(all(lsh));
    // lsh.erase(unique(all(lsh)), lsh.end());

    // for (int i = 0; i < lsh.size(); i ++ )
    //     lss_C[lsh[i]] = i + 1;

    // t.second = lss_C[t.second], s.second = lss_C[s.second];

    // for (int i = 1; i <= n; i ++ )
    //     pos[i].second = lss_C[pos[i].second]; 

    // 离散化不需要

    unordered_map<int, set<int> > R, C;

    for (int i = 1; i <= n; i ++ ) {
        R[pos[i].first].insert(pos[i].second);
        C[pos[i].second].insert(pos[i].first);
    }

    queue<pair<int, PII> > q;
    map<PII, bool> st;

    q.push({0, s});

    while(q.size()) {
        auto tt = q.front(); q.pop();
        int step = tt.first, x = tt.second.first, y = tt.second.second;

        // cout << step << " " << x << " " << y << endl;

        if (PII{x, y} == t) {
            cout << step << endl;
            return ;
        }

        int nx, ny;

        nx = x;
        auto t = R[x].lower_bound(y);
        if (t != R[x].end()) {
            ny = *t - 1;
            if (st.count({nx, ny}) == 0) {
                st[{nx, ny}] = true;
                q.push({step + 1, {nx, ny}});
            }
        }

        nx = x;
        t = R[x].lower_bound(y);
        if (t != R[x].begin()) {
            ny = *prev(t) + 1;
            if (st.count({nx, ny}) == 0) {
                st[{nx, ny}] = true;
                q.push({step + 1, {nx, ny}});
            }
        }

        ny = y;
        t = C[y].lower_bound(x);
        if (t != C[y].end()) {
            nx = *t - 1;
            if (st.count({nx, ny}) == 0) {
                st[{nx, ny}] = true;
                q.push({step + 1, {nx, ny}});
            }
        }

        ny = y;
        t = C[y].lower_bound(x);
        if (t != C[y].begin()) {
            nx = *prev(t) + 1;
            if (st.count({nx, ny}) == 0) {
                st[{nx, ny}] = true;
                q.push({step + 1, {nx, ny}});
            }
        }
    }

    cout << -1 << endl;
}

signed main() {
    solve();
}