#include "prelude.hpp"

class Solution {
    static ListNode* split(ListNode* head, int len) {
        for (int i = 1; head && i < len; ++i) {
            head = head->next;
        }
        if (!head) return nullptr;
        ListNode* rest = head->next;
        head->next = nullptr;
        return rest;
    }

    static ListNode* merge(ListNode* a, ListNode* b, ListNode* tail) {
        while (a && b) {
            ListNode*& smaller = b->val < a->val ? b : a;
            tail = tail->next = smaller;
            smaller = smaller->next;
        }
        tail->next = a ? a : b;
        while (tail->next) {
            tail = tail->next;
        }
        return tail;
    }

public:
    ListNode* sortList(ListNode* head) {
        int n = 0;
        for (ListNode* p = head; p; p = p->next) {
            ++n;
        }
        ListNode dummy(0, head);
        for (int len = 1; len < n; len *= 2) {
            ListNode* tail = &dummy;
            ListNode* cur = dummy.next;
            while (cur) {
                ListNode* a = cur;
                ListNode* b = split(a, len);
                cur = split(b, len);
                tail = merge(a, b, tail);
            }
        }
        return dummy.next;
    }
};
