#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> vals) {
    ListNode* head = build_list(vals);
    vector<pair<ListNode*, int>> original;
    for (ListNode* p = head; p; p = p->next) {
        original.emplace_back(p, p->val);
    }
    sort(original.begin(), original.end());
    ListNode* got = Solution().sortList(head);
    check(list_to_vec(got), sorted(vals), "head", vals);
    bool foreign = false, changed = false;
    for (ListNode* p = got; p; p = p->next) {
        auto it = lower_bound(original.begin(), original.end(), pair<ListNode*, int>(p, INT_MIN));
        if (it == original.end() || it->first != p) {
            foreign = true;
        } else if (it->second != p->val) {
            changed = true;
        }
    }
    ensure(!foreign, "the returned list contains a node that wasn't in the input "
                     "(re-link the original nodes, don't allocate new ones)", "head", vals);
    ensure(!changed, "a node's val was changed: sort by re-linking the nodes, not by moving values "
                     "between them", "head", vals);
}

TEST(examples) {
    run({4, -2, 9, 0});
    run({3, 1, 3, 2, 1});
    run({});
}

TEST(edge_cases) {
    run({7});
    run({2, 1});
    run({1, 2});
    run({5, 5, 5, 5});
    run({1, 2, 3, 4, 5, 6});
    run({6, 5, 4, 3, 2, 1});
    run({-100000, 100000, 0, -100000, 100000});
    run({3, 1, 2, 3, 1, 2, 3});
    run({2, 1, 2, 1, 2, 1, 2, 1, 2});
}

TEST(random) {
    Rng rng(148);
    for (int i = 0; i < 500; ++i) {
        int n = rng(0, 40);
        run(rng.ints(n, -rng(0, 8), rng(0, 8)));
    }
    for (int i = 0; i < 50; ++i) {
        run(rng.ints(rng(100, 1000), -100000, 100000));
    }
}

TEST(large) {
    Rng rng(1480);
    for (int i = 0; i < 4; ++i) {
        run(rng.ints(50000, -100000, 100000));
    }
}

TEST(large_patterns) {
    Rng rng(1481);
    const int n = 50000;
    vector<int> vals = sorted(rng.ints(n, -100000, 100000));
    run(vals);
    reverse(vals.begin(), vals.end());
    run(vals);
    run(rng.ints(n, -3, 3));
    vector<int> pipe(n);
    for (int i = 0; i < n; ++i) {
        pipe[i] = min(i, n - 1 - i) * ((i & 1) ? 1 : -1);
    }
    run(pipe);
}

}
