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
// dif INF, watch out.
#define INF 1ll << 62
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

// Cache efficient tree dp, by transforming the node order into bfs order.
// Then, calculating the dp bottom up in reverse bfs order.
// Furthermore, also cache-efficiently traversing the adjacency list.
// https://csacademy.com/contest/archive/task/growing-trees/statistics/

ll dpsub[N];
ll mxdp;
struct edge {
    int oth, init, chg;
};
vector<edge> adj[N];
edge adj2[N]; // for even more memory contiguousness.
pi adjrng[N]; // {low, high} inclusive.

int crd;

inline int edgval(const edge &e){
    return e.init + crd * e.chg;
}
int orig_to_bfs_ord[N];
int bfs_to_orig_ord[N];
int pr[N];
bool rvis[N];

void d5(int v){
    ll premx = 0;
    /* for(int ii = adjrng[v].first; ii <= adjrng[v].second; ++ii){ */
    for(int ii = adjrng[v].second; ii >= adjrng[v].first; --ii){
        const auto &i = adj2[ii];
        if(i.oth == pr[v])
            continue;
        ll sth = dpsub[i.oth] + edgval(i);
        mxdp = max(mxdp, premx + sth);
        premx = max(premx, sth);
    }
    dpsub[v] = premx;
}

void relabel(){
    vector<pi> vec{{0, -1}};
    int it = 0;
    while(it < (int)vec.size()){
        auto [v, p] = vec[it++];
        orig_to_bfs_ord[v] = it - 1;
        bfs_to_orig_ord[it - 1] = v;
        rvis[v] = 1;
        FORR(i,adj[v]){
            int chi = i.oth;
            if(rvis[chi]){
                i.oth = p;
                continue;
            }
            int nxid = vec.size();
            vec.push_back({i.oth, it - 1});
            pr[nxid] = it - 1;
            i.oth = nxid;
        }
    }
    int it2 = 0;
    for(int i = 0; i < it; ++i){
        adjrng[i].first = it2;
        for(auto &x: adj[bfs_to_orig_ord[i]]){
            adj2[it2++] = std::move(x);
        }
        adjrng[i].second = it2 - 1;
    }
}

int32_t main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,d;
    sc(n,d);
    FOR(i,1,n){
        int f, oth, init, chg;
        sc(f, oth, init, chg);
        --f, --oth;
        adj[f].push_back({oth, init, chg});
        adj[oth].push_back({f, init, chg});
    }
    relabel();
    pair<ll,int> res = {INF,INF};
    auto getres = [&](int x) -> pair<ll,int>{
        crd = x;
        mxdp = 0;
        // Iterowanie w reverse bfs order.
        for(int i = n - 1; i >= 0; --i)
            d5(i);
        return pair<ll,int>{mxdp, x};
    };
    int low = 0, high = d, mid;
    while(low < high){
        mid = (low + high) / 2;
        pi res1 = getres(mid);
        pi res2 = getres(mid + 1);
        if(res1 > res2){
            low = mid + 1;
        }
        else{
            high = mid;
        }
    }
    res = getres(low);
    cout << res.e2 << '\n' << res.e1 << '\n';
}

