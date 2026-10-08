#include "prelude.hpp"

class BSTIterator {
    vector<TreeNode*> stack;

    void push_left(TreeNode* node) {
        for (; node; node = node->left) {
            stack.push_back(node);
        }
    }

public:
    BSTIterator(TreeNode* root) { push_left(root); }

    int next() {
        TreeNode* node = stack.back();
        stack.pop_back();
        push_left(node->right);
        return node->val;
    }

    bool hasNext() { return !stack.empty(); }
};
