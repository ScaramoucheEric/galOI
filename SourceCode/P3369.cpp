/*
    @ Author:       Eric / Sky__White
    @ Filename:     P3369.cpp
    @ Date:         04/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <algorithm>
#include <set>

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
    int n; fin >> n;

    multiset<int> st;

    while(n -- ) {
        int opt, num;
        fin >> opt;


        if (opt == 1) {
            fin >> num;
            st.insert(num);
        }
        if (opt == 2) {
            fin >> num;
            st.erase(st.lower_bound(num));
        }
        if (opt == 3) {
            fin >> num;
            auto t = st.lower_bound(num);

            int sum = 0;
            while(t != st.end())
                sum ++, t = next(t);

            cout << sum << endl;
        }
        if (opt == 4) {
            fin >> num;

            num -- ;
            cout << *next(st.begin(), num) << endl;
        }
        if (opt == 5) {
            fin >> num;
            cout << (*prev(st.lower_bound(num))) << endl;
        }
        if (opt == 6) {
            fin >> num;
            cout << (*next(st.lower_bound(num))) << endl;
        }

    }
}