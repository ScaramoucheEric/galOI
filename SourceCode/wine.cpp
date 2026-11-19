/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     wine.cpp
    @ Time:         08/02/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <set>
#include <ctime>
#include <random>
#include <queue>
#include <cmath>

#define all(a) a.begin(), a.end()

using namespace std;

using LL = long long;

const LL INF = 0x3f3f3f3f3f3f3f3f;

signed main()
{
    freopen("wine.in", "r", stdin);
    freopen("wine.out", "w", stdout);

    srand(time(nullptr));

    int n, c; scanf("%d%d", &n, &c);

    vector<int> cup(n + 1);

    auto random = [](int l, int r) -> int {
        return rand() % (r - l + 1) + l;
    };

    for (int i = 1; i <= n; i ++ )
        scanf("%d", &cup[i]);

    vector<int> p(c + 1);

    for (int i = 0; i <= c; i ++ )
        scanf("%d", &p[i]);
    vector<int> back(cup);

    int ans = 0;

    auto calc = [&]() -> int {
        int res = 0;

        for (int i = 1; i <= n; i ++ )
            res += p[cup[i]];
        
        ans = max(ans, res);

        return res;
    };

    auto sa = [&]() -> void {
        int opt = calc();

        for (double T = 1e4; T >= 1e-4; T *= 0.97) {
            int a = random(1, n), b = random(1, n);

            if (a == b) continue;
            int ta = cup[a], tb = cup[b];
            if (cup[a] + cup[b] <= c)
                cup[b] += cup[a], cup[a] = 0;
            else
                cup[b] = c, cup[a] -= c - tb;

            int new_opt = calc();
            int delta = new_opt - opt;

            if (exp(delta / T) > rand() * 1.0 / RAND_MAX)
                opt = new_opt;
            else
                cup[a] = ta, cup[b] = tb;
        }
    };
    do {
        sa();
        cup = back;
    } while((double)clock() / CLOCKS_PER_SEC < 0.85);
    
    cout << ans << endl;
    
    return 0;
}   