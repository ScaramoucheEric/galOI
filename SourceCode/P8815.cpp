/*
    @ Author:       Eric / Sky_Yue
    @ Filename:     P8815.cpp
    @ Time:         08/04/2025
    @ Email:        acwing@foxmail.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <stack>
#include <cmath>
#include <unordered_map>

using namespace std;

const int N = 1000010;
string s;
stack<int> op, nums;
char tree[N];
int g[N][2];
int tot;
unordered_map<char, int> pro;

void calc() {
	int y = nums.top(); nums.pop(); int x = nums.top(); nums.pop();
	char opt = op.top(); op.pop();
	tot ++ ;
	tree[tot] = opt;
	g[tot][0] = x;
	g[tot][1] = y;
	nums.push(tot);
	
	return ;
}

int cnt_and, cnt_or;

int dfs(int u) {
	if (tree[u] == '1') return 1;
	if (tree[u] == '0') return 0;
	
	if (tree[u] == '|') {
		if (dfs(g[u][0])) {
			cnt_or ++ ;
			return 1;
		} else {
			return dfs(g[u][1]);
		}
	} else {
		if (dfs(g[u][0])) {
			return dfs(g[u][1]);
		} else {
			cnt_and ++ ;
			return 0;
		}
	}
}

int main() {
	pro['|'] = 1, pro['&'] = 2;
	getline(cin, s);
	for (int i = 0; i < int(s.size()); i ++ ) {
		switch(s[i]) {
			case '(': {
				op.push(s[i]);
				break;
			}
			case ')': {
				while(op.top() != '(') calc();
				op.pop();
				break;
			}
			case '&': {
				while(op.size() && pro[op.top()] >= pro[s[i]]) calc();
				op.push(s[i]);
				break;
			}
			case '|': {
				while(op.size() && pro[op.top()] >= pro[s[i]]) calc();
				op.push('|');
				break;
			}
			default: { // isdigit(s[i]) == true;
				tree[ ++ tot] = s[i];
				nums.push(tot);
				break;
			}
		}
	}
	
	while(op.size()) calc();
	
	int res = dfs(tot);
	
//	for (int i = 1; i <= tot; i ++ )
//		printf("%c ", tree[i]);
	
	printf("%d\n%d %d\n", res, cnt_and, cnt_or);
	
	return 0;
}