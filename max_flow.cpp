#include <bits/stdc++.h>
#define pb push_back
#define mp make_pair
#define all(a) begin(a),end(a)
#define FOR(x,val,to) for(int x=(val);x<int((to));++x)
#define FORE(x,val,to) for(auto x=(val);x<=(to);++x)
#define FORR(x,arr) for(auto &x: arr)
#define FORS(x,plus,arr) for(auto x = begin(arr)+(plus); x != end(arr); ++x)
#define FORREV(x,plus,arr) for(auto x = (arr).rbegin()+(plus); x !=(arr).rend(); ++x)
#define REE(s_) {cout<<s_<<'\n';exit(0);}
#define GETCIN(arr) for(auto &i: (arr)) cin>>i
#define GET(arr) for(auto &i: (arr)) sc(i)
#define GETSTR(arr) for(auto &i: (arr)) getstr(i)
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
template<typename T> inline T mod(T i, T n) { return (i % n + n) % n; }

#define MAX 1000

int res[MAX][MAX];
int p[MAX]; //prev node
int s,t; //source, sink
int f;

void augment(int cur, int mnedge){
    if(cur == s){
        f = mnedge;
        return;
    }
    if(p[cur] != -1){
        augment(p[cur], min(mnedge, res[p[cur]][cur]));
        res[p[cur]][cur] -= f;
        res[cur][p[cur]] += f;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n,m; //Number of nodes, vertices
    sc(n,m);
    int fir,sec,val;
    vector<int> adj[n]; //res list for quicker bfs
    while(m--){
        sc(fir,sec,val); //first -> second (weight)
        res[fir][sec] = res[sec][fir] = val; //undirected
        //res[fir][sec] = val; //if directed
        adj[fir].push_back(sec); // most be both irregardles, because
        adj[sec].push_back(fir); // of back edges
    }
    sc(s,t); //source,sink
    int mf = 0; //max flow
    bool vis[n]; //visited;
    LOOP:
        f = 0; //next flow candidate
        memset(p,-1,n << 2);
        memset(vis,0,sizeof vis);
        vis[s] = 1;
        queue<int> qu({s});
        while(!qu.empty()){
            int cur = qu.front(); qu.pop();
            if(cur == t)
                break;
            for(auto const &i: adj[cur]){
                if(res[cur][i] > 0 && !vis[i]){
                    vis[i] = 1; qu.push(i); p[i] = cur;
                }
            }
        }
        augment(t, 0x7f7f7f7f);
        if(f){ //after f == 0, no more possible flow, terminate
            mf += f;
            goto LOOP;
        }
    cout << "Max flow: " << mf << '\n';
}

