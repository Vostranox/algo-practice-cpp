#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(vector<int> citations, int want) {
    vector<int> arg = citations;
    check(Solution().hIndex(arg), want, "citations", citations);
}

static int brute(const vector<int>& citations) {
    for (int h = citations.size(); h > 0; --h) {
        int papers = 0;
        for (int c : citations) {
            papers += c >= h;
        }
        if (papers >= h) return h;
    }
    return 0;
}

TEST(examples) {
    run({4, 0, 6, 1, 5}, 3);
    run({2, 2, 2}, 2);
    run({0, 0}, 0);
}

TEST(edge_cases) {
    run({0}, 0);
    run({1}, 1);
    run({1000}, 1);
    run({1, 1}, 1);
    run({5, 5, 5, 5, 5}, 5);
    run({1000, 1000, 1000}, 3);
    run({0, 1, 2, 3, 4}, 2);
    run({10, 8, 5, 4, 3}, 4);
    run({1, 4, 1, 4, 1, 4}, 3);
    run({25, 8, 5, 3, 3}, 3);
}

TEST(random) {
    Rng rng(158);
    for (int i = 0; i < 500; ++i) {
        int n = rng(1, 10), hi = rng.coin() ? 12 : 1000;
        vector<int> citations = rng.ints(n, 0, hi);
        run(citations, brute(citations));
    }
}

TEST(large) {
    run(vector<int>(5000, 1000), 1000);
    run(vector<int>(5000, 0), 0);
    run(vector<int>(5000, 999), 999);
    Rng rng(1580);
    for (int iter = 0; iter < 3; ++iter) {
        vector<int> citations = rng.ints(5000, 0, 1000);
        run(citations, brute(citations));
    }
    vector<int> citations(5000);
    for (int i = 0; i < 5000; ++i) {
        citations[i] = i % 1001;
    }
    rng.shuffle(citations);
    run(citations, brute(citations));
}

}
