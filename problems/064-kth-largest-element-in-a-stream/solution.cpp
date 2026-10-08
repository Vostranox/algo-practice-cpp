/*
64. Kth Largest Element in a Stream  ·  Easy  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/kth-largest-element-in-a-stream/

Build a class that watches a stream of integers and can always report the k-th
largest value seen so far. "k-th largest" means the value at position k
(1-based) when everything seen is sorted from largest to smallest, so repeated
values count separately (in 9 7 7 3 the 3rd largest is 7).

    KthLargest(k, nums)  starts with the integer k and the initial values nums
    add(val) -> int      adds val to the stream, then returns the current
                         k-th largest value

Once val has been added, the stream always holds at least k values, so the
answer always exists.

Example 1:
    KthLargest(2, [7, 1, 4])
    add(3) -> 4      (stream: 7 4 3 1)
    add(8) -> 7      (stream: 8 7 4 3 1)
    add(7) -> 7      (stream: 8 7 7 4 3 1 -- the two 7s count separately)
    add(9) -> 8      (stream: 9 8 7 7 4 3 1)

Example 2:
    KthLargest(1, [])
    add(-5) -> -5
    add(2)  -> 2
    add(-1) -> 2

Constraints:
    0 <= nums.length <= 10^4
    1 <= k <= nums.length + 1
    -10^4 <= nums[i], val <= 10^4
    at most 10^4 calls to add

Target: O(log k) per add (a min-heap that holds only the k largest values).
*/
#include "prelude.hpp"

class KthLargest {
public:
    KthLargest(int k, vector<int>& nums) {
    }

    int add(int val) {
        throw NotImplemented();
    }
};
