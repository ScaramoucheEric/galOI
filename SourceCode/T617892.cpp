/*
    @ Author:       Eric / Sky__White
    @ Filename:     T617892.cpp
    @ Time:         12/31/2025
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <functional>

using namespace std;

int main() {
    int T; cin >> T;

    while (T -- ) {
        int r, q, n, m;
        cin >> r >> q >> n >> m;
        int l = m / 3;
        bool ok = false;
        if (q == 0) {
            ok = (r <= m);
        } else {
            if (n < l) {
                ok = (r <= m);
            } else {
                int L = 0, R = q, mid = 0;

                while(L <= R) {
                    mid = L + R >> 1;

                    cout << r << " " << mid << " " << mid * (n - l) << " " << m << " " << r - mid * (n - l) << endl;
                    if (r - mid * (n - l) <= m and r >= mid * n and r - mid * (n - l) > 0 and ) {
                        ok = true;
                        break;
                    }
                    if (r - mid * (n - l) > m and r >= mid * n) {
                        L = mid + 1;
                    } else {
                        R = mid - 1;
                    }
                }
            }
        }
        cout << (ok ? "Yes" : "No") << endl;
    }
    return 0;
}