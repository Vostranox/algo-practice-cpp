/*
70. Find Median from Data Stream  ·  Hard  ·  Heap / Priority Queue
Source: https://leetcode.com/problems/find-median-from-data-stream/

The median of a list of numbers is its middle value once sorted; when the list
has an even length, it is the average of the two middle values.
    [4, 1, 7] -> 4          [4, 1, 7, 2] -> (2 + 4) / 2 = 3.0

Build a class that receives integers one at a time and can report the median of
everything received so far at any moment.

    MedianFinder()           creates an empty structure
    addNum(num)              adds the integer num
    findMedian() -> double   returns the median of all numbers added so far

findMedian is only called after at least one addNum. Answers within 1e-5 of the
true median are accepted.

Example:
    MedianFinder()
    addNum(5)
    findMedian() -> 5.0
    addNum(-3)
    findMedian() -> 1.0      ((-3 + 5) / 2)
    addNum(10)
    findMedian() -> 5.0      (sorted: -3 5 10)
    addNum(1)
    findMedian() -> 3.0      (sorted: -3 1 5 10)

Constraints:
    -10^5 <= num <= 10^5
    at most 5 * 10^4 calls in total

Target: O(log n) per addNum and O(1) per findMedian (two heaps: a max-heap for
the smaller half and a min-heap for the larger half).
Follow-up: if every number were in [0, 100], how would you do it? And if 99% of
them were?
*/
#include "prelude.hpp"

class MedianFinder {
public:
    MedianFinder() {
    }

    void addNum(int num) {
        throw NotImplemented();
    }

    double findMedian() {
        throw NotImplemented();
    }
};
