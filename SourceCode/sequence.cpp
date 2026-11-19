/*
    @ Author:       Eric / Sky__White
    @ Filename:     sequence.cpp
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

const int Mod = 998244353;
const int FN = 2000000;
const int IN = 2000000;

int fn, in;
vector<int> f, rf, iv;

int mp(int a, int e) {
    int r = 1;
    while (e) {
        if (e & 1) r = r * a % Mod;
        a = a * a % Mod;
        e >>= 1;
    }
    return r;
}

void bf(int n) {
    f.resize(n + 1); rf.resize(n + 1);
    f[0] = 1;
    for (int i = 1; i <= n; i++) f[i] = f[i - 1] * i % Mod;
    rf[n] = mp(f[n], Mod - 2);
    for (int i = n; i >= 1; i--) rf[i - 1] = rf[i] * i % Mod;
}

void bi(int n) {
    iv.resize(n + 1);
    if (n >= 1) iv[1] = 1;
    for (int i = 2; i <= n; i++) iv[i] = Mod - (Mod / i) * iv[Mod % i] % Mod;
}

int C(int n, int r) {
    if (r < 0 || r > n) return 0;
    if (r == 0 || r == n) return 1;
    r = min(r, n - r);
    if (n <= fn) return f[n] * rf[r] % Mod * rf[n - r] % Mod;
    if (r <= in) {
        int res = 1;
        for (int i = 1; i <= r; i++) res = res * ((n - r + i) % Mod) % Mod * iv[i] % Mod;
        return res;
    }
    int res = 1;
    for (int i = 1; i <= r; i++) res = res * ((n - r + i) % Mod) % Mod * mp(i, Mod - 2) % Mod;
    return res;
}

vector<int> gd(int n) {
    vector<int> v;
    for (int i = 1; i * i <= n; i++) {
        if (n % i == 0) {
            v.push_back(i);
            if (i != n / i) v.push_back(n / i);
        }
    }
    sort(v.begin(), v.end());
    return v;
}

int sol(int Y, int K) {
    vector<int> d = gd(Y);
    int D = d.size();
    vector<int> dp(D, 0);
    for (int i = D - 1; i >= 0; i--) {
        int val = C(Y / d[i] - 1, K - 1);
        for (int j = i + 1; j < D; j++) {
            if (d[j] % d[i] == 0) {
                val -= dp[j];
                if (val < 0) val += Mod;
            }
        }
        dp[i] = val;
    }
    return dp[0];
}

signed main() {
    freopen("sequence.in", "r", stdin);
    freopen("sequence.out", "w", stdout);

    int T; fin >> T;
    vector<tuple<int, int, int>> qs(T);
    int my = 0, mr = 0;
    for (int i = 0; i < T; i++) {
        int x, y, K; fin >> x >> y >> K;
        qs[i] = {x, y, K};
        if (y % x == 0) {
            int Y = y / x;
            if (K <= Y) {
                my = max(my, Y);
                int r = K - 1, alt = Y - K;
                mr = max(mr, min(r, alt));
            }
        }
    }
    fn = min(my, FN); in = min(mr, IN);
    bf(fn); bi(in);
    for (auto [x, y, K] : qs) {
        if (y % x != 0 || K > y / x) { cout << 0 << '\n'; continue; }
        cout << sol(y / x, K) << '\n';
    }
    return 0;
}