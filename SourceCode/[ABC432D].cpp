#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
using namespace std;

typedef long long ll;
typedef __int128 ll128;

struct Rect {
    ll128 xl, xr, yl, yr;
    Rect() {}
    Rect(ll128 x1, ll128 x2, ll128 y1, ll128 y2) : xl(x1), xr(x2), yl(y1), yr(y2) {}
};

void print(ll128 x) {
    if (x == 0) {
        cout << 0;
        return;
    }
    string s;
    while (x) {
        s += char('0' + x % 10);
        x /= 10;
    }
    reverse(s.begin(), s.end());
    cout << s;
}

int main() {
    int N;
    ll X, Y;
    cin >> N >> X >> Y;
    vector<Rect> rects;
    rects.push_back(Rect(0, X-1, 0, Y-1));

    for (int i = 0; i < N; i++) {
        char c;
        ll A, B;
        cin >> c >> A >> B;
        vector<Rect> new_rects;
        for (Rect r : rects) {
            if (c == 'X') {
                if (r.xl <= A-1) {
                    Rect r1 = r;
                    r1.xr = min(r1.xr, (ll128)A-1);
                    r1.yl -= B;
                    r1.yr -= B;
                    if (r1.xl <= r1.xr && r1.yl <= r1.yr) {
                        new_rects.push_back(r1);
                    }
                }
                if (r.xr >= A) {
                    Rect r2 = r;
                    r2.xl = max(r2.xl, (ll128)A);
                    r2.yl += B;
                    r2.yr += B;
                    if (r2.xl <= r2.xr && r2.yl <= r2.yr) {
                        new_rects.push_back(r2);
                    }
                }
            } else {
                if (r.yl <= A-1) {
                    Rect r1 = r;
                    r1.yr = min(r1.yr, (ll128)A-1);
                    r1.xl -= B;
                    r1.xr -= B;
                    if (r1.xl <= r1.xr && r1.yl <= r1.yr) {
                        new_rects.push_back(r1);
                    }
                }
                if (r.yr >= A) {
                    Rect r2 = r;
                    r2.yl = max(r2.yl, (ll128)A);
                    r2.xl += B;
                    r2.xr += B;
                    if (r2.xl <= r2.xr && r2.yl <= r2.yr) {
                        new_rects.push_back(r2);
                    }
                }
            }
        }
        rects = new_rects;
    }

    int n = rects.size();
    vector<ll128> areas(n);
    for (int i = 0; i < n; i++) {
        areas[i] = (rects[i].xr - rects[i].xl + 1) * (rects[i].yr - rects[i].yl + 1);
    }

    vector<vector<int>> graph(n);
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            Rect a = rects[i];
            Rect b = rects[j];
            if ((a.xr + 1 == b.xl || b.xr + 1 == a.xl)) {
                ll128 y_low = max(a.yl, b.yl);
                ll128 y_high = min(a.yr, b.yr);
                if (y_low <= y_high) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                    continue;
                }
            }
            if ((a.yr + 1 == b.yl || b.yr + 1 == a.yl)) {
                ll128 x_low = max(a.xl, b.xl);
                ll128 x_high = min(a.xr, b.xr);
                if (x_low <= x_high) {
                    graph[i].push_back(j);
                    graph[j].push_back(i);
                }
            }
        }
    }

    vector<bool> visited(n, false);
    vector<ll128> comp_areas;
    for (int i = 0; i < n; i++) {
        if (!visited[i]) {
            queue<int> q;
            q.push(i);
            visited[i] = true;
            ll128 total = 0;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                total += areas[u];
                for (int v : graph[u]) {
                    if (!visited[v]) {
                        visited[v] = true;
                        q.push(v);
                    }
                }
            }
            comp_areas.push_back(total);
        }
    }

    sort(comp_areas.begin(), comp_areas.end());
    cout << comp_areas.size() << endl;
    for (int i = 0; i < comp_areas.size(); i++) {
        print(comp_areas[i]);
        if (i < comp_areas.size()-1) cout << " ";
    }
    cout << endl;

    return 0;
}