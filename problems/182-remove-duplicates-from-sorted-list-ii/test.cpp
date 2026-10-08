#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals) {
    ListNode* head = build_list(vals);
    vector<ListNode*> nodes = list_nodes(head);
    ListNode* got = Solution().deleteDuplicates(head);
    vector<int> want;
    vector<ListNode*> want_nodes;
    for (size_t i = 0; i < vals.size(); ++i) {
        if (count(vals.begin(), vals.end(), vals[i]) == 1) {
            want.push_back(vals[i]);
            want_nodes.push_back(nodes[i]);
        }
    }
    check(list_to_vec(got), want, "head", vals);
    ensure(list_nodes(got) == want_nodes,
           "the values are right, but the result must be the surviving original nodes "
           "(don't allocate new nodes or overwrite val)",
           "head", vals);
}

static vector<int> sorted_ints(Rng& rng, int n, int lo, int hi) { return sorted(rng.ints(n, lo, hi)); }

TEST(examples) {
    run({2, 5, 5, 6, 8, 8, 8, 9});
    run({3, 3, 3, 4, 7});
    run({6, 6});
}

TEST(edge_cases) {
    run({});
    run({1});
    run({1, 2});
    run({1, 1, 2});
    run({1, 2, 2});
    run({1, 1, 2, 2});
    run({4, 4, 4, 4, 4, 4});
    run({-100, -100, 0, 100, 100});
    run({-3, -1, 0, 2, 5});
    run({1, 1, 2, 3, 3, 4, 5, 5});
    run({1, 2, 2, 3, 4, 4, 5});
}

TEST(random) {
    Rng rng(82);
    for (int i = 0; i < 500; ++i) {
        int n = rng(0, 30), lo = rng(-100, 95);
        run(sorted_ints(rng, n, lo, lo + rng(0, 12)));
    }
}

TEST(large) {
    Rng rng(820);
    run(sorted_ints(rng, 300, -100, 100));
    run(sorted_ints(rng, 300, -10, 10));
    vector<int> vals;
    for (int v = -100; v <= 100; ++v) {
        vals.push_back(v);
        if (v % 2 == 0) {
            vals.push_back(v);
        }
    }
    vals.resize(300);
    run(vals);
    run(vector<int>(300, 100));
}

}
