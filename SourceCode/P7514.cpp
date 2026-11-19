/*
    @ Author:       Eric / Sky__White
    @ Filename:     P7514.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>

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

const int Mod = 1e9 + 7;
const int INF = 0x3f3f3f3f3f3f3f3f;

struct Node {
    int val, id;
    bool isB;
};

signed main() {
    int n, m; fin >> n >> m;

    vector<int> a(n), b(n);

    for (int i = 0; i < n; i ++ ) fin >> a[i];
    for (int i = 0; i < n; i ++ ) fin >> b[i];

    vector<Node> v;
    v.reserve(2 * n);

    for (int i = 0; i < n; i ++ ) {
        v.push_back({a[i], i, false});
        v.push_back({b[i], i, true});
    }
    sort(v.begin(), v.end(), [&](const Node x, const Node y) {
        return x.val < y.val;
    });

    vector<int> cntA(n, 0), cntB(n, 0);

    int cov = 0, bad = 0, ans = INF;

    int l = 0;
    for (int r = 0; r < 2 * n; r ++ ) {
        int id = v[r].id;
        if (v[r].isB) {
            if (cntB[id] == 0 && cntA[id] == 0) cov ++ ; 
            cntB[id] ++ ;
            if (cntB[id] == 1 && cntA[id] == 0) bad ++ ;
        } else {
            if (cntA[id] == 0 && cntB[id] == 0) cov ++ ;
            cntA[id] ++ ;
            if (cntA[id] == 1 && cntB[id] == 1) bad -- ;
        }

        while (cov == n && bad <= m) {
            ans = min(ans, (int)v[r].val - v[l].val);

            int lid = v[l].id;
            if (v[l].isB) {
                if (cntB[lid] == 1 && cntA[lid] == 0) bad -- ;
                cntB[lid] -- ;
                if (cntA[lid] == 0 && cntB[lid] == 0) cov -- ;
            } else {
                if (cntA[lid] == 1 && cntB[lid] == 1) bad ++ ;
                cntA[lid] -- ;
                if (cntA[lid] == 0 && cntB[lid] == 0) cov -- ;
            }

            l ++ ;
        }
    }
    
    cout << ans << endl;

    return 0;
}