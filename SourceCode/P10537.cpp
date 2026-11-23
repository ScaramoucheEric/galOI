/*
    @ Author:       Eric / Sky__White
    @ Filename:     Untitled-1
    @ Date:         24/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <queue>
#include <set>

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
#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

int solve(int N,int M,std::vector<int> F,std::vector<std::vector<int>> S) {
    vector<int> h(N), son(N);
	for(int i = 1; i < N; i ++ )
        h[i] = son[i] = 0, son[F[i]] ++ ;

	int k = 0, cnt = 0, cnt2 = 0;

	for(int i = 0; i < N - 1; i ++ ) {
		for(int j = 0; j < M; j ++ ) {
			int x = S[j][i];
			if(!h[x]){
				cnt ++ ;
                h[x] = 1; son[F[x]] -- ;
				cnt2 += !son[F[x]] and h[F[x]];
				cnt2 += !son[S[j][i]];
			}
		}
		k += (cnt == i + 1 and cnt2 == i + 1);
	}
	return k;
}