#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> hand, int groupSize, bool want) {
    vector<int> arg = hand;
    check(Solution().isNStraightHand(arg, groupSize), want, "hand", hand, "groupSize", groupSize);
}

static bool brute_rec(vector<int> cards, int g) {
    if (cards.empty()) return true;
    int m = static_cast<int>(cards.size()) - 1;
    for (int mask = 0; mask < (1 << m); ++mask) {
        if (__builtin_popcount(mask) != g - 1) continue;
        vector<int> group = {cards[0]}, left;
        for (int i = 0; i < m; ++i) {
            (mask >> i & 1 ? group : left).push_back(cards[i + 1]);
        }
        bool consecutive = true;
        for (int i = 0; i + 1 < g; ++i) {
            consecutive &= group[i + 1] - group[i] == 1;
        }
        if (consecutive && brute_rec(left, g)) return true;
    }
    return false;
}

static bool brute(const vector<int>& hand, int g) {
    return hand.size() % g == 0 && brute_rec(sorted(hand), g);
}

TEST(examples) {
    run({5, 1, 2, 6, 3, 4, 7, 6, 5}, 3, true);
    run({1, 2, 3, 3, 4, 6}, 3, false);
    run({8, 8}, 1, true);
}

TEST(edge_cases) {
    run({1}, 1, true);
    run({1, 1}, 2, false);
    run({2, 1}, 2, true);
    run({1, 2, 3}, 3, true);
    run({1, 2, 3}, 2, false);
    run({1, 2, 3, 4, 5, 6}, 4, false);
    run({0, 1000000000}, 2, false);
    run({999999999, 1000000000}, 2, true);
    run({1, 2, 2, 3, 3, 4}, 3, true);
    run({1, 1, 2, 2, 3, 3}, 3, true);
    run({3, 1, 4, 2, 6, 5}, 2, true);
    run({1, 3, 5, 7}, 2, false);
    run({1, 1, 2, 3}, 2, false);
    run({4, 4, 5, 5, 6, 6, 7, 7}, 4, true);
    run({10, 7, 9, 5, 8, 6}, 6, true);
    run({1, 2, 3, 4, 5, 7}, 6, false);
}

TEST(random) {
    Rng rng(846);
    for (int it = 0; it < 500; ++it) {
        int g = rng(1, 4);
        vector<int> hand;
        if (rng.coin(0.6)) {
            for (int k = rng(1, max(1, 9 / g)); k > 0; --k) {
                int s = rng(0, 4);
                for (int j = 0; j < g; ++j) {
                    hand.push_back(s + j);
                }
            }
            if (rng.coin(0.4)) {
                int& c = hand[rng(0, static_cast<int>(hand.size()) - 1)];
                c = max(0, c + (rng.coin() ? 1 : -1));
            }
        } else {
            hand = rng.ints(rng(1, 8), 0, 5);
            g = rng(1, static_cast<int>(hand.size()));
        }
        rng.shuffle(hand);
        run(hand, g, brute(hand, g));
    }
}

TEST(large) {
    Rng rng(12);
    for (int g : {2, 3, 7, 50, 1000}) {
        int groups = 10000 / g;
        vector<int> hand;
        for (int k = 0; k < groups; ++k) {
            int s = rng(0, 3 * groups);
            for (int j = 0; j < g; ++j) {
                hand.push_back(s + j);
            }
        }
        rng.shuffle(hand);
        run(hand, g, true);
        hand[rng(0, static_cast<int>(hand.size()) - 1)] = 1000000000;
        run(hand, g, false);
        int base = rng(0, 1000000);
        hand.clear();
        for (int k = 0; k < groups; ++k) {
            for (int j = 0; j < g; ++j) {
                hand.push_back(base + 2 * g * k + j);
            }
        }
        rng.shuffle(hand);
        run(hand, g, true);
        int k = rng(0, groups - 1);
        *find(hand.begin(), hand.end(), base + 2 * g * k + g - 1) += 1;
        run(hand, g, false);
    }
    vector<int> hand(10000);
    iota(hand.begin(), hand.end(), 500000000);
    rng.shuffle(hand);
    run(hand, 10000, true);
    hand[0] = hand[1];
    run(hand, 10000, false);
    hand.assign(9999, 0);
    iota(hand.begin(), hand.end(), 0);
    rng.shuffle(hand);
    run(hand, 3, true);
    *find(hand.begin(), hand.end(), 0) = 1;
    run(hand, 3, false);
}

}
