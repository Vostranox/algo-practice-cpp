#pragma once
#include "prelude.hpp"

#include <cxxabi.h>

namespace testing {

struct Failure {
    std::string msg;
};

[[noreturn]] inline void fail(const std::string& msg) { throw Failure{msg}; }

inline constexpr std::nullopt_t null = std::nullopt;
using Tree = std::vector<std::optional<int>>;

template <class T>
std::string repr(const T& x);

inline std::string type_name(const std::type_info& t) {
    int status = 0;
    char* d = abi::__cxa_demangle(t.name(), nullptr, nullptr, &status);
    std::string s = status == 0 && d ? d : t.name();
    std::free(d);
    return s;
}

namespace detail {
template <class T> struct is_optional : std::false_type {};
template <class T> struct is_optional<std::optional<T>> : std::true_type {};
template <class T> struct is_pair : std::false_type {};
template <class A, class B> struct is_pair<std::pair<A, B>> : std::true_type {};
template <class T> struct is_tuple : std::false_type {};
template <class... A> struct is_tuple<std::tuple<A...>> : std::true_type {};
template <class T> concept map_like = requires { typename T::key_type; typename T::mapped_type; };

inline std::string quote(std::string_view s, char q = '"') {
    std::string out(1, q);
    for (unsigned char c : s) {
        if (c == '\\' || c == static_cast<unsigned char>(q)) {
            out += '\\';
            out += static_cast<char>(c);
        } else if (c == '\n') {
            out += "\\n";
        } else if (c == '\t') {
            out += "\\t";
        } else if (c < 0x20 || c == 0x7f) {
            char buf[8];
            std::snprintf(buf, sizeof buf, "\\x%02x", c);
            out += buf;
        } else {
            out += static_cast<char>(c);
        }
    }
    out += q;
    return out;
}

inline std::string list_repr(const ListNode* head) {
    std::string out = "[";
    std::unordered_set<const ListNode*> seen;
    for (int n = 0; head; head = head->next, ++n) {
        if (n) {
            out += " -> ";
        }
        if (!seen.insert(head).second) {
            out += "<cycle>";
            break;
        }
        if (n == 40) {
            out += "...";
            break;
        }
        out += std::to_string(head->val);
    }
    return out + "]";
}

inline std::string tree_repr(const TreeNode* root) {
    std::vector<std::string> vals;
    std::deque<const TreeNode*> q{root};
    std::unordered_set<const TreeNode*> seen;
    while (!q.empty() && vals.size() < 80) {
        const TreeNode* n = q.front();
        q.pop_front();
        if (!n) {
            vals.push_back("null");
            continue;
        }
        if (!seen.insert(n).second) {
            vals.push_back("<cycle>");
            break;
        }
        vals.push_back(std::to_string(n->val));
        q.push_back(n->left);
        q.push_back(n->right);
    }
    bool more = !q.empty() && std::any_of(q.begin(), q.end(), [](auto* n) { return n != nullptr; });
    while (!vals.empty() && vals.back() == "null") {
        vals.pop_back();
    }
    std::string out = "tree[";
    for (size_t i = 0; i < vals.size(); ++i) {
        out += (i ? ", " : "") + vals[i];
    }
    return out + (more ? ", ...]" : "]");
}

inline std::string random_list_repr(const RandomNode* head) {
    std::unordered_map<const RandomNode*, int> index;
    int i = 0;
    for (auto* p = head; p && i < 40 && !index.count(p); p = p->next) {
        index[p] = i++;
    }
    std::string out = "[";
    i = 0;
    for (auto* p = head; p && i < 40; p = p->next, ++i) {
        if (i) {
            out += ", ";
        }
        out += "[" + std::to_string(p->val) + ", ";
        if (!p->random) {
            out += "null";
        } else if (index.count(p->random)) {
            out += std::to_string(index[p->random]);
        } else {
            out += "<outside>";
        }
        out += "]";
        if (i + 1 < 40 && p->next && index.count(p->next) && index[p->next] <= i) {
            out += ", <cycle>";
            break;
        }
    }
    return out + "]";
}

inline std::string graph_repr(const GraphNode* node) {
    if (!node) return "null";
    std::string out = "GraphNode(" + std::to_string(node->val) + ", neighbors=[";
    for (size_t i = 0; i < node->neighbors.size(); ++i) {
        out += (i ? ", " : "") + (node->neighbors[i] ? std::to_string(node->neighbors[i]->val) : std::string("null"));
    }
    return out + "])";
}
}

template <class T>
std::string repr(const T& x) {
    using U = std::remove_cvref_t<T>;
    if constexpr (std::is_same_v<U, bool>) {
        return x ? "true" : "false";
    } else if constexpr (std::is_same_v<U, char>) {
        return detail::quote(std::string_view(&x, 1), '\'');
    } else if constexpr (std::is_integral_v<U>) {
        return std::to_string(x);
    } else if constexpr (std::is_floating_point_v<U>) {
        std::ostringstream o;
        o << std::setprecision(12) << x;
        return o.str();
    } else if constexpr (std::is_same_v<U, std::nullptr_t> || std::is_same_v<U, std::nullopt_t>) {
        return "null";
    } else if constexpr (std::is_same_v<U, ListNode*> || std::is_same_v<U, const ListNode*>) {
        return detail::list_repr(x);
    } else if constexpr (std::is_same_v<U, TreeNode*> || std::is_same_v<U, const TreeNode*>) {
        return x ? detail::tree_repr(x) : "null";
    } else if constexpr (std::is_same_v<U, RandomNode*> || std::is_same_v<U, const RandomNode*>) {
        return detail::random_list_repr(x);
    } else if constexpr (std::is_same_v<U, GraphNode*> || std::is_same_v<U, const GraphNode*>) {
        return detail::graph_repr(x);
    } else if constexpr (std::is_convertible_v<const U&, std::string_view>) {
        return detail::quote(std::string_view(x));
    } else if constexpr (detail::is_optional<U>::value) {
        return x ? repr(*x) : std::string("null");
    } else if constexpr (detail::is_pair<U>::value) {
        return "(" + repr(x.first) + ", " + repr(x.second) + ")";
    } else if constexpr (detail::is_tuple<U>::value) {
        std::string out = "(";
        std::apply([&](const auto&... e) { size_t i = 0; ((out += (i++ ? ", " : "") + repr(e)), ...); }, x);
        return out + ")";
    } else if constexpr (std::is_pointer_v<U>) {
        if (!x) return "null";
        std::ostringstream o;
        o << static_cast<const void*>(x);
        return o.str();
    } else if constexpr (detail::map_like<U> || std::ranges::range<U>) {
        constexpr bool is_map = detail::map_like<U>;
        std::string out = is_map ? "{" : "[";
        size_t i = 0;
        for (const auto& e : x) {
            if (out.size() > 2000) {
                out += ", ...";
                if constexpr (std::ranges::sized_range<U>) {
                    out += " (" + std::to_string(std::ranges::size(x)) + " items)";
                }
                break;
            }
            if (i++) {
                out += ", ";
            }
            if constexpr (is_map) {
                out += repr(e.first) + ": " + repr(e.second);
            } else {
                out += repr(e);
            }
        }
        return out + (is_map ? "}" : "]");
    } else if constexpr (requires(std::ostream& o, const U& v) { o << v; }) {
        std::ostringstream o;
        o << x;
        return o.str();
    } else {
        return "<" + type_name(typeid(U)) + ">";
    }
}

inline std::string clip(std::string s, size_t limit = 400) {
    if (s.size() > limit) {
        s = s.substr(0, limit) + " ...<" + std::to_string(s.size()) + " chars>";
    }
    return s;
}

namespace detail {
inline void join_inputs(std::string&) {}
template <class V, class... R>
void join_inputs(std::string& out, const char* name, const V& v, const R&... rest) {
    if (!out.empty()) {
        out += ", ";
    }
    out += name;
    out += '=';
    out += clip(repr(v), 200);
    join_inputs(out, rest...);
}
inline void lines(std::string&) {}
template <class V, class... R>
void lines(std::string& out, const char* name, const V& v, const R&... rest) {
    std::string label = std::string(name) + ":";
    if (label.size() < 10) {
        label.resize(10, ' ');
    }
    out += "\n" + label + clip(repr(v));
    lines(out, rest...);
}
}

template <class... In>
std::string input_line(const In&... inputs) {
    static_assert(sizeof...(In) % 2 == 0, "inputs must be given as \"name\", value pairs");
    std::string s;
    detail::join_inputs(s, inputs...);
    return s.empty() ? s : "input:    " + s + "\n";
}

template <class T, class... In>
void check(const T& got, const std::type_identity_t<T>& want, const In&... inputs) {
    if (!(got == want)) {
        fail(input_line(inputs...) + "expected: " + clip(repr(want)) + "\ngot:      " + clip(repr(got)));
    }
}

template <class... In>
void check_close(double got, double want, const In&... inputs) {
    if (!(std::fabs(got - want) <= 1e-5 * std::max(1.0, std::fabs(want)))) {
        fail(input_line(inputs...) + "expected: " + repr(want) + "\ngot:      " + repr(got));
    }
}

template <class... In>
void ensure(bool cond, const std::string& problem, const In&... inputs) {
    static_assert(sizeof...(In) % 2 == 0, "values must be given as \"name\", value pairs");
    if (!cond) {
        std::string msg = "problem:  " + problem;
        detail::lines(msg, inputs...);
        fail(msg);
    }
}

template <class T>
std::vector<T> sorted(std::vector<T> v) {
    std::sort(v.begin(), v.end());
    return v;
}

template <class T>
std::vector<std::vector<T>> sort_all(std::vector<std::vector<T>> v) {
    for (auto& inner : v) {
        std::sort(inner.begin(), inner.end());
    }
    std::sort(v.begin(), v.end());
    return v;
}

template <class T>
bool has_duplicates(std::vector<T> v) {
    std::sort(v.begin(), v.end());
    return std::adjacent_find(v.begin(), v.end()) != v.end();
}

struct Rng {
    uint64_t s;
    explicit Rng(uint64_t seed) : s(seed * 0x9E3779B97F4A7C15 + 1) {}
    uint64_t next() {
        uint64_t z = (s += 0x9E3779B97F4A7C15);
        z = (z ^ (z >> 30)) * 0xBF58476D1CE4E5B9;
        z = (z ^ (z >> 27)) * 0x94D049BB133111EB;
        return z ^ (z >> 31);
    }
    int64_t range(int64_t lo, int64_t hi) {
        return lo + static_cast<int64_t>(next() % static_cast<uint64_t>(hi - lo + 1));
    }
    int operator()(int lo, int hi) { return static_cast<int>(range(lo, hi)); }
    double real() { return (next() >> 11) * 0x1.0p-53; }
    bool coin(double p = 0.5) { return real() < p; }
    std::vector<int> ints(int n, int lo, int hi) {
        std::vector<int> v(n);
        for (auto& x : v) {
            x = (*this)(lo, hi);
        }
        return v;
    }
    std::string str(int n, const std::string& alphabet) {
        std::string s(n, ' ');
        for (auto& c : s) {
            c = alphabet[next() % alphabet.size()];
        }
        return s;
    }
    template <class T>
    void shuffle(std::vector<T>& v) {
        for (size_t i = v.size(); i > 1; --i) {
            std::swap(v[i - 1], v[next() % i]);
        }
    }
    template <class T>
    const T& pick(const std::vector<T>& v) { return v[next() % v.size()]; }
};

inline ListNode* build_list(const std::vector<int>& vals) {
    ListNode dummy;
    ListNode* tail = &dummy;
    for (int v : vals) {
        tail = tail->next = new ListNode(v);
    }
    return dummy.next;
}

inline ListNode* build_cycle_list(const std::vector<int>& vals, int pos) {
    ListNode* head = build_list(vals);
    if (!head || pos < 0) return head;
    ListNode* tail = head;
    ListNode* target = nullptr;
    for (int i = 0;; ++i, tail = tail->next) {
        if (i == pos) {
            target = tail;
        }
        if (!tail->next) break;
    }
    tail->next = target;
    return head;
}

inline std::vector<int> list_to_vec(const ListNode* head) {
    std::vector<int> out;
    std::unordered_set<const ListNode*> seen;
    for (; head; head = head->next) {
        if (!seen.insert(head).second) {
            fail("returned list has a cycle: " + detail::list_repr(head));
        }
        out.push_back(head->val);
    }
    return out;
}

inline std::vector<ListNode*> list_nodes(ListNode* head) {
    std::vector<ListNode*> out;
    std::unordered_set<ListNode*> seen;
    for (; head && seen.insert(head).second; head = head->next) {
        out.push_back(head);
    }
    return out;
}

inline TreeNode* build_tree(const Tree& vals) {
    if (vals.empty() || !vals[0]) return nullptr;
    TreeNode* root = new TreeNode(*vals[0]);
    std::deque<TreeNode*> q{root};
    size_t i = 1;
    while (!q.empty() && i < vals.size()) {
        TreeNode* n = q.front();
        q.pop_front();
        if (i < vals.size() && vals[i]) {
            q.push_back(n->left = new TreeNode(*vals[i]));
        }
        ++i;
        if (i < vals.size() && vals[i]) {
            q.push_back(n->right = new TreeNode(*vals[i]));
        }
        ++i;
    }
    return root;
}

inline Tree tree_to_vec(const TreeNode* root) {
    Tree out;
    std::deque<const TreeNode*> q{root};
    std::unordered_set<const TreeNode*> seen;
    while (!q.empty()) {
        const TreeNode* n = q.front();
        q.pop_front();
        if (!n) {
            out.push_back(null);
            continue;
        }
        if (!seen.insert(n).second) {
            fail("returned tree contains a cycle or a node used twice");
        }
        out.push_back(n->val);
        q.push_back(n->left);
        q.push_back(n->right);
    }
    while (!out.empty() && !out.back()) {
        out.pop_back();
    }
    return out;
}

inline TreeNode* find_node(TreeNode* root, int val) {
    std::deque<TreeNode*> q{root};
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop_front();
        if (!n) continue;
        if (n->val == val) return n;
        q.push_back(n->left);
        q.push_back(n->right);
    }
    return nullptr;
}

inline std::vector<TreeNode*> tree_nodes(TreeNode* root) {
    std::vector<TreeNode*> out;
    std::deque<TreeNode*> q{root};
    while (!q.empty()) {
        TreeNode* n = q.front();
        q.pop_front();
        if (!n) continue;
        out.push_back(n);
        q.push_back(n->left);
        q.push_back(n->right);
    }
    return out;
}

inline RandomNode* build_random_list(const std::vector<std::pair<int, int>>& pairs) {
    std::vector<RandomNode*> nodes;
    for (auto& [v, r] : pairs) {
        nodes.push_back(new RandomNode(v));
    }
    for (size_t i = 0; i < nodes.size(); ++i) {
        if (i + 1 < nodes.size()) {
            nodes[i]->next = nodes[i + 1];
        }
        nodes[i]->random = pairs[i].second >= 0 ? nodes[pairs[i].second] : nullptr;
    }
    return nodes.empty() ? nullptr : nodes[0];
}

inline std::vector<RandomNode*> random_list_nodes(RandomNode* head) {
    std::vector<RandomNode*> out;
    std::unordered_set<RandomNode*> seen;
    for (; head; head = head->next) {
        if (!seen.insert(head).second) {
            fail("returned list has a cycle");
        }
        out.push_back(head);
    }
    return out;
}

inline std::vector<std::pair<int, int>> random_list_to_pairs(RandomNode* head) {
    auto nodes = random_list_nodes(head);
    std::unordered_map<RandomNode*, int> index;
    for (size_t i = 0; i < nodes.size(); ++i) {
        index[nodes[i]] = static_cast<int>(i);
    }
    std::vector<std::pair<int, int>> out;
    for (auto* n : nodes) {
        if (n->random && !index.count(n->random)) {
            fail("node with val " + std::to_string(n->val) + ": random points to a node outside the returned list");
        }
        out.emplace_back(n->val, n->random ? index[n->random] : -1);
    }
    return out;
}

inline GraphNode* build_graph(const std::vector<std::vector<int>>& adj) {
    if (adj.empty()) return nullptr;
    std::vector<GraphNode*> nodes;
    for (size_t i = 0; i < adj.size(); ++i) {
        nodes.push_back(new GraphNode(static_cast<int>(i) + 1));
    }
    for (size_t i = 0; i < adj.size(); ++i) {
        for (int j : adj[i]) {
            nodes[i]->neighbors.push_back(nodes[j - 1]);
        }
    }
    return nodes[0];
}

inline std::vector<GraphNode*> graph_nodes(GraphNode* node) {
    if (!node) return {};
    std::unordered_set<GraphNode*> seen{node};
    std::vector<GraphNode*> out{node}, stack{node};
    while (!stack.empty()) {
        GraphNode* n = stack.back();
        stack.pop_back();
        for (GraphNode* nb : n->neighbors) {
            if (!nb) {
                fail("node " + std::to_string(n->val) + " has a null neighbour");
            }
            if (seen.insert(nb).second) {
                out.push_back(nb);
                stack.push_back(nb);
            }
        }
    }
    std::sort(out.begin(), out.end(), [](auto* a, auto* b) { return a->val < b->val; });
    return out;
}

inline std::vector<std::vector<int>> graph_to_adj(GraphNode* node) {
    std::vector<std::vector<int>> adj;
    for (GraphNode* n : graph_nodes(node)) {
        adj.emplace_back();
        for (GraphNode* nb : n->neighbors) {
            adj.back().push_back(nb->val);
        }
    }
    return adj;
}

struct Trace {
    static constexpr size_t kKeep = 8;
    std::deque<std::string> last;
    size_t count = 0;

    template <class... A>
    explicit Trace(const std::string& ctor, const A&... args) { add(ctor, args...); }

    template <class... A>
    void add(const std::string& name, const A&... args) {
        std::string s = name + "(";
        size_t i = 0;
        ((s += (i++ ? ", " : "") + clip(repr(args), 80)), ...);
        last.push_back(s + ")");
        if (last.size() > kKeep) {
            last.pop_front();
        }
        ++count;
    }

    std::string recent() const {
        std::string out = count > last.size() ? "... -> " : "";
        for (size_t i = 0; i < last.size(); ++i) {
            out += last[i] + (i + 1 < last.size() ? " -> " : "");
        }
        return out;
    }

    std::string where() const { return "operation #" + std::to_string(count - 1) + ": " + last.back(); }
};

template <class G, class W>
void expect_result(const Trace& t, const G& got, const W& want) {
    if (!(got == want)) {
        fail(t.where() + "\nexpected: " + clip(repr(want)) + "\ngot:      " + clip(repr(got)) +
             "\ncalls so far: " + t.recent());
    }
}

inline void expect_close_result(const Trace& t, double got, double want) {
    if (!(std::fabs(got - want) <= 1e-5 * std::max(1.0, std::fabs(want)))) {
        fail(t.where() + "\nexpected: " + repr(want) + "\ngot:      " + repr(got) + "\ncalls so far: " + t.recent());
    }
}

#define CALL(t, obj, method, ...) ((t).add(#method __VA_OPT__(, ) __VA_ARGS__), (obj).method(__VA_ARGS__))
#define EXPECT_CALL(t, want, obj, method, ...) \
    ((t).add(#method __VA_OPT__(, ) __VA_ARGS__), ::testing::expect_result((t), (obj).method(__VA_ARGS__), (want)))
#define EXPECT_CALL_CLOSE(t, want, obj, method, ...) \
    ((t).add(#method __VA_OPT__(, ) __VA_ARGS__), ::testing::expect_close_result((t), (obj).method(__VA_ARGS__), (want)))

struct TestCase {
    const char* name;
    void (*fn)();
};

inline std::vector<TestCase>& registry() {
    static std::vector<TestCase> tests;
    return tests;
}

struct Registrar {
    Registrar(const char* name, void (*fn)()) { registry().push_back({name, fn}); }
};

#define TEST(name)                                                    \
    static void test_##name();                                        \
    static ::testing::Registrar registrar_##name(#name, test_##name); \
    static void test_##name()

enum Outcome { PASS = 0, FAIL = 10, TODO = 11, ERROR = 12 };

inline Outcome run_one(const TestCase& t, std::string& detail) {
    try {
        t.fn();
        return PASS;
    } catch (const Failure& f) {
        detail = f.msg;
        return FAIL;
    } catch (const NotImplemented&) {
        detail = "not implemented yet";
        return TODO;
    } catch (const std::exception& e) {
        detail = "uncaught exception " + type_name(typeid(e)) + ": " + e.what();
        return ERROR;
    } catch (...) {
        detail = "uncaught exception of unknown type";
        return ERROR;
    }
}

inline int main(int argc, char** argv) {
    std::string mode = argc > 1 ? argv[1] : "";
    if (mode == "--list") {
        for (auto& t : registry()) {
            std::cout << t.name << "\n";
        }
        return 0;
    }
    if (mode == "--run" && argc > 2) {
        for (auto& t : registry()) {
            if (std::string(t.name) != argv[2]) continue;
            std::string detail;
            Outcome o = run_one(t, detail);
            std::cout << std::flush;
            if (o != PASS) {
                std::cout << "\n@@test-detail\n" << detail << std::endl;
            }
            return o;
        }
        std::cerr << "no test named " << argv[2] << "\n";
        return 2;
    }
    int passed = 0;
    for (auto& t : registry()) {
        std::string detail;
        Outcome o = run_one(t, detail);
        std::cout << std::flush;
        if (o == PASS) {
            ++passed;
            std::cout << "  PASS  " << t.name << std::endl;
        } else {
            std::cout << "  FAIL  " << t.name << "\n";
            std::istringstream in(detail);
            for (std::string line; std::getline(in, line);) {
                std::cout << "        " << line << "\n";
            }
            std::cout << std::flush;
        }
    }
    std::cout << passed << "/" << registry().size() << " passed" << std::endl;
    return passed == static_cast<int>(registry().size()) ? 0 : 1;
}

}

int main(int argc, char** argv) {
    return testing::main(argc, argv);
}
