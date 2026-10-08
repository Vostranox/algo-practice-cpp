/*
143. Detect Squares  ·  Medium  ·  Math & Geometry
Source: https://leetcode.com/problems/detect-squares/

Design a structure that collects points on a plane and answers square queries.

    DetectSquares()           creates an empty collection
    add(point)                stores point = [x, y]. The same coordinates may be
                              added several times; every copy is kept and counts
                              as a separate point.
    count(point) -> int       given a query point [qx, qy], returns the number of
                              ways to pick three stored points such that those three
                              plus the query point are the four corners of a square
                              whose sides are parallel to the x/y axes and whose area
                              is positive. Picking a different copy of a duplicated
                              point counts as a different way. The query point itself
                              is not added to the collection.

Example:
    DetectSquares()
    add([1, 1]); add([1, 4]); add([4, 1])
    count([4, 4]) -> 1    (corners (1,1), (1,4), (4,1) plus the query (4,4))
    count([2, 2]) -> 0
    add([4, 1])           (a second copy of (4,1))
    count([4, 4]) -> 2    (either copy of (4,1) can be used)
    count([1, 4]) -> 0    ((4,4) is needed but was never added)

Constraints:
    point.length == 2, point = [x, y] with 0 <= x, y <= 1000
    at most 3000 calls to add and count in total

Target: add in O(1); count in O(number of distinct stored points).
*/
#include "prelude.hpp"

class DetectSquares {
public:
    DetectSquares() {
    }

    void add(vector<int> point) {
        throw NotImplemented();
    }

    int count(vector<int> point) {
        throw NotImplemented();
    }
};
