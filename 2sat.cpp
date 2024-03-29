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

vector<int> adj[N], adjrev[N];
bool vis[N];
int comp[N];
bool assign[N];
vector<int> order;
int it;

void d1(int v){
    vis[v] = 1;
    for(auto &i: adj[v]){
        if(!vis[i])
            d1(i);
    }
    order.push_back(v);
}

void d2(int v){
    comp[v] = it;
    for(auto &i: adjrev[v]){
        if(comp[i] == -1)
            d2(i);
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    // make sure than 2 * (x) is in brackets
    int n;
    // (x or y) -> (~x -> y) and (~y -> x)
    for(int i = 0; i < n; ++i){
        for(auto &x: adj[i]){
            adjrev[x].push_back(i);
            // Zwolnienie pamięci jeśli trzeba
            /* adj[i].clear(); */
            /* adj[i].shrink_to_fit(); */
        }
    }
    for(int i = 0; i < n; ++i){
        if(!vis[i])
            d1(i);
    }
    memset(comp,-1,n << 2);
    for(int i = 0; i < n; ++i){
        int v = order[n - i - 1];
        if(comp[v] == -1){
            d2(v);
            ++it;
        }
    }
    bool kk = 1;
    for(int i = 0; i < n; i += 2){
        //i -> x
        //i+1 -> ~x
        if(comp[i] == comp[i + 1]){
            kk = 0;
            break;
        }
        // component x przed componentem ~x w topo <-> x true
        assign[i / 2] = comp[i] > comp[i + 1];
        // XXX assign == 0 -> 2 * i + 1, nie 2 * i z tym. Might wanna flip this (2nd trening drużynowy 2021).
        /* assign[i / 2] = comp[i] < comp[i + 1]; */
        // Jak mam wybór jednego z dwóch w obrębie jednego iksa, i chcę wymusić
        // wybór jednego, bo np. inny jest pusty, albo jest <= 2 czegoś, dodaj
        // i * 2 + 1, i * 2.
    }
}

