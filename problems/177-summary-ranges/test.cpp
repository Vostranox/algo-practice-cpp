#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const vector<int>& nums, const vector<string>& want) {
    vector<int> arg = nums;
    check(Solution().summaryRanges(arg), want, "nums", nums);
}

static vector<string> ranges(const vector<int>& nums) {
    set<int64_t> present(nums.begin(), nums.end());
    vector<string> out;
    for (int64_t x : present) {
        if (present.count(x - 1)) continue;
        int64_t end = x;
        while (present.count(end + 1)) {
            ++end;
        }
        out.push_back(end == x ? to_string(x) : to_string(x) + "->" + to_string(end));
    }
    return out;
}

TEST(examples) {
    run({0, 1, 2, 5, 7, 8}, {"0->2", "5", "7->8"});
    run({-3, -2, 4, 6, 7, 8, 10}, {"-3->-2", "4", "6->8", "10"});
    run({}, {});
}

TEST(edge_cases) {
    run({9}, {"9"});
    run({1, 3}, {"1", "3"});
    run({-1, 0, 1}, {"-1->1"});
    run({-5, -4, -3, 0}, {"-5->-3", "0"});
    run({0, 2, 3, 4, 6}, {"0", "2->4", "6"});
    run({10, 11, 13, 14}, {"10->11", "13->14"});
    run({0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19}, {"0->19"});
}

TEST(int_limits) {
    run({INT_MIN}, {"-2147483648"});
    run({INT_MAX}, {"2147483647"});
    run({INT_MIN, INT_MAX}, {"-2147483648", "2147483647"});
    run({INT_MIN, INT_MIN + 1}, {"-2147483648->-2147483647"});
    run({INT_MAX - 1, INT_MAX}, {"2147483646->2147483647"});
    run({INT_MIN, -1, 0, INT_MAX}, {"-2147483648", "-1->0", "2147483647"});
    run({INT_MIN, INT_MIN + 1, INT_MAX - 1, INT_MAX}, {"-2147483648->-2147483647", "2147483646->2147483647"});
    run({INT_MIN + 1, INT_MAX - 1}, {"-2147483647", "2147483646"});
}

TEST(random) {
    Rng rng(228);
    for (int it = 0; it < 1000; ++it) {
        int64_t base = rng.pick(vector<int64_t>{0, -12, static_cast<int64_t>(INT_MIN), static_cast<int64_t>(INT_MAX) - 24});
        set<int> pick;
        int n = rng(0, 20);
        while (static_cast<int>(pick.size()) < n) {
            pick.insert(static_cast<int>(base + rng(0, 24)));
        }
        vector<int> nums(pick.begin(), pick.end());
        run(nums, ranges(nums));
    }
}

}
