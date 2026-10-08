#include "prelude.hpp"

class Twitter {
    using Tweets = vector<pair<int, int>>;
    int time = 0;
    unordered_map<int, Tweets> tweets;
    unordered_map<int, unordered_set<int>> following;

public:
    Twitter() {}

    void postTweet(int userId, int tweetId) { tweets[userId].emplace_back(time++, tweetId); }

    vector<int> getNewsFeed(int userId) {
        vector<tuple<int, int, const Tweets*>> heap;
        auto add_user = [&](int u) {
            auto it = tweets.find(u);
            if (it != tweets.end()) {
                heap.emplace_back(it->second.back().first, static_cast<int>(it->second.size()) - 1, &it->second);
            }
        };
        auto f = following.find(userId);
        heap.reserve(1 + (f == following.end() ? 0 : f->second.size()));
        add_user(userId);
        if (f != following.end()) {
            for (int u : f->second) {
                add_user(u);
            }
        }
        make_heap(heap.begin(), heap.end());
        vector<int> feed;
        while (!heap.empty() && feed.size() < 10) {
            pop_heap(heap.begin(), heap.end());
            auto [t, i, list] = heap.back();
            heap.pop_back();
            feed.push_back((*list)[i].second);
            if (i > 0) {
                heap.emplace_back((*list)[i - 1].first, i - 1, list);
                push_heap(heap.begin(), heap.end());
            }
        }
        return feed;
    }

    void follow(int followerId, int followeeId) {
        if (followerId != followeeId) {
            following[followerId].insert(followeeId);
        }
    }

    void unfollow(int followerId, int followeeId) {
        if (auto f = following.find(followerId); f != following.end()) {
            f->second.erase(followeeId);
        }
    }
};
