#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>

namespace std {
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
}
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

int main() {
    freopen("game.in", "r", stdin);
    freopen("game.out", "w", stdout);
    int t; fin >> t;

    while (t -- ) {
        unsigned int n, k; fin >> n >> k;
        if (n < k) {
            cout << n << endl;
            continue;
        }

        unsigned int mul = 1;
        int D = 1;
        while (mul <= n / k) {
            mul *= k;
            D ++ ;
        }
        unsigned int a = n / mul;
        unsigned int R = n % mul;
        int L = D - 1;

        unsigned int base = (k - 1) * ((unsigned int)(D - 1) * D / 2);

        unsigned int mD = (a - 1) * (unsigned int)D;

        unsigned int ALL = mul - 1;
        unsigned int T = ALL - R;
        unsigned int cnt;
        if (T == 0) {
            cnt = (unsigned int)L + 1;
        } else {
            unsigned int Pow = 1;
            int P0 = L;
            for (int p = 0; p < L; ++p) {
                if (Pow >= T) { P0 = p; break; }
                if (p != L - 1) Pow *= k;
            }
            cnt = (unsigned int)(L - P0);
        }
        mD += cnt;

        cout << base + mD << endl;
    }
    return 0;
}