#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

TEST(example) {
    Trace t("MinStack");
    MinStack s;
    CALL(t, s, push, 5);
    CALL(t, s, push, 2);
    CALL(t, s, push, 8);
    EXPECT_CALL(t, 2, s, getMin);
    CALL(t, s, pop);
    EXPECT_CALL(t, 2, s, top);
    CALL(t, s, pop);
    EXPECT_CALL(t, 5, s, getMin);
}

TEST(duplicate_minimums) {
    Trace t("MinStack");
    MinStack s;
    CALL(t, s, push, 3);
    CALL(t, s, push, 1);
    CALL(t, s, push, 1);
    EXPECT_CALL(t, 1, s, getMin);
    CALL(t, s, pop);
    EXPECT_CALL(t, 1, s, getMin);
    CALL(t, s, pop);
    EXPECT_CALL(t, 3, s, getMin);
}

TEST(extreme_values) {
    Trace t("MinStack");
    MinStack s;
    CALL(t, s, push, -2);
    EXPECT_CALL(t, -2, s, getMin);
    CALL(t, s, push, INT_MIN);
    CALL(t, s, push, INT_MAX);
    EXPECT_CALL(t, INT_MIN, s, getMin);
    EXPECT_CALL(t, INT_MAX, s, top);
    CALL(t, s, pop);
    CALL(t, s, pop);
    EXPECT_CALL(t, -2, s, getMin);
}

TEST(random_against_model) {
    Rng rng(7);
    Trace t("MinStack");
    MinStack s;
    vector<int> model;
    for (int i = 0; i < 30000; ++i) {
        double r = rng.real();
        if (model.empty() || r < 0.35) {
            int v = rng(-1000, 1000);
            model.push_back(v);
            CALL(t, s, push, v);
        } else if (r < 0.7) {
            model.pop_back();
            CALL(t, s, pop);
        } else if (r < 0.85) {
            EXPECT_CALL(t, model.back(), s, top);
        } else {
            EXPECT_CALL(t, *min_element(model.begin(), model.end()), s, getMin);
        }
    }
}

}
