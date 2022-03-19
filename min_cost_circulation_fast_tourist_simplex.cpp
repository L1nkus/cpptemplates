/**
 *    author:  tourist
 *    created: 19.03.2022 15:09:48       
**/
// https://atcoder.jp/contests/arc137/submissions/30231295
// 64ms tylko vs 442ms model solv
// Yep. Fastest submit by a very wide margin.
#include <bits/stdc++.h>
 
using namespace std;
 
// https://judge.yosupo.jp/submission/57330
 
static_assert(sizeof(int) == 4 && sizeof(long) == 8);
 
struct linked_lists {
    int L, N;
    vector<int> next, prev;
 
    // L: lists are [0...L), N: elements are [0,...N)
    explicit linked_lists(int L = 0, int N = 0) { assign(L, N); }
 
    int rep(int l) const { return l + N; } // "representative" of list l
    int head(int l) const { return next[rep(l)]; }
    int tail(int l) const { return prev[rep(l)]; }
    bool empty(int l) const { return next[rep(l)] == rep(l); }
 
    void push_front(int l, int n) { link(rep(l), n, head(l)); }
    void push_back(int l, int n) { link(tail(l), n, rep(l)); }
    void insert_before(int i, int n) { link(prev[i], n, i); }
    void insert_after(int i, int n) { link(i, n, next[i]); }
    void erase(int n) { link(prev[n], next[n]); }
    void pop_front(int l) { link(rep(l), next[head(l)]); }
    void pop_back(int l) { link(prev[tail(l)], rep(l)); }
 
    void clear() {
        iota(begin(next) + N, end(next), N); // sets next[rep(l)] = rep(l)
        iota(begin(prev) + N, end(prev), N); // sets prev[rep(l)] = rep(l)
    }
    void assign(int L, int N) {
        this->L = L, this->N = N;
        next.resize(N + L), prev.resize(N + L), clear();
    }
 
  private:
    inline void link(int u, int v) { next[u] = v, prev[v] = u; }
    inline void link(int u, int v, int w) { link(u, v), link(v, w); }
};
 
// Iterate through elements (call them i) of the list #l in "lists"
#define FOR_EACH_IN_LINKED_LIST(i, l, lists) \
    for (int z##i = l, i = lists.head(z##i); i != lists.rep(z##i); i = lists.next[i])
 
/**
 * Network simplex for minimum cost circulation with fixed supply/demand at nodes.
 * Supports negative costs, negative cost cycles, self-loops and multiple edges fine.
 *
 * Flow should be large enough to hold sum of supplies and edge flows
 * Cost should be large enough to hold sum of absolute costs * 2V (usually >=64 bits)
 *
 * Complexity: O(V) expected pivot, O(E) worst-case
 *
 * Usage:
 *     network_simplex<int, long> mcc(V);
 *     for (edges...) {
 *         mcc.add(u, v, cap, cost);
 *     }
 *     for (nodes...) {
 *         mcc.set_supply(u, supply);
 *         mcc.set_demand(u, demand);
 *     }
 *     bool feasible = mcc.mincost_circulation();
 *     auto mincost = mcc.circulation_cost();
 *
 * References:
 *   LEMON network_simplex.h
 *   OCW MIT MIT15_082JF10_av16.pdf
 *   OCW MIT MIT15_082JF10_lec16.pdf
 */
template <typename Flow, typename Cost>
struct network_simplex {
    // we number the vertices 0,...,V-1, R is given number V.
 
    explicit network_simplex(int V) : V(V), node(V + 1) {}
 
    void add(int u, int v, Flow cap, Cost cost) {
        assert(0 <= u && u < V && 0 <= v && v < V);
        edge.push_back({{u, v}, cap, cost}), E++;
    }
 
    void set_supply(int u, Flow supply) { node[u].supply = supply; }
    void set_demand(int u, Flow demand) { node[u].supply = -demand; }
    auto get_supply(int u) const { return node[u].supply; }
 
    auto get_potential(int u) const { return node[u].pi; }
    auto get_flow(int e) const { return edge[e].flow; }
    auto get_cost(int e) const { return edge[e].cost; }
 
    auto reduced_cost(int e) const {
        auto [u, v] = edge[e].node;
        return edge[e].cost + node[u].pi - node[v].pi;
    }
 
    template <typename CostSum = Cost>
    auto circulation_cost() const {
        CostSum sum = 0;
        for (int e = 0; e < E; e++) {
            sum += edge[e].flow * CostSum(edge[e].cost);
        }
        return sum;
    }
 
    void verify_spanning_tree() const {
        for (int e = 0; e < E; e++) {
            assert(0 <= edge[e].flow && edge[e].flow <= edge[e].cap);
            assert(edge[e].flow == 0 || reduced_cost(e) <= 0);
            assert(edge[e].flow == edge[e].cap || reduced_cost(e) >= 0);
        }
    }
 
    bool mincost_circulation() {
        static constexpr bool INFEASIBLE = false, OPTIMAL = true;
 
        // Check trivialities: positive cap[e] and sum of supplies is 0
        Flow sum_supply = 0;
        for (int u = 0; u < V; u++) {
            sum_supply += node[u].supply;
        }
        if (sum_supply != 0) {
            return INFEASIBLE;
        }
        for (int e = 0; e < E; e++) {
            if (edge[e].cap < 0) {
                return INFEASIBLE;
            }
        }
 
        // Compute inf_cost as sum of all costs + 1, and reset the flow network
        Cost inf_cost = 1;
        for (int e = 0; e < E; e++) {
            edge[e].flow = 0;
            edge[e].state = STATE_LOWER;
            inf_cost += abs(edge[e].cost);
        }
 
        edge.resize(E + V); // make space for V artificial edges
        bfs.resize(V + 1);
        children.assign(V + 1, V + 1);
 
        // Add V artificial edges with infinite cost and initial supply for feasible flow
        int root = V;
        node[root] = {-1, -1, 0, 0};
 
        for (int u = 0, e = E; u < V; u++, e++) {
            // spanning tree links
            node[u].parent = root, node[u].pred = e;
            children.push_back(root, u);
 
            auto supply = node[u].supply;
            if (supply >= 0) {
                node[u].pi = -inf_cost;
                edge[e] = {{u, root}, supply, inf_cost, supply, STATE_TREE};
            } else {
                node[u].pi = inf_cost;
                edge[e] = {{root, u}, -supply, inf_cost, -supply, STATE_TREE};
            }
        }
 
        // We want to, hopefully, find a pivot edge in O(sqrt(E)). This can be tuned.
        block_size = max(int(ceil(sqrt(E + V))), min(10, V + 1));
        next_arc = 0;
 
        // Pivot pivot pivot
        int in_arc = select_pivot_edge();
        while (in_arc != -1) {
            pivot(in_arc);
            in_arc = select_pivot_edge();
        }
 
        // If there is >0 flow through an artificial edge, the problem is infeasible.
        for (int e = E; e < E + V; e++) {
            if (edge[e].flow > 0) {
                edge.resize(E);
                return INFEASIBLE;
            }
        }
        edge.resize(E);
        return OPTIMAL;
    }
 
  private:
    enum ArcState : int8_t { STATE_UPPER = -1, STATE_TREE = 0, STATE_LOWER = 1 };
 
    struct Node {
        int parent, pred;
        Flow supply;
        Cost pi;
    };
    struct Edge {
        array<int, 2> node; // [0]->[1]
        Flow cap;
        Cost cost;
        Flow flow = 0;
        ArcState state = STATE_LOWER;
    };
 
    int V, E = 0, next_arc = 0, block_size = 0;
    vector<Node> node;
    vector<Edge> edge;
    linked_lists children;
    vector<int> bfs; // scratchpad for downwards bfs and evert
 
    int select_pivot_edge() {
        // block search: check block_size edges looping, and pick the lowest reduced cost
        Cost minimum = 0;
        int in_arc = -1;
        int count = block_size, seen_edges = E + V;
        for (int& e = next_arc; seen_edges-- > 0; e = e + 1 == E + V ? 0 : e + 1) {
            if (minimum > edge[e].state * reduced_cost(e)) {
                minimum = edge[e].state * reduced_cost(e);
                in_arc = e;
            }
            if (--count == 0 && minimum < 0) {
                break;
            } else if (count == 0) {
                count = block_size;
            }
        }
        return in_arc;
    }
 
    void pivot(int in_arc) {
        // Find lca of u_in and v_in with two pointers technique
        auto [u_in, v_in] = edge[in_arc].node;
        int a = u_in, b = v_in;
        while (a != b) {
            a = node[a].parent == -1 ? v_in : node[a].parent;
            b = node[b].parent == -1 ? u_in : node[b].parent;
        }
        int lca = a;
 
        // Orient the edge so that we add flow along u_in->v_in
        if (edge[in_arc].state == STATE_UPPER) {
            swap(u_in, v_in);
        }
 
        // Let's find the saturing flow push
        enum OutArcSide { SAME_EDGE, U_IN_SIDE, V_IN_SIDE };
        OutArcSide side = SAME_EDGE;
        Flow flow_delta = edge[in_arc].cap; // how much we can push to saturate
        int u_out = -1;                     // the exiting arc
 
        // Go up from u_in to lca, break ties by prefering lower vertices
        for (int u = u_in; u != lca && flow_delta > 0; u = node[u].parent) {
            int e = node[u].pred;
            bool edge_down = u == edge[e].node[1];
            Flow to_saturate = edge_down ? edge[e].cap - edge[e].flow : edge[e].flow;
 
            if (flow_delta > to_saturate) {
                flow_delta = to_saturate;
                u_out = u;
                side = U_IN_SIDE;
            }
        }
 
        // Go up from v_in to lca, break ties by prefering higher vertices
        for (int u = v_in; u != lca; u = node[u].parent) {
            int e = node[u].pred;
            bool edge_up = u == edge[e].node[0];
            Flow to_saturate = edge_up ? edge[e].cap - edge[e].flow : edge[e].flow;
 
            if (flow_delta >= to_saturate) {
                flow_delta = to_saturate;
                u_out = u;
                side = V_IN_SIDE;
            }
        }
 
        // Augment along the cycle if we can push anything
        if (flow_delta > 0) {
            auto delta = edge[in_arc].state * flow_delta;
            edge[in_arc].flow += delta;
 
            for (int u = edge[in_arc].node[0]; u != lca; u = node[u].parent) {
                int e = node[u].pred;
                edge[e].flow += u == edge[e].node[0] ? -delta : delta;
            }
            for (int u = edge[in_arc].node[1]; u != lca; u = node[u].parent) {
                int e = node[u].pred;
                edge[e].flow += u == edge[e].node[0] ? delta : -delta;
            }
        }
 
        // Return now if we didn't change the spanning tree. The state of in_arc flipped.
        if (side == SAME_EDGE) {
            edge[in_arc].state = ArcState(-edge[in_arc].state);
            return;
        }
 
        // Basis exchange: Replace out_arc with in_arc in the spanning tree
        int out_arc = node[u_out].pred;
        edge[in_arc].state = STATE_TREE;
        edge[out_arc].state = edge[out_arc].flow ? STATE_UPPER : STATE_LOWER;
 
        // Put u_in on the same side as u_out
        if (side == V_IN_SIDE) {
            swap(u_in, v_in);
        }
 
        // Evert: Walk up from u_in to u_out, and fix parent/pred/child pointers downwards
        int i = 0, S = 0;
        for (int u = u_in; u != u_out; u = node[u].parent) {
            bfs[S++] = u;
        }
        assert(S <= V);
        for (i = S - 1; i >= 0; i--) {
            int u = bfs[i], p = node[u].parent;
            children.erase(p); // remove p from its children list and add it to u's
            children.push_back(u, p);
            node[p].parent = u;
            node[p].pred = node[u].pred;
        }
        children.erase(u_in); // remove u_in from its children list and add it to v_in's
        children.push_back(v_in, u_in);
        node[u_in].parent = v_in;
        node[u_in].pred = in_arc;
 
        // Fix potentials: Visit the subtree of u_in (pi_delta is not 0).
        Cost current_pi = reduced_cost(in_arc);
        Cost pi_delta = u_in == edge[in_arc].node[0] ? -current_pi : current_pi;
 
        bfs[0] = u_in;
        for (i = 0, S = 1; i < S; i++) {
            int u = bfs[i];
            node[u].pi += pi_delta;
            FOR_EACH_IN_LINKED_LIST (v, u, children) { bfs[S++] = v; }
        }
    }
};
 
namespace std {
string to_string(__int128_t x) {
    if (x == 0)
        return "0";
    __uint128_t k = x;
    if (k == (__uint128_t(1) << 127))
        return "-170141183460469231731687303715884105728";
    string result;
    if (x < 0) {
        result += "-";
        x *= -1;
    }
    string t;
    while (x) {
        t.push_back('0' + x % 10);
        x /= 10;
    }
    reverse(t.begin(), t.end());
    return result + t;
}

ostream& operator<<(ostream& o, __int128_t x) { return o << to_string(x); }
} // namespace std


int main() {
  ios::sync_with_stdio(false);
  cin.tie(0);
  int n, m, d;
  cin >> n >> m >> d;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  network_simplex<long, long> ns(n + 1);
  for (int i = 0; i < n; i++) {
    ns.add(i, i + 1, a[i], -d);
    ns.add(i, i + 1, m, 0);
  }
  for (int i = 0; i < m; i++) {
    int l, r, c;
    cin >> l >> r >> c;
    ns.add(r, l - 1, 1, c);
  }
  assert(ns.mincost_circulation());
  __int128_t optimum = 0;
  for (int e = 0; e < 2 * n + m; e++) {
    optimum += __int128_t(ns.get_flow(e)) * ns.get_cost(e);
  }
  cout << -optimum << '\n';
  return 0;
}
