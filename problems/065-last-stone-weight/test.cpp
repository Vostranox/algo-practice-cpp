#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> stones, int want) {
    vector<int> arg = stones;
    check(Solution().lastStoneWeight(arg), want, "stones", stones);
}

static int simulate(vector<int> pile) {
    while (pile.size() > 1) {
        sort(pile.begin(), pile.end());
        int y = pile.back(); pile.pop_back();
        int x = pile.back(); pile.pop_back();
        if (y != x) {
            pile.push_back(y - x);
        }
    }
    return pile.empty() ? 0 : pile[0];
}

TEST(examples) {
    run({3, 8, 5, 1}, 1);
    run({6, 6}, 0);
    run({10, 4, 2}, 4);
}

TEST(edge_cases) {
    run({1}, 1);
    run({1000}, 1000);
    run({7, 3}, 4);
    run({2, 2, 2}, 2);
    run({1, 1, 1, 1}, 0);
    run({9, 3, 3, 1}, 2);
    run(vector<int>(30, 1000), 0);
    run(vector<int>(29, 1000), 1000);
    run({1, 2, 4, 8, 16}, 1);
}

TEST(random) {
    Rng rng(1046);
    for (int iter = 0; iter < 2000; ++iter) {
        int hi = rng.pick(vector<int>{5, 50, 1000});
        vector<int> stones = rng.ints(rng(1, 30), 1, hi);
        run(stones, simulate(stones));
    }
}

}
