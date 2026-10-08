/*
179. Simplify Path  ·  Medium  ·  Stack
Source: https://leetcode.com/problems/simplify-path/

You get an absolute Unix-style file path (it starts with '/'). Return its
canonical form. The rules:

    - "."  means the current directory: it can simply be dropped.
    - ".." means the parent directory: it removes the directory before it.
      At the root there is no parent, so ".." there leaves you at the root.
    - several slashes in a row ("//", "///") count as a single '/'.
    - any other name is a normal file or directory name -- including names
      made only of periods, like "..." or "....".

The canonical path starts with a single '/', separates names by exactly one
'/', contains no "." or ".." parts, and has no '/' at the end -- except the
root itself, which is just "/".

Example 1:
    Input:  path = "/docs//notes/"
    Output: "/docs/notes"

Example 2:
    Input:  path = "/srv/../../tmp/./x"
    Output: "/tmp/x"      (the second ".." happens at the root and does nothing)

Example 3:
    Input:  path = "/.../a/.."
    Output: "/..."        ("..." is an ordinary name)

Constraints:
    1 <= path.length <= 3000
    path consists of English letters, digits, '.', '/' and '_'
    path is a valid absolute Unix path

Target: O(n) time.
*/
#include "prelude.hpp"

class Solution {
public:
    string simplifyPath(string path) {
        throw NotImplemented();
    }
};
