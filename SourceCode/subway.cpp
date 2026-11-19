/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC420G].cpp
    @ Date:         27/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <set>
#include <map>

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
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

const int Mod = 1e9 + 7;

inline int qpow(int a, int b) {
    int res = 1; a %= Mod;
    while(b) {
        if(b & 1) res = res * a % Mod;
        a = a * a % Mod;
        b >>= 1;
    }
    return res;
}

const int INV2 = qpow(2, Mod - 2);
const int INV6 = qpow(6, Mod - 2);

inline int sum_sq(int n) {
    if(n <= 0) return 0;
    return n % Mod * (n + 1) % Mod * (2 * n + 1) % Mod * INV6 % Mod;
}

inline int sum_lin(int n) {
    if(n <= 0) return 0;
    return n % Mod * (n + 1) % Mod * INV2 % Mod;
}

class SegTree {
public:
    struct Node {
        int val;
        int c0, c1, c2;
    };
    vector<Node> t;
    int N;

    void init(int n) {
        N = n;
        t.resize(4 * n + 5, {0, 0, 0, 0});
    }

    inline void push_up(int p) {
        t[p].val = (t[p << 1].val + t[p << 1 | 1].val) % Mod;
    }

    inline void apply(int p, int l, int r, int nc0, int nc1, int nc2) {
        t[p].c0 = (t[p].c0 + nc0) % Mod;
        t[p].c1 = (t[p].c1 + nc1) % Mod;
        t[p].c2 = (t[p].c2 + nc2) % Mod;

        int s0 = (r - l + 1) % Mod;
        int s1 = (sum_lin(r) - sum_lin(l - 1) + Mod) % Mod;
        int s2 = (sum_sq(r) - sum_sq(l - 1) + Mod) % Mod;

        int add_val = (nc0 * s0 % Mod + nc1 * s1 % Mod + nc2 * s2 % Mod) % Mod;
        t[p].val = (t[p].val + add_val) % Mod;
    }

    inline void push_down(int p, int l, int r) {
        if(t[p].c0 == 0 && t[p].c1 == 0 && t[p].c2 == 0) return;
        int mid = (l + r) >> 1;
        apply(p << 1, l, mid, t[p].c0, t[p].c1, t[p].c2);
        apply(p << 1 | 1, mid + 1, r, t[p].c0, t[p].c1, t[p].c2);
        t[p].c0 = t[p].c1 = t[p].c2 = 0;
    }

    void build(int p, int l, int r, vector<int>& a) {
        if(l == r) {
            t[p].val = a[l] % Mod;
            return;
        }
        int mid = (l + r) >> 1;
        build(p << 1, l, mid, a);
        build(p << 1 | 1, mid + 1, r, a);
        push_up(p);
    }

    void modify(int p, int l, int r, int L, int R, int nc0, int nc1, int nc2) {
        if(L > R) return;
        if(l >= L && r <= R) {
            apply(p, l, r, nc0, nc1, nc2);
            return;
        }
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        if(L <= mid) modify(p << 1, l, mid, L, R, nc0, nc1, nc2);
        if(R > mid) modify(p << 1 | 1, mid + 1, r, L, R, nc0, nc1, nc2);
        push_up(p);
    }

    int query(int p, int l, int r, int L, int R) {
        if(L > R) return 0;
        if(l >= L && r <= R) return t[p].val;
        push_down(p, l, r);
        int mid = (l + r) >> 1;
        int res = 0;
        if(L <= mid) res = (res + query(p << 1, l, mid, L, R)) % Mod;
        if(R > mid) res = (res + query(p << 1 | 1, mid + 1, r, L, R)) % Mod;
        return res;
    }
};

signed main() {
    // IO("subway");
    int n, m; fin >> n >> m;

    vector<int> a(n + 1), S(n + 1), SS(n + 1);
    for(int i = 1; i <= n; i++) {
        fin >> a[i];
        S[i] = (S[i - 1] + a[i]) % Mod;
        SS[i] = (SS[i - 1] + S[i]) % Mod;
    }

    SegTree T;
    T.init(n);
    T.build(1, 1, n, SS);

    while(m--) {
        int op; cin >> op;
        if(op == 1) {
            int u, v, d; cin >> u >> v >> d;
            if(u > v) swap(u, v);
            d %= Mod;

            int half_d = d * INV2 % Mod;

            int c2 = half_d;
            int c1 = half_d * ((3 - 2 * u % Mod + Mod) % Mod) % Mod;
            int c0 = half_d * ((u * u % Mod - 3 * u % Mod + 2 + 2 * Mod) % Mod) % Mod;

            T.modify(1, 1, n, u, v, c0, c1, c2);

            if(v < n) {
                int len = (v - u + 1) % Mod;
                int K = len * d % Mod;

                int Val_v = half_d * len % Mod * ((len + 1) % Mod) % Mod;
                
                int rc1 = K;
                int rc0 = (Val_v - K * (v % Mod) % Mod + Mod) % Mod;

                T.modify(1, 1, n, v + 1, n, rc0, rc1, 0);
            }

        } else {
            int l, r; cin >> l >> r;
            int len = (r - l + 1) % Mod;

            int ans = 0;
            
            int SS_n = T.query(1, 1, n, n, n);
            ans = (ans + len * SS_n % Mod) % Mod;

            int L_idx2 = max(1LL, n - r);
            int R_idx2 = n - l;
            if(R_idx2 >= 1) {
                int sum2 = T.query(1, 1, n, L_idx2, R_idx2);
                ans = (ans - sum2 + Mod) % Mod;
            }

            int L_idx3 = max(1LL, l - 1);
            int R_idx3 = r - 1;
            if(R_idx3 >= 1) {
                int sum3 = T.query(1, 1, n, L_idx3, R_idx3);
                ans = (ans - sum3 + Mod) % Mod;
            }

            cout << ans << "\n";
        }
    }
    return 0;
}