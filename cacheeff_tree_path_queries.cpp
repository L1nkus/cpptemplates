#pragma GCC optimize("Ofast,unroll-loops")
#pragma GCC target("avx2")
#include <stdio.h>
#include <algorithm>
#include <vector>
#include <array>
#include <queue>
#include <deque>
#include <set>
#include <map>
#include <stdlib.h>
#include <ctime>
#include <climits>
#include <cmath>
#include <complex>
#include <iostream>
#include <cctype>
#include <cstring>
#include <numeric>
#include <bitset>
#include <stack>
#include <functional>
#include <cassert>
#include <tuple>
#include <iomanip>
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

#ifdef ONLINE_JUDGE
#define whatis(x) ;
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
#define N 1000001

// XXX out[u] is exclusive.

// Also, thanks to this op implementation, not only are hld path ids
// contigious, but also subtree ones, so can also use this for subtree queries.

// If there's some change, that only affects the result contribution of
// ancestors of the current node, or the descendents, try to just iterate over
// all ancestors, or over all descdenents.
// Very imporant to keep the core function as simple as possible.
// The lower separate arrays the better.
// If simple, 1e10 ops under 2s.
// (https://codeforces.com/contest/925/problem/E)

vi adj[N];
// wouldn't them in a struct be better?
// -> nope, 2x slower.
/* struct nodes { */
/*     int k; */
/*     ll b; */
/* } node[N]; */
int k[N];
ll b[N];
int n,q;

// XXX out[u] is exclusive.
// <in[u], out[u]) zwraca range poddrzewa nodea u.
int in[N], out[N], sz[N], nxt[N], p[N], d[N], in_to_orig[N];
void dfs_sz(int v) {
    sz[v] = 1;
    for(auto &u: adj[v]) {
        if(u == p[v])
            continue;
        p[u] = v;
        d[u] = d[v] + 1;
        dfs_sz(u);
        sz[v] += sz[u];
        if(sz[u] > sz[adj[v][0]]) {
            swap(u, adj[v][0]);
        }
    }
}

int hld_it;
void dfs_hld(int v) {
    in[v] = hld_it++;
    in_to_orig[in[v]] = v;
    for(auto u: adj[v]) {
        if(u == p[v])
            continue;
        nxt[u] = (u == adj[v][0] ? nxt[v] : u);
        dfs_hld(u);
    }
    out[v] = hld_it;
}

// I don't have to care about any adj, p, in etc. here, just the value arrays
// used in query / update funs.
void relabel(){
    int nwk[n];
    ll nwb[n];
    for(int i = 0; i < n; ++i){
        nwk[in[i]] = k[i];
        nwb[in[i]] = b[i];
        /* node[in[i]] = {k[i], b[i]}; */
    }
    memcpy(k, nwk, sizeof nwk);
    memcpy(b, nwb, sizeof nwb);
}

int target;
ll crtype;
ll res;
int crinck, crincb;

// https://www.codechef.com/submit/SONGIF
void query(int l, int r){
    for(int v = l; v <= r; ++v){
        res = max(res, k[v] * crtype + b[v]);
    }
}

void inc(int l, int r){
    for(int v = l; v <= r; ++v){
        k[v] += crinck;
        b[v] += crincb;
    }
}

void d1(int v, int u){
    while(nxt[v] != nxt[u]){
        if(d[nxt[v]] < d[nxt[u]]) swap(v, u);
        query(in[nxt[v]], in[v]);
        v = p[nxt[v]];
    }
    if(d[v] < d[u])
        swap(v, u);
    query(in[u], in[v]);
}

void d2(int v, int u){
    while(nxt[v] != nxt[u]){
        if(d[nxt[v]] < d[nxt[u]]) swap(v, u);
        inc(in[nxt[v]], in[v]);
        v = p[nxt[v]];
    }
    if(d[v] < d[u])
        swap(v, u);
    inc(in[u], in[v]);
}

// https://codeforces.com/contest/925/problem/E
// Iterating over ancestors and modifying crres
/* template<bool leaves> */
/* void query(int l, int r){ */
/*     if(leaves){ */
/*         for(int v = l; v <= r; ++v){ */
/*             if(dp[v] == 0) // opt till zero */
/*                 ++crres; */
/*             ++dp[v]; */
/*         } */
/*     } */
/*     else{ */
/*         for(int v = l; v <= r; ++v){ */
/*             if(--dp[v] == 0) */
/*                 --crres; */
/*         } */
/*     } */
/* } */

/* template<bool leaves> */
/* void d1(int v){ */
/*     if(leaves) */
/*         assert(!onpto[in[v]]); */
/*     else */
/*         assert(onpto[in[v]]); */
/*     onpto[in[v]] ^= 1; */
/*     if(leaves){ */
/*         if(dp[in[v]] > 0) */
/*             --crres; */
/*         dp[in[v]] += 213769; */
/*     } */
/*     else{ */
/*         dp[in[v]] -= 213769; */
/*         if(dp[in[v]] > 0) */
/*             ++crres; */
/*     } */
/*     if(v == 0) */
/*         return; */
/*     v = p[v]; */
/*     for(;;){ */
/*         query<leaves>(in[nxt[v]], in[v]); */
/*         if(nxt[v] == 0) */
/*             break; */
/*         v = p[nxt[v]]; */
/*     } */
/* } */


int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    sc(n,q);
    FOR(i,0,n)
        sc(k[i]);
    FOR(i,0,n)
        sc(b[i]);
    FOR(i,1,n){
        int f,s;
        sc(f,s);
        --f,--s;
        adj[f].push_back(s);
        adj[s].push_back(f);
    }
    dfs_sz(0);
    dfs_hld(0);
    relabel();
    while(q--){
        int typ;
        sc(typ);
        int u,v;
        sc(u,v);
        --u, --v;
        target = v;
        if(typ == 1){
            sc(crinck, crincb);
            /* d2(u, -1); */
            d2(u, v);
        }
        else{
            sc(crtype);
            res = -(1ll << 62);
            /* d1(u, -1); */
            d1(u, v);
            cout << res << '\n';
        }
    }
}
