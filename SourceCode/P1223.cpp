#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

using PII = pair<int,int>;

signed main() {
    int n; cin >> n;
    vector<PII> arr(n + 1);
    for (int i = 1; i <= n; i ++ )
        cin >> arr[i].first, arr[i].second = i;
    
    sort(1 + all(arr));

    for (int i = 1; i <= n; i ++ )
        cout << arr[i].second << " ";
    cout << endl;
    
    int sum = 0;

    for (int i = 1; i <= n; i ++ )
        sum += (n - i) * arr[i].first;
    
    printf("%.2lf\n", sum * 1.0 / n);

    return 0;
}