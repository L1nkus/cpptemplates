#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
#define ssize(x) int(x.size())
#define pb push_back
#define mp make_pair
#define all(a) begin(a),end(a)
// #define FOR(i, l, r) for(int i = (l); i <= (r); ++i)
#define FOR(i, l, r) for(int i = (l); i < (r); ++i)
#define FORE(i, l, r) for(int i = (l); i <= (r); ++i)
#define REP(i, n) FOR(i, 0, (n) - 1)
#define FORR(x,arr) for(auto &x: arr)
#define REE(s_) {cout<<s_<<'\n';exit(0);}
#define GET(arr) for(auto &i: (arr)) sc(i)
#define e1 first
#define e2 second
#define INF 0x7f7f7f7f
#define debug(x...) cerr << "[" #x "]: ", [](auto... $) {((cerr << $ << "; "),...); }(x), cerr << '\n'
typedef std::pair<int,int> pi;
typedef std::vector<int> vi;
typedef std::vector<std::string> vs;
typedef int64_t ll;
typedef uint64_t ull;
using namespace std;
using namespace __gnu_pbds;

#ifdef ONLINE_JUDGE
#define debug(...) {}
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class A, class B> auto& operator<<(ostream &o, pair<A, B> p) { return o << '(' << p.first << ", " << p.second << ')'; }
template<class T> auto operator<<(ostream &o, T x) -> decltype(x.end(), o) { o << '{'; int i = 0; for(auto e : x) o << (", ")+2*!i++ << e; return o << '}'; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
template<typename T> using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>; //s.find_by_order(), s.order_of_key() <- works like lower_bound
template<typename T> using ordered_map = tree<T, int, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// 1 << 19 if segtree where merges matter.
#define N 1000001

int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    int n, k;
    cin >> n >> k;
    int a[n];
    GET(a);
    int inv[n][n];
    for(int l = n - 1; l >= 0; --l){
        inv[l][l] = 0;
        FOR(r, l + 1, n){
            inv[l][r] = inv[l + 1][r] + inv[l][r - 1] - (l + 1 <= r - 1 ? inv[l + 1][r - 1] : 0) + a[r] > a[l];
        }
    }
    // 1. D&Q dp.
    int dp[k + 1][n + 1]; // don't need nk mem
    dp[0][0] = 0;
    FOR(i,0,n){
        dp[0][i + 1] = inv[0][i];
    }
    FORE(crk, 1, k){
        dp[crk][0] = 0;
        auto rec = [&](auto &self, int l, int r, int optl, int optr) -> void{
            if(l > r)
                return;
            int crpos = (l + r) / 2;
            pair<int,int> best{INF, -1}; // XXX LONG_LONG_MAX if ll
            FORE(i, min(optl, crpos), min(optr, crpos)){
                int cr = dp[crk - 1][i] + inv[i][crpos]; // tutaj dp exclusive
                best = min(best, {cr, i});
            }
            dp[crk][crpos + 1] = best.first;
            self(self, l, crpos - 1, optl, best.second);
            self(self, crpos + 1, r, best.second, optr);
        };
        rec(rec, 0, n - 1, 0, n);
    }
    cout << dp[k][n - 1] << '\n';
    // 2. Aliens trick (aka parametric search). (simple af actually) (but tutaj without proof)
}

