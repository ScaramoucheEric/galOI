/*
    @ Author:       Eric / Sky__White
    @ Filename:     P14582.cpp
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

void solve() {
    int m, k; fin >> m >> k;

    vector<bool> rem(10, false);
    for (int i = 0; i < k; i ++ ) {
        int p; fin >> p;
        rem[p] = true;
    }

    int d = -1;
    for (int x = 1; x <= 9; x ++ )
        if (!rem[x]) { d = x; break; }

    if (d == -1) {
        cout << -1 << "\n";
        return;
    }

    int mm = m, a = 0, b = 0;
    while (mm % 2 == 0) mm /= 2, a ++ ;
    while (mm % 5 == 0) mm /= 5, b ++ ;
    int t = max(a, b);

    int phi = mm, tmp = mm;
    for (int p = 2; p * p <= tmp; p ++ ) {
        if (tmp % p == 0) {
            while (tmp % p == 0) tmp /= p;
            phi = phi / p * (p - 1);
        }
    }
    if (tmp > 1) phi = phi / tmp * (tmp - 1);

    int len = mm * phi;

    if (t == 0) {
        cout << 1 << "\n" << d << ' ' << len << "\n";
    } else {
        cout << 2 << "\n" << d << ' ' << len << "\n" << 0 << ' ' << t << "\n";
    }
}

signed main() {
    int T; fin >> T;

    while (T -- ) solve();
    return 0;
}