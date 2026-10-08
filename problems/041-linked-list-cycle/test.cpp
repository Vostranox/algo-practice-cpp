#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals, int pos) {
    ListNode* head = build_cycle_list(vals, pos);
    vector<pair<int, ListNode*>> before;
    ListNode* p = head;
    for (size_t i = 0; i < vals.size(); ++i, p = p->next) {
        before.emplace_back(p->val, p->next);
    }
    bool got = Solution().hasCycle(head);
    check(got, pos >= 0, "head", vals, "pos", pos);
    vector<pair<int, ListNode*>> after;
    p = head;
    for (size_t i = 0; i < vals.size() && p; ++i, p = p->next) {
        after.emplace_back(p->val, p->next);
    }
    ensure(after == before, "the answer is right, but the list was modified", "head", vals, "pos", pos);
}

TEST(examples) {
    run({4, 1, 7, 2}, 1);
    run({6, 3}, 0);
    run({9}, -1);
}

TEST(edge_cases) {
    run({}, -1);
    run({5}, 0);
    run({1, 2}, -1);
    run({1, 2, 3, 4, 5}, 4);
    run({1, 2, 3, 4, 5}, 0);
    run({3, 3, 3, 3}, -1);
    run({3, 3, 3, 3}, 2);
}

TEST(random) {
    Rng rng(141);
    for (int t = 0; t < 500; ++t) {
        int n = rng(0, 30);
        run(rng.ints(n, -2, 2), n == 0 || rng.coin() ? -1 : rng(0, n - 1));
    }
}

TEST(large) {
    vector<int> vals(10000, 100000);
    for (int pos : {-1, 0, 5000, 9999}) {
        run(vals, pos);
    }
    Rng rng(1410);
    vector<int> mixed = rng.ints(10000, -100000, 100000);
    for (int pos : {-1, 1, 9998}) {
        run(mixed, pos);
    }
}

}
