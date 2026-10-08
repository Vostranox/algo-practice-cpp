#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> nums, int want) {
    vector<int> arg = nums;
    check(Solution().majorityElement(arg), want, "nums", nums);
}

static vector<int> make(Rng& rng, int n, int count, int maj, int lo, int hi) {
    vector<int> nums(count, maj);
    while (static_cast<int>(nums.size()) < n) {
        int x = rng(lo, hi);
        if (x != maj) {
            nums.push_back(x);
        }
    }
    rng.shuffle(nums);
    return nums;
}

TEST(examples) {
    run({2, 7, 2}, 2);
    run({5, 1, 5, 1, 5, 9, 5}, 5);
    run({-3}, -3);
}

TEST(edge_cases) {
    run({1, 1}, 1);
    run({3, 3, 4}, 3);
    run({4, 3, 3}, 3);
    run({1, 2, 3, 3, 3}, 3);
    run({7, 7, 7, 1, 2}, 7);
    run({1, 2, 1, 2, 1}, 1);
    run({2, 1, 2, 1, 2, 1, 2}, 2);
    run({6, 6, 6, 6}, 6);
    run({1000000000, -1000000000, 1000000000}, 1000000000);
    run({-1000000000, -1000000000, 1000000000}, -1000000000);
    run({0, 5, 0, 6, 0, 7, 0}, 0);
}

TEST(random) {
    Rng rng(155);
    for (int i = 0; i < 500; ++i) {
        int n = rng(1, 15);
        int maj = rng(-3, 3);
        run(make(rng, n, rng(n / 2 + 1, n), maj, -3, 3), maj);
    }
}

TEST(large) {
    Rng rng(1550);
    int n = 50000, half = n / 2 + 1;
    vector<int> nums;
    for (int i = 0; i < n - half; ++i) {
        nums.push_back(1000000000 - i);
    }
    for (int i = 0; i < half; ++i) {
        nums.push_back(-1000000000);
    }
    run(nums, -1000000000);
    rng.shuffle(nums);
    run(nums, -1000000000);
    vector<int> two(n - half, 1000000000);
    two.resize(n, 7);
    run(two, 7);
    vector<int> others = rng.ints(n - half, -1000000000, 1000000000), mixed;
    for (int& x : others) {
        x += x == 5;
    }
    for (int round = 0; round < 3; ++round) {
        rng.shuffle(others);
        mixed = others;
        mixed.resize(n, 5);
        run(mixed, 5);
    }
    run(make(rng, n, half, 123456789, -1000000000, 1000000000), 123456789);
    run(make(rng, n, half, 4, 0, 5), 4);
    run(vector<int>(n, -7), -7);
}

}
