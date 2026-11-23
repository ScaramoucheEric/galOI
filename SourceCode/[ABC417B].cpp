/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     [ABC417B].cpp
    @ Time:         08/02/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <set>
#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    int n, m; scanf("%d%d", &n, &m);

    multiset<int> a;

    for (int i = 1; i <= n; i ++ ) {
        int x; scanf("%d", &x);
        a.insert(x);
    }

    for (int j = 1; j <= m; j ++ ) {
        int x; scanf("%d", &x);
        auto it = a.find(x);
        if (it != a.end())
            a.erase(it);
    }

    for (auto i : a)
        printf("%d ", i);
    puts("");
}