#include "prelude.hpp"

class WordDictionary {
    struct Node {
        Node* child[26] = {};
        bool end = false;
    };
    Node root;

    bool match(const string& w, size_t i, Node* node) {
        for (; i < w.size(); ++i) {
            if (w[i] == '.') {
                for (Node* c : node->child) {
                    if (c && match(w, i + 1, c)) return true;
                }
                return false;
            }
            node = node->child[w[i] - 'a'];
            if (!node) return false;
        }
        return node->end;
    }

public:
    WordDictionary() {}

    void addWord(string word) {
        Node* node = &root;
        for (char c : word) {
            Node*& next = node->child[c - 'a'];
            if (!next) {
                next = new Node();
            }
            node = next;
        }
        node->end = true;
    }

    bool search(string word) { return match(word, 0, &root); }
};
