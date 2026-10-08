#include "prelude.hpp"

class Solution {
    int best = INT_MAX;
    TreeNode* prev = nullptr;

    void inorder(TreeNode* node) {
        if (!node) return;
        inorder(node->left);
        if (prev) {
            best = min(best, node->val - prev->val);
        }
        prev = node;
        inorder(node->right);
    }

public:
    int getMinimumDifference(TreeNode* root) {
        best = INT_MAX;
        prev = nullptr;
        inorder(root);
        return best;
    }
};
