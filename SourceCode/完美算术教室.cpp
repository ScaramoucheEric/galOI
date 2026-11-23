/*
    @ Author:       Eric / Sky__White
    @ Filename:     完美算术教室.cpp
    @ Date:         26/07/2026
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

const int Mod = 1e9 + 7;

signed main() {
    int n; fin >> n;

    string str; cin >> str;
    str = " " + str;

    vector<int> arr(n + 1), val(n + 1);
    vector<int> presum(n + 1), pre_h(n + 1), pow10(n + 1);
    vector<int> posA, posB;
    posA.reserve(n + 1); posB.reserve(n + 1);

    pow10[0] = 1;
    for (int i = 1; i <= n; i ++ ) {
        int x = str[i] ^ 48;
        arr[i] = x;

        if (arr[i] > 4) {
            val[i] = 9 - arr[i];
            arr[i] = arr[i] * 2 % 9;
        } else val[i] = arr[i];

        pow10[i] = pow10[i - 1] * 10 % Mod;
        presum[i] = (presum[i - 1] + arr[i]) % 9;
        pre_h[i] = (pre_h[i - 1] * 10 + arr[i]) % Mod;

        if (x == 3 || x == 6) posB.push_back(i);
        else if (x != 0 && x != 9) posA.push_back(i);
    }

    int q; fin >> q;
    int cand[12];

    while (q -- ) {
        int l, r; fin >> l >> r;

        int m = 0;
        auto itA = upper_bound(posA.begin(), posA.end(), r);
        int idx = (int)(itA - posA.begin()) - 1;
        for (int t = 0; t < 8 && idx >= 0 && posA[idx] >= l; t ++ , idx -- )
            cand[m ++ ] = posA[idx];

        auto itB = upper_bound(posB.begin(), posB.end(), r);
        idx = (int)(itB - posB.begin()) - 1;
        for (int t = 0; t < 2 && idx >= 0 && posB[idx] >= l; t ++ , idx -- )
            cand[m ++ ] = posB[idx];

        sort(cand, cand + m);

        int S[12];
        S[m] = 1;
        for (int i = m - 1; i >= 0; i -- ) {
            int v = val[cand[i]];
            int s = S[i + 1];
            int tmp = ((s << v) | (s >> (9 - v))) & 511;
            S[i] = s | tmp;
        }

        int base = (presum[r] - presum[l - 1] + 9) % 9;
        int p = (9 - base) % 9;

        int cur = p; int add = 0;
        for (int i = 0; i < m; i ++ ) {
            if ((S[i + 1] >> cur) & 1) continue;
            int pos = cand[i], v = val[pos];
            add = (add + v % Mod * pow10[r - pos]) % Mod;
            cur = (cur - v % 9 + 9) % 9;
        }

        if (cur != 0) {
            cout << -1 << endl;
        } else {
            int len = r - l + 1;
            int bnum = (pre_h[r] - pre_h[l - 1] * pow10[len] % Mod + Mod) % Mod;
            cout << (bnum + add) % Mod << endl;
        }
    }
    return 0;
}