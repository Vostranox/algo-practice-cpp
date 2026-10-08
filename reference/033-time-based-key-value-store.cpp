#include "prelude.hpp"

class TimeMap {
    unordered_map<string, vector<pair<int, string>>> history;

public:
    TimeMap() {}

    void set(string key, string value, int timestamp) {
        history[key].emplace_back(timestamp, move(value));
    }

    string get(string key, int timestamp) {
        auto it = history.find(key);
        if (it == history.end()) return "";
        auto& h = it->second;
        auto pos = upper_bound(h.begin(), h.end(), timestamp,
                               [](int ts, const pair<int, string>& e) { return ts < e.first; });
        return pos == h.begin() ? "" : prev(pos)->second;
    }
};
