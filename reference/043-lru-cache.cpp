#include "prelude.hpp"

class LRUCache {
    int cap;
    list<pair<int, int>> items;
    unordered_map<int, list<pair<int, int>>::iterator> where;

public:
    LRUCache(int capacity) : cap(capacity) {}

    int get(int key) {
        auto it = where.find(key);
        if (it == where.end()) return -1;
        items.splice(items.begin(), items, it->second);
        return it->second->second;
    }

    void put(int key, int value) {
        auto it = where.find(key);
        if (it != where.end()) {
            it->second->second = value;
            items.splice(items.begin(), items, it->second);
            return;
        }
        items.emplace_front(key, value);
        where[key] = items.begin();
        if (static_cast<int>(items.size()) > cap) {
            where.erase(items.back().first);
            items.pop_back();
        }
    }
};
