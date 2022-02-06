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
#define N 2000

// Przetestowane na Petrozavodsku 2022 Day4K, wbite w 3s N = 2000, q = 1e6, indendent złożoność to była liniówka.

// min, max in range
typedef pair<int, int> T;
pair<int, int> t[N << 1][N << 1];
int n, m;

pair<int, int> comb(pair<int, int> f, pair<int, int> s){
    return {min(f.first, s.first), max(f.second, s.second)};
}

T query(int r1, int r2, int c1, int c2){ // 0-ind, right EXCLUSIVE
    T res = {0x7f7f7f7f, -0x7f7f7f7f};
    for(r1 += n, r2 += n; r1 < r2; r1 >>= 1, r2 >>= 1){
        if(r1&1){
            for(int xl = c1 + m, xr = c2 + m; xl < xr; xl >>= 1, xr >>= 1){
                if(xl&1)
                    res = comb(res, t[r1][xl++]);
                if(xr&1)
                    res = comb(res, t[r1][--xr]);
            }
            ++r1;
        }
        if(r2&1){
            --r2;
            for(int xl = c1 + m, xr = c2 + m; xl < xr; xl >>= 1, xr >>= 1){
                if(xl&1)
                    res = comb(res, t[r2][xl++]);
                if(xr&1)
                    res = comb(res, t[r2][--xr]);
            }
        }
    }
    return res;
}

// untested
void modify(int r, int c, T val){
    t[r += n][c += m] = val;
    for(int x = c >> 1; x > 0; x >>= 1){
        t[r][x] = comb(t[r][x << 1], t[r][x << 1 | 1]);
    }
    r >>= 1;
    while(r > 1){
        for(int x = c; x > 0; x >>= 1){
            t[r][x] = comb(t[r << 1][x], t[r << 1 | 1][x]);
        }
        r >>= 1;
    }
}

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    T a[n][m];
    for(int i = 0; i < n; ++i){
        for(int x = 0; x < m; ++x){
            t[i + n][x + m] = a[i][x];
        }
    }
    for(int i = 2 * n - 1; i >= n; --i){
        for(int x = m - 1; x > 0; --x){
            t[i][x] = comb(t[i][x << 1], t[i][x << 1 | 1]);
        }
    }
    for(int i = n - 1; i > 0; --i){
        for(int x = 2 * m - 1; x > 0; --x){
            t[i][x] = comb(t[i << 1][x], t[i << 1 | 1][x]);
        }
    }
}

