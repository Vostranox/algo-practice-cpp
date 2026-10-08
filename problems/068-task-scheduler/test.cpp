#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<char> tasks, int n, int want) {
    vector<char> arg = tasks;
    check(Solution().leastInterval(arg, n), want, "tasks", tasks, "n", n);
}

static vector<char> chars(const string& s) { return vector<char>(s.begin(), s.end()); }

static int brute(const vector<char>& tasks, int n) {
    vector<char> labels = sorted(tasks);
    labels.erase(unique(labels.begin(), labels.end()), labels.end());
    int L = labels.size();
    vector<int> cnt(L, 0);
    for (char c : tasks) {
        ++cnt[find(labels.begin(), labels.end(), c) - labels.begin()];
    }
    using State = pair<vector<int>, vector<int>>;
    set<State> seen{{cnt, vector<int>(L, 0)}};
    vector<State> frontier(seen.begin(), seen.end());
    for (int steps = 0;; ++steps) {
        for (auto& [c, w] : frontier) {
            if (accumulate(c.begin(), c.end(), 0) == 0) return steps;
        }
        vector<State> next;
        for (auto& [c, w] : frontier) {
            vector<int> after = w;
            for (int& x : after) {
                x = max(0, x - 1);
            }
            vector<State> moves{{c, after}};
            for (int j = 0; j < L; ++j) {
                if (c[j] && w[j] == 0) {
                    State s{c, after};
                    --s.first[j];
                    s.second[j] = n;
                    moves.push_back(s);
                }
            }
            for (auto& s : moves) {
                if (seen.insert(s).second) {
                    next.push_back(s);
                }
            }
        }
        frontier = next;
    }
}

TEST(examples) {
    run(chars("XXXY"), 2, 7);
    run(chars("ABCABC"), 1, 6);
    run(chars("PPPRRRS"), 2, 8);
}

TEST(edge_cases) {
    run(chars("K"), 0, 1);
    run(chars("K"), 100, 1);
    run(chars("QQQQ"), 0, 4);
    run(chars("QQ"), 100, 102);
    run(chars("AABB"), 3, 6);
    run(chars("ABCDEFG"), 50, 7);
    run(chars("AAABBBCCCDD"), 2, 11);
    run(chars("AAAABCDEFG"), 2, 10);
}

TEST(random) {
    Rng rng(621);
    for (int iter = 0; iter < 300; ++iter) {
        string letters = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
        vector<char> pool(letters.begin(), letters.end());
        rng.shuffle(pool);
        vector<char> tasks;
        for (int i = 0, L = rng(1, 3); i < L; ++i) {
            tasks.insert(tasks.end(), rng(1, 4), pool[i]);
        }
        rng.shuffle(tasks);
        int n = rng(0, 3);
        run(tasks, n, brute(tasks, n));
    }
}

TEST(large) {
    Rng rng(6210);
    run(vector<char>(10000, 'A'), 100, (10000 - 1) * 101 + 1);

    vector<char> tasks;
    for (int i = 0; i < 26; ++i) {
        tasks.insert(tasks.end(), i < 16 ? 385 : 384, char('A' + i));
    }
    rng.shuffle(tasks);
    run(tasks, 0, 10000);
    run(tasks, 25, 10000);
    run(tasks, 50, 384 * 51 + 16);

    tasks.assign(5000, 'Z');
    for (int i = 0; i < 25; ++i) {
        tasks.insert(tasks.end(), 200, char('A' + i));
    }
    rng.shuffle(tasks);
    run(tasks, 1, 10000);
    run(tasks, 2, 4999 * 3 + 1);
    run(tasks, 100, 4999 * 101 + 1);
}

}
