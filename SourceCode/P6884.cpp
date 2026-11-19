#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int t = -1, num = 0;

    vector<int> bds;

    char ch;

    while(true) {
        ch = getchar();
        if (ch == '(') {
            bds.push_back(dfs());
            
        }
    }
    return 0;
}