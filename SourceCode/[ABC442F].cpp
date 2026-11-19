/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC442F].cpp
    @ Time:         01/24/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
using namespace std;

string s[5000];

int dp[5001];

signed main() {
	int n, i, j, c; cin>>n;
	for(i = 0; i < n; i ++ ) cin >> s[i];
	for(j = 0; j < n; j ++ ) {
		c = 0;
		for(i = 0; i < n; i ++ ) {
			if(s[i][j] == '#') c ++ ;
		}
		dp[n] += c;
		for(i = n - 1;i > -1; i -- )
		{
			if(s[i][j] == '#') c -- ;
			else c ++ ;
			dp[i] += c;
		}
		for(i = n; i > 0; i -- )
            dp[i - 1] = min(dp[i - 1], dp[i]);
	}
    cout << dp[0] << endl;
	return 0;
}