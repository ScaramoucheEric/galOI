/*
    @ Author:       Eric / Sky__White
    @ Filename:     temple.cpp
    @ Date:         14/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <cctype>
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

const int Mod = 1000000007;
const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n; fin >> n;

    vector<int> A(n + 2), B(n + 2);
    for (int i = 1; i <= n; i ++ )
        fin >> A[i] >> B[i];
    
    vector<int> d(n + 2);
    for (int i = 1; i <= n; i ++ )
        d[i] = A[i] - B[i];
    
    vector<int> pow2(n + 2); 
    pow2[0] = 1;
    for (int i = 1; i <= n; i ++ ) {
        pow2[i] = pow2[i-1] * 2 % Mod;
    }

    int sum = 0;
    for (int i = 1; i <= n; i ++ ) {
        int di = (d[i] % Mod + Mod) % Mod;
        sum = (sum + pow2[i-1] * di) % Mod;
    }
    
    function<int(int, int)> qpow = [&](int a, int b) {
        int res = 1;
        a %= Mod;
        while (b) {
            if (b & 1) res = res * a % Mod;
            a = a * a % Mod;
            b >>= 1;
        }
        return res;
    };

    int ress = (pow2[n] - 1 + Mod) % Mod;
    int inv = qpow(ress, Mod - 2);
    int xn = sum * inv % Mod;

    vector<int> x(n + 2);
    x[n] = xn;
    bool ok = true;
    for (int i = n; i >= 2; i -- ) {
        x[i - 1] = 2 * x[i] - d[i];
        if (x[i - 1] > INF or x[i - 1] < -INF) {
            ok = false;
            break;
        }
    }

    if (ok and x[n] != 2 * x[1] - d[1]) {
        ok = false;
    }
    if (ok) {
        for (int i = 1; i <= n; i++) {
            if (x[i] < 0) {
                ok = false;
                break;
            }
        }
    }

    if (!ok) {
        puts("No");
        return 0;
    }

    vector<int> cur_a = A;
    vector<int> rem_x = x;

    while (true) {
        bool changed = false;
        for (int i = 1; i <= n; i++) {
            if (rem_x[i] == 0) continue;
            int t = min(cur_a[i] / 2, rem_x[i]);
            if (t > 0) {
                changed = true;
                cur_a[i] -= 2 * t;
                int nxt = (i == n) ? 1 : i + 1;
                cur_a[nxt] += t;
                rem_x[i] -= t;
            }
        }
        if (!changed) break;
    }

    for (int i = 1; i <= n; i++) {
        if (rem_x[i] != 0 or cur_a[i] != B[i]) {
            ok = false;
            break;
        }
    }

    puts(ok ? "Yes" : "No");
    return 0;
}