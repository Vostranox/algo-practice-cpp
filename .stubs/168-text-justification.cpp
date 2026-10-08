/*
168. Text Justification  ·  Hard  ·  Arrays & Hashing
Source: https://leetcode.com/problems/text-justification/

You get a list of `words` and a line width `maxWidth`. Lay the words out, in
order, as lines of text that are each exactly `maxWidth` characters long:

  - Fill the lines greedily: put as many words on the current line as fit when
    adjacent words are separated by at least one space, then start a new line.
  - Every line except the last is fully justified: pad the gaps between its
    words with spaces so the line is exactly maxWidth wide. If the spaces can't
    be shared out evenly, the gap sizes differ by at most one, and the wider
    gaps come first (on the left).
  - A line holding a single word (that isn't the last line) has the word on the
    left and spaces after it.
  - The last line is left-justified: one space between words, then spaces up to
    maxWidth.

Return the lines.

Example 1:
    Input:  words = ["We", "hold", "these", "truths", "to", "be", "self-evident"],
            maxWidth = 14
    Output: ["We  hold these",      (3 spaces for 2 gaps: the left gap gets 2)
             "truths  to  be",
             "self-evident  "]      (last line: padded on the right)

Example 2:
    Input:  words = ["extraordinary", "is", "it"], maxWidth = 14
    Output: ["extraordinary ",      (a single word: padded on the right)
             "is it         "]

Constraints:
    1 <= words.length <= 300
    1 <= words[i].length <= 20
    words[i] consists of English letters and symbols (no spaces)
    1 <= maxWidth <= 100
    words[i].length <= maxWidth
*/
#include "prelude.hpp"

class Solution {
public:
    vector<string> fullJustify(vector<string>& words, int maxWidth) {
        throw NotImplemented();
    }
};
