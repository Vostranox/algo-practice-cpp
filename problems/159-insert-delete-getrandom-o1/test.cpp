#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

[[noreturn]] static void not_member(const Trace& t, int got, const string& holds) {
    fail(t.where() + "\nproblem:  getRandom returned a value that is not in the set\ngot:      " + repr(got) +
         "\nset holds: " + holds + "\ncalls so far: " + t.recent());
}

static int random_member(Trace& t, RandomizedSet& s, const set<int>& members) {
    int got = CALL(t, s, getRandom);
    if (!members.count(got)) {
        not_member(t, got, clip(repr(members)));
    }
    return got;
}

static void expect_uniform(Trace& t, RandomizedSet& s, const set<int>& members, int samples) {
    map<int, int> seen;
    for (int v : members) {
        seen[v] = 0;
    }
    for (int i = 0; i < samples; ++i) {
        ++seen[random_member(t, s, members)];
    }
    double expected = static_cast<double>(samples) / members.size();
    for (auto [v, count] : seen) {
        if (abs(count - expected) > 0.25 * expected) {
            fail("getRandom is not uniform: over " + to_string(samples) + " calls while the set held " +
                 repr(members) + ",\n" + repr(v) + " came up " + to_string(count) + " times (expected about " +
                 to_string(static_cast<int>(expected)) + ")\nall counts: " + repr(seen));
        }
    }
}

TEST(example) {
    Trace t("RandomizedSet");
    RandomizedSet s;
    EXPECT_CALL(t, true, s, insert, 4);
    EXPECT_CALL(t, false, s, insert, 4);
    EXPECT_CALL(t, true, s, insert, 9);
    EXPECT_CALL(t, false, s, remove, 7);
    random_member(t, s, {4, 9});
    EXPECT_CALL(t, true, s, remove, 4);
    EXPECT_CALL(t, 9, s, getRandom);
}

TEST(edge_cases) {
    Trace t("RandomizedSet");
    RandomizedSet s;
    EXPECT_CALL(t, false, s, remove, 0);
    EXPECT_CALL(t, true, s, insert, INT_MIN);
    for (int i = 0; i < 3; ++i) {
        EXPECT_CALL(t, INT_MIN, s, getRandom);
    }
    EXPECT_CALL(t, true, s, insert, INT_MAX);
    EXPECT_CALL(t, true, s, insert, 0);
    EXPECT_CALL(t, true, s, insert, -1);
    EXPECT_CALL(t, false, s, insert, INT_MAX);
    EXPECT_CALL(t, true, s, remove, -1);
    EXPECT_CALL(t, false, s, remove, -1);
    EXPECT_CALL(t, true, s, insert, -1);
    EXPECT_CALL(t, true, s, remove, INT_MIN);
    EXPECT_CALL(t, false, s, insert, -1);
    EXPECT_CALL(t, true, s, remove, -1);
    EXPECT_CALL(t, true, s, remove, 0);
    EXPECT_CALL(t, INT_MAX, s, getRandom);
    EXPECT_CALL(t, true, s, remove, INT_MAX);
    EXPECT_CALL(t, false, s, remove, INT_MAX);
    EXPECT_CALL(t, false, s, remove, INT_MIN);
    EXPECT_CALL(t, true, s, insert, 5);
    EXPECT_CALL(t, 5, s, getRandom);
}

TEST(get_random_is_uniform) {
    Trace t("RandomizedSet");
    RandomizedSet s;
    set<int> members;
    auto add = [&](int v) { EXPECT_CALL(t, true, s, insert, v); members.insert(v); };
    auto del = [&](int v) { EXPECT_CALL(t, true, s, remove, v); members.erase(v); };
    add(7);
    add(-3);
    expect_uniform(t, s, members, 20000);
    for (int v = 10; v <= 80; v += 10) {
        add(v);
    }
    expect_uniform(t, s, members, 20000);
    del(7), del(80), del(30), del(-3);
    expect_uniform(t, s, members, 24000);
    add(7), add(1000000000), add(-1000000000);
    expect_uniform(t, s, members, 27000);
    del(10), del(1000000000), del(20), del(7), del(50), del(-1000000000), del(60);
    expect_uniform(t, s, members, 20000);
}

struct Driver {
    RandomizedSet s;
    vector<pair<char, int>> calls;

    static string name(pair<char, int> c) {
        if (c.first == 'g') return "getRandom()";
        return (c.first == 'i' ? "insert(" : "remove(") + to_string(c.second) + ")";
    }
    [[noreturn]] void failure(const string& what) const {
        string recent = "RandomizedSet() -> ...";
        for (size_t j = calls.size() > 8 ? calls.size() - 8 : 0; j < calls.size(); ++j) {
            recent += " -> " + name(calls[j]);
        }
        fail("operation #" + to_string(calls.size()) + ": " + name(calls.back()) + "\n" + what + "\ncalls so far: " + recent);
    }
    void insert(int val, bool want) {
        calls.push_back({'i', val});
        bool got = s.insert(val);
        if (got != want) {
            failure("expected: " + repr(want) + "\ngot:      " + repr(got));
        }
    }
    void remove(int val, bool want) {
        calls.push_back({'r', val});
        bool got = s.remove(val);
        if (got != want) {
            failure("expected: " + repr(want) + "\ngot:      " + repr(got));
        }
    }
    template <class IsMember>
    void get_random(IsMember is_member, int size) {
        calls.push_back({'g', 0});
        int got = s.getRandom();
        if (!is_member(got)) {
            failure("problem:  getRandom returned a value that is not in the set (which holds " + to_string(size) +
                    " values)\ngot:      " + repr(got));
        }
    }
};

static vector<int> distinct_values(Rng& rng, int n) {
    uint32_t offset = static_cast<uint32_t>(rng.next());
    vector<int> vals(n);
    for (int i = 0; i < n; ++i) {
        vals[i] = static_cast<int>(static_cast<uint32_t>(i * 2654435761u + offset));
    }
    rng.shuffle(vals);
    return vals;
}

static void remove_newest(uint64_t seed) {
    Rng rng(seed);
    vector<int> vals = distinct_values(rng, 133333);
    vector<int> newest(vals.end() - 66665, vals.end());
    rng.shuffle(newest);
    Driver d;
    for (int v : vals) {
        d.insert(v, true);
    }
    for (int v : newest) {
        d.remove(v, true);
    }
    d.insert(newest[0], true);
    d.remove(newest[1], false);
}

static void remove_and_sample(uint64_t seed) {
    Rng rng(seed);
    const int n = 100000;
    vector<int> vals = distinct_values(rng, n);
    vector<int> order = vals;
    rng.shuffle(order);
    unordered_map<int, int> rank;
    for (int i = 0; i < n; ++i) {
        rank[order[i]] = i;
    }
    Driver d;
    for (int v : vals) {
        d.insert(v, true);
    }
    for (int i = 0; i < n / 2; ++i) {
        d.remove(order[i], true);
        d.get_random([&](int got) { auto it = rank.find(got); return it != rank.end() && it->second > i; }, n - i - 1);
    }
}

static void churn(uint64_t seed) {
    Rng rng(seed);
    const int m = 60000, step = 35791;
    auto value = [&](int k) { return static_cast<int>(INT_MIN + static_cast<int64_t>(step) * k); };
    vector<char> present(m, 0);
    int size = 0;
    Driver d;
    for (int i = 0; i < 200000; ++i) {
        double r = rng.real();
        int k = rng(0, m - 1);
        if (r < 0.45) {
            d.insert(value(k), !present[k]);
            size += !present[k];
            present[k] = 1;
        } else if (r < 0.8) {
            d.remove(value(k), present[k]);
            size -= present[k];
            present[k] = 0;
        } else if (size > 0) {
            d.get_random([&](int got) {
                int64_t off = static_cast<int64_t>(got) - INT_MIN;
                return off % step == 0 && off / step < m && present[off / step];
            }, size);
        }
    }
}

TEST(random) {
    for (int seed = 0; seed < 150; ++seed) {
        Rng rng(seed);
        Trace t("RandomizedSet");
        RandomizedSet s;
        set<int> model;
        for (int i = 0; i < 300; ++i) {
            double r = rng.real();
            int v = rng(-6, 6);
            if (r < 0.4) {
                EXPECT_CALL(t, model.count(v) == 0, s, insert, v);
                model.insert(v);
            } else if (r < 0.8) {
                EXPECT_CALL(t, model.count(v) == 1, s, remove, v);
                model.erase(v);
            } else if (!model.empty()) {
                random_member(t, s, model);
            }
        }
    }
    churn(380);
}

TEST(large) {
    remove_newest(381);
    remove_and_sample(382);
}

}
