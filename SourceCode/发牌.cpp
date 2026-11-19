/*
    @ Author:       Eric / Sky__White
    @ Filename:     发牌.cpp
    @ Date:         12/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <deque>
#include <vector>
#include <cstdio>
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

signed main() {
    // freopen("card.in", "r", stdin);
    // freopen("card.out", "w", stdout);

    int n, m, Q, k; fin >> n >> m >> Q >> k;

    vector<vector<int> > arr(n + 1, vector<int>(m));

    for (int i = 1; i <= n; i ++ ) {
        for (int j = 0; j < m; j ++ )
            fin >> arr[i][j];
    }

    deque<int> q;

    while(Q -- ) {
        int op; fin >> op;
        if (op == 1) {
            int t; fin >> t;

            for (int i = 0; i < m; i ++ )
                q.push_back(arr[1][i]);
            arr[1].clear();
            
            if (t == 1) {
                for (int i = n; i >= 2; i -- ) {
                    for (int j = 0; j < m; j ++ ) {
                        q.push_back(arr[i][j]);
                    }
                    arr[i].clear();
                }
            } else {
                for (int i = 2; i <= n; i ++ ) {
                    for (int j = 0; j < m; j ++ ) {
                        q.push_back(arr[i][j]);
                    }
                    arr[i].clear();
                }
            }
            
        } else if (op == 2) {
            int x; fin >> x;

            while(x -- ) {
                q.push_back(q.front());
                q.pop_front();
            }
        } else if (op == 3) {
            deque<int> a, b;
            for (int i = 1; i <= (n * m + 1) / 2; i ++ ) 
                if (q.size()) {
                    a.push_back(q.front());
                    q.pop_front();
                }
            
            while(q.size())
                b.push_back(q.front()),
                q.pop_front();

            while(a.size()) {
                q.push_back(a.front()), a.pop_front();
                if (b.size())
                    q.push_back(b.front()), b.pop_front();
            }

            if (n * m & 1)
                q.push_front(q.back()), q.pop_back();
        } else if (op == 4) {
            int t; fin >> t;
            
            if (t) {
                for (int j = m - 1; ~j; j -- ) {
                    arr[1].push_back(q.back()), q.pop_back();
                    for (int i = n; i >= 2; i -- ) {
                        arr[i].push_back(q.back()), q.pop_back();
                    }
                }
            } else {
                for (int j = m - 1; ~j; j -- ) {
                    arr[1].push_back(q.back()), q.pop_back();
                    for (int i = 2; i <= n; i ++ ) {
                        arr[i].push_back(q.back()), q.pop_back();
                    }
                }
            }
        } else if (op == 5) {
            int t; fin >> t;
            if (t == 1) {
                for (int i = 1; i <= n; i ++ )
                    sort(all(arr[i]), greater<int>());
            } else {
                for (int i = 1; i <= n; i ++ )
                    sort(all(arr[i]));
            }
        } else { 
            return 0;
        }

        // cout << "q:\n";
        // for (int i : q)
        //     cout << i << " ";
        // cout << endl;

        // cout << "arr:\n";
        // for (int i = 1; i <= n; i ++ )
        //     for (int j = 0; j < arr[i].size(); j ++ )
        //         cout << arr[i][j] << " \n"[j == arr[i].size() - 1];
        // cout << endl;
    }

    for (auto i : arr[k])
        cout << i << " ";
    cout << endl;
}