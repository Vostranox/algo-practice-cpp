#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

TEST(example) {
    Trace t("TimeMap");
    TimeMap m;
    CALL(t, m, set, "color", "red", 2);
    CALL(t, m, set, "color", "blue", 6);
    EXPECT_CALL(t, "", m, get, "color", 1);
    EXPECT_CALL(t, "red", m, get, "color", 2);
    EXPECT_CALL(t, "red", m, get, "color", 5);
    EXPECT_CALL(t, "blue", m, get, "color", 6);
    EXPECT_CALL(t, "blue", m, get, "color", 100);
    EXPECT_CALL(t, "", m, get, "size", 6);
}

TEST(several_keys) {
    Trace t("TimeMap");
    TimeMap m;
    EXPECT_CALL(t, "", m, get, "a", 1);
    CALL(t, m, set, "a", "x", 1);
    CALL(t, m, set, "b", "x", 3);
    CALL(t, m, set, "a", "y", 4);
    EXPECT_CALL(t, "x", m, get, "a", 1);
    EXPECT_CALL(t, "x", m, get, "a", 3);
    EXPECT_CALL(t, "", m, get, "b", 2);
    EXPECT_CALL(t, "x", m, get, "b", 3);
    CALL(t, m, set, "b", "z", 9);
    EXPECT_CALL(t, "x", m, get, "b", 8);
    EXPECT_CALL(t, "z", m, get, "b", 9);
    EXPECT_CALL(t, "y", m, get, "a", 10000000);
    EXPECT_CALL(t, "", m, get, "c", 10000000);
    EXPECT_CALL(t, "y", m, get, "a", 4);
}

TEST(edge_cases) {
    {
        Trace t("TimeMap");
        TimeMap m;
        CALL(t, m, set, "k", "v", 10000000);
        EXPECT_CALL(t, "", m, get, "k", 1);
        EXPECT_CALL(t, "", m, get, "k", 9999999);
        EXPECT_CALL(t, "v", m, get, "k", 10000000);
    }
    {
        string key(100, 'k'), val(100, '9');
        Trace t("TimeMap");
        TimeMap m;
        CALL(t, m, set, key, val, 1);
        CALL(t, m, set, key, "a", 2);
        CALL(t, m, set, key, val, 3);
        EXPECT_CALL(t, val, m, get, key, 1);
        EXPECT_CALL(t, "a", m, get, key, 2);
        EXPECT_CALL(t, val, m, get, key, 5);
        EXPECT_CALL(t, "", m, get, val, 5);
    }
}

TEST(random) {
    Rng rng(33);
    for (int round = 0; round < 40; ++round) {
        Trace t("TimeMap");
        TimeMap m;
        map<string, vector<pair<int, string>>> history;
        int now = 0;
        for (int i = 0; i < 300; ++i) {
            string key = rng.str(1, "abcd");
            if (rng.coin(0.4)) {
                now += rng(1, 5);
                string value = rng.str(1, "pqrs") + to_string(rng(0, 9));
                history[key].push_back({now, value});
                CALL(t, m, set, key, value, now);
            } else {
                int ts = rng(1, now + 5);
                string want;
                for (auto& [when, v] : history[key]) {
                    if (when <= ts) {
                        want = v;
                    }
                }
                EXPECT_CALL(t, want, m, get, key, ts);
            }
        }
    }
}

TEST(large) {
    Rng rng(981);
    TimeMap m;
    m.set("old", "first", 1);
    for (int i = 1; i < 100000; ++i) {
        m.set("key", "v" + to_string(i), 100 * i);
    }
    auto expect_get = [&](const string& key, int ts, const string& want) {
        string got = m.get(key, ts);
        if (got != want) {
            fail("after set(\"old\", \"first\", 1) and then set(\"key\", \"v<i>\", 100 * i) for i = 1 .. 99999:\n"
                 "get(" + repr(key) + ", " + to_string(ts) + ")\nexpected: " + repr(want) + "\ngot:      " + clip(repr(got)));
        }
    };
    for (int q = 0; q < 99900; ++q) {
        int ts = rng(1, 10000000);
        int i = min(ts / 100, 99999);
        expect_get("key", ts, i ? "v" + to_string(i) : string());
    }
    for (int q = 0; q < 50; ++q) {
        expect_get("old", rng(9000000, 10000000), "first");
    }
    for (int q = 0; q < 50; ++q) {
        expect_get("missing", rng(9000000, 10000000), "");
    }
}

}
