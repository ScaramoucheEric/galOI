/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC481C].cpp
    @ Date:         24/10/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>

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

#define int long long
#define all(arr) arr.begin(), arr.end()
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)
#define endl "\n"

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int Q; fin >> Q;

    unordered_map<string, int> st;
    int idx = 0;

    while(Q -- ) {
        string str; cin >> str;
        if (st.count(str)) cout << st[str] << endl;
        else st[str] = ++ idx , cout << st[str] << endl;;
    }
}