/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC446C].cpp
    @ Time:         02/21/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
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

void solve() {
    int D, n; fin >> n >> D;

    vector<int> A(n + 1), B(n + 1);

    // cout << "N " << n << endl;

    for (int i = 1; i <= n; i ++ ) {
        fin >> A[i];
    }
    for (int i = 1; i <= n; i ++ ) {
        fin >> B[i];
    }

    queue<int> q;

    for (int day = 1; day <= n; day ++ ) {
        while(A[day])
            q.push(day), A[day] -- ;
        while(q.size() and B[day] -- )
            q.pop();
        while(q.size() and day - q.front() >= D)
            q.pop();
        // cout << q.size() << endl;
    }

    printf("%llu\n", q.size());
}

signed main() {
    int T; fin >> T;

    while(T -- ) solve();
}