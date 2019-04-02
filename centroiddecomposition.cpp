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

bool bloc[N]; //if blocked cause prev centroid there
vector<pi> adj[N];
int child[N];
vi adj2[N]; //centroid tree
int root = -1; //centroid root

//queries on nodes
//minimum length path to colored node

vector<pair<int,int>> upc[N]; //all centroids this+higher {node,distance to it} -> max logn elements
int mn[N]; //min from centroid

//numer of paths with weight equal 0

ll ans;
int m1[N*2],m2[N*2];
vi vm1,vm2; //which nodes contain sth
//holding it like this + sort is WAY fater than maps
int len[N]; //number of children under centroid (centroid itself counts)

void rec(int v, int p, int acc){ //do something on centroid, f.e. calc all paths == x going through the centroid
    FORR(i,adj[v]){
        if(i.e1 == p || bloc[i.e1]) continue;
        rec(i.e1,v,acc+i.e2);
        if(!~p){ //zliczyć wyniki
            sort(all(vm2)); //remove duplicates, can alternatively use counting sort
            vm2.resize(unique(all(vm2))-vm2.begin());
            ans += m2[0+N];
            /* FORR(i,m2) */
            /*     ans += m1[-i.e1]*i.e2; */
            FORR(i,vm2){
                ans += m1[-i+N]*m2[i+N];
            }
            FORR(i,vm2){
                m1[i+N] += m2[i+N];
                m2[i+N] = 0;
                vm1.push_back(i+N);
            }
            vm2.clear();
        }
    }
    if(~p){
        ++m2[acc+N];
        vm2.push_back(acc);
    }
}

void pre(int v, int p){
    child[v] = 1;
    FORR(i,adj[v]){
        if(i.e1 == p) continue;
        pre(i.e1,v);
        child[v] += child[i.e1];
    }
}

void decomp(int v, int p){ //to get adj2 -> centroid tree
    int nd2 = child[v]/2;
    int wh = -1;
    FORR(i,adj[v]){
        if(child[i.e1] > nd2){
            wh = i.e1;
            break;
        }
    }
    if(~wh){
        child[wh] = child[v];
        child[v] = 1;
        FORR(i,adj[v]){
            if(i.e1 == wh) continue;
            child[v] += child[i.e1];
        }
        decomp(wh,p);
    }
    else{
        if(!~root) root = v;
        else adj2[p].push_back(v);
        len[v] = child[v];
        child[v] = 0;
        FORR(i,adj[v]){
            if(!child[i.e1]) continue;
            decomp(i.e1,v);
        }
    }
}

void dfs2(int v, int p, int c, int d){
    upc[v].push_back({c,d});
    FORR(i,adj[v]){
        if(i.e1 == p || bloc[i.e1]) continue;
        dfs2(i.e1,v,c,d+1);
    }
}

void gocent(int v){
    FORR(i,vm1)
        m1[i] = 0;
    vm1.clear();
    //For all paths:
        //rec(v,-1,0);
    dfs2(v,-1,v,0);
    bloc[v] = 1;
    FORR(i,adj2[v]){
        gocent(i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n;
    sc(n);
    int f,s,v;
    FOR(i,1,n){
        sc(f,s);
        char in;
        getch(in);
        v = in == 'W' ? -1 : in == 'M';
        --f,--s;
        adj[f].pb({s,v});
        adj[s].pb({f,v});
    }
    pre(0,-1);
    decomp(0,-1);
    memset(mn,127,n << 2);
    gocent(root);
    /* FOR(i,0,q){ */
    /*     sc(typ,nod); */
    /*     --nod; */
    /*     if(typ == 1){ */
    /*         FORR(i,upc[nod]){ */
    /*             mn[i.e1] = min(mn[i.e1],i.e2); */
    /*         } */
    /*     } */
    /*     else{ */
    /*         int ans = INF; */
    /*         FORR(i,upc[nod]){ */
    /*             ans = min(ans,mn[i.e1]+i.e2); */
    /*         } */
    /*         cout << ans << '\n'; */
    /*     } */
    /* } */
    cout << ans << '\n';
}

