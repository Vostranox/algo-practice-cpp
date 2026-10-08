/*
126. Hand of Straights  ·  Medium  ·  Greedy
Source: https://leetcode.com/problems/hand-of-straights/

You hold a hand of cards, each showing an integer (values can repeat). Decide
whether the whole hand can be split into groups so that

    * every group has exactly `groupSize` cards,
    * the cards of each group are consecutive values (like 4, 5, 6), and
    * every card belongs to exactly one group.

Return true if such a split exists, otherwise false.

Example 1:
    Input:  hand = [5, 1, 2, 6, 3, 4, 7, 6, 5], groupSize = 3
    Output: true          ([1, 2, 3], [4, 5, 6], [5, 6, 7])

Example 2:
    Input:  hand = [1, 2, 3, 3, 4, 6], groupSize = 3
    Output: false         (after [1, 2, 3], the cards 3, 4, 6 are not consecutive)

Example 3:
    Input:  hand = [8, 8], groupSize = 1
    Output: true

Constraints:
    1 <= hand.length <= 10^4
    0 <= hand[i] <= 10^9
    1 <= groupSize <= hand.length

Target: O(n log n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool isNStraightHand(vector<int>& hand, int groupSize) {
        throw NotImplemented();
    }
};
