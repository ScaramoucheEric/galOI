#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <functional>
#include <algorithm>

using namespace std;

// 颜色映射:
// 0 = 白色 (U)  上
// 1 = 黄色 (D)  下
// 2 = 绿色 (L)  左
// 3 = 蓝色 (R)  右
// 4 = 红色 (F)  前
// 5 = 橙色 (B)  后

struct RubikState {
    array<array<int, 9>, 6> colors; // 6个面，每个面9个格子

    bool operator==(const RubikState& other) const {
        return colors == other.colors;
    }
};

// 旋转一个面顺时针90度
void rotateFaceClockwise(array<int, 9>& face) {
    array<int, 9> newFace;
    newFace[0] = face[6];
    newFace[1] = face[3];
    newFace[2] = face[0];
    newFace[3] = face[7];
    newFace[4] = face[4];
    newFace[5] = face[1];
    newFace[6] = face[8];
    newFace[7] = face[5];
    newFace[8] = face[2];
    face = newFace;
}

void rotateFaceCounterClockwise(array<int, 9>& face) {
    for (int i = 0; i < 3; ++i) rotateFaceClockwise(face);
}

// U 旋转
RubikState moveU(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[0]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[4][i]; // 前
    for (int i = 0; i < 3; ++i) ns.colors[4][i] = ns.colors[2][i]; // 左->前
    for (int i = 0; i < 3; ++i) ns.colors[2][i] = ns.colors[5][i]; // 后->左
    for (int i = 0; i < 3; ++i) ns.colors[5][i] = ns.colors[3][i]; // 右->后
    for (int i = 0; i < 3; ++i) ns.colors[3][i] = temp[i]; // 原前->右
    return ns;
}

RubikState moveUprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[0]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[4][i];
    for (int i = 0; i < 3; ++i) ns.colors[4][i] = ns.colors[3][i];
    for (int i = 0; i < 3; ++i) ns.colors[3][i] = ns.colors[5][i];
    for (int i = 0; i < 3; ++i) ns.colors[5][i] = ns.colors[2][i];
    for (int i = 0; i < 3; ++i) ns.colors[2][i] = temp[i];
    return ns;
}

RubikState moveU2(const RubikState& s) {
    return moveU(moveU(s));
}

// D 旋转
RubikState moveD(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[1]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[4][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[4][6 + i] = ns.colors[3][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[3][6 + i] = ns.colors[5][8 - i];
    for (int i = 0; i < 3; ++i) ns.colors[5][8 - i] = ns.colors[2][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[2][6 + i] = temp[i];
    return ns;
}

RubikState moveDprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[1]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[4][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[4][6 + i] = ns.colors[2][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[2][6 + i] = ns.colors[5][8 - i];
    for (int i = 0; i < 3; ++i) ns.colors[5][8 - i] = ns.colors[3][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[3][6 + i] = temp[i];
    return ns;
}

RubikState moveD2(const RubikState& s) {
    return moveD(moveD(s));
}

// L 旋转
RubikState moveL(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[2]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[0][i * 3] = ns.colors[4][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[4][i * 3 + 2] = ns.colors[1][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[1][i * 3] = ns.colors[5][(2 - i) * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[5][(2 - i) * 3 + 2] = temp[i];
    return ns;
}

RubikState moveLprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[2]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[0][i * 3] = ns.colors[5][(2 - i) * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[5][(2 - i) * 3 + 2] = ns.colors[1][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[1][i * 3] = ns.colors[4][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[4][i * 3 + 2] = temp[i];
    return ns;
}

RubikState moveL2(const RubikState& s) {
    return moveL(moveL(s));
}

// R 旋转
RubikState moveR(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[3]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[0][i * 3 + 2] = ns.colors[5][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[5][i * 3] = ns.colors[1][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[1][i * 3 + 2] = ns.colors[4][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[4][i * 3] = temp[i];
    return ns;
}

RubikState moveRprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[3]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[0][i * 3 + 2] = ns.colors[4][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[4][i * 3] = ns.colors[1][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[1][i * 3 + 2] = ns.colors[5][i * 3];
    for (int i = 0; i < 3; ++i) ns.colors[5][i * 3] = temp[i];
    return ns;
}

RubikState moveR2(const RubikState& s) {
    return moveR(moveR(s));
}

// F 旋转
RubikState moveF(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[4]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[0][6 + i] = ns.colors[3][(2 - i) * 3];
    for (int i = 0; i < 3; ++i) ns.colors[3][(2 - i) * 3] = ns.colors[1][2 - i];
    for (int i = 0; i < 3; ++i) ns.colors[1][2 - i] = ns.colors[2][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[2][i * 3 + 2] = temp[i];
    return ns;
}

RubikState moveFprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[4]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[0][6 + i] = ns.colors[2][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[2][i * 3 + 2] = ns.colors[1][2 - i];
    for (int i = 0; i < 3; ++i) ns.colors[1][2 - i] = ns.colors[3][(2 - i) * 3];
    for (int i = 0; i < 3; ++i) ns.colors[3][(2 - i) * 3] = temp[i];
    return ns;
}

RubikState moveF2(const RubikState& s) {
    return moveF(moveF(s));
}

// B 旋转
RubikState moveB(const RubikState& s) {
    RubikState ns = s;
    rotateFaceClockwise(ns.colors[5]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i];
    for (int i = 0; i < 3; ++i) ns.colors[0][i] = ns.colors[3][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[3][i * 3 + 2] = ns.colors[1][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[1][6 + i] = ns.colors[2][(2 - i) * 3];
    for (int i = 0; i < 3; ++i) ns.colors[2][(2 - i) * 3] = temp[i];
    return ns;
}

RubikState moveBprime(const RubikState& s) {
    RubikState ns = s;
    rotateFaceCounterClockwise(ns.colors[5]);
    array<int, 3> temp;
    for (int i = 0; i < 3; ++i) temp[i] = ns.colors[0][i];
    for (int i = 0; i < 3; ++i) ns.colors[0][i] = ns.colors[2][(2 - i) * 3];
    for (int i = 0; i < 3; ++i) ns.colors[2][(2 - i) * 3] = ns.colors[1][6 + i];
    for (int i = 0; i < 3; ++i) ns.colors[1][6 + i] = ns.colors[3][i * 3 + 2];
    for (int i = 0; i < 3; ++i) ns.colors[3][i * 3 + 2] = temp[i];
    return ns;
}

RubikState moveB2(const RubikState& s) {
    return moveB(moveB(s));
}

// 启发函数：有多少个块不在正确位置（除以4简化）
int heuristic(const RubikState& s) {
    RubikState goal;
    for (int f = 0; f < 6; ++f)
        for (int i = 0; i < 9; ++i)
            goal.colors[f][i] = f; // 目标状态每个面颜色相同（f值即颜色）

    int diff = 0;
    for (int f = 0; f < 6; ++f)
        for (int i = 0; i < 9; ++i)
            if (s.colors[f][i] != goal.colors[f][i])
                ++diff;
    return diff / 4; // 下界估计
}

// IDA*搜索
bool dfs(const RubikState& state, int g, int bound, vector<string>& path,
         const vector<pair<string, function<RubikState(const RubikState&)>>>& moves) {
    int h = heuristic(state);
    if (g + h > bound) return false;
    if (h == 0) return true;

    for (const auto& [name, moveFunc] : moves) {
        if (!path.empty()) {
            string last = path.back();
            if ((last == "U" && name == "U'") || (last == "U'" && name == "U") ||
                (last == "U2" && name == "U2") ||
                (last == "D" && name == "D'") || (last == "D'" && name == "D") ||
                (last == "L" && name == "L'") || (last == "L'" && name == "L") ||
                (last == "R" && name == "R'") || (last == "R'" && name == "R") ||
                (last == "F" && name == "F'") || (last == "F'" && name == "F") ||
                (last == "B" && name == "B'") || (last == "B'" && name == "B"))
                continue;
        }
        path.push_back(name);
        if (dfs(moveFunc(state), g + 1, bound, path, moves))
            return true;
        path.pop_back();
    }
    return false;
}

vector<string> idaStar(const RubikState& start) {
    vector<pair<string, function<RubikState(const RubikState&)>>> moves = {
        {"U", moveU}, {"U'", moveUprime}, {"U2", moveU2},
        {"D", moveD}, {"D'", moveDprime}, {"D2", moveD2},
        {"L", moveL}, {"L'", moveLprime}, {"L2", moveL2},
        {"R", moveR}, {"R'", moveRprime}, {"R2", moveR2},
        {"F", moveF}, {"F'", moveFprime}, {"F2", moveF2},
        {"B", moveB}, {"B'", moveBprime}, {"B2", moveB2},
    };

    for (int bound = heuristic(start); ; bound += 2) {
        vector<string> path;
        if (dfs(start, 0, bound, path, moves))
            return path;
        if (bound > 30) break; // 避免无限循环
    }
    return {};
}

int main() {
    RubikState start;
    cout << "魔方颜色映射: 0=白(上) 1=黄(下) 2=绿(左) 3=蓝(右) 4=红(前) 5=橙(后)\n";
    cout << "请按顺序输入6个面, 每个面9个数字(0-5), 每面按行展开(左上到右下):\n";
    cout << "顺序: 上(U) 下(D) 左(L) 右(R) 前(F) 后(B)\n";

    for (int f = 0; f < 6; ++f) {
        cout << "输入面 " << f << " 的9个颜色值: ";
        for (int i = 0; i < 9; ++i) {
            cin >> start.colors[f][i];
        }
    }

    auto solution = idaStar(start);
    if (solution.empty()) {
        cout << "魔方已还原!\n";
    } else {
        cout << "最少步骤 (" << solution.size() << " 步): ";
        for (const auto& step : solution) cout << step << " ";
        cout << endl;
    }

    return 0;
}