#include "prelude.hpp"

class Solution {
public:
    vector<int> rightSideView(TreeNode* root) {
        vector<int> view;
        queue<TreeNode*> q;
        if (root) {
            q.push(root);
        }
        while (!q.empty()) {
            TreeNode* node = nullptr;
            for (size_t k = q.size(); k > 0; --k) {
                node = q.front();
                q.pop();
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            view.push_back(node->val);
        }
        return view;
    }
};
