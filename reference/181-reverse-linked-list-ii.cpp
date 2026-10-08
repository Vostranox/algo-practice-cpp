#include "prelude.hpp"

class Solution {
public:
    ListNode* reverseBetween(ListNode* head, int left, int right) {
        ListNode dummy(0, head);
        ListNode* before = &dummy;
        for (int i = 1; i < left; ++i) {
            before = before->next;
        }
        ListNode* first = before->next;
        for (int i = left; i < right; ++i) {
            ListNode* moved = first->next;
            first->next = moved->next;
            moved->next = before->next;
            before->next = moved;
        }
        return dummy.next;
    }
};
