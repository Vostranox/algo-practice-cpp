/*
69. Design Twitter  ·  Medium  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/design-twitter/

Design a tiny Twitter: users post tweets, follow and unfollow each other, and
read a news feed of the most recent tweets they can see.

    Twitter()                          creates an empty service
    postTweet(userId, tweetId)         user userId posts a new tweet with id tweetId
    getNewsFeed(userId) -> vector<int> the ids of the 10 most recent tweets posted
                                       by userId or by anyone userId currently
                                       follows, most recent first (fewer than 10
                                       if there aren't that many; [] if none)
    follow(followerId, followeeId)     followerId starts following followeeId
    unfollow(followerId, followeeId)   followerId stops following followeeId

Details:
    - "Most recent" means posted later: calls happen one after another. Tweet ids
      are unique but say nothing about the order (a bigger id is not newer).
    - Following is one-way, and a user always sees their own tweets.
    - The feed reflects who the user follows at the moment it is requested: after
      an unfollow, that user's older tweets disappear from the feed as well.
    - These calls change nothing: following someone you already follow,
      unfollowing someone you don't follow, and follow/unfollow with
      followerId == followeeId (you can't unfollow yourself).

Example:
    Twitter()
    postTweet(1, 50)
    postTweet(2, 7)
    getNewsFeed(1) -> [50]
    follow(1, 2)
    getNewsFeed(1) -> [7, 50]
    getNewsFeed(2) -> [7]            (following is one-way)
    postTweet(1, 3)
    getNewsFeed(1) -> [3, 7, 50]
    unfollow(1, 2)
    getNewsFeed(1) -> [3, 50]

Constraints:
    1 <= userId, followerId, followeeId <= 500
    0 <= tweetId <= 10^4, and all tweet ids are unique
    at most 3 * 10^4 calls in total

Target: postTweet/follow/unfollow in O(1); getNewsFeed for a user who follows
F people in about O(F + 10 log F) -- merge the newest ends of their tweet lists
with a heap instead of sorting every tweet they can see.
*/
#include "prelude.hpp"

class Twitter {
public:
    Twitter() {
    }

    void postTweet(int userId, int tweetId) {
        throw NotImplemented();
    }

    vector<int> getNewsFeed(int userId) {
        throw NotImplemented();
    }

    void follow(int followerId, int followeeId) {
        throw NotImplemented();
    }

    void unfollow(int followerId, int followeeId) {
        throw NotImplemented();
    }
};
