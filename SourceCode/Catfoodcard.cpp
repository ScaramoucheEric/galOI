/*
    @ Author:       Eric / Sky__White
    @ Filename:     Catfoodcard.cpp
    @ Date:         28/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <cmath>
#include <string>

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

signed main() {
    freopen("catfoodcark.in", "r", stdin);
    freopen("catfoodcark.out", "w", stdout);

    int n, m; fin >> n >> m;

    if (n < 2) {
        cout << "0 / 1" << endl;
        return 0;
    }

    vector<vector<int> > S(m);

    for (int i = 0; i < n; i ++ ) {
        int k; fin >> k;
        while(k -- ) {
            int c; fin >> c;
            S[c - 1].push_back(i);
        }
    }

    vector<int> b(m);
    for (int i = 0; i < m; i ++ )
        fin >> b[i];

    vector<int> ord(m);
    for (int i = 0; i < m; i ++ ) ord[i] = i;
    sort(all(ord), [&](int x, int y) {
        return b[x] > b[y];
    });

    vector<int> op(n);

    int z1 = n, z2 = 0;
    __int128 sum = 0;

    for (int i = 0; i < m; i ++ ) {
        int t = ord[i], a = 0;

        for (int j = 0; j < (int)S[t].size(); j ++ )
            a += (op[S[t][j]] == 0);

        int dd = (int)S[t].size() - a;
        int df = a - dd;
        int dg = (z1 - a) - (z2 - dd);

        sum += (__int128)b[t] * df * dg;

        for (int j = 0; j < (int)S[t].size(); j ++ )
            op[S[t][j]] ^= 1;

        z1 += dd - a;
        z2 += a - dd;
    }

    function<int(int,int)> gcd = [&](int a, int b) {
        if (!b) return a;
        return gcd(b, a % b);
    };

    int P = sum;
    int Q = n * (n - 1) / 2;
    int g = gcd(P, Q);
    P /= g; Q /= g;

    cout << P << " / " << Q << endl;

    return 0;
}