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
#define N 5500

int n, k;
ll dp[N];
ll wsum;
int a[N][3];
vector<pair<int,int>> inat[N];
int it;
vector<pair<int, int>> intvec; // all {val, l}; sorted by val, z r <= x
vector<int> active[N]; // active {val}; indexed by l
vector<int> compvec;

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    cin >> n >> k;
    FOR(i,0,n){
        cin >> a[i][0] >> a[i][1] >> a[i][2];
        compvec.push_back(a[i][0]);
        compvec.push_back(a[i][1]);
        wsum += a[i][2];
    }
    sort(all(compvec));
    compvec.erase(unique(all(compvec)), compvec.end());
    FOR(i,0,n){
        a[i][0] = lower_bound(all(compvec), a[i][0]) - compvec.begin();
        a[i][1] = lower_bound(all(compvec), a[i][1]) - compvec.begin();
        /* inat[a[i][1]].emplace_back(a[i][1], a[i][0]); */
        inat[a[i][1]].emplace_back(-a[i][2], a[i][0]);
    }
    n = compvec.size();
    FOR(i,0,n){
        FORR(x,inat[i]){
            intvec.insert(lower_bound(all(intvec), x), x); // forgot o order inny.
        }
        it = 0;
        int curcnt = 0;
        ll curs = 0;
        FORE(x,0,i){
            while(curcnt < k && it != intvec.size()){
                pi cr = intvec[it++];
                if(cr.second < x) // eq -> wywalimo po ustawieniu cr dp.
                    continue;
                active[cr.second].push_back(-cr.first);
                curs += -cr.first;
                ++curcnt;
            }
            /* dp[i] = max(dp[i], curs + (i ? dp[i - 1] : 0)); */
            dp[i] = max(dp[i], curs + (x ? dp[x - 1] : 0));
            FORR(j,active[x]){
                --curcnt;
                curs -= j;
            }
            active[x].clear();
        }
        /* whatis(i) */
        /* whatis(dp[i]) */
        /* whatis(intvec) */
    }
    cout << wsum - dp[n - 1] << '\n';
}

