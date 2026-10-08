#include "testing.hpp"
#include SOLUTION_FILE

namespace testing {

static void run(const string& path, const string& want) {
    check(Solution().simplifyPath(path), want, "path", path);
}

static string rewrite(const string& path) {
    string p;
    for (char c : path + "/") {
        if (!(c == '/' && !p.empty() && p.back() == '/')) {
            p += c;
        }
    }
    for (bool changed = true; changed;) {
        changed = false;
        size_t at = p.find("/./");
        if (at != string::npos) {
            p.replace(at, 3, "/");
            changed = true;
        } else if (p.rfind("/../", 0) == 0) {
            p.replace(0, 4, "/");
            changed = true;
        } else if ((at = p.find("/../")) != string::npos) {
            size_t start = p.rfind('/', at - 1);
            p.replace(start, at + 4 - start, "/");
            changed = true;
        }
    }
    if (p.size() > 1) {
        p.pop_back();
    }
    return p;
}

static string rep(const string& s, int times) {
    string out;
    for (int i = 0; i < times; ++i) {
        out += s;
    }
    return out;
}

TEST(examples) {
    run("/docs//notes/", "/docs/notes");
    run("/srv/../../tmp/./x", "/tmp/x");
    run("/.../a/..", "/...");
}

TEST(edge_cases) {
    run("/", "/");
    run("//", "/");
    run("/.", "/");
    run("/..", "/");
    run("/../..", "/");
    run("/a/..", "/");
    run("/a/../", "/");
    run("/a/./b/", "/a/b");
    run("/..../", "/....");
    run("/..a/b../.b./", "/..a/b../.b.");
    run("/.hidden", "/.hidden");
    run("/a//b////c/d//././/..", "/a/b/c");
    run("/a/b/c/../../..", "/");
    run("/a/b/c/../../../..", "/");
    run("/_/9/X_y.z", "/_/9/X_y.z");
    run("/a/./.././../b", "/b");
    run("/a/b/../../c/d/..", "/c");
    run("///x///", "/x");
    run("/x/.../../y", "/x/y");
}

TEST(random) {
    Rng rng(71);
    const vector<string> parts = {".", "..", "...", "a", "b", "ab", ".a", "a.", "_", "..b", "Z9"};
    for (int it = 0; it < 2000; ++it) {
        string path;
        for (int k = rng(0, 8); k > 0; --k) {
            path += string(rng(1, 3), '/') + rng.pick(parts);
        }
        if (path.empty() || rng.coin(0.3)) {
            path += string(rng(1, 2), '/');
        }
        run(path, rewrite(path));
    }
}

TEST(large) {
    run(rep("/a", 1500), rep("/a", 1500));
    run(rep("/..", 1000), "/");
    run(rep("/x", 750) + rep("/..", 500), rep("/x", 250));
    run(string(3000, '/'), "/");
    run(rep("/.", 1500), "/");
    run("/" + string(2999, '.'), "/" + string(2999, '.'));
    Rng rng(7100);
    const vector<string> parts = {".", "..", "..", "...", "a", "bc", "d_e", "...."};
    for (int it = 0; it < 20; ++it) {
        string path;
        while (path.size() < 2990) {
            path += string(rng(1, 2), '/') + rng.pick(parts);
        }
        path.resize(3000, '/');
        run(path, rewrite(path));
    }
}

}
