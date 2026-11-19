/*
    @ Author:       Eric / Sky__White
    @ Filename:     P4229.cpp
    @ Date:         25/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <set>
#include <map>

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

const int INF = 0x3f3f3f3f3f3f3f3f;

const int MOD = 998244353;

int qpow(int a, int e) {
    int r = 1; a %= MOD; if (a < 0) a += MOD;
    while (e) { if (e & 1) r = r * a % MOD; a = a * a % MOD; e >>= 1; }
    return r;
}


const int MAXL = 20005;                 
int sm[MAXL * 4], setv[MAXL * 4], mulv[MAXL * 4];
int has[MAXL * 4];

#define lc (o << 1)
#define rc (o << 1 | 1)

void tes(int o, int len, int flag, int sval, int mval) {
    sm[o] = (flag ? (sval % MOD) * (len % MOD) % MOD : sm[o]) % MOD * (mval % MOD) % MOD;
    if (flag) { has[o] = 1; setv[o] = sval % MOD * mval % MOD; mulv[o] = 1; }
    else {
        if (has[o]) setv[o] = setv[o] % MOD * mulv[o] % MOD * mval % MOD;
        mulv[o] = mulv[o] % MOD * mval % MOD;
    }
}
void pushdown(int o, int l, int r) {
    if (!has[o] && mulv[o] == 1) return;
    
    int mid = (l + r) >> 1;
    
    tes(lc, mid - l + 1, has[o], setv[o], mulv[o]);
    tes(rc, r - mid, has[o], setv[o], mulv[o]);
    
    has[o] = 0; mulv[o] = 1; setv[o] = 0;
}
void build(int o, int l, int r) {
    has[o] = 0; mulv[o] = 1; setv[o] = 0;
    
    if (l == r) { sm[o] = (l == 0 ? 1 : 0); return; }
    
    int mid = (l + r) >> 1;
    
    build(lc, l, mid);
    build(rc, mid + 1, r);
    
    sm[o] = (sm[lc] + sm[rc]) % MOD;
}
void update(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) { tes(o, r - l + 1, 1, val, 1); return; }
    
    pushdown(o, l, r); int mid = (l + r) >> 1;
    
    if (ql <= mid) update(lc, l, mid, ql, qr, val);
    if (qr > mid)  update(rc, mid + 1, r, ql, qr, val);
    
    sm[o] = (sm[lc] + sm[rc]) % MOD;
}
void update_mul(int o, int l, int r, int ql, int qr, int val) {
    if (ql <= l && r <= qr) { tes(o, r - l + 1, 0, 0, val); return; }
    
    pushdown(o, l, r); int mid = (l + r) >> 1;
    
    if (ql <= mid) update_mul(lc, l, mid, ql, qr, val);
    if (qr > mid)  update_mul(rc, mid + 1, r, ql, qr, val);
    
    sm[o] = (sm[lc] + sm[rc]) % MOD;
}
int query(int o, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sm[o];

    pushdown(o, l, r); int mid = (l + r) >> 1; int res = 0;
    
    if (ql <= mid) res = (res + query(lc, l, mid, ql, qr)) % MOD;
    if (qr > mid)  res = (res + query(rc, mid + 1, r, ql, qr)) % MOD;
    
    return res;
}

void work() {
    int n, m, k; fin >> n >> m >> k;

    vector<int> L(m), R(m), X(m); vector<int> cd;

    cd.push_back(1); cd.push_back(n + 1);

    for (int i = 0; i < m; i++) {
        fin >> L[i] >> R[i] >> X[i];

        cd.push_back(L[i]);
        cd.push_back(R[i] + 1);
    }
    sort(all(cd));
    cd.erase(unique(all(cd)), cd.end());
    int S = (int)cd.size() - 1;          

    
    vector<int> c(S, -1), nxt(S + 1);
    for (int i = 0; i <= S; i++) nxt[i] = i;
    function<int(int)> find = [&](int x) -> int {
        return nxt[x] == x ? x : nxt[x] = find(nxt[x]);
    };
    vector<int> ord(m);
    
    for (int i = 0; i < m; i++) ord[i] = i;

    sort(all(ord), [&](int a, int b) { return X[a] < X[b]; });
    
    for (int oi = 0; oi < m; oi++) {
        int idx = ord[oi];
    
        int id_l = upper_bound(all(cd), L[idx]) - cd.begin() - 1;
        int id_r = upper_bound(all(cd), R[idx]) - cd.begin() - 1;
    
        int t = find(id_l);
    
        while (t <= id_r) { c[t] = X[idx]; nxt[t] = find(t + 1); t = find(t); }
    }

    for (int t = 0; t < S; t++) if (c[t] == -1) c[t] = k;
    
    map<int, vector<int>> segM, limM;
    set<int> Vset;
    Vset.insert(k);

    for (int t = 0; t < S; t++) segM[c[t]].push_back(t);
    for (int i = 0; i < m; i++) { limM[X[i]].push_back(i); Vset.insert(X[i]); }

    int ans = 1;
    bool ok = true;
    for (int v : Vset) {
        if (!ok) break;
        vector<int>& segs = segM[v];
        vector<int>& lims = limM[v];
        int N = (int)segs.size();
        if (!lims.empty() && N == 0) { ans = 0; ok = false; break; }   
        vector<int> p(N + 1, 0);
        for (int idx : lims) {
            int id_l = upper_bound(all(cd), L[idx]) - cd.begin() - 1;
            int id_r = upper_bound(all(cd), R[idx]) - cd.begin() - 1;
            int L_idx = lower_bound(all(segs), id_l) - segs.begin() + 1;
            int R_idx = upper_bound(all(segs), id_r) - segs.begin() - 1 + 1;

            if (L_idx > R_idx || L_idx < 1 || R_idx > N) { ans = 0; ok = false; break; }
            if (L_idx > p[R_idx]) p[R_idx] = L_idx;
        }
        if (!ok) break;
        if (N == 0) continue;                                          
        build(1, 0, N);
        for (int i = 1; i <= N; i++) {
            int t = segs[i - 1];
            int w = cd[t + 1] - cd[t];
            int not_c = qpow(v - 1, w);

            int fill_c = (qpow(v, w) - qpow(v - 1, w)) % MOD;
            
            if (fill_c < 0) fill_c += MOD;
            
            int Ssum = query(1, 0, N, 0, i - 1);                 
            
            if (p[i] >= 1)     update(1, 0, N, 0, p[i] - 1, 0);    
            if (p[i] <= i - 1) update_mul(1, 0, N, p[i], i - 1, not_c);   

            int val = Ssum % MOD * fill_c % MOD;
            update(1, 0, N, i, i, val);
        }
        int layer = query(1, 0, N, 0, N);

        ans = ans % MOD * layer % MOD;
    }
    printf("%lld\n", ans);
}

signed main() {
    // freopen("password.in", "r", stdin);
    // freopen("password.out", "w", stdout);
    int T; fin >> T;
    while (T -- ) work();
    return 0;
}