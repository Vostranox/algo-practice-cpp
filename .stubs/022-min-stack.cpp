/*
22. Min Stack  ·  Medium  ·  Stack
Source: https://leetcode.com/problems/min-stack/

Implement a stack class that, besides the usual operations, can report the
smallest value it currently holds. Every operation must run in O(1) time.

    MinStack()       creates an empty stack
    push(val)        pushes val
    pop()            removes the top element
    top() -> int     returns the top element
    getMin() -> int  returns the smallest element in the stack

pop, top and getMin are only called when the stack is non-empty.

Example:
    MinStack(); push(5); push(2); push(8)
    getMin() -> 2
    pop()               (removes 8)
    top()    -> 2
    pop()               (removes 2)
    getMin() -> 5

Constraints:
    -2^31 <= val <= 2^31 - 1
    up to 3 * 10^4 calls in total
*/
#include "prelude.hpp"

class MinStack {
public:
    MinStack() {
    }

    void push(int val) {
        throw NotImplemented();
    }

    void pop() {
        throw NotImplemented();
    }

    int top() {
        throw NotImplemented();
    }

    int getMin() {
        throw NotImplemented();
    }
};
