/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC448E].cpp
    @ Time:         03/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <functional>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == ' - ') ?  - 1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}

#define int int
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int MOD = 10007;

int pow_10(int l, int m) {
    int res = 1 % m;
    int base = 10 % m;
    while (l > 0) {
        if (l & 1) res = (res * base) % m;
        base = (base * base) % m;
        l >>= 1;
    }
    return res;
}

pair<int, int> bd(int rem, int d, int l, int m) {
    int tqt = 0;
    
    int max_pow = 0;
    while ((1LL << max_pow) <= l) max_pow++;
    
    vector<vector<int> > ne(max_pow + 1, vector<int>(m));
    vector<vector<int> > sumq(max_pow + 1, vector<int>(m));
    
    for (int r = 0; r < m; r ++ ) {
        int val = r * 10LL + d;
        ne[0][r] = val % m;
        sumq[0][r] = val / m;
    }
    
    for (int p = 1; p <= max_pow; p++) {
        for (int r = 0; r < m; r++) {
            int m1 = ne[p - 1][r];
            ne[p][r] = ne[p - 1][m1];
            sumq[p][r] = sumq[p - 1][r] + sumq[p - 1][m1];
        }
    }
    
    int cur = rem;
    for (int p = max_pow; p >= 0; p -- ) {
        if (l >> p & 1) {
            tqt += sumq[p][cur];
            cur = ne[p][cur];
        }
    }
    
    return {cur, tqt};
}

signed main() {
    int k, m; fin >> k >> m;
    
    int remi = 0;
    int ans = 0;
    
    for (int i = 0; i < k; i++) {
        int d; int len;
        fin >> d >> len;
        
        auto [new_rem, quot] = bd(remi, d, len, m);
        
        ans = (ans * pow_10(len, MOD) + (quot % MOD)) % MOD;
        
        remi = new_rem;
    }
    
    cout << ans << endl;
    
    return 0;
}