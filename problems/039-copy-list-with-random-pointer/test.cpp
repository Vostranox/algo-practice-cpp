#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Pairs = vector<pair<int, int>>;

static void run(Pairs pairs) {
    RandomNode* head = build_random_list(pairs);
    vector<RandomNode*> orig = random_list_nodes(head);
    auto links = [&] {
        vector<tuple<int, RandomNode*, RandomNode*>> v;
        for (auto* n : orig) {
            v.emplace_back(n->val, n->next, n->random);
        }
        return v;
    };
    auto before = links();
    RandomNode* got = Solution().copyRandomList(head);
    check(random_list_to_pairs(got), pairs, "head", pairs);
    unordered_set<RandomNode*> originals(orig.begin(), orig.end());
    for (RandomNode* n : random_list_nodes(got)) {
        ensure(!originals.count(n), "the copy must consist of new nodes, but it contains a node of the original list",
               "head", pairs);
    }
    ensure(links() == before, "the original list was changed (restore it before returning)", "head", pairs);
}

TEST(examples) {
    run({{3, -1}, {5, 0}, {9, 3}, {1, 1}});
    run({{4, 0}});
    run({});
}

TEST(edge_cases) {
    run({{7, -1}});
    run({{1, -1}, {2, -1}, {3, -1}});
    run({{2, 2}, {2, 2}, {2, 2}});
    run({{-10000, 1}, {10000, 0}});
    run({{5, 1}, {6, 1}, {7, 1}, {8, 0}});
}

TEST(random) {
    Rng rng(138);
    for (int t = 0; t < 300; ++t) {
        int n = rng(0, 12);
        Pairs pairs;
        for (int i = 0; i < n; ++i) {
            pairs.emplace_back(rng(-3, 3), rng.coin(0.25) ? -1 : rng(0, n - 1));
        }
        run(pairs);
    }
}

TEST(large) {
    Rng rng(1380);
    Pairs pairs;
    for (int i = 0; i < 1000; ++i) {
        pairs.emplace_back(rng(-10000, 10000), rng.coin(0.1) ? -1 : rng(0, 999));
    }
    run(pairs);
    Pairs self;
    for (int i = 0; i < 1000; ++i) {
        self.emplace_back(i, i);
    }
    run(self);
}

}
