#include "prelude.hpp"

class Solution {
    int dfs(TreeNode* node, int pathMax) {
        if (!node) return 0;
        int good = node->val >= pathMax ? 1 : 0;
        pathMax = max(pathMax, node->val);
        return good + dfs(node->left, pathMax) + dfs(node->right, pathMax);
    }

public:
    int goodNodes(TreeNode* root) { return dfs(root, root->val); }
};
