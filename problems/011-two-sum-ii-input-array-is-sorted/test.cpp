#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> numbers, int target, vector<int> want) {
    vector<int> arg = numbers;
    check(Solution().twoSum(arg, target), want, "numbers", numbers, "target", target);
}

TEST(examples) {
    run({1, 3, 4, 7, 9}, 11, {3, 4});
    run({-5, -2, 0, 3}, -7, {1, 2});
    run({2, 3, 3, 8}, 6, {2, 3});
}

TEST(edge_cases) {
    run({0, 0}, 0, {1, 2});
    run({-1000, 1000}, 0, {1, 2});
    run({-3, 1, 2, 5}, 2, {1, 4});
    run({1, 2, 3, 4, 50, 60}, 110, {5, 6});
    run({-10, -1, 1, 2}, -11, {1, 2});
    run({1, 4, 4, 9}, 8, {2, 3});
    run({-500, -500, 400}, -1000, {1, 2});
}

TEST(random) {
    Rng rng(11);
    for (int done = 0; done < 300;) {
        vector<int> numbers = sorted(rng.ints(rng(2, 9), -15, 15));
        int target = rng(-30, 30);
        vector<vector<int>> pairs;
        for (int i = 0; i < static_cast<int>(numbers.size()); ++i) {
            for (int j = i + 1; j < static_cast<int>(numbers.size()); ++j) {
                if (numbers[i] + numbers[j] == target) {
                    pairs.push_back({i + 1, j + 1});
                }
            }
        }
        if (pairs.size() == 1) {
            run(numbers, target, pairs[0]);
            ++done;
        }
    }
}

TEST(large) {
    Rng rng(1111);
    const int n = 30000;
    for (auto [a, b] : vector<pair<int, int>>{{497, 498}, {-999, 998}, {-3, 2}, {-499, -498}, {5, 6}}) {
        vector<int> numbers;
        for (int i = 0; i < n - 2; ++i) {
            numbers.push_back(4 * rng(-250, 250));
        }
        numbers.push_back(a);
        numbers.push_back(b);
        sort(numbers.begin(), numbers.end());
        int ia = int(find(numbers.begin(), numbers.end(), a) - numbers.begin());
        int ib = int(find(numbers.begin(), numbers.end(), b) - numbers.begin());
        run(numbers, a + b, {ia + 1, ib + 1});
    }
}

}
