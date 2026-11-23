/*
    @ Author:       Eric / Sky__White
    @ Filename:     [ABC450C].cpp
    @ Time:         03/21/2026
    @ Email:        acwing@foxmail.com / 17802535158@163.com
*/

#include <iostream>
#include <vector>
#include <queue>
#include <utility>

using namespace std;
const int dx[] = {0, 1, 0, -1};
const int dy[] = {1, 0, -1, 0};

int main() {
    int H, W; cin >> H >> W;
    
    vector<string> grid(H);
    for (int i = 0; i < H; i ++ ) {
        cin >> grid[i];
    }
    
    vector<vector<bool> > visited(H, vector<bool>(W, false));
    
    int ans = 0;
    
    for (int i = 0; i < H; i ++ ) {
        for (int j = 0; j < W; j ++ ) {
            if (grid[i][j] == '.' and !visited[i][j]) {
                queue<pair<int, int> > q;
                q.push({i, j});
                visited[i][j] = true;
                
                bool is_border = false;
                
                while (!q.empty()) {
                    auto [x, y] = q.front();
                    q.pop();
                    
                    if (x == 0 or x == H - 1 or y == 0 or y == W - 1)
                        is_border = true;
                    
                    for (int d = 0; d < 4; d ++ ) {
                        int nx = x + dx[d];
                        int ny = y + dy[d];
                        if (nx >= 0 and nx < H and ny >= 0 and ny < W) {
                            if (grid[nx][ny] == '.' and !visited[nx][ny]) {
                                visited[nx][ny] = true;
                                q.push({nx, ny});
                            }
                        }
                    }
                }
                
                if (!is_border) {
                    ans ++ ;
                }
            }
        }
    }
    
    cout << ans << endl;
    
    return 0;
}