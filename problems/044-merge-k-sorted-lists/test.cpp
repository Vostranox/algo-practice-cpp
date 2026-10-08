#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<vector<int>>& in) {
    vector<ListNode*> lists;
    vector<ListNode*> nodes;
    vector<int> all;
    for (auto& v : in) {
        lists.push_back(build_list(v));
        for (ListNode* n : list_nodes(lists.back())) {
            nodes.push_back(n);
        }
        all.insert(all.end(), v.begin(), v.end());
    }
    vector<ListNode*> arg = lists;
    ListNode* got = Solution().mergeKLists(arg);
    check(list_to_vec(got), sorted(all), "lists", in);
    bool vals_kept = true;
    for (size_t i = 0, j = 0; i < in.size(); ++i) {
        for (int v : in[i]) {
            vals_kept &= nodes[j++]->val == v;
        }
    }
    vector<ListNode*> got_nodes = list_nodes(got);
    ensure(vals_kept && set<ListNode*>(got_nodes.begin(), got_nodes.end()) == set<ListNode*>(nodes.begin(), nodes.end()),
           "the values are right, but the result must be made of the original nodes spliced together "
           "(no new nodes, no overwritten val)",
           "lists", in);
}

TEST(examples) {
    run({{2, 6, 9}, {1, 6}, {3, 4, 10}});
    run({});
    run({{}, {5}});
}

TEST(edge_cases) {
    run({{-3, 0, 8}});
    run({{}, {}, {}});
    run({{1, 1, 1}, {1, 1}, {1}});
    run({{7, 8, 9}, {4, 5, 6}, {1, 2, 3}});
    run({{-10000}, {}, {10000}, {-10000, 10000}, {}});
}

TEST(random) {
    Rng rng(23);
    for (int t = 0; t < 300; ++t) {
        vector<vector<int>> in(rng(0, 8));
        for (auto& v : in) {
            v = sorted(rng.ints(rng(0, 6), -5, 5));
        }
        run(in);
    }
}

TEST(large) {
    Rng rng(230);
    vector<vector<int>> singles(10000);
    for (auto& v : singles) {
        v = {rng(-10000, 10000)};
    }
    run(singles);
    vector<vector<int>> twenty(20);
    for (auto& v : twenty) {
        v = sorted(rng.ints(500, -10000, 10000));
    }
    run(twenty);
    vector<vector<int>> mixed(10000);
    for (int i = 0; i < 10000; i += 500) {
        mixed[i] = sorted(rng.ints(rng(0, 500), -10000, 10000));
    }
    run(mixed);
}

}
