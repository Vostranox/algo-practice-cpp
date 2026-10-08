#include "prelude.hpp"

using Node = RandomNode;

class Solution {
public:
    Node* copyRandomList(Node* head) {
        unordered_map<Node*, Node*> copy{{nullptr, nullptr}};
        for (Node* p = head; p; p = p->next) {
            copy[p] = new Node(p->val);
        }
        for (Node* p = head; p; p = p->next) {
            copy[p]->next = copy[p->next];
            copy[p]->random = copy[p->random];
        }
        return copy[head];
    }
};
