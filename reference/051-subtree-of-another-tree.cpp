#include "prelude.hpp"

class Solution {
    static constexpr int NIL = INT_MIN;

    void serialize(TreeNode* node, vector<int>& out) {
        if (!node) {
            out.push_back(NIL);
            return;
        }
        out.push_back(node->val);
        serialize(node->left, out);
        serialize(node->right, out);
    }

public:
    bool isSubtree(TreeNode* root, TreeNode* subRoot) {
        vector<int> text, pat;
        serialize(root, text);
        serialize(subRoot, pat);
        vector<size_t> fail(pat.size(), 0);
        for (size_t i = 1, k = 0; i < pat.size(); ++i) {
            while (k && pat[i] != pat[k]) {
                k = fail[k - 1];
            }
            if (pat[i] == pat[k]) {
                ++k;
            }
            fail[i] = k;
        }
        for (size_t i = 0, k = 0; i < text.size(); ++i) {
            while (k && text[i] != pat[k]) {
                k = fail[k - 1];
            }
            if (text[i] == pat[k]) {
                ++k;
            }
            if (k == pat.size()) return true;
        }
        return false;
    }
};
