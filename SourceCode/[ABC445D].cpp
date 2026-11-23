/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC445D].cpp
    @ Time:         02/14/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <functional>
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
    };
}

#define int long long
#define all(a) a.begin(), a.end()

using namespace std; Read fin;

struct Node {
    int id, h, w;
};

bool cmp_H(const Node& a, const Node& b) {
    return a.h > b.h;
}

bool cmp_W(const Node& a, const Node& b) {
    return a.w > b.w;
}

signed main() {
    int h, w, n; fin >> h >> w >> n;
    
    vector<Node> node(n);
    for (int i = 0; i < n; i ++) {
        node[i].id = i + 1;
        fin >> node[i].h >> node[i].w;
    }
    
    vector<pair<int, int> > pos(n);
    
    vector<Node> hS = node;
    sort(hS.begin(), hS.end(), cmp_H);
    
    vector<Node> wS = node;
    sort(wS.begin(), wS.end(), cmp_W);
    
    int cur_x = 1, cur_y = 1;
    int max_H = 0;
    
    for (auto p : hS) {
        if (cur_y + p.w - 1 > w) {
            cur_x += max_H;
            cur_y = 1;
            max_H = 0;
        }
        
        pos[p.id - 1] = {cur_x, cur_y};
        
        max_H = max(max_H, p.h);
        
        cur_y += p.w;
    }
    
    for (int i = 0; i < n; i ++) {
        cout << pos[i].first << " " << pos[i].second << "\n";
    }
    
    return 0;
}