#include "prelude.hpp"

class Solution {
    static int depth(TreeNode* node) {
        int d = 0;
        for (; node; node = node->left) {
            ++d;
        }
        return d;
    }

public:
    int countNodes(TreeNode* root) {
        int count = 0;
        while (root) {
            int left = depth(root->left), right = depth(root->right);
            if (left == right) {
                count += 1 << left;
                root = root->right;
            } else {
                count += 1 << right;
                root = root->left;
            }
        }
        return count;
    }
};
