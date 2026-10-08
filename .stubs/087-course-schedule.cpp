/*
87. Course Schedule  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/course-schedule/

There are `numCourses` courses, labelled 0 .. numCourses - 1. Each entry
prerequisites[i] = {a, b} says that course b has to be completed before
course a can be taken. Return true if it is possible to complete all the
courses in some order, and false if the requirements make that impossible
(some course depends, directly or through a chain, on itself).

Example 1:
    Input:  numCourses = 3, prerequisites = [[1, 0], [2, 1]]
    Output: true        (take 0, then 1, then 2)

Example 2:
    Input:  numCourses = 3, prerequisites = [[1, 0], [2, 1], [0, 2]]
    Output: false       (0 -> 1 -> 2 -> 0 is a cycle)

Example 3:
    Input:  numCourses = 2, prerequisites = []
    Output: true

Constraints:
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= 5000
    prerequisites[i].size() == 2,  0 <= a, b < numCourses
    all pairs are distinct (a == b can occur: that course can never be taken)

Target: O(numCourses + prerequisites.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    bool canFinish(int numCourses, vector<vector<int>>& prerequisites) {
        throw NotImplemented();
    }
};
