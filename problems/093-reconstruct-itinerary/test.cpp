#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Tickets = vector<vector<string>>;

static void run(const Tickets& tickets, const vector<string>& want) {
    Tickets arg = tickets;
    check(Solution().findItinerary(arg), want, "tickets", tickets);
}

static bool extend(map<string, map<string, int>>& left, vector<string>& route, size_t total) {
    if (route.size() == total + 1) return true;
    auto it = left.find(route.back());
    if (it == left.end()) return false;
    for (auto& [to, count] : it->second) {
        if (count == 0) continue;
        --count;
        route.push_back(to);
        if (extend(left, route, total)) return true;
        route.pop_back();
        ++count;
    }
    return false;
}

static vector<string> smallest_itinerary(const Tickets& tickets) {
    map<string, map<string, int>> left;
    for (auto& t : tickets) {
        ++left[t[0]][t[1]];
    }
    vector<string> route{"JFK"};
    extend(left, route, tickets.size());
    return route;
}

static Tickets random_trip(Rng& rng, const vector<string>& airports, int len) {
    Tickets tickets;
    string here = "JFK";
    for (int i = 0; i < len; ++i) {
        string next;
        do {
            next = rng.pick(airports);
        } while (next == here);
        tickets.push_back({here, next});
        here = next;
    }
    rng.shuffle(tickets);
    return tickets;
}

TEST(examples) {
    run({{"JFK", "LAX"}, {"LAX", "JFK"}, {"JFK", "BOS"}}, {"JFK", "LAX", "JFK", "BOS"});
    run({{"JFK", "ORD"}, {"ORD", "DEN"}, {"DEN", "ORD"}, {"ORD", "JFK"}}, {"JFK", "ORD", "DEN", "ORD", "JFK"});
    run({{"SEA", "JFK"}, {"JFK", "SEA"}, {"JFK", "ATL"}, {"ATL", "JFK"}}, {"JFK", "ATL", "JFK", "SEA", "JFK"});
}

TEST(edge_cases) {
    run({{"JFK", "AAA"}}, {"JFK", "AAA"});
    run({{"JFK", "AAA"}, {"AAA", "JFK"}, {"JFK", "AAA"}}, {"JFK", "AAA", "JFK", "AAA"});
    run({{"JFK", "AAA"}, {"AAA", "BBB"}, {"AAA", "CCC"}, {"CCC", "AAA"}},
        {"JFK", "AAA", "CCC", "AAA", "BBB"});
    run({{"JFK", "ZZZ"}, {"JFK", "BBB"}, {"BBB", "JFK"}}, {"JFK", "BBB", "JFK", "ZZZ"});
    run({{"JFK", "AAA"}, {"JFK", "BBB"}, {"BBB", "JFK"}}, {"JFK", "BBB", "JFK", "AAA"});
    run({{"JFK", "SFO"}, {"SFO", "JFK"}, {"JFK", "SFO"}, {"SFO", "ATL"}, {"ATL", "SFO"}},
        {"JFK", "SFO", "ATL", "SFO", "JFK", "SFO"});
}

TEST(random) {
    Rng rng(93);
    vector<string> airports{"JFK", "AAA", "BBB", "CCC", "DDD"};
    for (int t = 0; t < 400; ++t) {
        vector<string> some(airports.begin(), airports.begin() + rng(2, 5));
        Tickets tickets = random_trip(rng, some, rng(1, 10));
        run(tickets, smallest_itinerary(tickets));
    }
}

TEST(large) {
    Rng rng(930);
    vector<string> names;
    for (char a = 'B'; a <= 'Z' && names.size() < 149; ++a) {
        for (char b = 'A'; b <= 'Z' && names.size() < 149; b += 3) {
            names.push_back(string{a, b, 'X'});
        }
    }
    Tickets tickets{{"JFK", "AAA"}};
    for (auto& x : names) {
        tickets.push_back({"JFK", x}), tickets.push_back({x, "JFK"});
    }
    rng.shuffle(tickets);
    vector<string> want{"JFK"};
    for (auto& x : sorted(names)) {
        want.push_back(x), want.push_back("JFK");
    }
    want.push_back("AAA");
    run(tickets, want);

    vector<string> airports{"JFK"};
    for (char c = 'A'; c <= 'Z'; ++c) {
        airports.push_back(string(3, c));
    }
    for (int k : {3, 5, 8, 27}) {
        vector<string> some(airports.begin(), airports.begin() + k);
        for (int t = 0; t < 5; ++t) {
            Tickets trip = random_trip(rng, some, 300);
            run(trip, smallest_itinerary(trip));
        }
    }
}

}
