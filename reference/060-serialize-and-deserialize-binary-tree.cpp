#include "prelude.hpp"

class Codec {
    TreeNode* read(const char*& p) {
        if (*p == '#') {
            p += 2;
            return nullptr;
        }
        char* end;
        TreeNode* node = new TreeNode(static_cast<int>(strtol(p, &end, 10)));
        p = end + 1;
        node->left = read(p);
        node->right = read(p);
        return node;
    }

public:
    string serialize(TreeNode* root) {
        string out;
        vector<TreeNode*> stack{root};
        while (!stack.empty()) {
            TreeNode* node = stack.back();
            stack.pop_back();
            if (!node) {
                out += "#,";
                continue;
            }
            out += to_string(node->val);
            out += ',';
            stack.push_back(node->right);
            stack.push_back(node->left);
        }
        return out;
    }

    TreeNode* deserialize(string data) {
        const char* p = data.c_str();
        return read(p);
    }
};
