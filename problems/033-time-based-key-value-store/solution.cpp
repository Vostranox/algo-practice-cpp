/*
33. Time Based Key-Value Store  ·  Medium  ·  Binary Search
Source: https://leetcode.com/problems/time-based-key-value-store/

Design a key-value store that remembers every value a key has had over time.

    TimeMap()                     creates an empty store
    set(key, value, timestamp)    records that `key` got the value `value` at time `timestamp`
    get(key, timestamp) -> string returns the value `key` had at time `timestamp`: the value
                                  from the set() call for this key with the largest timestamp
                                  that is <= `timestamp`. Returns "" (empty string) if the key
                                  was never set at or before that time.

The timestamps of set() calls are strictly increasing over all calls (so each
key's history arrives in time order). get() may ask about any timestamp.

Example:
    TimeMap()
    set("color", "red", 2)
    set("color", "blue", 6)
    get("color", 1)    -> ""        (nothing set yet at time 1)
    get("color", 2)    -> "red"
    get("color", 5)    -> "red"
    get("color", 6)    -> "blue"
    get("color", 100)  -> "blue"
    get("size", 6)     -> ""        (this key was never set)

Constraints:
    1 <= key.length, value.length <= 100; keys and values use lowercase letters and digits
    1 <= timestamp <= 10^7
    timestamps of set() calls are strictly increasing
    at most 2 * 10^5 calls to set and get in total

Target: O(1) set, O(log n) get (n = number of values stored for that key).
*/
#include "prelude.hpp"

class TimeMap {
public:
    TimeMap() {
    }

    void set(string key, string value, int timestamp) {
        throw NotImplemented();
    }

    string get(string key, int timestamp) {
        throw NotImplemented();
    }
};
