/*
    @ Author:       Eric / Sky__White
    @ Filename:     P15233.cpp
    @ Date:         17/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
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

signed main() {
    string str; cin >> str; int n = str.size(); str = ' ' + str;
    int q; fin >> q;

    vector<int> num(1);
    vector<char> op(1);

    for (int i = 1; i <= n; i ++ ) {
        int sum = 0;
        while(i <= n and isdigit(str[i])) sum = (sum << 1) + (sum << 3) + (str[i ++ ] ^ 48);
        num.push_back(sum);
        if (i <= n) {
            op.push_back(str[i]);
        }
    }

    n = num.size() - 1;

    // for (int i = 1; i <= n; i ++ ) cout << num[i] << " \n"[i == n];
    // for (int i = 1; i <= n - 1; i ++ ) cout << op[i] << " \n"[i == n - 1];

    vector<int> opt;

    while(q -- ) {
        int num; char ch; fin >> num; ch = getchar();

        if (op[num] == '*' and ch != '*') {
            op[num] = ch, opt.push_back(num);
        }
    }

    reverse(all(opt));

    vector<int> fa(n + 1);
    for (int i = 1; i <= n; i ++ ) fa[i] = i;

    function<int(int)> find = [&](int x) -> int {
        if (fa[x] == x) return x;
        return fa[x] = find(fa[x]);
    };

    int res = 0;

    for (int i = 1; i < n; i ++ ) {
        if (op[i] == '*') {
            ((num[find(i + 1)] *= num[find(i)]) += Mod) %= Mod;
            num[find(i)] = 0;
            fa[find(i)] = find(i + 1);
        } else if (op[i] == '-') {
            num[find(i + 1)] = -num[find(i + 1)];
        }
    }

    for (int i = 1; i <= n; i ++ )
        (res += num[i] + Mod) %= Mod;

    vector<int> ans; ans.push_back(res);

    for (auto i : opt) {
        // cout << num[find(i + 1)] << " -> ";

        (res += -num[find(i + 1)] + Mod) %= Mod;
        (res += -num[find(i)] + Mod) %= Mod;

        if (op[i] == '-')
            num[find(i + 1)] *= -1;
        op[i] = '*';

        ((num[find(i + 1)] *= num[find(i)]) += Mod) %= Mod;
        num[find(i)] = 0;

        (res += num[find(i + 1)] + Mod) %= Mod;
        fa[find(i)] = find(i + 1);

        ans.push_back(res);

        // cout << num[find(i + 1)] << endl;

        // for (int i = 1; i <= n; i ++ )
        //     cout << num[i] << " \n"[i == n];
    }

    reverse(all(ans));

    for (int i : ans)
        cout << i << endl;
}