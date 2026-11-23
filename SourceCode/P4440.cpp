/*
    @ Author:       Eric / Sky__White
    @ Filename:     P4440.cpp
    @ Time:         02/24/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <unordered_map>

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

bool is_ugly(const vector<int>& q, int i) {
    int mx = q[0];
    for (int j = 1; j <= i; ++j) mx = max(mx, q[j]);
    return mx == i + 1;
}

int count_ugly(const vector<int>& q) {
    int cnt = 0;
    int mx = q[0];
    for (int i = 0; i < q.size(); ++i) {
        mx = max(mx, q[i]); 
        if (mx == i + 1) cnt++;
    }
    return cnt;
}

void solve() {
    int n; cin >> n;

    vector<int> p(n);
    for (int i = 0; i < n; ++i) cin >> p[i];

    vector<int> ugly_pos;
    int mx = p[0];
    for (int i = 0; i < n; ++i) {
        mx = max(mx, p[i]);
        if (mx == i + 1) ugly_pos.push_back(i);
    }

    if (ugly_pos.size() <= 1) {
        for (int x : p) cout << x << " ";
        cout << "\n";
        return;
    }

    int first_ugly = ugly_pos[0];
    int big_val = first_ugly + 2;
    int big_pos = -1;
    
    for (int j = first_ugly + 1; j < n; ++j) {
        if (p[j] > first_ugly + 1) {
            big_pos = j;
            break;
        }
    }

    if (big_pos != -1) {
        swap(p[first_ugly], p[big_pos]);
    } else {
        puts("-1");
        int last_ugly = ugly_pos.back();
        if (last_ugly < n - 1) {
            swap(p[last_ugly], p[last_ugly + 1]);
        } else {
            swap(p[0], p[1]);
        }
    }

    for (int x : p) cout << x << " ";
    cout << "\n";
}

signed main() {
    int t;
    cin >> t;
    while (t--) solve();
    return 0;
}