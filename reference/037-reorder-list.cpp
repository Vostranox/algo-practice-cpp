#include "prelude.hpp"

class Solution {
public:
    void reorderList(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head->next;
        while (fast && fast->next) {
            slow = slow->next;
            fast = fast->next->next;
        }
        ListNode* second = slow->next;
        slow->next = nullptr;
        ListNode* prev = nullptr;
        while (second) {
            ListNode* next = second->next;
            second->next = prev;
            prev = second;
            second = next;
        }
        for (ListNode *first = head, *back = prev; back;) {
            ListNode* next1 = first->next;
            ListNode* next2 = back->next;
            first->next = back;
            back->next = next1;
            first = next1;
            back = next2;
        }
    }
};
