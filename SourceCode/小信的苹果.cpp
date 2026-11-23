/*
    @ Author:       Eric / Sky__White
    @ Filename:     小信的苹果.cpp
    @ Date:         14/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdio>
#include <queue>

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

const int MAXV = 200000;
const int MAXD = 20; // bit_length <= 18, 20 is safe

int freq[MAXV + 5][MAXD];
int dep[MAXV + 5];

signed main() {
    // freopen("apple.in", "r", stdin);
    // freopen("apple.out", "w", stdout);

    int n, m;
    fin >> n >> m;

    vector<int> a(n);
    int maxA = 0;
    for (int i = 0; i < n; i++) {
        fin >> a[i];
        maxA = max(maxA, a[i]);
    }

    dep[0] = 0;
    for (int i = 1; i <= maxA; i++) {
        dep[i] = dep[i >> 1] + 1;
    }

    for (int val : a) {
        int d = dep[val];

        int x = val;
        while (x > 0) {
            freq[x][d]++;
            x >>= 1;
        }

        freq[0][d]++;
    }

    int ans = LLONG_MAX;

    for (int x = 0; x <= maxA; x++) {
        int total = 0;
        for (int d = 0; d < MAXD; d++) {
            total += freq[x][d];
        }

        if (total < m) continue;

        int need = m;
        int sumDepths = 0;

        for (int d = 0; d < MAXD && need > 0; d++) {
            int take = min(need, freq[x][d]);
            sumDepths += 1LL * take * d;
            need -= take;
        }

        int cost = sumDepths - 1LL * m * dep[x];
        ans = min(ans, cost);
    }

    cout << ans << '\n';
    return 0;
}