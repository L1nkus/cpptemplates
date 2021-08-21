#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define pb push_back
#define mp make_pair
#define all(a) begin(a),end(a)
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
#define FORE(x,val,to) for(auto x=(val);x<=(to);++x)
#define FORR(x,arr) for(auto &x: arr)
#define FORS(x,plus,arr) for(auto x = begin(arr)+(plus); x != end(arr); ++x)
#define FORREV(x,plus,arr) for(auto x = (arr).rbegin()+(plus); x !=(arr).rend(); ++x)
#define REE(s_) {cout<<s_<<'\n';exit(0);}
#define GET(arr) for(auto &i: (arr)) sc(i)
#define whatis(x) cerr << #x << " is " << (x) << endl;
#define e1 first
#define e2 second
#define INF 0x7f7f7f7f
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
typedef uint64_t ull;
#define umap unordered_map
#define uset unordered_set
using namespace std;
using namespace __gnu_pbds;

#ifdef ONLINE_JUDGE
#define whatis(x) ;
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

// Upewnij się, ile dokładnie każdy node może (maksymalnie) dostać flowu (Druz1B flashbacks)
// Czasami, jeśli dany node ma wiele ograniczonych in-edgy, a ma mieć
// ograniczone out-edgea, to trzeba dodać dodatkowy node z jednym inem od tego,
// aby na pewno ograniczenia co do całkowitego out-flowu z tego nodea się zgadzały

// Btw, ten graf nie może mieć ujemnych cykli -> Przed aplikowaniem mcmf trzeba
// tak przekształcić graf, aby nie miał ujemnych cykli, czyli either jakaś
// konwersja do scc może być potrzebna, albo findowanie edgea z najmniejszym
// capacity w cyklu, i zastąpianie cyklu jednym nodem będącym bottleneckiem
// jakoś (https://codeforces.com/blog/entry/53404).

// Also, wtf, this implementation had TLE on atcoder problem with 4s tle, while
// atcoder library mcmf passed in 257ms (though it doesn't support negative
// edges). This version didn't pass even without negative edges.
// https://atcoder.jp/contests/abc214/submissions/25128817 vs https://atcoder.jp/contests/abc214/submissions/25128832

// Tomasz Nowak, Michał Staniewski
struct MCMF {
    struct Edge {
        int v, u, flow, cap;
        ll cost;
        friend ostream& operator<<(ostream &os, Edge &e) {
            return os << vector<ll>{e.v, e.u, e.flow, e.cap, e.cost};
        }
    };
    int n;
    const ll inf_ll = 1e18;
    const int inf_int = 1e9;
    vector<vector<int>> graph;
    vector<Edge> edges;
    MCMF(int N) : n(N), graph(n) {}
    void add_edge(int v, int u, int cap, ll cost) {
        int e = edges.size();
        graph[v].emplace_back(e);
        graph[u].emplace_back(e + 1);
        edges.emplace_back(Edge{v, u, 0, cap, cost});
        edges.emplace_back(Edge{u, v, 0, 0, -cost});
    }
    pair<int, ll> augment(int source, int sink) {
        vector<ll> dist(n, inf_ll);
        vector<int> from(n, -1);
        dist[source] = 0;
        deque<int> que = {source};
        vector<bool> inside(n);
        inside[source] = true;
        while(que.size()) {
            int v = que.front();
            inside[v] = false;
            que.pop_front();
            for(int i : graph[v]) {
                Edge &e = edges[i];
                if(e.flow != e.cap and dist[e.u] > dist[v] + e.cost) {
                    dist[e.u] = dist[v] + e.cost;
                    from[e.u] = i;
                    if(not inside[e.u]) {
                        inside[e.u] = true;
                        que.emplace_back(e.u);
                    }
                }
            }
        }
        if(from[sink] == -1)
            return {0, 0};
        int flow = inf_int, e = from[sink];
        while(e != -1) {
            flow = min(flow, edges[e].cap - edges[e].flow);
            e = from[edges[e].v];
        }
        e = from[sink];
        while(e != -1){
            edges[e].flow += flow;
            edges[e ^ 1].flow -= flow;
            e = from[edges[e].v];
        }
        return {flow, flow * dist[sink]};
    }

    pair<int, ll> operator()(int source, int sink) {
        int flow = 0;
        ll cost = 0;
        pair<int, ll> got;
        do {
            got = augment(source, sink);
            flow += got.first;
            cost += got.second;
        } while(got.first);
        return {flow, cost};
    }
};

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
}

