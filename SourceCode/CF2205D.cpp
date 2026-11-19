/*
    @ Author:       Eric / Sky__White
    @ Filename:     CF2205D.cpp
    @ Date:         17/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <stack>
#include <vector>
#include <functional>

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

const int Mod = 1e9 + 7;

void solve() {
    int n; fin >> n;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    stack<int> a, b;

    int pos = 1;

    vector<int> l(n + 1), r(n + 1);

    while(pos <= n) {
        while(a.size() and a.top() < arr[pos])
            a.pop();
        a.push(arr[pos]);
        l[pos ++ ] = a.size();
    }
    pos -- ;

    while(pos) {
        while(b.size() and b.top() < arr[pos])
            b.pop();
        b.push(arr[pos]);
        r[pos -- ] = b.size();
    }

    int res = 0;
    for (int i = 1; i <= n; i ++ )
        res = max(res, l[i] + r[i] - 1);
    
    cout << n - res << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}