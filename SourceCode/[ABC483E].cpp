#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <functional>
#include <string>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >>(T & x) {
            T sum = 0; short opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
        inline Read operator >>(string & x) {
            x.clear();
            char ch = getchar();
            while(!isalpha(ch)) ch = getchar();
            while(isalpha(ch)) x += ch, ch = getchar();
            return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);
#define endl "\n"

using namespace std; Read fin;

const int MAXN = 1500005;
int tr[MAXN][26];
vector<int> g[MAXN];
int c[MAXN];
int tot = 0;
int res = 0;
int n, m;
string s;

void dfs(int u, int dep, int r) {
    if (dep == m) {
        res += c[u];
        return;
    }
    int t = s[dep] - 'a';
    
    if (tr[u][t]) {
        dfs(tr[u][t], dep + 1, r);
    }

    if (r > 0) {
        for (int x : g[u]) {
            if (x != t) {
                dfs(tr[u][x], dep + 1, r - 1);
            }
        }
    }
}

void add() {
    int u = 0;
    for (char ch : s) {
        int v = ch - 'a';
        cout << u << " " << v << " " << tot << endl;
        if (!tr[u][v]) {
            tr[u][v] = ++ tot;
            g[u].push_back(v);
        }
        u = tr[u][v];
    }
    c[u] ++ ;
}

signed main() {
    fin >> n >> m;

    for (int i = 0; i < n; i ++ ) {
        fin >> s;
        dfs(0, 0, 2);
        add();
    }
    
    cout << res << endl;
    return 0;
}