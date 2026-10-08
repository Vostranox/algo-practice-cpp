/*
197. Evaluate Division  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/evaluate-division/

You are told some quotients: equations[i] = {A, B} together with values[i]
means A / B = values[i], where A and B are variable names (strings). For every
query {C, D} in `queries`, work out C / D from these facts, and return the
answers in query order. When C / D can't be determined, the answer to that
query is -1.0. That happens when C or D never appears in any equation (even
for C == D), or when no chain of equations links C to D.

The facts never contradict each other and every variable is non-zero.

Example 1:
    Input:  equations = [["x", "y"], ["y", "z"]], values = [3.0, 4.0],
            queries = [["x", "z"], ["z", "y"], ["x", "x"], ["w", "w"], ["x", "w"]]
    Output: [12.0, 0.25, 1.0, -1.0, -1.0]
            (x/z = (x/y) * (y/z);  z/y = 1/4;  x/x = 1;  w appears in no equation)

Example 2:
    Input:  equations = [["a", "b"], ["c", "d"]], values = [2.0, 5.0],
            queries = [["a", "c"], ["d", "c"], ["b", "a"]]
    Output: [-1.0, 0.2, 0.5]      (nothing links a and c)

Example 3:
    Input:  equations = [["p1", "q"], ["r", "q"]], values = [1.5, 0.5],
            queries = [["p1", "r"]]
    Output: [3.0]                 (p1 = 1.5q and r = 0.5q)

Constraints:
    1 <= equations.length <= 20,  equations[i].size() == 2
    values.length == equations.length,  0.0 < values[i] <= 20.0
    1 <= queries.length <= 20,  queries[i].size() == 2
    variable names have 1 to 5 characters: lowercase letters and digits
    the equations are consistent
    answers are compared with a tolerance of 1e-5

Target: one graph search (BFS/DFS) per query, or a weighted union-find.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<double> calcEquation(vector<vector<string>>& equations, vector<double>& values,
                                vector<vector<string>>& queries) {
        throw NotImplemented();
    }
};
