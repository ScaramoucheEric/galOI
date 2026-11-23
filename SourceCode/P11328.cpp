/*
    @ Author:       Eric / Sky__White
    @ Filename:     P11328.cpp
    @ Date:         10/07/2026
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

void solve() {
    int n; fin >> n;

    struct Node {
        int L, X;

        bool operator < (const Node & W) const {
            return X < W.X;
        }
    }; vector<Node> arr(n + 1);

    for (int i = 1; i <= n; i ++ )
        fin >> arr[i].X;
    for (int i = 1; i <= n; i ++ )
        fin >> arr[i].L;

    sort(1 + all(arr), [&](Node a, Node b) {
        return a.L + a.X < b.L + b.X;
    });

    priority_queue<Node> q;

    int res = 0, cur = 0;
    for (int i = 1; i <= n; i ++ ) {
        if (arr[i].L >= cur) {
            cur += arr[i].X;
            q.push(arr[i]);
            res ++ ;
        } else if (q.top().X > arr[i].X) {
            cur -= q.top().X;
            // cout << cur << " " << q.top().L << " " << q.top().X << " -> ";
            q.pop();
            cur += arr[i].X;
            q.push(arr[i]);
            // cout << cur << " " << arr[i].L << " " << arr[i].X << endl;
        }
        // cout << res << endl;
    }

    cout << res << endl;
}

signed main() {
    // int T; fin >> T;

    // while(T -- ) {
        solve();
    // }
}