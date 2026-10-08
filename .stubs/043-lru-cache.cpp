/*
43. LRU Cache  ·  Medium  ·  Linked List
Source: https://leetcode.com/problems/lru-cache/

Design a key-value cache with a fixed capacity that, when it is full, makes
room by evicting the least recently used key.

    LRUCache(capacity)     creates an empty cache holding at most capacity keys
    get(key) -> int        returns the value stored for key, or -1 if key is not
                           in the cache; a successful get counts as a use of key
    put(key, value)        stores value under key (inserting it or overwriting
                           the old value); this counts as a use of key. If that
                           insertion makes the cache hold more than capacity
                           keys, evict the key whose last use is the oldest.

get and put must each run in O(1) average time.

Example (capacity 2):
    LRUCache(2)
    put(1, 10); put(2, 20)
    get(1)     -> 10
    put(3, 30)          (evicts key 2: key 1 was used more recently)
    get(2)     -> -1
    put(1, 15)          (overwrites key 1; key 3 is now the least recently used)
    put(4, 40)          (evicts key 3)
    get(3)     -> -1
    get(1)     -> 15
    get(4)     -> 40

Constraints:
    1 <= capacity <= 3000
    0 <= key <= 10^4
    0 <= value <= 10^5
    at most 2 * 10^5 calls to get and put
*/
#include "prelude.hpp"

class LRUCache {
public:
    LRUCache(int capacity) {
    }

    int get(int key) {
        throw NotImplemented();
    }

    void put(int key, int value) {
        throw NotImplemented();
    }
};
