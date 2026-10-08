/*
30. Koko Eating Bananas  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/koko-eating-bananas/

There are several piles of bananas; piles[i] is the number of bananas in pile i.
Koko chooses a whole-number eating speed k (bananas per hour). Each hour she
picks one pile and eats k bananas from it - or, if the pile has fewer than k
left, she finishes that pile and waits out the rest of the hour (she never
starts another pile in the same hour). So a pile of p bananas takes
ceil(p / k) hours.

Return the smallest speed k that lets her finish every pile within h hours.
(It always exists, because h >= piles.length.)

Example 1:
    Input:  piles = [4, 9, 6], h = 6
    Output: 4             (k = 4 takes 1 + 3 + 2 = 6 hours; k = 3 would take 2 + 3 + 2 = 7)

Example 2:
    Input:  piles = [10, 1, 25], h = 3
    Output: 25            (3 hours for 3 piles: each pile has to go in a single hour)

Example 3:
    Input:  piles = [100], h = 9
    Output: 12            (ceil(100 / 12) = 9, but ceil(100 / 11) = 10)

Constraints:
    1 <= piles.length <= 10^4
    piles.length <= h <= 10^9
    1 <= piles[i] <= 10^9

Target: O(n log(max(piles))) time.
*/
#include "prelude.hpp"

class Solution {
public:
    int minEatingSpeed(vector<int>& piles, int h) {
        throw NotImplemented();
    }
};
