#include "prelude.hpp"

using Node = QuadNode;

class Solution {
    Node* build(const vector<vector<int>>& grid, int r, int c, int size) {
        if (size == 1) return new Node(grid[r][c] == 1, true);
        int h = size / 2;
        Node* q[4] = {build(grid, r, c, h), build(grid, r, c + h, h), build(grid, r + h, c, h),
                      build(grid, r + h, c + h, h)};
        bool same = true;
        for (Node* x : q) {
            same = same && x->isLeaf && x->val == q[0]->val;
        }
        if (same) {
            bool val = q[0]->val;
            for (Node* x : q) {
                delete x;
            }
            return new Node(val, true);
        }
        return new Node(false, false, q[0], q[1], q[2], q[3]);
    }

public:
    Node* construct(vector<vector<int>>& grid) { return build(grid, 0, 0, static_cast<int>(grid.size())); }
};
