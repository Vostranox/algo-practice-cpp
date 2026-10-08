#include "prelude.hpp"

class Solution {
public:
    void flatten(TreeNode* root) {
        for (TreeNode* node = root; node; node = node->right) {
            if (!node->left) continue;
            TreeNode* last = node->left;
            while (last->right) {
                last = last->right;
            }
            last->right = node->right;
            node->right = node->left;
            node->left = nullptr;
        }
    }
};
