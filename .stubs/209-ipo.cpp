/*
209. IPO  ·  Hard  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/ipo/

You start with capital w and may complete at most k projects, one after
another; each project can be done at most once. Project i can only be started
while your current capital is at least capital[i] (that is just a requirement:
starting it costs nothing), and completing it adds profits[i] to your capital.

Choose which projects to do, and in which order, so that your final capital is
as large as possible, and return that final capital.

Example 1:
    Input:  k = 2, w = 1, profits = [3, 5, 2, 10], capital = [0, 2, 1, 5]
    Output: 9     (project 0 takes the capital to 4, then project 1 to 9;
                   project 3 needs capital 5, which one project can't reach)

Example 2:
    Input:  k = 3, w = 0, profits = [4, 1, 6], capital = [1, 0, 6]
    Output: 5     (project 1, then project 0; project 2 stays out of reach,
                   so only two projects get done)

Example 3:
    Input:  k = 1, w = 2, profits = [5, 3], capital = [3, 2]
    Output: 5     (only project 1 is affordable)

Constraints:
    1 <= k <= 10^5
    0 <= w <= 10^9
    1 <= n <= 10^5   (n = profits.length = capital.length)
    0 <= profits[i] <= 10^4
    0 <= capital[i] <= 10^9
    the answer is at most 10^9 + 10^5 * 10^4 < 2^31, so it fits in an int

Target: O((n + k) log n). (The large tests have n = k = 10^5, so looking
through all the projects for every pick, O(n * k), times out.)
*/
#include "prelude.hpp"

class Solution {
public:
    int findMaximizedCapital(int k, int w, vector<int>& profits, vector<int>& capital) {
        throw NotImplemented();
    }
};
