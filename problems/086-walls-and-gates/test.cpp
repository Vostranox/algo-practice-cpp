#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Grid = vector<vector<int>>;
constexpr int INF = 2147483647;

static void run(const Grid& rooms, const Grid& want) {
    Grid got = rooms;
    Solution().wallsAndGates(got);
    if (rooms.size() * rooms[0].size() > 100 && got != want && got.size() == want.size()) {
        for (size_t r = 0; r < want.size(); ++r) {
            for (size_t c = 0; c < want[r].size() && c < got[r].size(); ++c) {
                if (got[r][c] != want[r][c]) {
                    fail("input:    <" + to_string(rooms.size()) + " x " + to_string(rooms[0].size()) +
                         " grid built in the test>\nproblem:  cell (" + to_string(r) + ", " + to_string(c) +
                         ") should be " + to_string(want[r][c]) + " but is " + to_string(got[r][c]));
                }
            }
        }
    }
    check(got, want, "rooms", rooms);
}

static Grid distances(const Grid& rooms) {
    int m = rooms.size(), n = rooms[0].size();
    Grid out = rooms;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            if (rooms[r][c] != INF) continue;
            vector<vector<int>> dist(m, vector<int>(n, -1));
            deque<pair<int, int>> q{{r, c}};
            dist[r][c] = 0;
            while (!q.empty()) {
                auto [i, j] = q.front();
                q.pop_front();
                if (rooms[i][j] == 0) {
                    out[r][c] = dist[i][j];
                    break;
                }
                int dr[] = {1, -1, 0, 0}, dc[] = {0, 0, 1, -1};
                for (int d = 0; d < 4; ++d) {
                    int x = i + dr[d], y = j + dc[d];
                    if (x >= 0 && x < m && y >= 0 && y < n && dist[x][y] < 0 && rooms[x][y] != -1) {
                        dist[x][y] = dist[i][j] + 1;
                        q.push_back({x, y});
                    }
                }
            }
        }
    }
    return out;
}

TEST(examples) {
    run({{INF, INF, 0}, {INF, -1, INF}, {0, INF, INF}}, {{2, 1, 0}, {1, -1, 1}, {0, 1, 2}});
    run({{0, -1, INF}, {INF, -1, INF}}, {{0, -1, INF}, {1, -1, INF}});
    run({{INF, INF, INF, 0}}, {{3, 2, 1, 0}});
}

TEST(edge_cases) {
    run({{INF, 0}}, {{1, 0}});
    run({{0}}, {{0}});
    run({{-1}}, {{-1}});
    run({{INF}}, {{INF}});
    run({{INF, -1}, {-1, 0}}, {{INF, -1}, {-1, 0}});
    run({{0, -1, INF}, {INF, -1, INF}, {INF, INF, INF}},
        {{0, -1, 6}, {1, -1, 5}, {2, 3, 4}});
    run({{0, INF, INF, INF, 0}}, {{0, 1, 2, 1, 0}});
    run({{0, 0}, {0, 0}}, {{0, 0}, {0, 0}});
}

TEST(random) {
    Rng rng(86);
    for (int t = 0; t < 300; ++t) {
        int m = rng(1, 8), n = rng(1, 8);
        double wall = rng.real(), gate = 0.3 * rng.real();
        Grid rooms(m, vector<int>(n));
        for (auto& row : rooms) {
            for (int& x : row) {
                double u = rng.real() * (wall + gate + 1.0);
                x = u < wall ? -1 : u < wall + gate ? 0 : INF;
            }
        }
        run(rooms, distances(rooms));
    }
}

TEST(large) {
    const int m = 250, n = 250;
    Grid rooms(m, vector<int>(n, INF)), want(m, vector<int>(n));
    rooms[0][0] = rooms[0][n - 1] = rooms[m - 1][0] = rooms[m - 1][n - 1] = 0;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            want[r][c] = min(r, m - 1 - r) + min(c, n - 1 - c);
        }
    }
    run(rooms, want);

    for (int r = 0; r < m; ++r) {
        rooms[r].assign(n, INF);
        rooms[r][0] = 0;
        iota(want[r].begin(), want[r].end(), 0);
    }
    run(rooms, want);

    vector<pair<int, int>> corridor;
    for (int r = 0; r < m; ++r) {
        for (int c = 0; c < n; ++c) {
            rooms[r][c] = c % 2 == 0 ? INF : -1;
        }
    }
    for (int c = 0; c < n; c += 2) {
        bool down = (c / 2) % 2 == 0;
        for (int i = 0; i < m; ++i) {
            corridor.push_back({down ? i : m - 1 - i, c});
        }
        if (c + 2 < n) {
            int gap = down ? m - 1 : 0;
            rooms[gap][c + 1] = INF;
            corridor.push_back({gap, c + 1});
        }
    }
    rooms[0][0] = 0;
    want = rooms;
    for (size_t steps = 0; steps < corridor.size(); ++steps) {
        want[corridor[steps].first][corridor[steps].second] = steps;
    }
    run(rooms, want);
}

}
