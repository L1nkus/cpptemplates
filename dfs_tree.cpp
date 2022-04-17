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

vi adj[N];

vi back[N];

bool vis[N];
int h[N], dp[N];
int bckh[N];

void d1(int v, int p){
    vis[v] = 1;
    dp[v] = 1;
    FORR(i,adj[v]){
        // jak mogą być multiedge, to to trzeba zmodyfikować
        if(i == p) continue;
        if(!vis[i]){
            h[i] = h[v] + 1;
            d1(i,v);
            // XDDDD ??????
            /* dp[i] += dp[v]; */
            dp[v] += dp[i];
            bckh[v] = min(bckh[v], bckh[i]);
            /* if(bckh[i] > h[v]){ */
            /*     whatis("bridge") */
            /* } */
        }
        else{
            // tylko tutaj cnie
            // albo z dolnego w gore lepiej
            if(h[v] > h[i]){
                back[v].pb(i);
                bckh[v] = min(bckh[v], h[i]);
            }
        }
    }
}

int res;
int resa[N];
int n,m;

int d2(int v, int p){
    // backedge closest to root
    vis[v] = 1;
    int mxup = h[v];
    FORR(i,back[v]){
        mxup = min(mxup, h[i]);
    }
    int dec = 0;
    FORR(i,adj[v]){
        if(i == p) continue;
        if(!vis[i]){
            int obt = d2(i,v);
            if(obt >= h[v]){ // there's a bridge there
                /* res += dp[i] * (n - dp[i] - 1); */
                /* resa[v] += dp[i] * (n - dp[i] - 1); */
                // A also counts?
                /* whatis(v) */
                /* whatis(i) */
                /* whatis(dp[i]) */
                /* whatis(n - dp[i] - 1) */
                // dec dp[i] from others?
                /* resa[v] += dp[i] * (n - dp[i] - 1); */
                resa[v] += dp[i] * (n - dp[i] - 1 - dec);
                dec += dp[i];
                /* resa[v] += dp[i] * (n - dp[i] - 1); */
                // -> += n - 1 everywhere po prostu
            }
            mxup = min(mxup, obt);
        }
    }
    return mxup;
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n >> m;
    int f,s;
    FOR(i,0,m){
        cin >> f >> s;
        --f,--s;
        adj[f].pb(s);
        adj[s].pb(f);
    }
    d1(0,-1);
    memset(vis,0,n);
    d2(0,-1);
    FOR(i,0,n){
        /* assert(resa[i] % 2 == 0); */
        // / 2 nie zawsze poprawne jest
        /* cout << resa[i] / 2 << '\n'; */
        /* cout << resa[i] << '\n'; */
        cout << resa[i] + n - 1 << '\n';
    }
}

