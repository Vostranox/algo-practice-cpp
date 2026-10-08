#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(int target, const vector<int>& position, const vector<int>& speed, int want) {
    vector<int> p = position, s = speed;
    check(Solution().carFleet(target, p, s), want, "target", target, "position", position, "speed", speed);
}

static int brute(int target, const vector<int>& position, const vector<int>& speed) {
    int n = position.size();
    set<pair<int64_t, int64_t>> arrivals;
    for (int i = 0; i < n; ++i) {
        int64_t num = target - position[i], den = speed[i];
        for (int j = 0; j < n; ++j) {
            int64_t nj = target - position[j], dj = speed[j];
            if (position[j] > position[i] && nj * den > num * dj) {
                num = nj, den = dj;
            }
        }
        int64_t g = gcd(num, den);
        arrivals.insert({num / g, den / g});
    }
    return static_cast<int>(arrivals.size());
}

static void shuffle_cars(Rng& rng, vector<int>& position, vector<int>& speed) {
    vector<pair<int, int>> cars;
    for (size_t i = 0; i < position.size(); ++i) {
        cars.push_back({position[i], speed[i]});
    }
    rng.shuffle(cars);
    for (size_t i = 0; i < cars.size(); ++i) {
        tie(position[i], speed[i]) = cars[i];
    }
}

TEST(examples) {
    run(20, {6, 16, 0, 10}, {2, 1, 4, 5}, 2);
    run(10, {0, 5}, {2, 1}, 1);
    run(10, {0, 5}, {1, 2}, 2);
}

TEST(edge_cases) {
    run(10, {4}, {3}, 1);
    run(1, {0}, {1}, 1);
    run(10, {3, 1, 6}, {1, 1, 1}, 3);
    run(10, {9, 0}, {1, 10}, 1);
    run(20, {13, 6}, {3, 6}, 1);
    run(1000000, {500000, 0}, {1, 2}, 1);
    run(1000000, {500001, 0}, {1, 2}, 2);
    run(1000000, {500000, 1}, {1, 2}, 1);
    run(1000000, {1, 0}, {999998, 999999}, 1);
    run(1000000, {1, 0}, {999999, 999998}, 2);
    run(100, {90, 80, 0}, {1, 5, 10}, 1);
    run(100, {90, 50, 0}, {10, 1, 2}, 2);
}

TEST(random) {
    Rng rng(26);
    for (int iter = 0; iter < 3000; ++iter) {
        int target = rng(1, 30);
        int n = rng(1, min(8, target));
        vector<int> all(target);
        iota(all.begin(), all.end(), 0);
        rng.shuffle(all);
        vector<int> position(all.begin(), all.begin() + n);
        vector<int> speed = rng.ints(n, 1, 6);
        run(target, position, speed, brute(target, position, speed));
    }
    for (int iter = 0; iter < 300; ++iter) {
        int target = rng(900000, 1000000);
        int n = rng(1, 12);
        set<int> used;
        vector<int> position, speed;
        while (static_cast<int>(position.size()) < n) {
            int p = rng(0, 50) < 25 ? rng(0, 40) : rng(0, target - 1);
            if (used.insert(p).second) {
                position.push_back(p), speed.push_back(rng(999980, 1000000));
            }
        }
        run(target, position, speed, brute(target, position, speed));
    }
}

TEST(large) {
    Rng rng(260);
    const int n = 100000, target = 1000000;
    vector<int> by_rank(n);
    for (int k = 0; k < n; ++k) {
        by_rank[k] = 10 * (n - 1 - k);
    }

    vector<int> position = by_rank, speed(n, 1);
    shuffle_cars(rng, position, speed);
    run(target, position, speed, n);

    position = by_rank;
    for (int k = 0; k < n; ++k) {
        speed[k] = target - by_rank[k];
    }
    shuffle_cars(rng, position, speed);
    run(target, position, speed, 1);

    position = by_rank;
    for (int k = 0; k < n; ++k) {
        speed[k] = k % 100 == 0 ? 1 : 1000000;
    }
    shuffle_cars(rng, position, speed);
    run(target, position, speed, n / 100);

    position = by_rank;
    speed[0] = 1;
    for (int k = 1; k < n; ++k) {
        speed[k] = rng(100000, 1000000);
    }
    shuffle_cars(rng, position, speed);
    run(target, position, speed, 1);
}

}
