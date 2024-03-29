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

vector<int> adj[N]; //index of edge
int edge[N]; //sum of 2 nodes; 0 means taken
vector<int> euler; //list of nodes in order of eulerian traversal
vector<vector<int>> cycles; //individual simple cycles making up the euler cycle
bool vis[N];

void dfs(int v){
/* void dfs(int v, int pedge){ */
    while(!adj[v].empty()){
        // co ten if robi?
        if(edge[adj[v].back()]){
        // does that fix it?
        // albo w ogólę usuniecie?
        /* if(edge[adj[v].back()] && pedge != adj[v].back()){ */
            int oth = edge[adj[v].back()]-v;
                //if undirected also set edge[] to 0, and make a check for it
                //beforehands
            // to to wyjasnia wsm
            edge[adj[v].back()] = 0;
            adj[v].pop_back();
            dfs(oth);
            /* dfs(oth, edge[adj[v].back()]); */
            euler.push_back(oth);
        }
        else{
            adj[v].pop_back();
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,m;
    sc(n,m);
    int f,s;
    // doesn't work with multiple edges
    FOR(i,0,m){
        sc(f,s);
        --f,--s;
        adj[f].pb(i);
            // if it were undireted
        adj[s].pb(i);
            // or doesn't rly work
        edge[i] = f+s;
        /* int w; */
        /* sc(w); */
    }
    dfs(0);
    /* dfs(0,-1); */
    euler.push_back(0);
    reverse(all(euler));
    cout << euler << '\n';
    stack<int> st;
    FORR(i,euler){
        if(vis[i]){
            cycles.push_back({i});
            while(st.top() != i){
                vis[st.top()] ^= 1;
                cycles.back().push_back(st.top());
                st.pop();
            }
            cycles.back().push_back(i);
            reverse(all(cycles.back()));
        }
        else{
            vis[i] ^= 1;
            st.push(i);
        }
    }
    cout << cycles << '\n';
}

