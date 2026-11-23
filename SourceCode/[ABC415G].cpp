#include <cstring>
#include <iostream>
#include <algorithm>
#include <unordered_map>
#include <functional>
#include <cstdio>
#include <vector>

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

#define int long long
#define all(arr) arr.begin(), arr.end()

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;
using PII = pair<int, int>;

const int LIMIT = 300 * 300;

signed main() {
    int n, m; fin >> n >> m;

    unordered_map<int, int> A;
    for (int i = 1; i <= m; i ++ ) {
        int a, b; fin >> a >> b;
        A[a] = max(A[a], b);
    }
    vector<PII> arr;
    for (auto i : A) {
        arr.push_back(i);
    }

    sort(all(arr), [&](PII x, PII y) {
        return (x.first - x.second) * y.first < (y.first - y.second) * x.first;
    });

    int best_a = arr[0].first;
    int best_b = arr[0].second;
    int loss = best_a - best_b;

    int res = 0;
    int times = 0;
    if (n > LIMIT) {
        times = (n - LIMIT) / loss;
        n -= times * loss;
        res += times * best_a;
    }

    vector<int> dp(n + 1, 0);
    for (int i = 1; i <= n; i ++ ) {
        dp[i] = i;
        for (auto [a, b] : arr) {
            if (i - a >= 0)
                dp[i] = max(dp[i], dp[i - a + b] + a);
        }
    }

    cout << res + dp[n] << endl;
    return 0;
}