#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <functional>
#include <set>
#include <unordered_map>
#include <ctime>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read operator >> (T & x) {
            T sum = 0, opt = 1;
            char ch = getchar();
            while(!isdigit(ch)) opt = (ch == '-') ? -1 : 1, ch = getchar();
            while( isdigit(ch)) sum = (sum << 1) + (sum << 3) + (ch ^ 48), ch = getchar();
            x = sum * opt; return *this;
        }
    };
}

using namespace std; Read fin;

#define int long long
#define all(a) a.begin(), a.end()

signed main() {
    int n, m;
    fin >> n >> m;
    
    vector<int> arr(n + 1); set<int> st;
    for (int i = 1; i <= n; i++) {
        fin >> arr[i]; st.insert(arr[i]);
    }
    function<void()> solve = [&]() {
        int opt = 1;
        unordered_map<int, int> table;

        for (auto i : st) table[i] = opt ++ ;

        for (int i = 1; i <= n; i ++ )
            arr[i] = table[arr[i]];
        
        // for (int i = 1; i <= n; i ++ )
        //     cout << arr[i] << " ";
        // cout << endl;

        opt -- ;

        vector<vector<int> > pre(opt + 1, vector<int>(n + 2));

        for (int i = 1; i <= n; i ++ ) {
            pre[arr[i]][i] ++ ;
        }
        for (int i = 1; i <= opt; i ++ ) {
            for (int j = 1; j <= n; j ++ )
                pre[i][j] += pre[i][j - 1];
        }

        // for (int i = 1; i <= opt; i ++ ) {
        //     for (int j = 1; j <= n; j ++ )
        //         cout << pre[i][j] << " ";
        //     cout << endl;
        // }

        while(m -- ) {
            int l, r, L, R; fin >> l >> r >> L >> R;

            int ret = 0;
            
            for (int i = 1; i <= opt; i ++ ) {
                if (pre[i][r] - pre[i][l - 1] != pre[i][R] - pre[i][L - 1])
                    ret += abs(pre[i][r] - pre[i][l - 1] - pre[i][R] + pre[i][L - 1]);
                // cout << pre[i][r] - pre[i][l - 1] << " " <<  pre[i][R] - pre[i][L - 1] << endl;
                if (ret > 2) break;
            }
            // cout << ret << endl;
            if (ret == 2) puts("DA");
            else puts("NE");
        }
    };

    if (*max_element(1 + all(arr)) < 40) {
        solve();
        return 0;
    }
    
    vector<__int128> pre_sum(n + 1, 0);
    vector<__int128> pre_sq(n + 1, 0);
    vector<__int128> pre_cube(n + 1, 0);
    
    for (int i = 1; i <= n; i++) {
        pre_sum[i] = pre_sum[i - 1] + arr[i];
        pre_sq[i] = pre_sq[i - 1] + (__int128)arr[i] * arr[i];
        pre_cube[i] = pre_cube[i - 1] + (__int128)arr[i] * arr[i] * arr[i];
    }
    
    while (m--) {
        int l, r, L, R;
        fin >> l >> r >> L >> R;
        
        if ((r - l) != (R - L)) {
            cout << "NE\n";
            continue;
        }
        
        __int128 sum1 = pre_sum[r] - pre_sum[l - 1];
        __int128 sum2 = pre_sum[R] - pre_sum[L - 1];
        __int128 sq1 = pre_sq[r] - pre_sq[l - 1];
        __int128 sq2 = pre_sq[R] - pre_sq[L - 1];
        __int128 cube1 = pre_cube[r] - pre_cube[l - 1];
        __int128 cube2 =  pre_cube[R] - pre_cube[L - 1];
        
        __int128 diff_sum = sum1 - sum2;
        __int128 diff_sq = sq1 - sq2;
        __int128 diff_cube = cube1 - cube2;
        
        if (diff_sum == 0 && diff_sq == 0 && diff_cube == 0) {
            cout << "NE\n";
            continue;
        }
        
        if (diff_sum == 0) {
            cout << "NE\n";
            continue;
        }
        
        if (diff_sq % diff_sum != 0) {
            cout << "NE\n";
            continue;
        }
        
        __int128 sum_xy = diff_sq / diff_sum;
        __int128 diff_xy = diff_sum;
        
        __int128 x = (sum_xy + diff_xy) / 2;
        __int128 y = (sum_xy - diff_xy) / 2;
        
        __int128 verify_cube = (x - y) * (x * x + x * y + y * y);
        if (diff_cube != verify_cube) {
            cout << "NE\n";
            continue;
        }

        cout << "DA" << endl;
    }
    
    return 0;
}
