#include "prelude.hpp"

class Solution {
public:
    int ladderLength(string beginWord, string endWord, vector<string>& wordList) {
        unordered_set<string> unseen(wordList.begin(), wordList.end());
        if (!unseen.count(endWord)) return 0;
        unseen.erase(beginWord);
        queue<string> q;
        q.push(beginWord);
        for (int words = 1; !q.empty(); ++words) {
            for (int k = q.size(); k > 0; --k) {
                string w = q.front();
                q.pop();
                if (w == endWord) return words;
                for (char& ch : w) {
                    char orig = ch;
                    for (char c = 'a'; c <= 'z'; ++c) {
                        ch = c;
                        if (unseen.erase(w)) {
                            q.push(w);
                        }
                    }
                    ch = orig;
                }
            }
        }
        return 0;
    }
};
