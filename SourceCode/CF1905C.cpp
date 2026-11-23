#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
#include <vector>
#include <cstdio>

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
    } fin;
}

#define int long long
#define all(a) a.begin(), a.end()

using namespace std;

void solve() {
    int n; fin >> n;

    string str; cin >> str; str = ' ' + str;

    if ([&](){
        for (int i = 2; i <= n; i ++ )
            if (str[i] < str[i - 1]) {
                return false;
            }
        return true;
    }()) {
        puts("0");
        return ;
    }
    
    char cur = 'a'; vector<int> pos; string opt;

    for (int i = n; i; i -- ) {
        if (str[i] >= cur)
            pos.push_back(i), opt.push_back(str[i]), cur = str[i];
    }

    reverse(all(opt));

    for (int i = 0; i < opt.size(); i ++ )
        str[pos[i]] = opt[i];

    // cout << str << endl;

    for (int i = 2; i <= n; i ++ )
        if (str[i] < str[i - 1]) {
            puts("-1");
            return ;
        }

    function<int(int,int)> qpow = [&](int a, int b) -> int {
        if (b == 0) return 1;
        if (b == 1) return a;

        int t = qpow(a, b >> 1);
        int res = t * t;

        return res;
    };
    
    int cnt = 1;
    
    
    for (int i = 1; i < opt.size(); i ++ ) {
        for (int i = 1; i <= n; i ++ )
            cout << i << " " << cnt << endl;
        if (opt[i] == opt[i - 1]) cnt ++ ;
        else break;
    }

    cout << opt.size() - cnt << endl;
}

signed main() {
    int T; fin >> T;

    while(T -- ) {
        solve();
    }
}