#include "prelude.hpp"

class KthLargest {
    int k;
    priority_queue<int, vector<int>, greater<int>> heap;

public:
    KthLargest(int k, vector<int>& nums) : k(k) {
        for (int x : nums) {
            add(x);
        }
    }

    int add(int val) {
        heap.push(val);
        if (static_cast<int>(heap.size()) > k) {
            heap.pop();
        }
        return heap.top();
    }
};
