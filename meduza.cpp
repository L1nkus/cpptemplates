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
#define N 1000001

int whcykl[N], depth[N]; // whcykl jak na wyjsciu, depth weighted
int id[N]; // znormalizowane id w cyklu, tylko dla tych gdize depth[i] == 0 -> whcykl[i] == i
// id[i] == -1 -> nie jest na cyklu
int pre[N]; // pre na cyklu
vector<pi> adj[N];
int anc[N][18]; // log(n) values for each node (1 << i)
int d[N]; // unweighted

int vis[N];
vi cykl;

int d1(int v, int p){
    vis[v] = 1;
    FORR(i,adj[v]){
        if(i.e1 == p)
            continue;
        if(vis[i.e1] == 1){
            cykl = {v};
            return i.e1;
        }
        else if(vis[i.e1] == 0){
            int ret = d1(i.e1,v);
            if(~ret){
                if(ret == INF)
                    return ret;
                cykl.push_back(v);
                if(ret == v)
                    return INF;
                else
                    return ret;
            }
        }
    }
    vis[v] = 2;
    return -1;
}

int ancestor(int node, int cnt){
    int val = 0;
    while(cnt){ //could also just go through every bit
        if(cnt&1){
            node = anc[node][val];
        }
        cnt >>= 1;
        ++val;
    }
    return node;
}

void d2(int v, int p){
    if(p == -1)
        p = v;
    anc[v][0] = p;
    for(int i = 1; i < 18; ++i){
        anc[v][i] = anc[anc[v][i-1]][i-1]; //could break if equal to 0
    }
    for(auto &i: adj[v]){
        if(id[i.e1] != -1 || i.e1 == p)
            continue;
        d[i.e1] = d[v] + 1;
        depth[i.e1] = depth[v] + i.e2;
        whcykl[i.e1] = whcykl[v];
        d2(i.e1,v);
    }
}

int lca(int f, int s){
    if(d[f] > d[s]) swap(f,s);
    s = ancestor(s,d[s]-d[f]);
    if(f == s) return f;
    for(int i = 17; i >= 0; --i){
        if(anc[f][i] != anc[s][i]){
            f = anc[f][i];
            s = anc[s][i];
        }
    }
    return anc[f][0];
}

int dist(int f, int s){
    return depth[f] + depth[s] - 2 * depth[lca(f,s)];
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n;
    sc(n);
    int f,s,w;
    set<pi> st;
    FOR(i,0,n){
        sc(f,s,w);
        if(f == s)
            continue;
        if(!st.insert({min(f,s),max(f,s)}).e2){
            bool sth = 0;
            FORR(x,adj[f]){
                if(x.e1 == s){
                    sth = 1;
                    x.e2 = min(x.e2,w);
                    break;
                }
            }
            assert(sth);
            sth = 0;
            FORR(x,adj[s]){
                if(x.e1 == f){
                    sth = 1;
                    x.e2 = min(x.e2,w);
                    break;
                }
            }
            assert(sth);
        }
        else{
            adj[f].pb({s,w});
            adj[s].pb({f,w});
        }
    }
    FOR(i,0,n){
        if(vis[i])
            continue;
        int ret = d1(i,-1);
        if(~ret){
            whatis(cykl)
            break;
        }
    }
    memset(id,-1,n << 2);
    pre[0] = 0;
    FOR(i,0,cykl.size()){
        id[cykl[i]] = i;
        whcykl[cykl[i]] = cykl[i];
        if(i){
            int whw = -1;
            FORR(x,adj[cykl[i]]){
                if(x.e1 == cykl[i-1]){
                    whw = x.e2;
                    break;
                }
            }
            assert(~whw);
            pre[i] = pre[i-1] + whw;
        }
    }
    int tot = -1;
    if(cykl.size()){
        assert(cykl.size() > 2);
        tot = pre[cykl.size() - 1];
        int whw = -1;
        FORR(x,adj[cykl[cykl.size() - 1]]){
            if(x.e1 == cykl[0]){
                whw = x.e2;
                break;
            }
        }
        assert(~whw);
        tot += whw;
        FOR(i,0,cykl.size()){
            d2(cykl[i],-1);
        }
    }
    else{
        // one arbirtary root, where root has whcykl set to self initially
        whcykl[0] = 0;
        d2(0,-1);
        FOR(i,0,n)
            assert(whcykl[i] == whcykl[0]);
    }
    int t;
    sc(t);
    while(t--){
        sc(f,s);
        if(whcykl[f] == whcykl[s]){
            cout << dist(f,s) << '\n';
        }
        else{
            int res = depth[f] + depth[s];
            f = whcykl[f];
            s = whcykl[s];
            f = id[f];
            s = id[s];
            assert(~f);
            assert(~s);
            if(f > s)
                swap(f,s);
            int pres = pre[s] - pre[f];
            // nie/bez -1
            pres = min(pres, tot - pres);
            res += pres;
            cout << res << '\n';
        }
    }
}

