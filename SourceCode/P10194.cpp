#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <unordered_map>
#include <queue>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    ios::sync_with_stdio(false);
    cin.tie(0);

    int n; cin >> n;

    vector<int> a(n + 1 + n);

    for (int i = 1; i <= n; i ++ )
        cin >> a[i], a[i + n] = i;

    vector<int> l(n + n + 1), r(n + 1 + n);
        
	l[1] = 0;
	for (int i = 2; i <= n + n; i++) {
		int x = i - 1;
		while (a[x] >= a[i] && x != 0)
			x = l[x];
		l[i] = x;
	}
	r[n + n] = n + n + 1;
	for (int i = n + n - 1; i >= 1; i--) {
		int x = i + 1;
		while (a[x] > a[i] && x != 0 && x != n + n + 1)
			x = r[x];
		r[i] = x;
    }

    int temp = 0;
	int sum = 0;
	for (int i = 1; i <= n; i++) {
		if (a[i] < a[temp] or temp == 0)
			temp = i;
		sum += a[i];
	}

    vector<int> ans(n + 1 + n);

    for (int i = temp + 1; i <= temp + n; i++) {
		if (a[i] == a[temp])
			continue;

		int x = r[i] - l[i] - 1, y = a[i] - max(a[l[i]] + 1, a[r[i]] + 1) + 1;
		ans[1] += y;
		ans[x + 1] -= y;
	}

    for (int i = 1; i <= n; i ++ )
        ans[i] += ans[i - 1];
    for (int i = 1; i <= n; i ++ )
        ans[i] += ans[i - 1];
    for (int i = 1; i <= n; i ++ )
        cout << sum - ans[i] << endl;

    return 0;
}