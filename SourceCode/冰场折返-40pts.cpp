/*
    @ Author:       Eric / Sky__White
    @ Filename:     冰场折返.cpp
    @ Date:         14/07/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <cstring>
#include <iostream>
#include <algorithm>
#include <vector>
#include <functional>
#include <cstdio>
#include <queue>
#include <map>

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

using PII = pair<int, int> ;

const int INF = 0x3f3f3f3f3f3f3f3f;
const PII Null = {-1, -1};

signed main() {
    // freopen("skating.in", "r", stdin);
    // freopen("skating.out", "w", stdout);

    int N, M, n; fin >> N >> M >> n;

    PII s, t;

    fin >> s.first >> s.second >> t.first >> t.second;

    vector<PII> posi(n + 1);

    for (int i = 1; i <= n; i ++ ) {
        fin >> posi[i].first >> posi[i].second;
    }

    map<PII, vector<PII> > G;
    map<PII, bool> st;

    for (int i = 1; i <= n; i ++ ) {
        int ul, ur, lu, ld, dl, dr, ru, rd; ul = ur = lu = ld = dl = dr = ru = rd = INF;
        PII to_ul, to_ur, to_lu, to_ld, to_dl, to_dr, to_ru, to_rd; to_ul = to_ur = to_lu = to_ld = to_dl = to_dr = to_ru = to_rd = {-1, -1};
        for (int j = 1; j <= n; j ++ ) {
            if (abs(posi[i].first - posi[j].first) + abs(posi[i].second - posi[j].second) <= 2) continue;
            if (posi[i].first - 1 == posi[j].first) {
                if (posi[i].second < posi[j].second) {
                    if (dr > posi[j].second - posi[i].second)
                        dr = posi[j].second - posi[i].second, to_dr = {posi[j].first, posi[j].second - 1};
                } else {
                    if (dl > posi[i].second - posi[j].second)
                        dl = posi[i].second - posi[j].second, to_dl = {posi[j].first, posi[j].second + 1};
                }
            } else if (posi[i].first + 1 == posi[j].first) {
                if (posi[i].second < posi[j].second) {
                    if (ur > posi[j].second - posi[i].second)
                        ur = posi[j].second - posi[i].second, to_ur = {posi[j].first, posi[j].second - 1};
                } else {
                    if (ul > posi[i].second - posi[j].second)
                        ul = posi[i].second - posi[j].second, to_ul = {posi[j].first, posi[j].second + 1};
                }
            } else if (posi[i].second + 1 == posi[j].second) {
                if (posi[i].first < posi[j].first) {
                    if (ru > posi[j].first - posi[i].first)
                        ru = posi[j].first - posi[i].first, to_ru = {posi[j].first - 1, posi[j].second};
                } else {
                    if (rd > posi[i].first - posi[j].first)
                        rd = posi[i].first - posi[j].first, to_rd = {posi[j].first + 1, posi[j].second};
                }
            } else if (posi[i].second - 1 == posi[j].second) {
                if (posi[i].first < posi[j].first) {
                    if (lu > posi[j].first - posi[i].first)
                        lu = posi[j].first - posi[i].first, to_lu = {posi[j].first - 1, posi[j].second};
                } else {
                    if (ld > posi[i].first - posi[j].first)
                        ld = posi[i].first - posi[j].first, to_ld = {posi[j].first + 1, posi[j].second};
                }
            }
        }

        if (to_ur != Null) {
            G[{posi[i].first + 1, posi[i].second}].push_back(to_ur);
        }
        if (to_ul != Null) {
            G[{posi[i].first + 1, posi[i].second}].push_back(to_ul);
        }
        if (to_dr != Null) {
            G[{posi[i].first - 1, posi[i].second}].push_back(to_dr);
        }
        if (to_dl != Null) {
            G[{posi[i].first - 1, posi[i].second}].push_back(to_dl);
        }
        if (to_lu != Null) {
            G[{posi[i].first, posi[i].second - 1}].push_back(to_lu);
        }
        if (to_ld != Null) {
            G[{posi[i].first, posi[i].second - 1}].push_back(to_ld);
        }
        if (to_ru != Null) {
            G[{posi[i].first, posi[i].second + 1}].push_back(to_ru);
        }
        if (to_rd != Null) {
            G[{posi[i].first, posi[i].second + 1}].push_back(to_rd);
        }
    }
    
    int L, R, D, U; L = R = D = U = INF;
    PII to_L, to_R, to_D, to_U; to_L = to_R = to_D = to_U = Null;
    for (int j = 1; j <= n; j ++ ) {
        if (abs(s.first - posi[j].first) + abs(s.second - posi[j].second) <= 1) continue;
        if (s.first == posi[j].first) {
            if (s.second < posi[j].second) {
                if (R > posi[j].second - s.second)
                    R = posi[j].second - s.second, to_R = {posi[j].first, posi[j].second - 1};
            } else {
                if (L > s.second - posi[j].second)
                    L = s.second - posi[j].second, to_L = {posi[j].first, posi[j].second + 1};
            }
        } else if (s.second == posi[j].second) {
            if (s.first < posi[j].first) {
                if (U > posi[j].first - s.first)
                    U = posi[j].first - s.first, to_U = {posi[j].first - 1, posi[j].second};
            } else {
                if (D > s.first - posi[j].first)
                    D = s.first - posi[j].first, to_D = {posi[j].first + 1, posi[j].second};
            }
        }
    }

    // if (s.first == t.first) {
    //     if (s.second < t.second) {
    //         if (R > t.second - s.second)
    //             R = t.second - s.second, to_R = t;
    //     } else {
    //         if (L > s.second - t.second)
    //             L = s.second - t.second, to_L = t;
    //     }
    // }
    // if (s.second == t.second) {
    //     if (s.first < t.first) {
    //         if (U > t.first - s.first)
    //             U = t.first - s.first, to_U = t;
    //     } else {
    //         if (D > s.first - t.first)
    //             D = s.first - t.first, to_D = t;
    //     }
    // }

    if (to_R != Null) {
        G[s].push_back(to_R);
    }
    if (to_L != Null) {
        G[s].push_back(to_L);
    }
    if (to_U != Null) {
        G[s].push_back(to_U);
    }
    if (to_D != Null) {
        G[s].push_back(to_D);
    }

    // for (int i = 1; i <= n; i ++ ) {
    //     int ul, ur, lu, ld, dl, dr, ru, rd; ul = ur = lu = ld = dl = dr = ru = rd = INF;
    //     PII to_ul, to_ur, to_lu, to_ld, to_dl, to_dr, to_ru, to_rd; to_ul = to_ur = to_lu = to_ld = to_dl = to_dr = to_ru = to_rd = {-1, -1};

    //     if (abs(posi[i].first - t.first) + abs(posi[i].second - t.second) <= 0) continue;

    //     if (posi[i].first - 1 == t.first) {
    //         if (posi[i].second < t.second) {
    //             if (dr > t.second - posi[i].second)
    //                 dr = t.second - posi[i].second, to_dr = {t.first, t.second};
    //         } else {
    //             if (dl > posi[i].second - t.second)
    //                 dl = posi[i].second - t.second, to_dl = {t.first, t.second};
    //         }
    //     } else if (posi[i].first + 1 == t.first) {
    //         if (posi[i].second < t.second) {
    //             if (ur > t.second - posi[i].second)
    //                 ur = t.second - posi[i].second, to_ur = {t.first, t.second};
    //         } else {
    //             if (ul > posi[i].second - t.second)
    //                 ul = posi[i].second - t.second, to_ul = {t.first, t.second};
    //         }
    //     } else if (posi[i].second + 1 == t.second) {
    //         if (posi[i].first < t.first) {
    //             if (ru > t.first - posi[i].first)
    //                 ru = t.first - posi[i].first, to_ru = {t.first, t.second};
    //         } else {
    //             if (rd > posi[i].first - t.first)
    //                 rd = posi[i].first - t.first, to_rd = {t.first, t.second};
    //         }
    //     } else if (posi[i].second - 1 == t.second) {
    //         if (posi[i].first < t.first) {
    //             if (lu > t.first - posi[i].first)
    //                 lu = t.first - posi[i].first, to_lu = {t.first, t.second};
    //         } else {
    //             if (ld > posi[i].first - t.first)
    //                 ld = posi[i].first - t.first, to_ld = {t.first, t.second};
    //         }
    //     }

    //     if (to_ur != Null) {
    //         G[{posi[i].first + 1, posi[i].second}].push_back(to_ur);
    //     }
    //     if (to_ul != Null) {
    //         G[{posi[i].first + 1, posi[i].second}].push_back(to_ul);
    //     }
    //     if (to_dr != Null) {
    //         G[{posi[i].first - 1, posi[i].second}].push_back(to_dr);
    //     }
    //     if (to_dl != Null) {
    //         G[{posi[i].first - 1, posi[i].second}].push_back(to_dl);
    //     }
    //     if (to_lu != Null) {
    //         G[{posi[i].first, posi[i].second - 1}].push_back(to_lu);
    //     }
    //     if (to_ld != Null) {
    //         G[{posi[i].first, posi[i].second - 1}].push_back(to_ld);
    //     }
    //     if (to_ru != Null) {
    //         G[{posi[i].first, posi[i].second + 1}].push_back(to_ru);
    //     }
    //     if (to_rd != Null) {
    //         G[{posi[i].first, posi[i].second + 1}].push_back(to_rd);
    //     }
    // }

    queue<pair<int, PII> > q;

    q.push({0, s});
    st[s] = true;

    while(q.size()) {
        auto tt = q.front(); q.pop();
        PII u = tt.second; int step = tt.first;

        // printf("u.x = %lld; u.y = %lld; step = %lld\n", u.first, u.second, step);

        if (u == t) {
            cout << step << endl;
            return 0;
        }

        for (auto v : G[u]) {
            if (st[v]) continue;
            st[v] = true;
            if (v == t) {
                cout << step + 1 << endl;
                return 0;
            }
            q.push({step + 1, v});
        }
    }

    cout << -1 << endl;

    return 0;
}