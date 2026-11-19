/*
    @ Author:       Eric / Sky__White
    @ Filename:     [AcWing 106].cpp
    @ Time:         11/28/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
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

void solve() {
    int n; fin >> n;

    priority_queue<int> q1;
    priority_queue<int, vector<int>, greater<int> > q;

    int x; fin >> x;
    q.push(x);
    cout << (n + 1) / 2 << endl;
    cout << x << " ";

    for (int i = 2; i <= n; i += 2) {
        fin >> x; 
        if (x > q.top()) q.push(x);
        else q1.push(x);
        fin >> x; 
        if (x > q.top()) q.push(x);
        else q1.push(x);

        if (q.size() > q1.size() + 1) q1.push(q.top()), q.pop();
        if (q1.size() > q.size() - 1) q.push(q1.top()), q1.pop();

        cout << q.top();

        if (((i + 1) / 2 + 1) % 10) putchar(' ');
        else putchar('\n');
    }
    if (((n + 1) / 2) % 10)
        cout << endl;
}

signed main() {
    int T; fin >> T;
    while(T -- ) {
        int c; fin >> c;
        cout << c << " ";
        solve();
    }
}