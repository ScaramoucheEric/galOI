/*
    @ Author:       Eric / Sky__White
    @ Filename:     P6136.cpp
    @ Date:         19/08/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <cstdio>
#include <vector>
#include <functional>
#include <array>

namespace std {
    class Read {
        public:
        template<typename T>
        inline Read &operator >> (T & x) {
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
#define IO(x) froepen(x ".in", "r", stdin), freopen(x ".out", "w", stdout)

using namespace std; Read fin;

class Splay {
    public:
    struct Node {
        int val, cnt, size;
        array<int, 2> son;

        Node(int val = 0, int cnt = 1, int size = 1) : val(val), cnt(cnt), size(size) {
            son[0] = son[1] = 0;
        }
    }; vector<Node> t;

    int root;

    int make(int val) {
        t.push_back(0);
        return t.size() - 1;
    }

    int insert(int val) {
        if(!root) {
            root = make(val);
            return root;
        }
        int cur = root;
        while(true) {
            if(val == t[cur].val) {
                t[cur].cnt++;
                t[cur].size++;
                return cur;
            }
            int nxt = (val > t[cur].val);
            if(!t[cur].son[nxt]) {
                t[cur].son[nxt] = make(val);
                t[t[cur].son[nxt]].size = t[cur].size + 1;
                split(t[cur].son[nxt]);
                return t[cur].son[nxt];
            }
            cur = t[cur].son[nxt];
        }
    }

    void split(int cur) {
        if(!cur) return;
        split(t[cur].son[0]);
        split(t[cur].son[1]);
        t[cur].size = t[t[cur].son[0]].size + t[t[cur].son[1]].size + t[cur].cnt;
    }

    void merge(int cur) {
        if(!cur) return;
        merge(t[cur].son[0]);
        merge(t[cur].son[1]);
        t[cur].size = t[t[cur].son[0]].size + t[t[cur].son[1]].size + t[cur].cnt;
    }

    int find(int val) {
        int cur = root;
        while(cur) {
            if(val == t[cur].val) return cur;
            int nxt = (val > t[cur].val);
            cur = t[cur].son[nxt];
        }
        return -1;
    }

    int findk(int k) {
        int cur = root;
        while(cur) {
            if(t[t[cur].son[0]].size >= k) cur = t[cur].son[0];
            else if(t[t[cur].son[0]].size + t[cur].cnt >= k) return cur;
            else k -= t[t[cur].son[0]].size + t[cur].cnt, cur = t[cur].son[1];
        }
    }

    int findpre(int val) {
        int cur = root, pre = -1;
        while(cur) {
            if (val == t[cur].val) return pre;
            if (val > t[cur].val) pre = cur, cur = t[cur].son[1];
            else cur = t[cur].son[0];
        }
        return pre;
    }

    int findnext(int val) {
        int cur = root, next = -1;
        while(cur) {
            if (val == t[cur].val) return next;
            if (val < t[cur].val) next = cur, cur = t[cur].son[0];
            else cur = t[cur].son[1];
        }
        return next;
    }

    int erase(int val) {
        int cur = find(val);
        if (cur == -1) return -1;
        int pre = findpre(val), next = findnext(val);
        if (pre != -1) split(pre);
        if (next != -1) split(next);
    }

    int findsum(int val) {
        int cut = root;
        if (val) cut = find(val);
        split(cut);
        int res = t[cut].size;
        if (val) merge(cut), merge(cut);
        return res;
    }
};

signed main() {
    int n, m; fin >> n >> m;

    Splay T;

    for (int i = 1, x; i <= n; i ++ ) fin >> x, T.insert(x);

    vector<int> T(n + 1);

    int last = 0;
    while(m -- ) {
        int opt, x; fin >> opt >> x;
        x ^= last;
        if (opt == 1) T.insert(x);
        else if (opt == 2) T.erase(x) ^ last;
        else if (opt == 3) last = T.findsum(x) ^ last;
        else if (opt == 4) last = T.findk(x) ^ last;
        else if (opt == 5) last = T.findpre(x) ^ last;
        else last = T.findnext(x) ^ last;
    }
}