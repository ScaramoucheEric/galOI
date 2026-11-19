/*
    @ Author:       Eric / Sky__White
    @ Filename:     gene.cpp
    @ Date:         19/07/2026
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
#define uint unsigned long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int Mod = 1e9 + 7;

signed main() {
    // freopen("gene.in", "r", stdin);
    // freopen("gene.out", "w", stdout);

    int n; fin >> n; string str; cin >> str; str = ' ' + str;

    const uint base = 131;
    vector<uint> h(n + 1), p(n + 1);
    p[0] = 1;
    for (int i = 1; i <= n; i ++ ) (p[i] = p[i - 1] * base) %= Mod;
    for (int i = 1; i <= n; i ++ ) (h[i] = h[i - 1] * base + (uint)(str[i] - 'a' + 1)) %= Mod;

    auto get = [&](int l, int r) -> uint {
        if (l > r) return 0;
        return (h[r] - (h[l - 1] * p[r - l + 1]) % Mod + Mod) % Mod;
    };

    function<int(int, int)> calc_f = [&](int i, int start) -> int {
        for (int f = start; f >= 0; f -- ) {
            if (get(i + 1, i + f) == get(n - i - f + 1, n - i))
                return f;
        }
        return 0;
    };

    int ans = 0;
    int max_i = n / 2;

    int cur_f = 0;
    
    {
        int i = max_i;
        int max_f = (n - 2 * i) / 2;
        int f_i = calc_f(i, max_f);
        if (get(1, i) == get(n - i + 1, n))
            ans = max(ans, i + f_i);
        cur_f = f_i;
    }

    for (int i = max_i - 1; i >= 0; --i) {
        int max_f = (n - 2 * i) / 2;
        int start = min(cur_f + 2, max_f);
        int f_i = calc_f(i, start);
        if (get(1, i) == get(n - i + 1, n))
            ans = max(ans, i + f_i);
        cur_f = f_i;
    }

    cout << ans << endl;
}