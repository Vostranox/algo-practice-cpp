#include "prelude.hpp"

class Solution {
public:
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        auto greater_val = [](ListNode* a, ListNode* b) { return a->val > b->val; };
        priority_queue<ListNode*, vector<ListNode*>, decltype(greater_val)> heap(greater_val);
        for (ListNode* l : lists) {
            if (l) {
                heap.push(l);
            }
        }
        ListNode dummy;
        ListNode* tail = &dummy;
        while (!heap.empty()) {
            ListNode* node = heap.top();
            heap.pop();
            tail = tail->next = node;
            if (node->next) {
                heap.push(node->next);
            }
        }
        tail->next = nullptr;
        return dummy.next;
    }
};
