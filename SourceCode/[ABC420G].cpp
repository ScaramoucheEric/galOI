/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC420G].cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>

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
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

using INT = __int128;

signed main() {
    int x; fin >> x;

    int T = 4 * x - 1;
    int absT = (T >= 0) ? T : -T;

    vector<int> gg;
    for (int d = 1; d * d <= absT; ++d) {
        if (absT % d == 0) {
            gg.push_back(d);
            gg.push_back(-d);
            if (d != absT / d) {
                gg.push_back(absT / d);
                gg.push_back(-(absT / d));
            }
        }
    }

    auto mod4 = [](int v) -> int { return (int)(((v % 4) + 4) % 4); };

    set<int> ans;
    for (int a : gg) {
        int b = T / a;
        int s = a + b;
        int dff = a - b;

        if (s < 0) continue;
        if (mod4(s) != 0) continue;
        if (mod4(dff) != 2) continue;

        int m = s / 4;
        int n = (dff - 2) / 4;

        INT L = (INT)m * m;
        INT R = (INT)n * n + n + x;
        if (L != R) continue;

        ans.insert(n);
    }

    cout << ans.size() << "\n";
    
    for (int n : ans) {
        cout << n << " ";
    }
    cout << endl;

    return 0;
}