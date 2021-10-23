/* #pragma GCC optimize("O3,unroll-loops") */
/* #pragma GCC optimize("Ofast,unroll-loops") */
/* #pragma GCC target("avx2,popcnt") */
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
 
#ifdef ONLINE_JUDGE
#define whatis(x) ;
#endif
#ifdef _WIN32
#define getchar_unlocked() _getchar_nolock()
#define _CRT_DISABLE_PERFCRIT_LOCKS
#endif
template<class L, class R> ostream& operator<<(ostream &os, pair<L, R> P) { os<<"("<<P.first<<","<<P.second<<")"; return os; }
template<class L, class R> ostream& operator<<(ostream &os, map<L, R> P) { for(auto const &vv: P)os<<"("<<vv.first<<","<<vv.second<<")"; return os; }
template<class T> ostream& operator<<(ostream &os, set<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
template<class T> ostream& operator<<(ostream &os, vector<T> V) { os<<"[";for(auto const &vv:V)os<<vv<<","; os<<"]"; return os; }
inline int fstoi(const string &str){auto it=str.begin();bool neg=0;int num=0;if(*it=='-')neg=1;else num=*it-'0';++it;while(it<str.end()) num=num*10+(*it++-'0');if(neg)num*=-1;return num;}
inline void getch(char &x){while(x = getchar_unlocked(), x < 33){;}}
inline void getstr(string &str){str.clear(); char cur;while(cur=getchar_unlocked(),cur<33){;}while(cur>32){str+=cur;cur=getchar_unlocked();}}
template<typename T> inline bool sc(T &num){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){if(c == EOF) return false;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; return true;}template<typename T, typename ...Args> inline void sc(T &num, Args &...args){ bool neg=0; int c; num=0; while(c=getchar_unlocked(),c<33){;} if(c=='-'){ neg=1; c=getchar_unlocked(); } for(;c>47;c=getchar_unlocked()) num=num*10+c-48; if(neg) num*=-1; sc(args...); }
#define N 1000001
 
/* const long long B = 3007000499; */
unsigned long long h[2][10000000], p[10000000];
/* long long h[2][10000000], p[10000000]; */
int hs(int ind, int l, int r){
    /* return ((h[ind][r] - (l ? h[ind][l-1] * p[r-l+1] : 0)) % B + B) % B; */
    return h[ind][r] - (l ? h[ind][l-1] * p[r-l+1] : 0);
};
int n;
int binsrch (int beg1, int beg2){
    // giga binsrch.
    /* int ret = 0; */
    /* while(beg1 < n && beg2 < n && s[0][beg1] == s[1][beg2]) */
    /*     ++ret, ++beg1, ++beg2; */
    /* return ret; */
    int low = 1, high = n - max(beg1, beg2), mid, ans = 0;
    while(low <= high){
        mid = (low + high) >> 1;
        if(hs(0, beg1, beg1 + mid - 1) == hs(1, beg2, beg2 + mid - 1)){
            low = mid + 1;
            ans = mid;
        }
        else{
            high = mid - 1;
        }
    }
    return ans;
};
int main(){
    ios_base::sync_with_stdio(0);cin.tie(0);
    // LCS in O(maxmismatches^2 * logn)
    // Used for https://codeforces.com/group/LmIOjBbYv6/contest/350553/problem/E
    // Length of longest palindromic subsequence is equivalent to length of LCS
    // with reversed self. Very useful for determining longest such,
    // if n - result is bounded.
    string s[2];
    /* cin >> s[0]; */
    getstr(s[0]);
    int forhs;
    sc(forhs);
    constexpr int maxwyn = 1700;
    constexpr int off = maxwyn;
    static int dp[maxwyn][(maxwyn << 1 | 1)];
    memset(dp, -1, sizeof dp);
    const long long A = 113;
    n = s[0].size();
    s[1] = string(s[0].rbegin(), s[0].rend());
    p[0] = 1;
    for(int i = 1; i < n; ++i){
        /* p[i] = p[i - 1] * A % B; */
        p[i] = p[i - 1] * A;
    }
    FOR(x,0,2){
        h[x][0] = s[x][0];
        for(int i = 1; i < n; ++i){
            /* h[x][i] = (h[x][i - 1] * A + s[x][i]) % B; */
            h[x][i] = (h[x][i - 1] * A + s[x][i]);
        }
    }
    /* auto hs = [&](int ind, int l, int r){ */
    /*     /1* return ((h[ind][r] - (l ? h[ind][l-1] * p[r-l+1] : 0)) % B + B) % B; *1/ */
    /*     return h[ind][r] - (l ? h[ind][l-1] * p[r-l+1] : 0); */
    /* }; */
    /* auto binsrch = [&](int beg1, int beg2){ */
    /*     // giga binsrch. */
    /*     /1* int ret = 0; *1/ */
    /*     /1* while(beg1 < n && beg2 < n && s[0][beg1] == s[1][beg2]) *1/ */
    /*     /1*     ++ret, ++beg1, ++beg2; *1/ */
    /*     /1* return ret; *1/ */
    /*     int low = 1, high = n - max(beg1, beg2), mid, ans = 0; */
    /*     while(low <= high){ */
    /*         mid = (low + high) >> 1; */
    /*         if(hs(0, beg1, beg1 + mid - 1) == hs(1, beg2, beg2 + mid - 1)){ */
    /*             low = mid + 1; */
    /*             ans = mid; */
    /*         } */
    /*         else{ */
    /*             high = mid - 1; */
    /*         } */
    /*     } */
    /*     return ans; */
    /* }; */
    /* dp[0][off] = 0; */
    int res = INF; // min needed rem cnt
    dp[0][off] = binsrch(0, 0);
    // XXX assumes equaly sized strings. Triv modification to allow diff sizes though.
    for(int wyn = 0; wyn < maxwyn; ++wyn){
        for(int j = -wyn; j <= wyn; ++j){ // position diff. not larger than cr wyn obv.
            if(dp[wyn][j + off] == -1)
                continue;
            int p1 = dp[wyn][j + off];
            int p2 = dp[wyn][j + off] + j;
            if(p1 == n && p2 == n){
                res = min(res, wyn);
                continue;
            }
            if(wyn + 1 == maxwyn)
                continue;
            if(p1 == n)
                dp[wyn + 1][j + off + 1] = max(dp[wyn + 1][j + off + 1], dp[wyn][j + off]);
            else if(p2 == n) // -> j > 0
                dp[wyn + 1][j + off - 1] = max(dp[wyn + 1][j + off - 1], dp[wyn][j + off] + 1);
            else{
                assert(s[0][p1] != s[1][p2]);
                int k1 = binsrch(p1 + 1, p2);
                dp[wyn + 1][j + off - 1] = max(dp[wyn + 1][j + off - 1], dp[wyn][j + off] + k1 + 1);
                int k2 = binsrch(p1, p2 + 1);
                dp[wyn + 1][j + off + 1] = max(dp[wyn + 1][j + off + 1], dp[wyn][j + off] + k2);
            }
        }
    }
    res >>= 1; // Because mismatches counted twice, as per each string.
    cout << n - res << '\n';
}

