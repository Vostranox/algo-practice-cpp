/*
88. Course Schedule II  ·  Medium  ·  Graphs
Source: https://leetcode.com/problems/course-schedule-ii/

There are `numCourses` courses, labelled 0 .. numCourses - 1. Each entry
prerequisites[i] = {a, b} says that course b has to be completed before
course a can be taken. Return an order in which all the courses can be taken:
a list containing every course exactly once, where every course appears after
all of its prerequisites. If several orders work, return any of them. If no
order works (the requirements contain a cycle), return an empty list.

Example 1:
    Input:  numCourses = 4, prerequisites = [[1, 0], [2, 0], [3, 1], [3, 2]]
    Output: [0, 1, 2, 3]      ([0, 2, 1, 3] is accepted too)

Example 2:
    Input:  numCourses = 2, prerequisites = [[0, 1], [1, 0]]
    Output: []                (each course needs the other)

Example 3:
    Input:  numCourses = 1, prerequisites = []
    Output: [0]

Constraints:
    1 <= numCourses <= 2000
    0 <= prerequisites.length <= numCourses * (numCourses - 1)
    prerequisites[i].size() == 2,  0 <= a, b < numCourses,  a != b
    all pairs are distinct

Target: O(numCourses + prerequisites.length) time.
*/
#include "prelude.hpp"

class Solution {
public:
    vector<int> findOrder(int numCourses, vector<vector<int>>& prerequisites) {
        throw NotImplemented();
    }
};
