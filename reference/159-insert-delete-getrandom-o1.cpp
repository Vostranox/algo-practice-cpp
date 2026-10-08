#include "prelude.hpp"

class RandomizedSet {
    vector<int> vals;
    unordered_map<int, int> where;
    mt19937 gen{12345};

public:
    RandomizedSet() {}

    bool insert(int val) {
        if (where.count(val)) return false;
        where[val] = vals.size();
        vals.push_back(val);
        return true;
    }

    bool remove(int val) {
        auto it = where.find(val);
        if (it == where.end()) return false;
        int i = it->second;
        vals[i] = vals.back();
        where[vals[i]] = i;
        vals.pop_back();
        where.erase(val);
        return true;
    }

    int getRandom() { return vals[uniform_int_distribution<int>(0, static_cast<int>(vals.size()) - 1)(gen)]; }
};
