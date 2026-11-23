/*
    @ Author:       Eric / Sky__White
    @ Filename:     P12237.cpp
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

const int Mod = 1e9 + 7;
const int MOD = 998244353;

int qpow(int a, int e) {
    int r = 1;
    a %= MOD;
    while (e) {
        if (e & 1) r = r * a % MOD;
        a = a * a % MOD;
        e >>= 1;
    }
    return r;
}

signed main() {
    int n; fin >> n;

    vector<char> is_prime(n + 1, 1);
    if (n >= 0) is_prime[0] = 0;
    if (n >= 1) is_prime[1] = 0;

    vector<int> primes;
    
    for (int i = 2; i <= n; i ++ ) {
        if (is_prime[i]) primes.push_back(i);
        for (int j = 0; j < primes.size(); ++j) {
            int pj = primes[j];
            int x = 1LL * i * pj;
            if (x > n) break;
            is_prime[x] = 0;
            if (i % pj == 0) break;
        }
    }

    int p = primes.size();
    int c = n - p;

    int fact = 1;
    for (int i = 2; i <= n; i ++ ) fact = fact * i % MOD;

    int inv2  = qpow(2, MOD - 2);
    int inv4  = qpow(4, MOD - 2);
    int invp1 = qpow(p + 1, MOD - 2);

    int S = 0;
    int cntP = 0;
    for (int i = 1; i <= n; i ++ ) {
        if (is_prime[i]) {
            cntP ++ ;
        } else {
            int k  = cntP;
            int pk = p - k;
            int a1 = (k  % MOD) * ((k  + 1) % MOD) % MOD;
            int a2 = (pk % MOD) * ((pk + 1) % MOD) % MOD;
            S = (S + a1 + a2) % MOD;
        }
    }

    int ir = (c % MOD) * (((int)c - 1) % MOD + MOD) % MOD * inv4 % MOD;
    int cp = S % MOD * inv2 % MOD * invp1 % MOD;

    int ba = (ir + cp) % MOD;
    int ans = fact % MOD * ba % MOD;

    cout << ans << "\n";
    return 0;
}