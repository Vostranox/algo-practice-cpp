#include "prelude.hpp"

class Solution {
    int best = 0;

    int height(TreeNode* node) {
        if (!node) return 0;
        int left = height(node->left), right = height(node->right);
        best = max(best, left + right);
        return 1 + max(left, right);
    }

public:
    int diameterOfBinaryTree(TreeNode* root) {
        best = 0;
        height(root);
        return best;
    }
};
