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
#define whatis(x) cerr << #x << " is " << x << endl;
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

#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//Heavy-Light Decomposition on nodes
//Sum of values on the path between 2 nodes (including them)
//Input:
//(size of tree) -> n
//edges (n-1)
//number of queries
//Q x y - query
//M x v - modify by value
//values initially at 0.

//KEEP IN MIND THAT EVERYTHING HERE IS IN 32-BIT INTS

//CHANGE N !!!111
#define N 10000
vector<int> adj[N];
int n;
int chain[N], num[N];
int top[N];
int nit, chit;
int chsz[N];
int t[N << 1];
int nxt[N], p[N];
int sz[N];
int depth[N];
int all[N];

inline void modify(int pos, int val){
    all[chain[pos]] += val; //or if max, have to compute it from start to end, worth it for O(NlogN) instead of O(Nlog^2N)
    pos = num[pos] + n;
    for(t[pos] = val; pos > 1; pos >>= 1)
        t[pos >> 1] = t[pos] + t[pos^1];
}

inline int segquery(int l, int r){
    int ret = 0;
    for(l += n, r += n; l < r; l >>= 1, r >>= 1){
        if(l&1) ret += t[l++];
        if(r&1) ret += t[--r];
    }
    return ret;
}

inline int query(int l, int r){
    int ret = 0;
    while(chain[l] != chain[r]){
        if(depth[top[chain[l]]] < depth[top[chain[r]]]) swap(l,r);
        int st = top[chain[l]];
        if(num[l] - num[st] + 1 == chsz[chain[l]]){
            ret += all[chain[l]];
        }
        else{
            ret += segquery(num[st], num[l]+1);
        }
        l = p[st];
    }
    if(depth[l] > depth[r]) swap(l,r);
    ret += segquery(num[l], num[r]+1);
    return ret;
}

void hld(int cur, int prev){
    chain[cur] = chit;
    num[cur] = nit++;
    if(!chsz[chit])
        top[chit] = cur;
    ++chsz[chit];
    int nxtnode = -1, best = 0;
    for(auto &i: adj[cur]){
        if(i == prev) continue;
        if(sz[i] > best)
            best = sz[i], nxtnode = i;
    }
    if(~nxtnode)
        hld(nxtnode,cur);
    for(auto &i: adj[cur]){
        if(i == prev || i == nxtnode) continue;
        ++chit;
        hld(i,cur);
    }
}

void dfs(int cur, int prev){
    sz[cur] = 1;
    for(auto &i: adj[cur]){
        if(i == prev) continue;
        depth[i] = depth[cur]+1;
        p[i] = cur;
        dfs(i,cur);
        sz[cur] += sz[i];
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int f,s,q,v;
    char type;
    sc(n);
    FOR(i,1,n){
        sc(f,s);
        adj[f].pb(s);
        adj[s].pb(f);
    }
    dfs(0,-1);
    hld(0,-1);
    sc(q);
    while(q--){
        getch(type);
        if(type == 'M'){
            sc(f,v);
            modify(f,v);
        }
        else{
            sc(f,s);
            cout << query(f,s) << endl;
        }
    }
}

