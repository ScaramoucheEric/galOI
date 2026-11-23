/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3469.cpp
    @ Time:         11/23/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <unordered_map>
#include <vector>
#include <cmath>
#include <functional>

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
    } fin;
}

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

const int INF = 0x3f3f3f3f3f3f3f3f;

const int N = 100005;
const int M = 500005;

int n, m;
vector<int> G[N];
int dfn[N], low[N], stp;
int siz[N];
int ans[N];
bool cut[N];

void tarjan(int u, int fa) {
    dfn[u] = low[u] = ++ stp;
    siz[u] = 1;
    int sum = 0, cnt = 0;
    
    for (int v : G[u]) {
        if (!dfn[v]) {
            cnt ++ ;
            tarjan(v, u);
            siz[u] += siz[v];
            low[u] = min(low[u], low[v]);
            
            if (low[v] >= dfn[u]) {
                cut[u] = true;
                ans[u] += (int)siz[v] * (n - siz[v]);
                sum += siz[v];
            }
        } else if (fa != v) {
            low[u] = min(low[u], dfn[v]);
        }
    }
    
    if (fa == 0 && cnt >= 2) {
        cut[u] = true;
    }
    
    if (cut[u]) {
        ans[u] += (n - 1 - sum) * (sum + 1) + (n - 1);
    } else {
        ans[u] = 2 * (n - 1);
    }
}

signed main() {
    fin >> n >> m;
    for (int i = 0; i < m; i++) {
        int u, v;
        fin >> u >> v;
        G[u].push_back(v);
        G[v].push_back(u);
    }
    
    tarjan(1, 0);
    
    for (int i = 1; i <= n; i++) {
        cout << ans[i] << endl;
    }

    // for (int i = 1; i <= n; i ++ )
    //     if (cut[i])
    //         cout << i << " ";
    
    return 0;
}