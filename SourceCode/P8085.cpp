/*
    @ Author:       Eric / Sky__White
    @ Filename:     P8085.cpp
    @ Date:         06/01/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <ctime>
#include <random>
#include <map>
#include <queue>
#include <vector>
#include <unordered_map>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt, return *this;
        }
    };
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

signed main() {
    vector<string> str1, str2;

    string str;
    while(true) {
        cin >> str;
        if (str == "$")
            break;
        str1.push_back(str);
    }
    while(true) {
        cin >> str;
        if (str == "$")
            break;
        str2.push_back(str);
    }

    unordered_map<string, int> mp1, mp2;
    vector<int> A(str1.size(), -1), B(str2.size(), -1);

    for (int i = 0; i < str1.size(); i ++ ) {
        if (mp1.count(str1[i]) != 0) A[i] = mp1[str1[i]];
        mp1[str1[i]] = i;
    }
    for (int i = 0; i < str2.size(); i ++ ) {
        if (mp2.count(str2[i]) != 0) B[i] = mp2[str2[i]];
        mp1[str2[i]] = i;
    }

    for (int i : A)
        cout << i << " ";
    cout << endl;
    for (int i : B)
        cout << i << " ";
    cout << endl;

    
}