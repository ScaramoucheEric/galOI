/*
    @ Author:       Eric / Sky__White
    @ Filename:     2026spring61.cpp
    @ Date:         03/31/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
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

using namespace std; Read fin;
#define int long long

signed main() {
    int n; fin >> n;
    vector<int> a(n);
    for (int i = 0; i < n; ++i) fin >> a[i];
    
    priority_queue<int, vector<int>, greater<int> > q;
    int ans = 0;
    
    for (int x : a) {
        q.push(x);
        ans += x - q.top();
        q.pop();
        q.push(x);
    }
    
    cout << ans << endl;
    return 0;
}