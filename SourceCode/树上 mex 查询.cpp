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

const int N = 500005, M = 1000010, E = 1000010, LG = 20;

int h[N], t[E], nx[E], ec, wl[E];
inline void add(int u, int v, int w) { t[ec] = v; wl[ec] = w; nx[ec] = h[u]; h[u] = ec++; }

int dep[N], fir[N], eu[M], en, ds[N];
int lg[M], st[LG][M];

struct F { int u, p, e; };
F sk[N];
void bdfs() {
    dep[1] = 0; ds[1] = 0; fir[1] = 0; eu[0] = 1; en = 1;
    int top = 0;
    sk[top ++ ] = {1, 0, h[1]};
    while (top > 0) {
        F &f = sk[top - 1];
        if (f.e) {
            int e = f.e; f.e = nx[e];
            int v = t[e];
            if (v == f.p) continue;
            dep[v] = dep[f.u] + 1;
            ds[v] = ds[f.u] + wl[e];
            fir[v] = en; eu[en ++ ] = v;
            sk[top ++ ] = {v, f.u, h[v]};
        } else {
            top -- ;
            if (top > 0) eu[en ++ ] = sk[top - 1].u;
        }
    }
}
void bst() {
    for (int i = 0; i < en; i ++ ) st[0][i] = eu[i];
    for (int j = 1; (1 << j) <= en; j ++ ) {
        int hf = 1 << (j - 1);
        for (int i = 0; i + (1 << j) <= en; i ++ ) {
            int a = st[j - 1][i], b = st[j - 1][i + hf];
            st[j][i] = (dep[a] < dep[b]) ? a : b;
        }
    }
    lg[1] = 0;
    for (int i = 2; i <= en; i ++ ) lg[i] = lg[i >> 1] + 1;
}
inline int lca(int u, int v) {
    int l = fir[u], r = fir[v];
    if (l > r) { int x = l; l = r; r = x; }
    int k = lg[r - l + 1];
    int a = st[k][l], b = st[k][r - (1 << k) + 1];
    return (dep[a] < dep[b]) ? a : b;
}
inline int dist(int u, int v) {
    int w = lca(u, v);
    return ds[u] + ds[v] - 2 * ds[w];
}

int pos[N], da[N], db[N];

signed main() {
    int n, q; fin >> n >> q;

    memset(pos, -1, sizeof pos);
    for (int i = 1; i <= n; i ++ ) {
        int w; fin >> w;
        if (w >= 0 && w <= n) pos[w] = i;
    }

    ec = 1; memset(h, 0, sizeof h);
    for (int i = 1; i < n; i ++ ) {
        int u, v, w; fin >> u >> v >> w;
        add(u, v, w); add(v, u, w);
    }

    bdfs(); bst();

    int fm = n;
    for (int v = 0; v <= n; v ++ ) if (pos[v] == -1) { fm = v; break; }

    memset(da, -1, sizeof da); memset(db, -1, sizeof db);
    for (int m = 1; m <= n; m ++ ) {
        da[m] = da[m - 1]; db[m] = db[m - 1];

        int p = pos[m - 1];

        if (p != -1) {
            if (da[m] == -1) da[m] = db[m] = p;
            else {
                int a = da[m], b = db[m];
                int c0 = dist(a, b), c1 = dist(a, p), c2 = dist(b, p);

                if (c1 >= c0 && c1 >= c2) db[m] = p;
                else if (c2 >= c0 && c2 >= c1) da[m] = p;
            }
        }
    }

    for (int i = 0; i < q; i ++ ) {
        int x, k; fin >> x >> k;

        int L = 0, R = fm;

        while (L < R) {
            int mid = (L + R + 1) >> 1;
            bool ok;
            if (mid == 0) ok = true;
            else {
                int a = da[mid], b = db[mid];
                ok = (dist(a, x) <= k && dist(b, x) <= k);
            }
            if (ok) L = mid; else R = mid - 1;
        }
        printf("%lldn", L);
    }
    return 0;
}