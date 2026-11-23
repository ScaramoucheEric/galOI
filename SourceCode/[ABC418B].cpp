#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstdio>
#include <functional>

using namespace std;

int main() {
    string str; cin >> str;

    int n = str.size(); str = ' ' + str;

    function<double(int,int)> calc = [&](int l, int r) -> double {
        int cnt = 0;
        
        if (r - l + 1 < 3 or str[l] != 't' or str[r] != 't')
            return 0;

        for (int i = l + 1; i <= r - 1; i ++ ) {
            cnt += str[i] == 't';
        }

        return (double)cnt / (r - l + 1 - 2);
    };

    double res = 0;
    for (int i = 1; i <= n; i ++ )
        for (int j = i + 1; j <= n; j ++ )
            res = max(res, calc(i, j));

    printf("%.17lf\n", res);

    return 0;
}