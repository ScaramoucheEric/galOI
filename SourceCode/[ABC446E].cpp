/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC446E].cpp
    @ Time:         02/21/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <map>
#include <cstdio>
#include <queue>
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
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

using PII = pair<int, int> ;

int Mod, A, B;

PII ne(PII a) {
    return {a.second, (a.first * B + a.second * A) % Mod};
}

signed main() {
    scanf("%lld%lld%lld", &Mod, &A, &B);

    vector<vector<vector<PII> > > g(Mod, vector<vector<PII> >(Mod));

    for (int i = 0; i < Mod; i ++ ) {
        for (int j = 0; j < Mod; j ++ ) {
            PII to = ne({i, j});
            g[to.first][to.second].push_back({i, j});
        }
    }

    vector<vector<bool> > st(Mod, vector<bool>(Mod, false));

    queue<PII> q;

    for (int i = 0; i < Mod; i ++ )
        q.push({i, 0}), q.push({0, i}), st[i][0] = st[0][i] = true;

    
    while(q.size()) {
        PII u = q.front(); q.pop();

        for (auto v : g[u.first][u.second]) {
            if (st[v.first][v.second]) continue;
            q.push(v); st[v.first][v.second] = true;
        }
    }

    int cnt = 0;

    for (int i = 1; i < Mod; i ++ )
        for (int j = 1; j < Mod; j ++ )
            if (!st[i][j])
                cnt ++ ;

    for (int i = 1; i < Mod; i ++ )
        for (int j = 1; j < Mod; j ++ ) {
                cout << i << " " << j << endl;

                cout << Mod << endl;
            }

    cout << cnt << endl;
}