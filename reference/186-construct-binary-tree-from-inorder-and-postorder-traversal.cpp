#include "prelude.hpp"

class Solution {
    unordered_map<int, int> pos;
    int next = 0;

    TreeNode* build(const vector<int>& postorder, int lo, int hi) {
        if (lo > hi) return nullptr;
        int val = postorder[next--];
        int mid = pos[val];
        TreeNode* node = new TreeNode(val);
        node->right = build(postorder, mid + 1, hi);
        node->left = build(postorder, lo, mid - 1);
        return node;
    }

public:
    TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
        pos.clear();
        for (int i = 0; i < static_cast<int>(inorder.size()); ++i) {
            pos[inorder[i]] = i;
        }
        next = static_cast<int>(postorder.size()) - 1;
        return build(postorder, 0, static_cast<int>(inorder.size()) - 1);
    }
};
