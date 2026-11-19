/*
    @ Author:       Eric / Sky__White
    @ Filename:     P11233.cpp
    @ Date:         20/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <unordered_map>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

void solve() {
    int n; fin >> n;

    vector<int> a;
    a.reserve(n);
    int ans = 0;
    for (int i = 0; i < n; ++i) {
        int x; fin >> x;
        
        if (a.empty() or a.back() != x) {
            a.push_back(x);
        } else {
            ans += x;
        }
    }
    int m = (int)a.size();
    vector<int> suf(m, m);
    unordered_map<int, int> last;
    
    for (int i = m - 1; i >= 0; --i) {
        auto it = last.find(a[i]);
        if (it != last.end()) suf[i] = it->second;
        else suf[i] = m;
        last[a[i]] = i;
    }
    vector<int> f(m + 1, 0);
    for (int i = m - 1; i >= 0; --i) {
        f[i] = f[i + 1];
        if (suf[i] != m) {
            f[i] = max(f[i], f[suf[i] - 1] + a[i]);
        }
    }
    cout << ans + f[0] << endl;
}

signed main() {
    int T; fin >> T;

    while (T -- )
        solve();

    return 0;
}
