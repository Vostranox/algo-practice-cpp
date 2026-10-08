#include "prelude.hpp"

class Solution {
    int sum(TreeNode* node, int prefix) {
        if (!node) return 0;
        int number = prefix * 10 + node->val;
        if (!node->left && !node->right) return number;
        return sum(node->left, number) + sum(node->right, number);
    }

public:
    int sumNumbers(TreeNode* root) { return sum(root, 0); }
};
