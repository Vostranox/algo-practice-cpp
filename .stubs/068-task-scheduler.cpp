/*
68. Task Scheduler  ·  Medium  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/task-scheduler/

A CPU has to run a list of tasks; each task is labelled with an uppercase
letter, and several tasks may share a label. Time is divided into units, and in
each unit the CPU either runs exactly one pending task (any one -- tasks can be
run in any order) or stays idle. Tasks with the same label need a cool-down:
between two runs of the same label there must be at least n other time units
(runs of other tasks or idle units).

Return the minimum number of time units needed to run every task, idle units
included.

Example 1:
    Input:  tasks = ['X', 'X', 'X', 'Y'], n = 2
    Output: 7        (X Y idle X idle idle X)

Example 2:
    Input:  tasks = ['A', 'B', 'C', 'A', 'B', 'C'], n = 1
    Output: 6        (A B C A B C -- no idling needed)

Example 3:
    Input:  tasks = ['P', 'P', 'P', 'R', 'R', 'R', 'S'], n = 2
    Output: 8        (P R S P R idle P R)

Constraints:
    1 <= tasks.length <= 10^4
    tasks[i] is an uppercase English letter
    0 <= n <= 100

Target: O(tasks.length) time -- e.g. simulate with a max-heap of remaining
counts plus a queue of labels that are cooling down (skip ahead in time when
everything is cooling down), or find a counting formula.
*/
#include "prelude.hpp"

class Solution {
public:
    int leastInterval(vector<char>& tasks, int n) {
        throw NotImplemented();
    }
};
