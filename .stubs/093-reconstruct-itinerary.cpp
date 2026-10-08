/*
93. Reconstruct Itinerary  ·  Hard  ·  Advanced Graphs
Source: https://leetcode.com/problems/reconstruct-itinerary/

You get a traveller's plane tickets, tickets[i] = {from, to}, each a one-way
flight between airports named by three uppercase letters. The trip starts at
"JFK" and uses every ticket exactly once (duplicate tickets are separate
tickets). Return the itinerary: the list of airports in the order visited,
starting with "JFK". At least one valid itinerary is guaranteed to exist.

If several itineraries are valid, return the one that is smallest when the
lists are compared airport by airport in alphabetical order (the same as
comparing the concatenated strings). Careful: always flying to the
alphabetically smallest next airport can get stuck with tickets left over.

Example 1:
    Input:  tickets = [["JFK","LAX"], ["LAX","JFK"], ["JFK","BOS"]]
    Output: ["JFK","LAX","JFK","BOS"]
            (going to BOS first would strand the LAX tickets)

Example 2:
    Input:  tickets = [["JFK","ORD"], ["ORD","DEN"], ["DEN","ORD"], ["ORD","JFK"]]
    Output: ["JFK","ORD","DEN","ORD","JFK"]

Example 3:
    Input:  tickets = [["SEA","JFK"], ["JFK","SEA"], ["JFK","ATL"], ["ATL","JFK"]]
    Output: ["JFK","ATL","JFK","SEA","JFK"]

Constraints:
    1 <= tickets.length <= 300
    tickets[i].size() == 2; from and to are 3 uppercase letters; from != to
    at least one itinerary uses all tickets

Target: O(E log E) time (E = number of tickets).
*/
#include "prelude.hpp"

class Solution {
public:
    vector<string> findItinerary(vector<vector<string>>& tickets) {
        throw NotImplemented();
    }
};
