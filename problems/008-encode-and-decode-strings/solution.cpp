/*
8. Encode and Decode Strings  ·  Medium  ·  Arrays & Hashing
Source: https://leetcode.com/problems/encode-and-decode-strings/

Design a way to pack a list of strings into ONE string and unpack it again:

    string encode(vector<string>& strs)   turns the list into a single string
    vector<string> decode(string s)       turns that string back into the list

decode(encode(strs)) must equal strs exactly, for every possible list: same
length, same order, same characters, empty strings and the empty list
included. The strings may contain ANY char value (all 256 of them: digits,
'#', ',', ':', spaces, '\n', '\0', the bytes of UTF-8 text such as "é" or
"😀", ...), so no single separator character is safe on its own.

Rules:
    - decode must work from the string alone: the tests encode with one Codec
      object and decode with a different, fresh one, so nothing can be kept
      in the object (or in static/global variables) between the two calls.
    - Design the format yourself.

Example 1:
    Input:  strs = ["neet", "code", "love", "you"]
    Output: ["neet", "code", "love", "you"]       (after encode, then decode)

Example 2:
    Input:  strs = ["", "a#b", "3#", "x,y"]
    Output: ["", "a#b", "3#", "x,y"]

Example 3:
    Input:  strs = []
    Output: []            (and [""] must come back as [""], not [])

Constraints:
    0 <= strs.length <= 200
    0 <= strs[i].length <= 200
    strs[i] may contain any char value

Target: O(total length) time for both encode and decode.
*/
#include "prelude.hpp"

class Codec {
public:
    string encode(vector<string>& strs) {
        throw NotImplemented();
    }

    vector<string> decode(string s) {
        throw NotImplemented();
    }
};
