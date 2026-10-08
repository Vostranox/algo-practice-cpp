/*
65. Last Stone Weight  ·  Easy  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/last-stone-weight/

You have a pile of stones with positive integer weights, given as the array
`stones`. Repeatedly take the two heaviest stones out of the pile, with weights
x <= y, and smash them together:
    - if x == y, both stones are destroyed;
    - otherwise the lighter stone is destroyed and the heavier one is left with
      weight y - x, and it goes back into the pile.
Stop as soon as at most one stone is left. Return the weight of the remaining
stone, or 0 if no stone is left.

Example 1:
    Input:  stones = [3, 8, 5, 1]
    Output: 1
    (8 and 5 -> 3, pile [3, 3, 1]; 3 and 3 -> both destroyed, pile [1])

Example 2:
    Input:  stones = [6, 6]
    Output: 0

Example 3:
    Input:  stones = [10, 4, 2]
    Output: 4
    (10 and 4 -> 6, pile [6, 2]; 6 and 2 -> 4, pile [4])

Constraints:
    1 <= stones.length <= 30
    1 <= stones[i] <= 1000

Target: O(n log n) with a max-heap.
*/
#include "prelude.hpp"

class Solution {
public:
    int lastStoneWeight(vector<int>& stones) {
        throw NotImplemented();
    }
};
