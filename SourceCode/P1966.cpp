#include <cstring>
#include <iostream>
#include <map>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <cmath>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n; cin >> n;

    vector<int> a(n + 1), b(n + 1);

    for (int i = 1; i <= n; i ++ ) cin >> a[i];
    for (int i = 1; i <= n; i ++ ) cin >> b[i];

    map<int, int> st;

    vector<int> arr = a;

    sort(1 + all(a));

    a.erase(unique(1 + all(a)), a.end());

    for (int i = 1; i < a.size(); i ++ )
        st[a[i]] = i;
    
}