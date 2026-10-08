#pragma once
#include <bits/stdc++.h>
// #include <__msvc_all_public_headers.hpp>
using namespace std;

struct NotImplemented : std::exception {
    const char* what() const noexcept override { return "not implemented yet"; }
};

struct ListNode {
    int val;
    ListNode* next;
    ListNode() : val(0), next(nullptr) {}
    ListNode(int x) : val(x), next(nullptr) {}
    ListNode(int x, ListNode* next) : val(x), next(next) {}
};

struct TreeNode {
    int val;
    TreeNode* left;
    TreeNode* right;
    TreeNode() : val(0), left(nullptr), right(nullptr) {}
    TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
    TreeNode(int x, TreeNode* left, TreeNode* right) : val(x), left(left), right(right) {}
};

struct RandomNode {
    int val;
    RandomNode* next;
    RandomNode* random;
    RandomNode(int _val) : val(_val), next(nullptr), random(nullptr) {}
};

struct GraphNode {
    int val;
    vector<GraphNode*> neighbors;
    GraphNode() : val(0) {}
    GraphNode(int _val) : val(_val) {}
    GraphNode(int _val, vector<GraphNode*> _neighbors) : val(_val), neighbors(_neighbors) {}
};

struct NextNode {
    int val;
    NextNode* left;
    NextNode* right;
    NextNode* next;
    NextNode() : val(0), left(nullptr), right(nullptr), next(nullptr) {}
    NextNode(int _val) : val(_val), left(nullptr), right(nullptr), next(nullptr) {}
    NextNode(int _val, NextNode* _left, NextNode* _right, NextNode* _next)
        : val(_val), left(_left), right(_right), next(_next) {}
};

struct QuadNode {
    bool val;
    bool isLeaf;
    QuadNode* topLeft;
    QuadNode* topRight;
    QuadNode* bottomLeft;
    QuadNode* bottomRight;
    QuadNode() : val(false), isLeaf(false), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {}
    QuadNode(bool _val, bool _isLeaf)
        : val(_val), isLeaf(_isLeaf), topLeft(nullptr), topRight(nullptr), bottomLeft(nullptr), bottomRight(nullptr) {}
    QuadNode(bool _val, bool _isLeaf, QuadNode* _topLeft, QuadNode* _topRight, QuadNode* _bottomLeft, QuadNode* _bottomRight)
        : val(_val), isLeaf(_isLeaf), topLeft(_topLeft), topRight(_topRight), bottomLeft(_bottomLeft), bottomRight(_bottomRight) {}
};
