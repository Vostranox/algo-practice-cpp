#include "prelude.hpp"

class Solution {
public:
    vector<double> averageOfLevels(TreeNode* root) {
        vector<double> out;
        queue<TreeNode*> q;
        q.push(root);
        while (!q.empty()) {
            size_t count = q.size();
            int64_t sum = 0;
            for (size_t k = 0; k < count; ++k) {
                TreeNode* node = q.front();
                q.pop();
                sum += node->val;
                if (node->left) {
                    q.push(node->left);
                }
                if (node->right) {
                    q.push(node->right);
                }
            }
            out.push_back(static_cast<double>(sum) / count);
        }
        return out;
    }
};
