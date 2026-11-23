/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2182F1.cpp
    @ Date:         16/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <unordered_map>
#include <cstdio>
using namespace std;

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

const int MOD = 998244353;
const int MAXC = 60;
const int MAXJ = 62;

signed main() {
    int n, m; fin >> n >> m;

    int maxN = n + m;

    vector<int> pow2(maxN + 1);
    vector<vector<int>> u(maxN + 1, vector<int>(MAXJ + 1));

    function<void()> init = [&]() {
        pow2[0] = 1;
        for (int i = 1; i <= maxN; i ++ )
            pow2[i] = pow2[i - 1] * 2 % MOD;

        for (int i = 0; i <= maxN; i ++ ) {
            u[i][0] = pow2[i];
            for (int j = 1; j <= MAXJ; j ++ ) {
                if (j > i) u[i][j] = 0;
                else u[i][j] = (u[i - 1][j] + u[i - 1][j - 1]) % MOD;
            }
        }
    };
    init();

    unordered_map<int, int> cnt;

    for (int i = 1; i <= n; i ++ ) {
        int c; fin >> c;
        cnt[c] ++;
    }

    while (m --) {
        int op, x; fin >> op >> x;
        if (op == 1) {
            cnt[x] ++ ;
        } else if (op == 2) {
            cnt[x] -- ;
        } else {
            int rem = x, ans = 0, pre = 1, k = 0;

            int total = 0;
            for (auto &p : cnt) total += p.second;

            for (int i = MAXC; i >= 0; i -- ) {
                int c = cnt[i];
                if (c == 0) continue;

                total -= c;

                int now = 0;

                while (now < c) {
                    int d = 0;
                    if (i - k >= 0) d = 1LL << (i - k);
                    if (d == 0) break;

                    if (d < rem && d > rem / 2) {
                        rem -= d;
                        k ++;
                        now ++;
                    } else {
                        break;
                    }
                }

                if (now < c) {
                    int d = 0;
                    if (i - k >= 0) d = 1LL << (i - k);
                    if (d >= rem && d > 0) {
                        int need = now + 1;
                        if (need <= MAXJ) {
                            int ways = pre * u[c][need] % MOD;
                            ways = ways * pow2[total] % MOD;
                            ans = (ans + ways) % MOD;
                        }
                    }
                }

                int comb = 0;
                if (now <= MAXJ) {
                    comb = (u[c][now] - (now + 1 <= MAXJ ? u[c][now + 1] : 0) + MOD) % MOD;
                }
                pre = pre * comb % MOD;
                if (pre == 0) break;   
            }

            printf("%lld\n", ans % MOD);
        }
    }
    return 0;
}