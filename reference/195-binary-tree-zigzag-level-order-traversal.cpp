#include "prelude.hpp"

class Solution {
public:
    vector<vector<int>> zigzagLevelOrder(TreeNode* root) {
        vector<vector<int>> out;
        queue<TreeNode*> q;
        if (root) {
            q.push(root);
        }
        while (!q.empty()) {
            vector<int> level;
            for (size_t k = q.size(); k > 0; --k) {
                TreeNode* node = q.front();
                q.pop();
                level.push_back(node->val);
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            if (out.size() % 2) {
                reverse(level.begin(), level.end());
            }
            out.push_back(move(level));
        }
        return out;
    }
};
