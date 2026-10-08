#include "prelude.hpp"

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        int count[26] = {};
        for (char c : tasks) {
            ++count[c - 'A'];
        }
        priority_queue<int> heap;
        for (int c : count) {
            if (c) {
                heap.push(c);
            }
        }
        queue<pair<int, int>> cooling;
        int time = 0;
        while (!heap.empty() || !cooling.empty()) {
            ++time;
            if (!heap.empty()) {
                int left = heap.top() - 1;
                heap.pop();
                if (left) {
                    cooling.emplace(left, time + n);
                }
            } else {
                time = cooling.front().second;
            }
            if (!cooling.empty() && cooling.front().second == time) {
                heap.push(cooling.front().first);
                cooling.pop();
            }
        }
        return time;
    }
};
