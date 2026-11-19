#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <queue>

using namespace std;

using PII = pair<int,int>;

const int INF = 0x3f3f3f3f;

int main() {
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);

	int n, m; cin >> n >> m;

	vector<int> arr(n + 1);

	for (int i = 1; i <= n; i ++ )
		cin >> arr[i];

	vector<vector<PII> > G(3 * n + 1);

	for (int i = 1; i <= m; i ++ ) {
		int a, b, c; cin >> a >> b >> c;

		for (int i = 0; i < 3; i ++ )
			G[a + i * n].push_back({b + i * n, 0});
		if (c - 1)
			for (int i = 0; i < 3; i ++ )
				G[b + i * n].push_back({a + i * n, 0});
	}
	
	for (int i = 1; i <= n; i ++ ) {
		G[i].push_back({i + n, arr[i]});
		G[i + n].push_back({i + n + n, -arr[i]});
	}

	n *= 3;

	vector<int> dist(n + 1, INF);
	vector<bool> st(n + 1, false);

	function<void()> spfa = [&]() {
		dist[1] = 0;

		queue<int> q;

		q.push(1);
		st[1] = true;

		while(q.size()) {
			int u = q.front(); q.pop(); st[u] = false;

			for (auto [v, w] : G[u]) {
				if (dist[v] > dist[u] + w) {
					dist[v] = dist[u] + w;
					if (!st[v])
						q.push(v), st[v] = true;
				}
			}
		}
	};

	spfa();

	int res = min(dist[n / 3], dist[n]);

//	for (int i = 1; i <= n; i ++ ) {
//		cout << dist[i] << " ";
//		if (i % (n / 3) == 0)
//			cout << endl;
//	}

	cout << -res << endl;

	return 0;
}
