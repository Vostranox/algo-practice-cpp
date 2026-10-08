#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Pairs = vector<vector<string>>;

static void run(const Pairs& equations, const vector<double>& values, const Pairs& queries,
                const vector<double>& want) {
    Pairs eq = equations, qs = queries;
    vector<double> vals = values;
    vector<double> got = Solution().calcEquation(eq, vals, qs);
    ensure(got.size() == want.size(), "expected exactly one answer per query", "equations", equations,
           "values", values, "queries", queries, "got", got);
    for (size_t i = 0; i < want.size(); ++i) {
        check_close(got[i], want[i], "equations", equations, "values", values, "queries", queries,
                    "wrong answer for query", queries[i]);
    }
}

struct Planted {
    map<string, double> hidden;
    Pairs equations;
    vector<double> values;

    void equation(const string& a, const string& b) {
        equations.push_back({a, b});
        values.push_back(hidden.at(a) / hidden.at(b));
    }

    vector<double> answers(const Pairs& queries) const {
        map<string, string> label;
        for (auto& e : equations) {
            label[e[0]] = e[0], label[e[1]] = e[1];
        }
        for (bool changed = true; changed;) {
            changed = false;
            for (auto& e : equations) {
                string low = min(label[e[0]], label[e[1]]);
                for (auto& v : e) {
                    if (label[v] != low) {
                        label[v] = low, changed = true;
                    }
                }
            }
        }
        vector<double> out;
        for (auto& q : queries) {
            bool known = label.count(q[0]) && label.count(q[1]);
            out.push_back(known && label.at(q[0]) == label.at(q[1]) ? hidden.at(q[0]) / hidden.at(q[1]) : -1.0);
        }
        return out;
    }
};

TEST(examples) {
    run({{"x", "y"}, {"y", "z"}}, {3.0, 4.0}, {{"x", "z"}, {"z", "y"}, {"x", "x"}, {"w", "w"}, {"x", "w"}},
        {12.0, 0.25, 1.0, -1.0, -1.0});
    run({{"a", "b"}, {"c", "d"}}, {2.0, 5.0}, {{"a", "c"}, {"d", "c"}, {"b", "a"}}, {-1.0, 0.2, 0.5});
    run({{"p1", "q"}, {"r", "q"}}, {1.5, 0.5}, {{"p1", "r"}}, {3.0});
}

TEST(edge_cases) {
    run({{"a", "b"}}, {2.0}, {{"a", "b"}, {"b", "a"}, {"a", "a"}, {"b", "b"}, {"a", "c"}, {"c", "a"}, {"c", "c"}},
        {2.0, 0.5, 1.0, 1.0, -1.0, -1.0, -1.0});
    run({{"a", "bc"}, {"ab", "c"}}, {2.0, 3.0}, {{"a", "bc"}, {"ab", "c"}, {"a", "c"}, {"bc", "ab"}},
        {2.0, 3.0, -1.0, -1.0});
    run({{"a", "a"}}, {1.0}, {{"a", "a"}, {"a", "b"}}, {1.0, -1.0});
    run({{"a", "b"}, {"b", "a"}}, {4.0, 0.25}, {{"a", "b"}, {"b", "a"}}, {4.0, 0.25});
    run({{"a", "b"}, {"c", "b"}, {"c", "d"}}, {2.0, 3.0, 5.0}, {{"a", "d"}, {"d", "a"}, {"b", "d"}},
        {10.0 / 3.0, 0.3, 5.0 / 3.0});
    run({{"a", "b"}, {"c", "d"}, {"b", "c"}}, {2.0, 3.0, 4.0}, {{"a", "d"}, {"d", "a"}}, {24.0, 1.0 / 24.0});
    run({{"x1", "x10"}}, {0.5}, {{"x10", "x1"}, {"x1", "x1"}, {"x", "x1"}}, {2.0, 1.0, -1.0});
    run({{"a", "b"}, {"b", "c"}}, {20.0, 20.0}, {{"a", "c"}, {"c", "a"}}, {400.0, 0.0025});
    run({{"big", "tiny"}}, {0.001}, {{"tiny", "big"}}, {1000.0});
}

TEST(random) {
    Rng rng(197);
    for (int iter = 0; iter < 400; ++iter) {
        Planted p;
        set<string> names;
        int nvars = rng(1, 10);
        while (static_cast<int>(names.size()) < nvars) {
            names.insert(rng.str(rng(1, 3), "ab1"));
        }
        vector<string> vars(names.begin(), names.end());
        for (auto& v : vars) {
            p.hidden[v] = 0.5 + 7.5 * rng.real();
        }
        for (int i = rng(1, 20); i > 0; --i) {
            const string& a = rng.pick(vars);
            const string& b = rng.coin(0.05) ? a : rng.pick(vars);
            p.equation(a, b);
        }
        Pairs queries;
        for (int i = rng(1, 20); i > 0; --i) {
            string c = rng.pick(vars), d = rng.pick(vars);
            if (rng.coin(0.1)) {
                c = rng.str(rng(4, 5), "xyz9");
            }
            if (rng.coin(0.1)) {
                d = rng.str(rng(4, 5), "xyz9");
            }
            queries.push_back({c, d});
        }
        run(p.equations, p.values, queries, p.answers(queries));
    }
}

TEST(large) {
    Rng rng(1970);
    Planted chain;
    vector<string> v;
    for (int i = 0; i <= 20; ++i) {
        v.push_back("v" + to_string(i)), chain.hidden[v.back()] = pow(20.0, 20 - i);
    }
    for (int i = 0; i < 20; ++i) {
        if (rng.coin()) {
            chain.equation(v[i], v[i + 1]);
        } else {
            chain.equation(v[i + 1], v[i]);
        }
    }
    Pairs queries = {{"v0", "v20"}, {"v20", "v0"}, {"v5", "v15"}, {"v19", "v1"}, {"v10", "v10"}, {"v0", "v21"}};
    for (int i = 0; i < 14; ++i) {
        queries.push_back({rng.pick(v), rng.pick(v)});
    }
    run(chain.equations, chain.values, queries, chain.answers(queries));

    Planted star;
    star.hidden["h"] = 3.0;
    vector<string> leaves;
    for (int i = 1; i <= 20; ++i) {
        leaves.push_back("s" + to_string(i));
        star.hidden[leaves.back()] = 0.2 + 39.8 * rng.real();
        star.equation(leaves.back(), "h");
    }
    queries.clear();
    for (int i = 0; i < 20; ++i) {
        queries.push_back({rng.pick(leaves), rng.pick(leaves)});
    }
    run(star.equations, star.values, queries, star.answers(queries));

    Planted two;
    vector<string> left, right;
    for (int i = 0; i <= 10; ++i) {
        left.push_back("l" + to_string(i)), right.push_back("r" + to_string(i));
        two.hidden[left.back()] = 1.0 + 4.0 * rng.real();
        two.hidden[right.back()] = 1.0 + 4.0 * rng.real();
    }
    for (int i = 0; i < 10; ++i) {
        two.equation(left[i], left[i + 1]), two.equation(right[i + 1], right[i]);
    }
    queries.clear();
    for (int i = 0; i < 20; ++i) {
        auto& side = rng.coin() ? left : right;
        queries.push_back({rng.pick(side), rng.coin(0.4) ? rng.pick(&side == &left ? right : left) : rng.pick(side)});
    }
    run(two.equations, two.values, queries, two.answers(queries));
}

}
