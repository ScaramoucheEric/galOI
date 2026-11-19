/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC355E].cpp
    @ Date:         24/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/
#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <queue>
#include <cmath>
#include <set>

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

const int N = 1 << 20;

const double eps = 1e-6;

struct edge {
    int v, nxt;
} e[N << 2];

int head[N], tott;

void add(int u, int v) {
    e[++tott] = {v, head[u]};
    head[u] = tott;
}

int frm[N];

void bfs(int st, int ed) {
    queue<int> q;
    q.push(st);
    frm[st] = st;

    while (!q.empty()) {
        int u = q.front();
        q.pop();
    
        if (u == ed) return;
    
        for (int i = head[u]; i; i = e[i].nxt) {
            int v = e[i].v;
            if (frm[v] >= 0) continue;
            
            frm[v] = u;
            q.push(v);
        }
    }
}

signed main() {
    int n, l, r;
    cin >> n >> l >> r;
    r ++ ;
    
    for (int k = 0; k <= n; k ++ ) {
        for (int i = 0; ((i + 1) << k) <= (1ll << n); i ++ ) {
            add(i << k, (i + 1) << k);
            add((i + 1) << k, i << k);
        }
    }
    
    for (int i = 0; i <= (1 << n); i ++ ) {
        frm[i] = -1;
    }
    
    bfs(l, r);
    
    int ans = 0;
    for (int i = frm[r]; i != r; r = i, i = frm[i]) {
        if (i < r) {
            cout << "? " << (int)(log2(r - i) + eps) << " " << (i >> (int)(log2(r - i) + eps)) << endl;
            int d; cin >> d;
            ans += d;
        } else {
            cout << "? " << (int)(log2(i - r) + eps) << " " << (r >> (int)(log2(i - r) + eps)) << endl;
            int d; cin >> d;
            ans -= d;
        }
    }
    
    cout << "! " << (ans % 100 + 100) % 100 << endl;
    return 0;
}