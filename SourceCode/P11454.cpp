#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <unordered_map>
#include <map>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

using PII = pair<int,int>;

const int dx[] = {0, 0, 0,-1,+1},
          dy[] = {0,-1,+1, 0, 0};
unordered_map<char, int> mp = {{'U', 1}, {'D', 2}, {'L', 3}, {'R', 4}};

signed main() {
    int n, m; cin >> n >> m;

    vector<PII> arr(m + 1);
    vector<string> vec(n + 1, string(m + 2, '?'));

    map<PII, PII> fa;

    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= n; j ++ )
            fa[{i, j}] = {i, j};

    for (int i = 1; i <= n; i ++ ) {
        cin >> arr[i].first >> arr[i].second;
        char ch = getchar(); ch = getchar();
        vec[arr[i].first][arr[i].second] = ch;
    }

    for (int i = 1; i <= n; i ++ ) {

    }
}