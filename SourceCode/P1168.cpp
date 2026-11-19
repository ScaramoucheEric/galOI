#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>
#include <queue>

using namespace std;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n; cin >> n;

    priority_queue<int> q1;
    priority_queue<int, vector<int>, greater<int> > q2;

    int x; cin >> x;
    q2.push(x);
    cout << x << endl;
    for (int i = 2; i < n; i += 2) {
        cin >> x;
        if (x > q2.top()) {
            q2.push(x);
        } else {
            q1.push(x);
        }
        cin >> x;
        if (x > q2.top()) {
            q2.push(x);
        } else {
            q1.push(x);
        }

        while (q2.size() > q1.size() + 1) {
            x = q2.top(); q2.pop();
            q1.push(x);
        }
        while (q1.size() >= q2.size()) {
            x = q1.top(); q1.pop();
            q2.push(x);
        }

        cout << q2.top() << endl;
    }
}