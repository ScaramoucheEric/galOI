/*
    @ Author:       Eric / Sky__White
    @ Filename:     P1886.cpp
    @ Date:         06/17/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <deque>

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
    int n, m; fin >> n >> m;

    vector<int> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i];
    }

    deque<int> q;

    for (int i = 1; i <= n; i ++ ) {
        if (q.size() and arr[i] > arr[q.back()]) {
            q.push_back(i);
        } else {
            while(q.size() and arr[q.back()] > arr[i])
                q.pop_back();
            q.push_back(i);
        }

        while(i - q.front() + 1 > m)
            q.pop_front();

        if (i >= m)
            cout << arr[q.front()] << " ";
    }

    cout << endl;

    q.clear();

    for (int i = 1; i <= n; i ++ ) {
        if (q.size() and arr[i] < arr[q.back()]) {
            q.push_back(i);
        } else {
            while(q.size() and arr[q.back()] < arr[i])
                q.pop_back();
            q.push_back(i);
        }

        while(i - q.front() + 1 > m)
            q.pop_front();

        if (i >= m)
            cout << arr[q.front()] << " ";
    }
}