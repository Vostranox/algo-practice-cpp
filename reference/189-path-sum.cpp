#include "prelude.hpp"

class Solution {
public:
    bool hasPathSum(TreeNode* root, int targetSum) {
        if (!root) return false;
        int rest = targetSum - root->val;
        if (!root->left && !root->right) return rest == 0;
        return hasPathSum(root->left, rest) || hasPathSum(root->right, rest);
    }
};
