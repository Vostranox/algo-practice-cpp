#include "prelude.hpp"

class Solution {
    bool valid(TreeNode* node, int64_t low, int64_t high) {
        if (!node) return true;
        if (node->val <= low || node->val >= high) return false;
        return valid(node->left, low, node->val) && valid(node->right, node->val, high);
    }

public:
    bool isValidBST(TreeNode* root) { return valid(root, INT64_MIN, INT64_MAX); }
};
