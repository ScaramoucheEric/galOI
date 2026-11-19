/*
    @ Author:       Eric / Sky__White
    @ Filename:     小信的数字切割.cpp
    @ Date:         21/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <cstdio>
#include <vector>
#include <set>
#include <queue>
#include <ctime>

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

struct P {
    int first; pair<string, string> second;
    bool operator <(const P & W) const {
        return first > W.first;
    }
};

priority_queue<P> q;

struct Node {
    string a;

    Node(string str) : a(str) {}

    Node operator + (const Node & W) const {
        Node res("");
        int pos = 0;
        string A = a, B = W.a;
        reverse(all(A)), reverse(all(B));

        while(pos < min(A.size(), B.size())) {
            res.a.push_back(A[pos] + B[pos] - '0');
            pos ++ ;
        }

        while(pos < A.size()) {
            res.a.push_back(A[pos]);
            pos ++ ;
        }
        while(pos < B.size()) {
            res.a.push_back(B[pos]);
            pos ++ ;
        }

        for (int i = 0; i < res.a.size() - 1; i ++ )
            if (res.a[i] > '9')
                res.a[i] -= 10, res.a[i + 1] ++ ;
        
        if (res.a.back() > '9') {
            res.a.back() -= 10;
            res.a.push_back('1');
        }

        reverse(all(res.a));

        return res;
    }


    bool operator < (const Node & W) const {
        if (a == W.a) return false;
        if (a == "-") return false;
        if (W.a == "-") return true;
        if (a.size() < W.a.size()) return true;
        if (a.size() > W.a.size()) return false;
        return a < W.a;
    }
};

signed main() {
    // freopen("cut.in", "r", stdin);
    // freopen("cut.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);

    int n; cin >> n;
    string str; cin >> str;

    int cnt_a = 0, cnt_b = n;

    // cout << clock() * 1.0 / CLOCKS_PER_SEC << '\n';

    vector<pair<string, string> > q;

    int cnt = 0;
    for (int i = n / 2; i; i -- ) {
        // cout << str.substr(0, i) << " " << str.substr(i) << endl;
        if (i + 1 < n and str[i] != '0' or i == n - 1)
            cnt ++ , q.push_back({str.substr(0, i), str.substr(i)});
        if (cnt > 3) break;
    }
    cnt = 0;
    for (int i = n / 2; i < n; i ++ ) {
        // cout << str.substr(0, i) << " " << str.substr(i) << endl;
        if (i + 1 < n and str[i] != '0' or i == n - 1)
            cnt ++ , q.push_back({str.substr(0, i), str.substr(i)});
        if (cnt > 3) break;
    }
    
    // puts("");

    int opt = 4;

    Node res("-");
    // cout << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
    
    for (auto &[a, b] : q) {
        Node t = Node(a) + Node(b);
        if (t < res) res = t;
    }

    cout << res.a << '\n';

    // cout << clock() * 1.0 / CLOCKS_PER_SEC << '\n';
    return 0;
}