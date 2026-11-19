/*
    @ Author:       Eric / Sky__White
    @ Filename:     P8903.cpp
    @ Date:         11/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <cstdio>
#include <cmath>
#include <iostream>
#include <algorithm>
#include <queue>
#include <vector>

namespace std {
	class Read {
		public:
			template<typename T>
				inline Read & operator >> (T & x) {
					T sum = 0, opt = 1;
					char ch = getchar();
					while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
					while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
					x = sum * opt; return *this;
				}
	};
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

const int INF = 0x3f3f3f3f3f3f3f3f;

signed main() {
    int n, A, B; fin >> n >> A >> B;

    struct Cow {
        int p, c, x;

        bool operator < (const Cow & W) const {
            return x < W.x;
        }
    };

    vector<Cow> arr(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> arr[i].p >> arr[i].c >> arr[i].x;
    }

    sort(1 + all(arr));

    for (int i = 1; i <= n; i ++ ) {
        
    }
}