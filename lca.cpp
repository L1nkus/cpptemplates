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
#define INF 0x7F7F7F7F //2139062143 | 127 in memset -> memset(arr,127,size)
#define SINF 1061109567 //Safe INF, for graphs or 2d arrays 63 in memset(arr,63,size)
#define LL_INF 7234017283807667300 //100 in memset(arr,100,size) !!!must be LL
#define whatis(x) cerr << #x << " is " << x << endl;
#define e1 first
#define e2 second
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
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
template<typename T> inline void print_128(T num){ if(!num) return; print_128(num / 10); cout.put((num % 10) + '0'); }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;

//online lca by binary lifting

vector<int> adj[1000];
int anc[1000][11]; //log(n) values for each node (1 << i)
int d[1000];
// 240821, możesz też użyć tin, tout, for
// bool is_ancestor(int u, int v)
// {
//     return tin[u] <= tin[v] && tout[u] >= tout[v];
// }

void pre(int cur, int prev){
    anc[cur][0] = prev;
    for(int i = 1; i < 10; ++i){
        anc[cur][i] = anc[anc[cur][i-1]][i-1]; //could break if equal to 0
    }
    for(auto &i: adj[cur]){
        if(i != prev)
            d[i] = d[cur]+1, pre(i, cur);
    }
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

int lca(int f, int s){
    if(d[f] > d[s]) swap(f,s);
    s = ancestor(s,d[s]-d[f]);
    if(f == s) return f;
    // this was a very bad bug
    /* for(int i = 0; i < 10; ++i){ */
    for(int i = 9; i >= 0; --i){
        if(anc[f][i] != anc[s][i]){
            f = anc[f][i];
            s = anc[s][i];
        }
    }
    return anc[f][0];
}

int dist(int f, int s){
    return d[f] + d[s] - 2 * d[lca(f,s)];
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n; //Number of nodes, root is 0
    cin >> n;
    int cur;
    for(int i = 1; i < n; ++i){
        cin >> cur; //i(th) node's parent is cur
        adj[cur].push_back(i);
    }
    pre(0,0);
    int q; //query count
    cin >> q;
    int f,s;
    while(q--){
        cin >> f >> s;
        cout << lca(f,s) << endl;
    }
}

