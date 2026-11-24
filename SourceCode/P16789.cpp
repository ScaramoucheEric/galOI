/*
    @ Author:       Eric / Sky__White
    @ Filename:     P16789.cpp
    @ Date:         24/11/2026
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
        inline Read& operator >> (T & x) {
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
#define endl "\n"
#define IO(x) freopen(x ".in", "r", stdin), freopen(x ".out", "w", stdout);

using namespace std; Read fin;

signed main() {
    #ifndef ONLINE_JUDGE
    IO("P16789")
    #endif

    int n; fin >> n;

    struct Job {
        int deadline, val; bool main;

        bool operator <(const Job W) const {
            return val > W.val;
        }
    }; vector<Job> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].deadline >> arr[i].val >> arr[i].main;
    }

    // for (int i = 1; i <= n; i ++ ) {
    //     cout << arr[i].deadline << " " << arr[i].val << " " << arr[i].main << endl;
    // }

    sort(1 + all(arr), [&](Job a, Job b) {
        return a.deadline < b.deadline;
    });

    priority_queue<Job> main_q, minor_q;

    int cur_time = 0, res = 0, main_cnt = 0;

    for (int i = 1; i <= n; i ++ ) {
        if (arr[i].main) {
            if (cur_time >= arr[i].deadline) {
                if (minor_q.size()) {
                    res -= minor_q.top().val;
                    minor_q.pop();
                    res += arr[i].val;
                    main_cnt ++ ;
                    main_q.push(arr[i]);
                } else {
                    auto t = main_q.top();
                    if (t.val < arr[i].val) {
                        main_q.pop();
                        main_q.push(arr[i]);
                        res += arr[i].val - t.val;
                    }
                }
            } else {
                main_cnt ++ ;
                cur_time ++ ;
                res += arr[i].val;
                main_q.push(arr[i]);
            }
        } else {
            if (cur_time >= arr[i].deadline) {
                if (minor_q.size()) {
                    auto t = minor_q.top();
                    if (t.val < arr[i].val) {
                        res += arr[i].val - t.val;
                        minor_q.pop(); minor_q.push(arr[i]);
                    }
                }
            } else {
                cur_time ++ ;
                res += arr[i].val;
                minor_q.push(arr[i]);
            }
        }
    }

    cout << main_cnt << " " << res << endl;

    return 0;
}