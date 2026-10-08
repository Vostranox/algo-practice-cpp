#include "prelude.hpp"

using Node = NextNode;

class Solution {
public:
    Node* connect(Node* root) {
        Node* level = root;
        while (level) {
            Node dummy;
            Node* tail = &dummy;
            for (Node* n = level; n; n = n->next) {
                if (n->left) {
                    tail = tail->next = n->left;
                }
                if (n->right) {
                    tail = tail->next = n->right;
                }
            }
            level = dummy.next;
        }
        return root;
    }
};
