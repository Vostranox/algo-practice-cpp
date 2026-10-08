/*
159. Insert Delete GetRandom O(1)  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/insert-delete-getrandom-o1/

Design a set of integers that can also hand out a uniformly random element.

    RandomizedSet()        creates an empty set
    insert(val) -> bool    adds val unless it is already in the set; returns
                           true if val was added, false if it was there already
    remove(val) -> bool    deletes val if it is in the set; returns true if val
                           was deleted, false if it wasn't in the set
    getRandom() -> int     returns one of the values currently in the set, every
                           value with the same probability

Each operation must run in O(1) average time. getRandom is only called while
the set is non-empty.

Example:
    RandomizedSet()
    insert(4)   -> true
    insert(4)   -> false    (4 is already in the set)
    insert(9)   -> true
    remove(7)   -> false    (7 isn't in the set)
    getRandom() -> 4 or 9, each with probability 1/2
    remove(4)   -> true
    getRandom() -> 9        (the only value left)

Constraints:
    -2^31 <= val <= 2^31 - 1
    at most 2 * 10^5 calls in total
    getRandom is only called when the set holds at least one value
*/
#include "prelude.hpp"

class RandomizedSet {
public:
    RandomizedSet() {
    }

    bool insert(int val) {
        throw NotImplemented();
    }

    bool remove(int val) {
        throw NotImplemented();
    }

    int getRandom() {
        throw NotImplemented();
    }
};
