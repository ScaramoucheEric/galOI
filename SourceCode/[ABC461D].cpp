#include <iostream>
#include <vector>
#include <string>

using namespace std;

int main() {
    int H, W, K;
    cin >> H >> W >> K;

    vector<vector<int>> grid(H, vector<int>(W));
    for (int i = 0; i < H; ++i) {
        string s;
        cin >> s;
        for (int j = 0; j < W; ++j) {
            grid[i][j] = s[j] - '0';
        }
    }

    long long total = 0;
    vector<int> col_sum(W);

    for (int top = 0; top < H; ++top) {
        fill(col_sum.begin(), col_sum.end(), 0);
        for (int bottom = top; bottom < H; ++bottom) {
            for (int j = 0; j < W; ++j) {
                col_sum[j] += grid[bottom][j];
            }

            int left1 = 0, left2 = 0;
            int sum1 = 0, sum2 = 0;
            long long cnt = 0;
            for (int right = 0; right < W; ++right) {
                sum1 += col_sum[right];
                while (sum1 > K) {
                    sum1 -= col_sum[left1];
                    ++left1;
                }

                sum2 += col_sum[right];
                while (left2 <= right && sum2 > K - 1) {
                    sum2 -= col_sum[left2];
                    ++left2;
                }

                cnt += (left2 - left1);
            }
            total += cnt;
        }
    }

    cout << total << '\n';
    return 0;
}