#include "prelude.hpp"
using Node = GraphNode;

class Solution {
public:
    Node* cloneGraph(Node* node) {
        if (!node) return nullptr;
        unordered_map<Node*, Node*> copy{{node, new Node(node->val)}};
        vector<Node*> stack{node};
        while (!stack.empty()) {
            Node* cur = stack.back();
            stack.pop_back();
            for (Node* nb : cur->neighbors) {
                if (!copy.count(nb)) {
                    copy[nb] = new Node(nb->val);
                    stack.push_back(nb);
                }
                copy[cur]->neighbors.push_back(copy[nb]);
            }
        }
        return copy[node];
    }
};
