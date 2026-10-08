#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void expect_stream(int k, vector<int> nums, vector<int> adds, vector<int> wants) {
    Trace t("KthLargest", k, nums);
    vector<int> arg = nums;
    KthLargest obj(k, arg);
    for (size_t i = 0; i < adds.size(); ++i) {
        EXPECT_CALL(t, wants[i], obj, add, adds[i]);
    }
}

static void model_stream(int k, vector<int> nums, const vector<int>& adds) {
    vector<int> model = sorted(nums);
    Trace t("KthLargest", k, nums);
    vector<int> arg = nums;
    KthLargest obj(k, arg);
    for (int v : adds) {
        model.insert(upper_bound(model.begin(), model.end(), v), v);
        EXPECT_CALL(t, model[model.size() - k], obj, add, v);
    }
}

TEST(examples) {
    expect_stream(2, {7, 1, 4}, {3, 8, 7, 9}, {4, 7, 7, 8});
    expect_stream(1, {}, {-5, 2, -1}, {-5, 2, 2});
}

TEST(edge_cases) {
    expect_stream(3, {5, 1}, {2, 6, 0}, {1, 2, 2});
    expect_stream(3, {4, 4, 4, 4}, {4, 5, 6, 7}, {4, 4, 4, 5});
    expect_stream(2, {-10000, 10000}, {-10000, 10000, 0}, {-10000, 10000, 10000});
    expect_stream(4, {1, 2, 3, 4}, {0, 5, 3}, {1, 2, 3});
    expect_stream(1, {3, 9, 2}, {1, 10, -7}, {9, 10, 10});
}

TEST(random) {
    Rng rng(64);
    for (int iter = 0; iter < 500; ++iter) {
        int n = rng(0, 8);
        vector<int> nums = rng.ints(n, -20, 20);
        int k = rng(1, n + 1);
        model_stream(k, nums, rng.ints(rng(1, 10), -20, 20));
    }
}

TEST(large) {
    Rng rng(703);
    vector<int> nums = rng.ints(10000, -10000, 10000);
    model_stream(5000, nums, rng.ints(10000, -10000, 10000));
    model_stream(10001, nums, rng.ints(10000, -10000, 10000));
    model_stream(1, nums, rng.ints(10000, -10000, 10000));
}

}
