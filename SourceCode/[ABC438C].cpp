/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC437C].cpp
    @ Time:         12/20/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <algorithm>

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

void solve() {
    int n; fin >> n;

    vector<int> C(n);
    int totalP = 0;
    
    for (int i = 0; i < n; i++) {
        int w, p;
        fin >> w >> p;
        C[i] = w + p;
        totalP += p;
    }
    
    sort(C.begin(), C.end());
    
    int sum = 0, cnt = 0;

    for (int i = 0; i < n; i ++ ) {
        if (sum + C[i] <= totalP) {
            sum += C[i];
            cnt ++ ;
        } else break;
    }
    cout << cnt << endl;
}

signed main() {
    int T; fin >> T;
    while (T--) {
        solve();
    }
    
    return 0;
}