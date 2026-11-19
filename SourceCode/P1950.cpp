#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>

namespace std {
    public:
    class Read {
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
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

class Tree {
    public:
        struct Node {
            int id, num;
        }
        
};
struct Node {
};

signed main() {
    int n, m; fin >> n >> m;
    vector<string> str(n + 1, string(m + 1));
    
    for (int i = 1; i <= n; i ++ )
        for (int j = 1; j <= m; j ++ )
            cin >> str[i][j];

    vector<vector<int> > num(n + 2, vector<int>(m + 1));

    for (int j = 1; j <= m; j ++ )
        for (int i = n; i >= 1; i -- ) {
            num[i][j] = num[i + 1][j] + str[i][j] == '.';
        }
}