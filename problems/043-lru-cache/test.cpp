#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

TEST(example) {
    Trace t("LRUCache", 2);
    LRUCache c(2);
    CALL(t, c, put, 1, 10);
    CALL(t, c, put, 2, 20);
    EXPECT_CALL(t, 10, c, get, 1);
    CALL(t, c, put, 3, 30);
    EXPECT_CALL(t, -1, c, get, 2);
    CALL(t, c, put, 1, 15);
    CALL(t, c, put, 4, 40);
    EXPECT_CALL(t, -1, c, get, 3);
    EXPECT_CALL(t, 15, c, get, 1);
    EXPECT_CALL(t, 40, c, get, 4);
}

TEST(capacity_one) {
    Trace t("LRUCache", 1);
    LRUCache c(1);
    EXPECT_CALL(t, -1, c, get, 0);
    CALL(t, c, put, 0, 0);
    EXPECT_CALL(t, 0, c, get, 0);
    CALL(t, c, put, 7, 70);
    EXPECT_CALL(t, -1, c, get, 0);
    EXPECT_CALL(t, 70, c, get, 7);
    CALL(t, c, put, 7, 71);
    EXPECT_CALL(t, 71, c, get, 7);
}

TEST(updates_and_reads_refresh) {
    Trace t("LRUCache", 3);
    LRUCache c(3);
    CALL(t, c, put, 1, 1);
    CALL(t, c, put, 2, 2);
    CALL(t, c, put, 3, 3);
    CALL(t, c, put, 1, 100);
    EXPECT_CALL(t, 2, c, get, 2);
    CALL(t, c, put, 4, 4);
    EXPECT_CALL(t, -1, c, get, 3);
    EXPECT_CALL(t, 100, c, get, 1);
    EXPECT_CALL(t, -1, c, get, 5);
    CALL(t, c, put, 5, 5);
    EXPECT_CALL(t, -1, c, get, 2);
    EXPECT_CALL(t, 4, c, get, 4);
    EXPECT_CALL(t, 5, c, get, 5);
    EXPECT_CALL(t, 100, c, get, 1);
}

struct Model {
    int cap, size = 0;
    int64_t clock = 0;
    vector<int> value = vector<int>(10001, -1);
    vector<int64_t> last = vector<int64_t>(10001, 0);
    priority_queue<pair<int64_t, int>, vector<pair<int64_t, int>>, greater<>> heap;
    explicit Model(int cap) : cap(cap) {}
    void touch(int key) {
        last[key] = ++clock;
        heap.push({last[key], key});
    }
    int get(int key) {
        if (value[key] < 0) return -1;
        touch(key);
        return value[key];
    }
    void put(int key, int v) {
        if (value[key] < 0) {
            ++size;
        }
        value[key] = v;
        touch(key);
        while (size > cap) {
            auto [ts, k] = heap.top();
            heap.pop();
            if (value[k] >= 0 && last[k] == ts) {
                value[k] = -1, --size;
            }
        }
    }
};

TEST(random) {
    for (int s = 0; s < 200; ++s) {
        Rng rng(s);
        int cap = 1 + s % 5;
        Trace t("LRUCache", cap);
        LRUCache c(cap);
        Model m(cap);
        for (int i = 0; i < 200; ++i) {
            int key = rng(0, 8);
            if (rng.coin()) {
                EXPECT_CALL(t, m.get(key), c, get, key);
            } else {
                int value = rng(0, 100000);
                m.put(key, value);
                CALL(t, c, put, key, value);
            }
        }
    }
}

static void many_ops(uint64_t seed, int cap, int key_max, int ops) {
    Rng rng(seed);
    LRUCache c(cap);
    Model m(cap);
    vector<array<int, 3>> calls;
    auto name = [](const array<int, 3>& op) {
        return op[0] ? "get(" + to_string(op[1]) + ")" : "put(" + to_string(op[1]) + ", " + to_string(op[2]) + ")";
    };
    for (int i = 0; i < ops; ++i) {
        int key = rng(0, key_max);
        if (rng.coin()) {
            calls.push_back({1, key, 0});
            int want = m.get(key), got = c.get(key);
            if (got != want) {
                string recent = "LRUCache(" + to_string(cap) + ") -> ...";
                for (size_t j = calls.size() > 8 ? calls.size() - 8 : 0; j < calls.size(); ++j) {
                    recent += " -> " + name(calls[j]);
                }
                fail("operation #" + to_string(calls.size()) + ": " + name(calls.back()) + "\nexpected: " + to_string(want) +
                     "\ngot:      " + to_string(got) + "\ncalls so far: " + recent);
            }
        } else {
            int value = rng(0, 100000);
            calls.push_back({0, key, value});
            m.put(key, value);
            c.put(key, value);
        }
    }
}

TEST(large) {
    many_ops(146, 3000, 10000, 100000);
    many_ops(147, 3000, 4500, 100000);
}

}
