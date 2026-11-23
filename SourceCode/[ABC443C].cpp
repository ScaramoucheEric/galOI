/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC443C].cpp
    @ Time:         01/31/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>

namespace std {
    class Read {
    public:
        template<typename T>
        inline Read& operator>>(T& x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while (!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while (isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt;
            return *this;
        }
    } fin;
}

#define int long long

using namespace std;

signed main() {
    int n, T;
    fin >> n >> T;
    
    int ops = 0;
    int total = 0;
    
    for (int i = 0; i < n; i++) {
        int a;
        fin >> a;
        if (ops < a) {
            total += a - ops;
            ops = a + 100;
        }
    }
    
    if (ops < T) {
        total += T - ops;
    }
    
    cout << total << endl;
    
    return 0;
}