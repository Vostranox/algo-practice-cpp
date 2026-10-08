#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

struct Model {
    vector<pair<int, int>> log;
    map<int, set<int>> follows;

    void post(int u, int t) { log.emplace_back(u, t); }
    void follow(int a, int b) {
        if (a != b) {
            follows[a].insert(b);
        }
    }
    void unfollow(int a, int b) { follows[a].erase(b); }
    vector<int> feed(int u) {
        const set<int>& f = follows[u];
        vector<int> out;
        for (auto it = log.rbegin(); it != log.rend() && out.size() < 10; ++it) {
            if (it->first == u || f.count(it->first)) {
                out.push_back(it->second);
            }
        }
        return out;
    }
};

TEST(example) {
    Trace t("Twitter");
    Twitter tw;
    CALL(t, tw, postTweet, 1, 50);
    CALL(t, tw, postTweet, 2, 7);
    EXPECT_CALL(t, (vector<int>{50}), tw, getNewsFeed, 1);
    CALL(t, tw, follow, 1, 2);
    EXPECT_CALL(t, (vector<int>{7, 50}), tw, getNewsFeed, 1);
    EXPECT_CALL(t, (vector<int>{7}), tw, getNewsFeed, 2);
    CALL(t, tw, postTweet, 1, 3);
    EXPECT_CALL(t, (vector<int>{3, 7, 50}), tw, getNewsFeed, 1);
    CALL(t, tw, unfollow, 1, 2);
    EXPECT_CALL(t, (vector<int>{3, 50}), tw, getNewsFeed, 1);
}

TEST(follow_rules) {
    Trace t("Twitter");
    Twitter tw;
    EXPECT_CALL(t, vector<int>{}, tw, getNewsFeed, 4);
    CALL(t, tw, postTweet, 4, 100);
    CALL(t, tw, follow, 4, 4);
    EXPECT_CALL(t, (vector<int>{100}), tw, getNewsFeed, 4);
    CALL(t, tw, unfollow, 4, 4);
    EXPECT_CALL(t, (vector<int>{100}), tw, getNewsFeed, 4);
    CALL(t, tw, unfollow, 4, 9);
    CALL(t, tw, follow, 4, 9);
    EXPECT_CALL(t, (vector<int>{100}), tw, getNewsFeed, 4);
    CALL(t, tw, follow, 4, 9);
    CALL(t, tw, postTweet, 9, 0);
    EXPECT_CALL(t, (vector<int>{0, 100}), tw, getNewsFeed, 4);
    CALL(t, tw, unfollow, 4, 9);
    EXPECT_CALL(t, (vector<int>{100}), tw, getNewsFeed, 4);
    EXPECT_CALL(t, (vector<int>{0}), tw, getNewsFeed, 9);
    CALL(t, tw, unfollow, 4, 9);
    CALL(t, tw, follow, 9, 4);
    EXPECT_CALL(t, (vector<int>{0, 100}), tw, getNewsFeed, 9);
}

TEST(feed_limit_and_order) {
    Trace t("Twitter");
    Twitter tw;
    for (int id : {500, 3, 9999, 42, 7, 10000, 1, 250, 66, 8, 13, 2}) {
        CALL(t, tw, postTweet, 1, id);
    }
    EXPECT_CALL(t, (vector<int>{2, 13, 8, 66, 250, 1, 10000, 7, 42, 9999}), tw, getNewsFeed, 1);
    CALL(t, tw, postTweet, 2, 5000);
    CALL(t, tw, follow, 1, 2);
    EXPECT_CALL(t, (vector<int>{5000, 2, 13, 8, 66, 250, 1, 10000, 7, 42}), tw, getNewsFeed, 1);
    CALL(t, tw, postTweet, 3, 77);
    EXPECT_CALL(t, (vector<int>{5000, 2, 13, 8, 66, 250, 1, 10000, 7, 42}), tw, getNewsFeed, 1);
    CALL(t, tw, follow, 1, 3);
    EXPECT_CALL(t, (vector<int>{77, 5000, 2, 13, 8, 66, 250, 1, 10000, 7}), tw, getNewsFeed, 1);
    EXPECT_CALL(t, (vector<int>{5000}), tw, getNewsFeed, 2);
    CALL(t, tw, unfollow, 1, 2);
    EXPECT_CALL(t, (vector<int>{77, 2, 13, 8, 66, 250, 1, 10000, 7, 42}), tw, getNewsFeed, 1);
    CALL(t, tw, postTweet, 5, 11);
    CALL(t, tw, postTweet, 6, 21);
    CALL(t, tw, postTweet, 5, 12);
    CALL(t, tw, postTweet, 6, 22);
    CALL(t, tw, postTweet, 7, 31);
    CALL(t, tw, postTweet, 5, 13);
    CALL(t, tw, follow, 5, 6);
    EXPECT_CALL(t, (vector<int>{13, 22, 12, 21, 11}), tw, getNewsFeed, 5);
    CALL(t, tw, follow, 5, 7);
    EXPECT_CALL(t, (vector<int>{13, 31, 22, 12, 21, 11}), tw, getNewsFeed, 5);
    EXPECT_CALL(t, (vector<int>{22, 21}), tw, getNewsFeed, 6);
    EXPECT_CALL(t, (vector<int>{31}), tw, getNewsFeed, 7);
}

TEST(random) {
    Rng rng(355);
    for (int round = 0; round < 5; ++round) {
        Model model;
        vector<int> ids(10001);
        iota(ids.begin(), ids.end(), 0);
        rng.shuffle(ids);
        ids.resize(3000);
        Trace t("Twitter");
        Twitter tw;
        for (int i = 0; i < 6000; ++i) {
            double r = rng.real();
            int a = rng(1, 8), b = rng(1, 8);
            if (r < 0.4 && !ids.empty()) {
                int id = ids.back();
                ids.pop_back();
                model.post(a, id);
                CALL(t, tw, postTweet, a, id);
            } else if (r < 0.7) {
                EXPECT_CALL(t, model.feed(a), tw, getNewsFeed, a);
            } else if (r < 0.85) {
                model.follow(a, b);
                CALL(t, tw, follow, a, b);
            } else {
                model.unfollow(a, b);
                CALL(t, tw, unfollow, a, b);
            }
        }
    }
}

TEST(large) {
    Rng rng(3550);
    Model model;
    Trace t("Twitter");
    Twitter tw;
    for (int v = 2; v <= 21; ++v) {
        model.follow(1, v);
        CALL(t, tw, follow, 1, v);
    }
    vector<int> ids(10001);
    iota(ids.begin(), ids.end(), 0);
    rng.shuffle(ids);
    for (int i = 0; i < 10000; ++i) {
        int u = rng(1, 60);
        model.post(u, ids[i]);
        CALL(t, tw, postTweet, u, ids[i]);
    }
    for (int i = 0; i < 15000; ++i) {
        int u = rng.coin(0.95) ? 1 : rng(2, 60);
        EXPECT_CALL(t, model.feed(u), tw, getNewsFeed, u);
    }
}

}
