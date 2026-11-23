/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3178.cpp
    @ Date:         06/13/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <algorithm>
#include <cstring>
#include <functional>
#include <vector>
#include <queue>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? - 1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;
#include <iostream>
#include <vector>

using lint = long long;
constexpr int N = 1e5 + 10;

int n, m, root, a[N];
vector<int> G[N];

int idx, fa[N], dep[N], siz[N], son[N], top[N], dfn[N], rnk[N];

struct SegmentTree {
  lint sum[N << 2], lzy[N << 2];

  void maketag(int u, int l, int r, lint x) {
    sum[u] += (r - l + 1) * x;
    lzy[u] += x;
  }

  void pushup(int u) { sum[u] = sum[u << 1] + sum[u << 1 | 1]; }

  void pushdown(int u, int l, int r) {
    int mid = l + r >> 1;
    maketag(u << 1, l, mid, lzy[u]);
    maketag(u << 1 | 1, mid + 1, r, lzy[u]);
    lzy[u] = 0;
  }

  void build(int u, int l, int r) {
    if (l == r) {
      sum[u] = a[rnk[l]];
      return;
    }
    int mid = l + r >> 1;
    build(u << 1, l, mid), build(u << 1 | 1, mid + 1, r);
    pushup(u);
  }

  void upd(int u, int l, int r, int ql, int qr, lint x) {
    if (ql <= l && r <= qr) {
      maketag(u, l, r, x);
      return;
    }
    int mid = l + r >> 1;
    pushdown(u, l, r);
    if (ql <= mid) upd(u << 1, l, mid, ql, qr, x);
    if (qr > mid) upd(u << 1 | 1, mid + 1, r, ql, qr, x);
    pushup(u);
  }

  lint ask(int u, int l, int r, int ql, int qr) {
    if (ql <= l && r <= qr) return sum[u];
    int mid = l + r >> 1;
    pushdown(u, l, r);
    if (qr <= mid) return ask(u << 1, l, mid, ql, qr);
    if (ql > mid) return ask(u << 1 | 1, mid + 1, r, ql, qr);
    return ask(u << 1, l, mid, ql, qr) + ask(u << 1 | 1, mid + 1, r, ql, qr);
  }
} T;

void dfs1(int u, int f) {
  fa[u] = f, dep[u] = dep[f] + 1, siz[u] = 1;
  for (auto v : G[u]) {
    if (v == f) continue;
    dfs1(v, u);
    siz[u] += siz[v];
    if (siz[v] > siz[son[u]]) son[u] = v;
  }
}

void dfs2(int u, int tp) {
  top[u] = tp, dfn[u] = ++idx, rnk[idx] = u;
  if (son[u]) dfs2(son[u], tp);
  for (auto v : G[u])
    if (v != fa[u] && v != son[u]) dfs2(v, v);
}

void modify_path(int u, int v, int w) {
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    T.upd(1, 1, n, dfn[top[u]], dfn[u], w);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) swap(u, v);
  T.upd(1, 1, n, dfn[v], dfn[u], w);
}

void modify_subtree(int u, int w) {
  if (u == root)
    T.maketag(1, 1, n, w);
  else if (dfn[u] <= dfn[root] && dfn[root] <= dfn[u] + siz[u] - 1) {
    int v = root;
    while (dep[top[v]] > dep[u] + 1) v = fa[top[v]];
    v = rnk[dfn[top[v]] + dep[u] + 1 - dep[top[v]]];  
    if (1 <= dfn[v] - 1) T.upd(1, 1, n, 1, dfn[v] - 1, w);
    if (dfn[v] + siz[v] <= n) T.upd(1, 1, n, dfn[v] + siz[v], n, w);
  } else
    T.upd(1, 1, n, dfn[u], dfn[u] + siz[u] - 1, w);
}

lint query_path(int u, int v) {
  lint res = 0;
  while (top[u] != top[v]) {
    if (dep[top[u]] < dep[top[v]]) swap(u, v);
    res += T.ask(1, 1, n, dfn[top[u]], dfn[u]);
    u = fa[top[u]];
  }
  if (dep[u] < dep[v]) swap(u, v);
  res += T.ask(1, 1, n, dfn[v], dfn[u]);
  return res;
}

lint query_subtree(int u) {
  if (u == root) return T.sum[1];
  if (dfn[u] <= dfn[root] && dfn[root] <= dfn[u] + siz[u] - 1) {
    int v = root;
    while (dep[top[v]] > dep[u] + 1) v = fa[top[v]];
    v = rnk[dfn[top[v]] + dep[u] + 1 - dep[top[v]]];
    lint res = 0;
    if (1 <= dfn[v] - 1) res += T.ask(1, 1, n, 1, dfn[v] - 1);
    if (dfn[v] + siz[v] <= n) res += T.ask(1, 1, n, dfn[v] + siz[v], n);
    return res;
  }
  return T.ask(1, 1, n, dfn[u], dfn[u] + siz[u] - 1);
}

signed main() {
  fin >> n, root = 1;

  for (int i = 1; i <= n; ++i) fin >> a[i];
  for (int i = 2, f; i <= n; ++i) {
    fin >> f;
    G[i].emplace_back(f);
    G[f].emplace_back(i);
  }
  dfs1(1, 0), dfs2(1, 1), T.build(1, 1, n);
  for (fin >> m; m; --m) {
    int op, u, v, w;
    fin >> op >> u;
    if (op == 1)
      root = u;
    else if (op == 2)
      fin >> v >> w, modify_path(u, v, w);
    else if (op == 3)
      fin >> w, modify_subtree(u, w);
    else if (op == 4)
      fin >> v, cout << query_path(u, v) << "\n";
    else
      cout << query_subtree(u) << "\n";
  }
  cout.flush();
  return 0;
}