#include "prelude.hpp"

class DetectSquares {
    vector<vector<int>> cnt = vector<vector<int>>(1001, vector<int>(1001, 0));
    vector<pair<int, int>> distinct;

public:
    DetectSquares() {}

    void add(vector<int> point) {
        if (cnt[point[0]][point[1]]++ == 0) {
            distinct.emplace_back(point[0], point[1]);
        }
    }

    int count(vector<int> point) {
        int qx = point[0], qy = point[1], total = 0;
        for (auto [x, y] : distinct) {
            if (x != qx && abs(x - qx) == abs(y - qy)) {
                total += cnt[x][y] * cnt[x][qy] * cnt[qx][y];
            }
        }
        return total;
    }
};
