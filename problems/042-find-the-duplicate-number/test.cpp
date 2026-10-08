#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().findDuplicate(arg), want, "nums", nums);
    ensure(arg == nums, "the answer is right, but nums was modified (it must stay unchanged)", "nums", nums,
           "nums after", arg);
}

static vector<int> make(Rng& rng, int n, int dup, int times) {
    vector<int> others;
    for (int v = 1; v <= n; ++v) {
        if (v != dup) {
            others.push_back(v);
        }
    }
    rng.shuffle(others);
    vector<int> nums(times, dup);
    nums.insert(nums.end(), others.begin(), others.begin() + (n + 1 - times));
    rng.shuffle(nums);
    return nums;
}

TEST(examples) {
    run({2, 4, 1, 3, 4}, 4);
    run({3, 1, 3, 2}, 3);
    run({2, 2, 2, 2, 2}, 2);
}

TEST(edge_cases) {
    run({1, 1}, 1);
    run({1, 3, 4, 2, 2}, 2);
    run({5, 1, 2, 3, 4, 5}, 5);
    run({1, 4, 1, 3, 1}, 1);
    run({4, 4, 4, 4, 1}, 4);
}

TEST(random) {
    Rng rng(287);
    for (int t = 0; t < 2000; ++t) {
        int n = rng(1, 12);
        int dup = rng(1, n);
        run(make(rng, n, dup, rng(2, n + 1)), dup);
    }
}

TEST(large) {
    Rng rng(2870);
    int n = 100000;
    run(make(rng, n, 77777, 2), 77777);
    run(make(rng, n, 1, 2), 1);
    run(make(rng, n, n, 50000), n);
    vector<int> worst(n + 1);
    iota(worst.begin(), worst.end() - 1, 1);
    worst.back() = n;
    run(worst, n);
}

}
