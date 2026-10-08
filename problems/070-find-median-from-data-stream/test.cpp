#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void model_stream(const vector<int>& values) {
    vector<int> model;
    Trace t("MedianFinder");
    MedianFinder mf;
    for (int v : values) {
        model.insert(upper_bound(model.begin(), model.end(), v), v);
        CALL(t, mf, addNum, v);
        size_t m = model.size();
        double want = m % 2 ? model[m / 2] : (model[m / 2 - 1] + static_cast<double>(model[m / 2])) / 2;
        EXPECT_CALL_CLOSE(t, want, mf, findMedian);
    }
}

static void expect_medians(const vector<int>& values, const vector<double>& wants) {
    Trace t("MedianFinder");
    MedianFinder mf;
    for (size_t i = 0; i < values.size(); ++i) {
        CALL(t, mf, addNum, values[i]);
        EXPECT_CALL_CLOSE(t, wants[i], mf, findMedian);
    }
}

TEST(example) {
    expect_medians({5, -3, 10, 1}, {5.0, 1.0, 5.0, 3.0});
}

TEST(edge_cases) {
    {
        Trace t("MedianFinder");
        MedianFinder mf;
        CALL(t, mf, addNum, 1);
        CALL(t, mf, addNum, 2);
        EXPECT_CALL_CLOSE(t, 1.5, mf, findMedian);
        EXPECT_CALL_CLOSE(t, 1.5, mf, findMedian);
        CALL(t, mf, addNum, 2);
        EXPECT_CALL_CLOSE(t, 2.0, mf, findMedian);
    }
    expect_medians({-100000, 100000, 100000, -100000, 7}, {-100000.0, 0.0, 100000.0, 0.0, 7.0});
    expect_medians({100000, 100000}, {100000.0, 100000.0});
    expect_medians({9, 7, 5, 3, 1}, {9.0, 8.0, 7.0, 6.0, 5.0});
    expect_medians({-4, 0, 4, 8, 12}, {-4.0, -2.0, 0.0, 2.0, 4.0});
    expect_medians({3, 3, 3, 3, 3}, {3.0, 3.0, 3.0, 3.0, 3.0});
}

TEST(random) {
    Rng rng(295);
    for (int iter = 0; iter < 500; ++iter) {
        model_stream(rng.ints(rng(1, 15), -10, 10));
    }
}

TEST(large) {
    Rng rng(2950);
    model_stream(rng.ints(25000, -100000, 100000));
}

}
