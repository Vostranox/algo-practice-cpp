#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

using Genes = vector<string>;

static void run(const string& start, const string& end, const Genes& bank, int want) {
    Genes arg = bank;
    check(Solution().minMutation(start, end, arg), want, "startGene", start, "endGene", end, "bank", bank);
}

static int differences(const string& a, const string& b) {
    int d = 0;
    for (int i = 0; i < 8; ++i) {
        d += a[i] != b[i];
    }
    return d;
}

static int fewest(const string& start, const string& end, const Genes& bank) {
    if (start == end) return 0;
    Genes nodes = {start};
    for (auto& g : bank) {
        if (find(nodes.begin(), nodes.end(), g) == nodes.end()) {
            nodes.push_back(g);
        }
    }
    int n = nodes.size(), target = find(nodes.begin(), nodes.end(), end) - nodes.begin();
    if (target == n || target == 0) return -1;
    const int INF = 1000;
    vector<vector<int>> d(n, vector<int>(n, INF));
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            d[i][j] = i == j ? 0 : differences(nodes[i], nodes[j]) == 1 ? 1 : INF;
        }
    }
    for (int k = 0; k < n; ++k) {
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < n; ++j) {
                d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
            }
        }
    }
    return d[0][target] >= INF ? -1 : d[0][target];
}

static string mutate(Rng& rng, string g, int times) {
    while (times-- > 0) {
        int pos = rng(0, 7);
        char c;
        do {
            c = "ACGT"[rng(0, 3)];
        } while (c == g[pos]);
        g[pos] = c;
    }
    return g;
}

TEST(examples) {
    run("AAAAACCC", "AAAAAGGC", {"AAAAAGCC", "AAAAAGGC"}, 2);
    run("GATTACAA", "GATTACCA", {"GATTACAT", "CATTACAA"}, -1);
    run("AAAAAAAA", "AAAAAATT", {"AAAAAATT", "GAAAAAAA", "GAAAAATA", "GAAAAATT"}, 4);
}

TEST(edge_cases) {
    run("ACGTACGT", "ACGTACGT", {"ACGTACGT"}, 0);
    run("AAAAAAAA", "AAAAAAAC", {}, -1);
    run("AAAAAAAA", "AAAAAAAC", {"AAAAAAAC"}, 1);
    run("AAAAAAAA", "CCAAAAAA", {"CCAAAAAA"}, -1);
    run("TTTTTTTT", "TTTTTTTA", {"TTTTTTTT", "TTTTTTTA"}, 1);
    run("AAAAAAAA", "GAAAAAAA", {"CAAAAAAA", "GAAAAAAA"}, 1);
    run("AAAAAAAA", "CCCAAAAA", {"CAAAAAAA", "AAAAAAAG", "CCAAAAAA", "CAAAAAAG", "CCCAAAAA"}, 3);
    run("AAAAAAAA", "AAAAAACC", {"TAAAAAAA", "TAAAAAAC", "TAAAAACC", "AAAAAACC"}, 4);
    run("ACGTACGT", "TGCATGCA", {"TGCATGCA", "ACGTACGA", "ACGTACCA"}, -1);
}

TEST(random) {
    Rng rng(199);
    for (int iter = 0; iter < 800; ++iter) {
        string start = mutate(rng, "AAAAAAAA", 8);
        Genes bank, grown = {start};
        set<string> pool;
        int size = rng(0, 10);
        while (static_cast<int>(pool.size()) < size) {
            string g = rng.coin(0.85) ? mutate(rng, rng.pick(grown), 1) : mutate(rng, start, 8);
            if (pool.insert(g).second) {
                bank.push_back(g), grown.push_back(g);
            }
        }
        rng.shuffle(bank);
        string end = !bank.empty() && rng.coin(0.85) ? rng.pick(bank) : mutate(rng, start, rng(1, 3));
        if (end == start && !pool.count(start)) continue;
        run(start, end, bank, fewest(start, end, bank));
    }
}

TEST(large) {
    Genes chain;
    string g = "AAAAAAAA";
    for (int i = 0; i < 8; ++i) {
        g[i] = 'C', chain.push_back(g);
    }
    g[0] = 'G', chain.push_back(g);
    g[1] = 'G', chain.push_back(g);
    Rng rng(1990);
    Genes bank = chain;
    rng.shuffle(bank);
    run("AAAAAAAA", "GGCCCCCC", bank, 10);
    run("AAAAAAAA", "CCCCCAAA", bank, 5);
    run("GGCCCCCC", "AAAAAAAA", bank, -1);
    run("CAAAAAAA", "GGCCCCCC", bank, 9);
    bank = chain;
    bank[4] = "TTTTTTTT";
    rng.shuffle(bank);
    run("AAAAAAAA", "GGCCCCCC", bank, -1);
    run("AAAAAAAA", "CCCCAAAA", bank, 4);
    bank.clear();
    for (int i = 0; i < 8; ++i) {
        bank.push_back(string(8, 'T')), bank.back()[i] = 'G';
    }
    bank.push_back("TTTTTTTC"), bank.push_back("ATTTTTTT");
    rng.shuffle(bank);
    run("TTTTTTTT", "TTTGTTTT", bank, 1);
    run("TTTTTTTT", "ATTTTTTT", bank, 1);
    run("TTTGTTTT", "GTTTTTTT", bank, -1);
}

}
